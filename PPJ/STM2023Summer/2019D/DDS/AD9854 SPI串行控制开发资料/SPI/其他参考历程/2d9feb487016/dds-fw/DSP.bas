Attribute VB_Name = "modDSP"
Option Explicit

'Written by Gerald Youngblood, AC5OG
'Copywrite 2000, 2001, 2002
'This code may be used freely for experimentation by Amateur Radio exerimenters
'but is not licensed for commercial use in any manner.

'===============================================================================
'CAPTURESIZE and NFFT must be the same power of two
'BLKSIZE and FILTERTAPS must each be 1/2 of NFFT for overlap/add
'
'The capture event rate is 2048/44100 = 0.04644 seconds per block or ~21.5
'blocks per second.
'The FFT bin size is Fs/N = 44100/4096 = 10.7666 Hz/bin
'===============================================================================
Public Const Fs As Long = 44100         'Sampling frequency in samples per second
Public Const NFFT As Long = 4096        'Number of FFT bins
Public Const BLKSIZE As Long = 2048     'Number of samples in capture/play block
Public Const CAPTURESIZE As Long = 4096 'Number of samples in Capture Buffer
Public Const FILTERTAPS As Long = 2048  'Number of taps in bandpass filter
Private BinSize As Single               'Size of FFT Bins in Hz

Private order As Long                   'Calculate Order power of 2 from NFFT
Private filterM(NFFT) As Double         'Polar Magnitude of filter freq resp
Private filterP(NFFT) As Double         'Polar Phase of filter freq resp
Private RealIn(NFFT) As Double          'FFT buffers
Private RealOut(NFFT) As Double
Private ImagIn(NFFT) As Double
Private ImagOut(NFFT) As Double

Private IOverlap(NFFT - FILTERTAPS - 1) As Double 'Overlap prev FFT/IFFT
Private QOverlap(NFFT - FILTERTAPS - 1) As Double 'Overlap prev FFT/IFFT

Private RealOut_1(NFFT) As Double       'Fast Convolution Filter buffers
Private RealOut_2(NFFT) As Double
Private ImagOut_1(NFFT) As Double
Private ImagOut_2(NFFT) As Double

Public FHigh As Long                    'High frequency cutoff in Hz
Public FLow As Long                     'Low frequency cutoff in Hz
Public Fl As Double                     'Low frequency cutoff as fraction of Fs
Public Fh As Double                     'High frequency cutoff as fraction of Fs
Public SSB As Boolean                   'True for Single Sideband Modes
Public USB As Boolean                   'Sideband select variable
Public TX As Boolean                    'Transmit mode selected
Public IFShift As Boolean               'True for 11.025KHz IF

Public AGC As Boolean                   'AGC enabled
Public AGCHang As Long                  'AGC AGCHang time factor
Public AGCMode As Long                  'Saves the AGC Mode selection
Public RXHang As Long                   'Save RX Hang time setting
Public AGCLoop As Long                  'AGC AGCHang time buffer counter
Private Vpk As Double                   'Peak filtered output signal
Private G(24) As Double                 'Gain AGCHang time buffer
Private Gain As Double                  'Gain state setting for AGC
Private PrevGain As Double              'AGC Gain during previous input block
Private GainStep As Double              'AGC attack time steps
Private GainDB As Double                'AGC Gain in dB
Private TempOut(BLKSIZE) As Double      'Temp buffer to compute Gain
Public MaxGain As Long                  'Maximum AGC Gain factor
    
Private FFTBins As Long                 'Number of FFT Bins for Display
Private M(NFFT) As Double               'Double precision polar magnitude
Private P(NFFT) As Double               'Double precision phase angle
Private S As Long                       'Loop counter for samples
      
Public Static Sub DSP(inBuffer() As Integer, outBuffer() As Integer)

'The DSP subroutine performs modulation and demodulation of single sideband signals.
'The IF is offset from baseband by 11.025KHz.  Filtering is accomplished using FFT
'Convolution and overlap/add.  Variable hang time digital AGC is also provided.
'
'Parameters:
'inBuffer() - buffer containing the quadrature sampled signal from the ADC
'outBuffer() - buffer returned by the DSP subroutine for output to the DAC

'================================ COPY BUFFERS ======================================

    Erase RealIn, ImagIn

    For S = 0 To CAPTURESIZE - 1 Step 2         'Copy I to RealIn and Q to ImagIn
        RealIn(S \ 2) = inBuffer(S + 1)         'Zero stuffing second half of
        ImagIn(S \ 2) = inBuffer(S)             'RealIn and ImagIn
    Next S

'============================== FFT CONVERSION ======================================
    
    nspzrFftNip RealIn, ImagIn, RealOut, ImagOut, order, NSP_Forw
    
    nspdbrCartToPolar RealOut, ImagOut, M, P, NFFT    'Cartesian to polar
  
'==================================== IF SHIFT ======================================

IFShift = True                              'Force to True for the demo

    If IFShift = True Then                  'Shift sidebands from 11.025KHz IF
        For S = 0 To 1023
            If USB Then
                M(S) = M(S + 1024)          'Move upper sideband to 0Hz
                P(S) = P(S + 1024)
            Else
                M(S + 3072) = M(S + 1)      'Move lower sideband to 0Hz
                P(S + 3072) = P(S + 1)
            End If
        Next
    End If

