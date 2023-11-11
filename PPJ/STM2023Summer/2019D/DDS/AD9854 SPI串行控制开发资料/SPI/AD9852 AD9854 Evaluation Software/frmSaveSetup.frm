VERSION 5.00
Begin VB.Form frmSaveSetup 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Save Setup File"
   ClientHeight    =   3390
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5835
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   3390
   ScaleWidth      =   5835
   ShowInTaskbar   =   0   'False
   Begin VB.FileListBox filListSave 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1650
      Left            =   240
      Pattern         =   "*.54s"
      TabIndex        =   7
      Top             =   600
      Width           =   2640
   End
   Begin VB.TextBox txtFileToSave 
      Height          =   375
      Left            =   1200
      TabIndex        =   6
      Top             =   2400
      Width           =   4455
   End
   Begin VB.DriveListBox drvListSave 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   315
      Left            =   960
      TabIndex        =   3
      Top             =   120
      Width           =   4695
   End
   Begin VB.DirListBox dirListSave 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1665
      Left            =   3000
      TabIndex        =   2
      Top             =   600
      Width           =   2640
   End
   Begin VB.CommandButton cmdSaveSetup 
      Caption         =   "Save"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   2880
      Width           =   1935
   End
   Begin VB.CommandButton cmdCancelSave 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3720
      TabIndex        =   0
      Top             =   2880
      Width           =   1935
   End
   Begin VB.Label lblFileName 
      Caption         =   "File Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   2520
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Save in:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   855
   End
End
Attribute VB_Name = "frmSaveSetup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdCancelSave_Click()

    frmSaveSetup.Hide
    Unload frmSaveSetup
    
End Sub

Private Sub cmdSaveSetup_Click()
    
    Dim SaveInfo, SaveVal, FileName As String
    If Right(dirListSave.Path, 1) = "\" Then
        FileName = dirListSave.Path & txtFileToSave.Text
    Else
        FileName = dirListSave.Path & "\" & txtFileToSave.Text
    End If
    
    If Right(FileName, 4) = ".54s" Then
        FileName = FileName
    Else
        FileName = FileName & ".54s"
    End If
    
    
    Open FileName For Output As #11
    
    SaveInfo = "AD9854"
    
    Write #11, SaveInfo
    
    'Save all values
    
    'Form: Amplitude
    SaveInfo = "Output Amplitude"
    If frmAmplitude.optOutAmpProg = True Then
        SaveVal = True
    Else
        SaveVal = False
    End If
    Write #11, SaveInfo, SaveVal

    SaveInfo = "Amplitude Scaling"
    If frmAmplitude.optUseFixed = True Then
        SaveVal = True
    Else
        SaveVal = False
    End If
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "I Channel One"
    SaveVal = frmAmplitude.txtIChan1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "I Channel Two"
    SaveVal = frmAmplitude.txtIChan2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "I Channel Three"
    SaveVal = frmAmplitude.txtIChan3
    Write #11, SaveInfo, SaveVal
       
    SaveInfo = "I Channel Hex"
    SaveVal = frmAmplitude.txtIChanHex
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q Channel One"
    SaveVal = frmAmplitude.txtQChan1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q Channel Two"
    SaveVal = frmAmplitude.txtQChan2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q Channel Three"
    SaveVal = frmAmplitude.txtQChan3
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q Channel Hex"
    SaveVal = frmAmplitude.txtQChanHex
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Ramp Rate Register One"
    SaveVal = frmAmplitude.txtORR1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Ramp Rate Register Two"
    SaveVal = frmAmplitude.txtORR2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Ramp Rate Register Hex"
    SaveVal = frmAmplitude.txtORRHex
    Write #11, SaveInfo, SaveVal
        
    'Form: Clock
    
    SaveInfo = "Bypass PLL"
    If frmClock.chkBypassPLL = 1 Then
        SaveVal = 1
    Else: SaveVal = 0
    End If
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "VCO Range"
    If frmClock.optPLL_Lo = True Then
        SaveVal = True
    Else: SaveVal = False
    End If
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Reference Clock"
    SaveVal = frmClock.txtClock
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Clock Multiplier"
    SaveVal = frmClock.txtPLL
    Write #11, SaveInfo, SaveVal
       
    SaveInfo = "Update Clock Register One"
    SaveVal = frmClock.txtUDCLK1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Update Clock Register Two"
    SaveVal = frmClock.txtUDCLK2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Update Clock Register Three"
    SaveVal = frmClock.txtUDCLK3
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Update Clock Register Four"
    SaveVal = frmClock.txtUDCLK4
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Update Clock Hex"
    SaveVal = frmClock.txtUDCLKHex
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Update Clock Frequency"
    SaveVal = frmClock.txtUDCLKMHz
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Update Clock Location"
    If frmClock.optInternal = True Then
        SaveVal = True
    Else: SaveVal = False
    End If
    Write #11, SaveInfo, SaveVal
    
    'Form: Control
    SaveInfo = "Communications Mode"
    If frmControl.optParallel = True Then
        SaveVal = "Parallel"
    Else
        If frmControl.opt2WireSerial = True Then
            SaveVal = "TwoWire"
        Else
            If frmControl.opt3WireSerial = True Then
                    SaveVal = "ThreeWire"
            End If
        End If
    End If
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Communications Mode Is LSB 1st Mode"
    SaveVal = frmControl.chkLSB1st
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Comparator Power Down"
    SaveVal = frmControl.chkCompPwrDwn
    Write #11, SaveInfo, SaveVal

    SaveInfo = "PLL Power Down"
    SaveVal = frmControl.chkPllPwrDwn
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q-DAC Power Down"
    SaveVal = frmControl.chkQDacPwrDwn
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "All DAC Power Down"
    SaveVal = frmControl.chkAllDacPwrDwn
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Full Digital Power Down"
    SaveVal = frmControl.chkFulDigPwrDwn
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Bypass Inverse Sync"
    SaveVal = frmControl.chkBypInvSinc
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Source Q-DAC"
    SaveVal = frmControl.chkSrcQDac
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q-DAC Register One"
    SaveVal = frmControl.txtQDac1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q-DAC Register Two"
    SaveVal = frmControl.txtQDac2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q-DAC Register Three"
    SaveVal = frmControl.txtQDac3
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Q-DAC Register Hex"
    SaveVal = frmControl.txtQDacHex
    Write #11, SaveInfo, SaveVal
    
    'Form: Frequency
    
    SaveInfo = "Mode"
    If frmFrequency.optSingleTone = True Then
        SaveVal = "Single Tone"
    Else:
        If frmFrequency.optUnrampedFSK = True Then
            SaveVal = "Unramped FSK"
        Else:
            If frmFrequency.optRampedFSK = True Then
                SaveVal = "Ramped FSK"
            Else:
                If frmFrequency.optChirpMode = True Then
                    SaveVal = "Chirp"
                Else:
                    If frmFrequency.optBPSKmode = True Then
                        SaveVal = "BPSK"
                    End If
                End If
            End If
        End If
    End If
    Write #11, SaveInfo, SaveVal
       
    SaveInfo = "Frequency Tuning Word One, Register One"
    SaveVal = frmFrequency.txtFTW1_1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Tuning Word One, Register Two"
    SaveVal = frmFrequency.txtFTW1_2
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Tuning Word One, Register Three"
    SaveVal = frmFrequency.txtFTW1_3
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Tuning Word One, Register Four"
    SaveVal = frmFrequency.txtFTW1_4
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Tuning Word One, Register Five"
    SaveVal = frmFrequency.txtFTW1_5
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Tuning Word One, Register Six"
    SaveVal = frmFrequency.txtFTW1_6
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Tuning Word One, MHZ"
    SaveVal = frmFrequency.txtFTW1MHz
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Tuning Word Two, Register One"
    SaveVal = frmFrequency.txtFTW2_1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Tuning Word Two, Register Two"
    SaveVal = frmFrequency.txtFTW2_2
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Tuning Word Two, Register Three"
    SaveVal = frmFrequency.txtFTW2_3
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Tuning Word Two, Register Four"
    SaveVal = frmFrequency.txtFTW2_4
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Tuning Word Two, Register Five"
    SaveVal = frmFrequency.txtFTW2_5
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Tuning Word Two, Register Six"
    SaveVal = frmFrequency.txtFTW2_6
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Tuning Word Two, MHZ"
    SaveVal = frmFrequency.txtFTW2MHz
    Write #11, SaveInfo, SaveVal
        
    
    SaveInfo = "Frequency Step Word, Register One"
    SaveVal = frmFrequency.txtFSW1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Step Word, Register Two"
    SaveVal = frmFrequency.txtFSW2
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Step Word, Register Three"
    SaveVal = frmFrequency.txtFSW3
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Step Word, Register Four"
    SaveVal = frmFrequency.txtFSW4
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Step Word, Register Five"
    SaveVal = frmFrequency.txtFSW5
    Write #11, SaveInfo, SaveVal
    

    SaveInfo = "Frequency Step Word, Register Six"
    SaveVal = frmFrequency.txtFSW6
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Step Word, MHZ"
    SaveVal = frmFrequency.txtFSWMHz
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Step Rate, Register One"
    SaveVal = frmFrequency.txtFSR1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Step Rate, Register Two"
    SaveVal = frmFrequency.txtFSR2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Step Rate, Register Three"
    SaveVal = frmFrequency.txtFSR3
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Step Rate, Register Four"
    SaveVal = frmFrequency.txtFSR4
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Step Rate, Register Five"
    SaveVal = frmFrequency.txtFSR5
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Frequency Step Rate, Hex"
    SaveVal = frmFrequency.txtFSRHex
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #1, Register One"
    SaveVal = frmFrequency.txtPhAdj1_1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #1, Register Two"
    SaveVal = frmFrequency.txtPhAdj1_2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #1, Register Three"
    SaveVal = frmFrequency.txtPhAdj1_3
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #1, Register Four"
    SaveVal = frmFrequency.txtPhAdj1_4
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #1, Register Hex"
    SaveVal = frmFrequency.txtPhAdj1Hex
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #2, Register One"
    SaveVal = frmFrequency.txtPhAdj2_1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #2, Register Two"
    SaveVal = frmFrequency.txtPhAdj2_2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #2, Register Three"
    SaveVal = frmFrequency.txtPhAdj2_3
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #2, Register Four"
    SaveVal = frmFrequency.txtPhAdj2_4
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Phase Adjust #2, Register Hex"
    SaveVal = frmFrequency.txtPhAdj2Hex
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Special Mode, Triangle Bit"
    SaveVal = frmFrequency.chkTriangle
    Write #11, SaveInfo, SaveVal
        
    SaveInfo = "Special Mode, Clr ACC1 Bit"
    SaveVal = frmFrequency.chkACC1
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Special Mode, Clr ACC2 Bit"
    SaveVal = frmFrequency.chkACC2
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "FSK/BPSK/Hold Pin"
    If frmFrequency.optFDataHi = True Then
        SaveVal = True
    Else: SaveVal = False
    End If
    Write #11, SaveInfo, SaveVal
    
    SaveInfo = "Output Ramp Pin"
    If frmFrequency.optORampHi = True Then
        SaveVal = True
    Else: SaveVal = False
    End If
    Write #11, SaveInfo, SaveVal
    
    Close 11
    frmSaveSetup.Hide
    Unload frmSaveSetup
    
End Sub

Private Sub cmdSaveSetup_KeyPress(KeyAscii As Integer)
    
    If KeyAscii = 13 Then
        Call cmdSaveSetup_Click
    End If
    
End Sub

Private Sub dirListSave_Change()
    
    filListSave.Path = dirListSave.Path
    txtFileToSave.Text = filListSave.FileName
    
End Sub

Private Sub drvListSave_Change()

    dirListSave.Path = drvListSave.Drive
    
End Sub

Private Sub filListSave_Click()

    txtFileToSave.Text = filListSave.FileName
    
End Sub

Private Sub filListSave_DblClick()
    
    Call cmdSaveSetup_Click
    
End Sub

Private Sub Form_Load()
    'Center in the screen
    Top = ((MDI_Main.Height - Height) / 2) - 1000
    Left = (MDI_Main.Width - Width) / 2
'    Top = 1500
'    Left = 2500
'    Width = 5955
'    Height = 3705
    
End Sub

Private Sub txtFileToSave_KeyPress(KeyAscii As Integer)
    
    If KeyAscii = 13 Then
    
        Call cmdSaveSetup_Click
        
    End If
    
End Sub