'=========================== SIDEBAND SELECTION ======================================

    If SSB = True Then                      'SSB or CW Modes
        If USB = True Then
            For S = FFTBins To NFFT - 1      'Zero out lower sideband
                M(S) = 0
            Next
        Else
            For S = 0 To FFTBins - 1         'Zero out upper sideband
                M(S) = 0
            Next
        End If
    End If

'========================= FAST CONVOLUTION FILTER ===================================

    nspdbMpy2 filterM, M, NFFT              'Magnitude
    nspdbAdd2 filterP, P, NFFT              'Phase
    
'======================= INVERSE FFT AND OVERLAP ADD ==================================

    'Convert polar to cartesian
    nspdbrPolarToCart M, P, RealIn, ImagIn, NFFT

    'Inverse FFT to convert back to time domain
    nspzrFftNip RealIn, ImagIn, RealOut, ImagOut, order, NSP_Inv
    
    'Overlap and Add from last FFT/IFFT:  RealOut(s) = RealOut(s) + Overlap(s)
    nspdbAdd3 RealOut, IOverlap, RealOut, FILTERTAPS - 2
    nspdbAdd3 ImagOut, QOverlap, ImagOut, FILTERTAPS - 2

    'Save Overlap for next pass
    For S = BLKSIZE To NFFT - 1
        IOverlap(S - BLKSIZE) = RealOut(S)
        QOverlap(S - BLKSIZE) = ImagOut(S)
    Next
    
'=========================== DIGITAL AGC ============================================
                
    If AGC = True Then
    
        'If true increment AGCLoop counter, otherwise reset to zero
        AGCLoop = IIf(AGCLoop < AGCHang - 1, AGCLoop + 1, 0)
                
        nspdbrCartToPolar RealOut, ImagOut, M, P, BLKSIZE    'Envelope Polar Magnitude
        
        Vpk = nspdMax(M, BLKSIZE)                   'Get peak magnitude
       
        If Vpk <> 0 Then                            'Check for divide by zero
            G(AGCLoop) = 16384 / Vpk                'AGC gain factor with 6 dB headroom
            Gain = nspdMin(G, AGCHang)              'Find peak gain reduction (Min)
        End If

        If Gain > MaxGain Then Gain = MaxGain       'Limit Gain to MaxGain
        
        If Gain < PrevGain Then                     'AGC Gain is decreasing
            GainStep = (PrevGain - Gain) / 44       '44 Sample ramp = 1 ms attack time
            For S = 0 To 43                         'Ramp Gain down over 1 ms period
                M(S) = M(S) * (PrevGain - ((S + 1) * GainStep))
            Next
            For S = 44 To BLKSIZE - 1               'Multiply remaining Envelope by Gain
                M(S) = M(S) * Gain
            Next
        Else
            If Gain > PrevGain Then                 'AGC Gain is increasing
                GainStep = (Gain - PrevGain) / 44   '44 Sample ramp = 1 ms decay time
                For S = 0 To 43                     'Ramp Gain up over 1 ms period
                    M(S) = M(S) * (PrevGain + ((S + 1) * GainStep))
                Next
                For S = 44 To BLKSIZE - 1           'Multiply remaining Envelope by Gain
                    M(S) = M(S) * Gain
                Next
            Else
                nspdbMpy1 Gain, M, BLKSIZE          'Multiply Envelope by AGC gain
            End If
        End If

        PrevGain = Gain                             'Save Gain for next loop
        
        nspdbThresh1 M, BLKSIZE, 32760, NSP_GT      'Limit absolute output to prevent overflow
        
    End If
        
'=========================== SEND TO OUTPUT BUFFER ======================================

    nspdbrPolarToCart M, P, RealOut, ImagOut, BLKSIZE   'Convert Polar to Cartesian
    
    Dim c As Long
        
    For S = 0 To BLKSIZE - 1                            'Stereo Copy RealOut to outBuffer
        
        outBuffer(S * 2) = CInt(RealOut(S))             'Right Channel Real TX or RX
      
        If TX = True Then
            outBuffer((S * 2) + 1) = CInt(ImagOut(S))   'Left Channel Imag transmit
        Else
            outBuffer((S * 2) + 1) = CInt(RealOut(S))   'Left Channel Real receive
        End If
    Next
  
End Sub

'======================= COMPUTE FILTER COEFFICIENTS ====================================

Public Static Sub CalcFilter(FLow As Long, FHigh As Long)
    
    Static Rh(NFFT) As Double               'Impulse response for bandpass filter
    Static Ih(NFFT) As Double               'Imaginary set to zero
    Static reH(NFFT) As Double             'real part of filter response
    Static imH(NFFT) As Double             'imag part of filter response
    
    Erase Ih
    
    Fh = FHigh / Fs                         'Compute high and low cutoff
    Fl = FLow / Fs                          'as a fraction of Fs
    BinSize = Fs / NFFT                     'Compute FFT Bin size in Hz

    FFTBins = (FHigh / BinSize) + 50         'Number of FFT Bins in filter width
    
    order = NFFT                            'Compute order as NFFT power of 2
    Dim O As Long
    
    For O = 1 To 16                         'Calculate the filter order
        order = order \ 2
        If order = 1 Then
            order = O
            Exit For
        End If
    Next
        
    'Calculate infinite impulse response bandpass filter coefficients
    'with window
    nspdFirBandpass Fl, Fh, Rh, FILTERTAPS, NSP_WinBlackmanOpt, 1
    
    'Compute the complex frequency domain of the bandpass filter
    nspzrFftNip Rh, Ih, reH, imH, order, NSP_Forw
    nspdbrCartToPolar reH, imH, filterM, filterP, NFFT
    
End Sub

