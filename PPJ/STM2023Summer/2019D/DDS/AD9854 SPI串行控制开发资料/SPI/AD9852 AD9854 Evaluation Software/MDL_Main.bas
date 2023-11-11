Attribute VB_Name = "MDL_Main"
'***************************************************************
'AD9854 Customer Evaluation Software                           *
'Written by Jack Collins, Analog Devices, 1999                 *
'***************************************************************
'
'Revision History
'----------------
'6/01/99   Rev 1.0 - Initial version.
'6/14/99   Rev 1.1 - Fixed UDCLK freq box.
'6/21/99   Rev 1.2 - Fixed FSR hex box.
'6/28/99   Rev 1.3 - Eliminated tags and implemented LSB1st.
'7/12/99   Rev 1.4 - Cleaned up serial write/read sequence.
'7/13/99   Rev 1.5 - Added error checking in FTW calculations
'                  - Added Save/Load setup file routines
'                  - Added Save Registers routing
'7/30/99   Rev 1.6 - Fixed Ramp Rate Register default.
'
'Changes below made by Shane Lambeth
'8/04/99   Rev 1.7a- Added DriverX control & LPT Port detection and menu.
'8/30/99   Rev 1.7b- Added PC to Board connection detection, -DEBUG
'                    command line switch, -OPTO command line switch
'                    for compatability with either the optoisolator
'                    board or the customer eval board.
'09/10/99  Rev 1.7b- Added opto isolator board detection in the
'                    CheckConnection() subroutine
'09/14/99  Rev 1.7 - Added "Check Parallel Port Connection" to the
'                    parallel port menu.
'01/09/00  Rev 1.71- (frmAmplitude)
'                    Changed caption on optUseRamp to
'                    "Enable Shaped Keying Function" match up with datasheet
'                    terminology
'                    Changed the caption on the label lblORR  to
'                    "Ramp Rate Counter Register" to match up with datasheet
'                    terminology
'                    (frmClock)
'                    Changed the caption for the chkBypassPll control to
'                    "Bypass the Ref Clock Multiplier", to matchup with naming
'                    conventions used in the datasheet.
'                    Changed the caption for the cmdLoadPLL control to matchup
'                    with the naming conventions of the datasheet.
'                    (frmFrequency)
'                    Fixed a bug that didn't allow the user access to the
'                    proper controls in different modulation modes.
'06/21/00  Rev 1.71.1- Hid the PLL powerdown checkbox because if this is used the
'                    DUT can not be powered up again.
'02/05/01  Rev 1.71.2- Added the ability to enter negative numbers in the
'                    frequency step word box.
'05/11/01  Rev 1.71.3- Fixed a bug in the tunning word calculation
'11/08/02  Rev 1.72- Added XP compatability by upgrading the LPT selection Dialog
'***************************************************************

Option Explicit                         'Declare all variables.
Option Base 1                           'Lower array index = 1.

Public LPTPort As Integer               'LPT port address.
Public LSB1st As Integer                'LSB1st flag variable.
Public OldPll As String                 'Previous PLL value.
Public PMode As Integer                 'Parallel mode pin.
Public FData As Integer                 'FSKDATA pin state.
Public ORamp As Integer                 'OUTRAMP pin state.
Public RBE As Long                      'ReadBack enable.

'Added 08/27/99 - flag for optoisolator board
Public OptoBoardFlag As Boolean
Public DeelayValue As Integer 'Value that sets the delay in Deelay()
'Added 08/27/99 - flag for debug purposes
Public DebugFlag As Boolean
'Added 09/20/99 - Flag added to enable readback compatability
'with the engineering board that data readback isn't inverted
Public NormRdBack As Boolean

'Define a locale type
Public Type LocInfo
    sCountry As String
    iDecSep As Integer
    sDecSep As String
    sNegSign As String
End Type

'Define a global locale variable for use in the program
Public MyLocInfo As LocInfo

Public Enum AD985452IOMode
    Two_Wire_Serial_Mode = 0
    Three_Wire_Serial_Mode = 1
    Parallel_Mode = 2
End Enum


'***************************************************************
'The following routines write or read data to or from a port   *
'address.  Visual Basic has no provision for this function so  *
'3rd party routines are used.                                  *
'***************************************************************

'Declare Function Inp Lib "VCPIO.DLL" Alias "inp1" (ByVal Port As Integer) As Integer
'Declare Sub Out Lib "VCPIO.DLL" Alias "out1" (ByVal Port As Integer, ByVal LDat As Long)

Public Sub GetSerMdeStr(S As String)

Dim i As Integer

      'Write control register.
      S = "000"
      
      'Set power down bits.
      If frmControl.chkCompPwrDwn.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      If frmControl.chkPllPwrDwn.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      If frmControl.chkQDacPwrDwn.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      If frmControl.chkAllDacPwrDwn.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      If frmControl.chkFulDigPwrDwn.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      'Set PLL bits.
      S = S & "0"
      
      If frmClock.optPLL_Hi.Value = True Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      If frmClock.chkBypassPLL.Value = 1 Then
      
         S = S & "1"
         i = Val(OldPll)
         
      Else
      
         S = S & "0"
         i = Val(frmClock.txtPLL.Text)
         
      End If
      
      Select Case i
      
         Case 4
            S = S & "00100"
         Case 5
            S = S & "00101"
         Case 6
            S = S & "00110"
         Case 7
            S = S & "00111"
         Case 8
            S = S & "01000"
         Case 9
            S = S & "01001"
         Case 10
            S = S & "01010"
         Case 11
            S = S & "01011"
         Case 12
            S = S & "01100"
         Case 13
            S = S & "01101"
         Case 14
            S = S & "01110"
         Case 15
            S = S & "01111"
         Case 16
            S = S & "10000"
         Case 17
            S = S & "10001"
         Case 18
            S = S & "10010"
         Case 19
            S = S & "10011"
         Case 20
            S = S & "10100"
         
         End Select
         
      'Set mode bits.
      If frmFrequency.chkACC1.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
    
      If frmFrequency.chkACC2.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
    
      If frmFrequency.chkTriangle.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
    
      If frmControl.chkSrcQDac.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      If frmFrequency.optSingleTone.Value = True Then
        S = S & "000"
      ElseIf frmFrequency.optUnrampedFSK.Value = True Then
        S = S & "001"
      ElseIf frmFrequency.optRampedFSK.Value = True Then
        S = S & "010"
      ElseIf frmFrequency.optChirpMode.Value = True Then
        S = S & "011"
      ElseIf frmFrequency.optBPSKmode.Value = True Then
        S = S & "100"
      End If
      
      If frmClock.optInternal.Value = True Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      'Set other bits.
      S = S & "0"
      
      If frmControl.chkBypInvSinc.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      If frmAmplitude.optOutAmpProg.Value = True Then
         S = S & "1"
      Else
         S = S & "0"
      End If

      If frmAmplitude.optUseRamp.Value = True Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      S = S & "00"
      
      If frmControl.chkLSB1st.Value = 1 Then
         S = S & "1"
      Else
         S = S & "0"
      End If
      
      If frmControl.opt3WireSerial.Value = True Then
         S = S & "1"
      Else
         S = S & "0"
      End If

End Sub

Public Sub GetSysClk(SysClk As Single)

'This procedure calculates the system clock frequency
'and returns the value in units of megahertz.

Dim ClkFrq As Single
Dim PllVal As Integer

ClkFrq = CSng(frmClock.txtClock.Text)

If frmClock.chkBypassPLL.Value = 0 Then

   PllVal = CSng(frmClock.txtPLL.Text)
   
Else

   PllVal = 1
   
End If

SysClk = ClkFrq * PllVal

End Sub

Public Sub GetWrdStr(IntVal As Integer, TmpStr As String)

'This procedure calculates and returns an 8-digit
'binary string based up the incoming numeric value.

Dim i As Integer

TmpStr = ""

For i = 7 To 0 Step -1

   If IntVal >= 2 ^ i Then
   
      TmpStr = TmpStr & "1"
      IntVal = IntVal - 2 ^ i
      
   Else
   
      TmpStr = TmpStr & "0"
      
   End If
   
Next i

End Sub

Public Sub IntFrmBinStr(K As Integer, S As String, L As Integer)

'This procedure calculates an integer value (K)
'from a variable length (L) binary string (S).

Dim i As Integer

K = 0

For i = 1 To L

   If Mid(S, i, 1) = "1" Then K = K + 2 ^ (i * -1 + L)

Next i

End Sub

Public Sub SwitchToSerial()

Dim LCtl As Long

   'Initialize address bus low.
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
   Deelay DeelayValue
   LatchAddr

   'Initialize CS,SCLK,PMODE high.
   'Initialize RESET,UDCLK low.
   'Initialize FDATA,ORAMP accordingly.
   LCtl = CLng(19 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

   'Initialize CS,SCLK high.
   'Initialize RESET,UDCLK,PMODE low.
   'Initialize FDATA,ORAMP accordingly.
   LCtl = CLng(3 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl
   
   PMode = 0

End Sub

Public Sub SwitchToParallel()

Dim LCtl As Long

   'Initialize WRBAR,RDBAR high.
   'Initialize RESET,UDCLK,PMODE low.
   'Initialize FDATA,ORAMP accordingly.
   LCtl = CLng(3 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

   'Initialize WRBAR,RDBAR,PMODE high.
   'Initialize RESET,UDCLK low.
   'Initialize FDATA,ORAMP accordingly.
   LCtl = CLng(19 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl
   
   PMode = 16

End Sub

Public Sub InitPort()

Dim LCtl As Long

'Initialize latch lines and RBE all low.
Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 11& + RBE)
Deelay DeelayValue

'Initialize data lines all low.
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
Deelay DeelayValue
LatchData

'Initialize addr lines all low.
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
Deelay DeelayValue
LatchAddr

'If parallel mode.
If PMode = 16 Then

   'Initialize WRBAR,RDBAR,PMODE high.
   'Initialize RESET,UDCLK low.
   'Initialize FDATA,ORAMP accordingly.
   LCtl = CLng(19 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl
   
Else

   'Initialize RESET,UDCLK,PMODE low.
   'Initialize CS,SCLK high.
   'Initialize FDATA,ORAMP accordingly.
   LCtl = CLng(3 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl
   
End If

End Sub

Public Sub PWrite(IDat As Integer, IAdr As Integer)

Dim LDat As Long, LAdr As Long, LCtl As Long

'Convert parameters to long.
LDat = CLng(IDat)
LAdr = CLng(IAdr)

'Set up data bits.
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LDat)
Deelay DeelayValue
LatchData

'Set up addr bits.
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LAdr)
Deelay DeelayValue
LatchAddr

'WRBAR,RESET,UDCLK = lo
'RDBAR,PMODE = hi
LCtl = CLng(18 + FData + ORamp)
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
Deelay DeelayValue
LatchCtrl

'RESET,UDCLK = lo
'WRBAR,RDBAR,PMODE = hi
LCtl = CLng(19 + FData + ORamp)
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
Deelay DeelayValue
LatchCtrl
  
End Sub

Public Sub SWrite(Deta As String, Addr As String)

Dim i As Integer
Dim LWrd As Long
Dim TmpStr As String, PrvStr As String

'Take CS low.
LWrd = CLng(1 + FData + ORamp)
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
Deelay DeelayValue
LatchCtrl

'Take SCLK low.
LWrd = CLng(FData + ORamp)
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
Deelay DeelayValue
LatchCtrl

'Prepend to address nibble.
Addr = "0000" & Addr

'Reverse if necessary.
If LSB1st = 1 Then RevStr Addr

'Initialize previous value.
PrvStr = "0"

'For eight bits.
For i = 1 To 8
   
   'What is current data bit.
   TmpStr = Mid(Addr, i, 1)
      
   'Change data bit only if necessary.
   If (TmpStr = "1") And (PrvStr = "0") Then
         
      Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 254&)
      Deelay DeelayValue
      LatchAddr
         
      PrvStr = "1"
      
   ElseIf (TmpStr = "0") And (PrvStr = "1") Then
      
      Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
      Deelay DeelayValue
      LatchAddr
         
      PrvStr = "0"
      
   End If
      
   'Take SCLK high.
   LWrd = CLng(1 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
   Deelay DeelayValue
   LatchCtrl
      
   'Take SCLK low.
   LWrd = CLng(FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
   Deelay DeelayValue
   LatchCtrl

Next i

'Reverse if necessary.
If LSB1st = 1 Then RevStr Deta

'For length of data string.
For i = 1 To Len(Deta)
   
   'Get current bit.
   TmpStr = Mid(Deta, i, 1)
      
   'Change data bit only if necessary.
   If (TmpStr = "1") And (PrvStr = "0") Then
         
      Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 254&)
      Deelay DeelayValue
      LatchAddr
         
      PrvStr = "1"
      
   ElseIf (TmpStr = "0") And (PrvStr = "1") Then
      
      Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
      Deelay DeelayValue
      LatchAddr
         
      PrvStr = "0"
      
   End If
      
   'Take SCLK high.
   LWrd = CLng(1 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
   Deelay DeelayValue
   LatchCtrl
   
   If i < Len(Deta) Then
      
      'Take SCLK low.
      LWrd = CLng(FData + ORamp)
      Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
      Deelay DeelayValue
      LatchCtrl
      
   End If

Next i
      
'Clear data.
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
Deelay DeelayValue
LatchAddr

'Take CS high.
LWrd = CLng(3 + FData + ORamp)
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
Deelay DeelayValue
LatchCtrl

End Sub

Public Sub SRead(Deta As String, Addr As String)

Dim LWrd As Long
Dim i As Integer, Bits As Integer, Res As Integer
Dim TmpStr As String, PrvStr As String

'Take CS low.
LWrd = CLng(1 + FData + ORamp)
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
Deelay DeelayValue
LatchCtrl

'Take SCLK low.
LWrd = CLng(FData + ORamp)
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
Deelay DeelayValue
LatchCtrl

'Prepend to address nibble.
Addr = "1000" & Addr

'Reverse if necessary.
If LSB1st = 1 Then RevStr Addr

'Initialize previous bit.
PrvStr = "0"
    
'For eight bits.
For i = 1 To 8
   
   'Get current data bit.
   TmpStr = Mid(Addr, i, 1)
      
   'Change data bit only if necessary.
   If (TmpStr = "1") And (PrvStr = "0") Then
         
      Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 254&)
      Deelay DeelayValue
      LatchAddr
         
      PrvStr = "1"
      
   ElseIf (TmpStr = "0") And (PrvStr = "1") Then
      
      Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
      Deelay DeelayValue
      LatchAddr
         
      PrvStr = "0"
      
   End If
      
   'Take SCLK high.
   LWrd = CLng(1 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
   Deelay DeelayValue
   LatchCtrl
      
   If i < 8 Then
    
      'Take SCLK low.
      LWrd = CLng(FData + ORamp)
      Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
      Deelay DeelayValue
      LatchCtrl
      
   End If

Next i

'Clear data.
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
Deelay DeelayValue
LatchAddr

'Get ready to readback.
If frmControl.opt2WireSerial.Value = True Then

   RBE = 4&
   Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 11& + RBE)
   
   End If
   
   
Dim BitsToRead As String

If LSB1st = 1 Then
    BitsToRead = Left(Addr, 4)
    RevStr BitsToRead
Else
    BitsToRead = Right(Addr, 4)
End If

'Determine number of bits to read.
Select Case BitsToRead

   Case "1010"
      Bits = 8
   Case "0000", "0001", "1000", "1001", "1011"
      Bits = 16
   Case "0110"
      Bits = 24
   Case "0101", "0111"
      Bits = 32
   Case "0010", "0011", "0100"
      Bits = 48

End Select

'Initialize readback string.
TmpStr = ""

'For number of readback bits.
For i = 1 To Bits

   'Take SCLK low.
   LWrd = CLng(FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
   Deelay DeelayValue
   LatchCtrl

   'Readback port and mask unwanted bits.
    Res = frmLPTSelect.LptInput(lpt_bp1_StatusReg) And 8
   
   'Build string.  Note - Data inverted to work with customer eval board
   'If InvRdBack board flag is set then data isn't inverted
   If NormRdBack Then
        If Res = 8 Then
           'If true then zero.
           TmpStr = TmpStr & "1"
        Else
           'If false then one.
           TmpStr = TmpStr & "0"
        End If
   Else
        If Res = 8 Then
           'If true then zero.
           TmpStr = TmpStr & "0"
        Else
           'If false then one.
           TmpStr = TmpStr & "1"
        End If
   End If
   'Take SCLK high.
   LWrd = CLng(1 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
   Deelay DeelayValue
   LatchCtrl
            
Next i

'Reverse if necessary.
If LSB1st = 1 Then RevStr TmpStr

'Assign to return string.
Deta = TmpStr

'Return RBE to false if necessary.
If frmControl.opt2WireSerial.Value = True Then

   RBE = 0&
   Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 11& + RBE)
   
   End If
   
'Take CS high.
LWrd = CLng(3 + FData + ORamp)
Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LWrd)
Deelay DeelayValue
LatchCtrl

End Sub

Public Sub RevStr(S As String)

'This procedure reverses the order of the incoming
'string for communication in LSB1st mode.

Dim i As Integer
Dim TmpStr As String, RevStr As String

For i = 1 To Len(S)

   TmpStr = Mid(S, i, 1)
   
   RevStr = TmpStr & RevStr

Next i

S = RevStr

End Sub

Public Sub LatchData()

Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 10& + RBE)      'Drive bit high.
Deelay DeelayValue
Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 11& + RBE)      'Drive bit low.
Deelay DeelayValue

End Sub

Public Sub LatchAddr()

Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 9& + RBE)       'Drive bit high.
Deelay DeelayValue
Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 11& + RBE)      'Drive bit low.
Deelay DeelayValue

End Sub

Public Sub LatchCtrl()

Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 3& + RBE)       'Drive bit high.
Deelay DeelayValue
Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 11& + RBE)      'Drive bit low.
Deelay DeelayValue

End Sub

Public Sub Deelay(N As Integer)

Dim i As Integer, J As Integer

   For i = 1 To N
      J = i + N
   Next i

End Sub
'Main subroutine
Public Sub Main()
    If App.PrevInstance = True Then
        'Exit the program immediatly
        End
    End If
    
    'Parse the command line
    'Optoisolator board switch is found
    If InStr(1, UCase(Command$), "-OPTO") <> 0 Then
        DeelayValue = 15000 'Set deelay to 15000
        OptoBoardFlag = True
    Else
        DeelayValue = 500
        OptoBoardFlag = False
    End If
    
    'Debug switch is found
    If InStr(1, UCase(Command$), "-DEBUG") <> 0 Then
        DebugFlag = True
        frmDebug.Show 'Show the debug form
        'Set the check box for the optoisolator board
        If OptoBoardFlag Then
            frmDebug.chkOptoisolatorBoard.Value = 1
        End If
    Else
        DebugFlag = False
    End If
    
    MDI_Main.Caption = "AD9852/54 Customer Evaluation Software Revision " & App.Major & "." & App.Minor
    MDI_Main.Show
End Sub

'Checks the connection using the currently selected LPT Port

'Feature added on 09/10/1999 by Shane Lambeth
'Also detects the engineering that inverts the data readback
'board and sets the NormRdBack global variable to true if it isn't
'allready true
Public Function CheckConnection() As Boolean
    Dim ResStr As String
    Dim ReadBackVal As String
    Const ReadBVCustomer = "00010000011001000000000100100000"
    Const ReadBVOpto = "00001111100110111111111011011111"
    
    'Reset the part
    frmFrequency.resetTheDut
    
    'Switch to Two Wire Serial Mode
    frmControl.SelectIOMode Two_Wire_Serial_Mode
    
    'Readback from register 7
    SRead ResStr, "0111"
    
    'Massage the data
    ReadBackVal = "000" & Mid(ResStr, 4, 5)
    ReadBackVal = ReadBackVal & Mid(ResStr, 9, 8)
    ReadBackVal = ReadBackVal & Mid(ResStr, 17, 8)
    ReadBackVal = ReadBackVal & Mid(ResStr, 25, 8)

    If DebugFlag Then
        With frmDebug.txtReadBackVals
            'Add the new value readback to the text box
            .SelStart = Len(.Text)
            .SelLength = Len(ReadBackVal)
            .SelText = ReadBackVal
        End With
    End If
    
    'Check the readback for a value
    Select Case ReadBackVal
        Case ReadBVCustomer:
            'Return true
            CheckConnection = True
        Case ReadBVOpto:
            'Return true
            CheckConnection = True
            NormRdBack = True
        Case Else:
            'Return false
            CheckConnection = False
    End Select
    
    'Switch back to parallel mode
    frmControl.SelectIOMode Parallel_Mode
End Function

'This function will check each parallel port for an evaluation board
Public Function FindConnection(ByRef CancelHit As Boolean) As Boolean
    Dim PortCntr As Integer
    Dim MsgStr As String
    Dim retval As Integer
    Dim ConnectionFound As Boolean
    
    'Initialize variables
    ConnectionFound = False
    
    MsgStr = "Make sure that the evaluation board is connected" & vbCrLf
    MsgStr = MsgStr & "to the parallel port you want to use and the evaluation" & vbCrLf
    MsgStr = MsgStr & "board is powered up!" & vbCrLf & vbCrLf
    MsgStr = MsgStr & "Note: This will reset the AD9852/54 and the software." & vbCrLf
    MsgStr = MsgStr & vbCrLf & "Press OK button when ready or CANCEL."
    
    retval = MsgBox(MsgStr, vbExclamation + vbApplicationModal + vbOKCancel, "Find Port")
    'If the user responds with OK then continue
    If retval = vbOK Then
        'Itterate through all of the ports
        For PortCntr = 0 To frmLPTSelect.LPTGetPortCount() - 1
            'Select the port
            Call frmLPTSelect.LPTSelectPort(PortCntr)
            'Check for a connection
            If CheckConnection() Then
                ConnectionFound = True
                Exit For
            End If
        Next PortCntr
        'If no connection was found
'        If ConnectionFound = False Then
'            MsgStr = "No valid connection could be found!!!" & vbCrLf & vbCrLf
'            MsgStr = MsgStr & "Make sure that the evaluation board is connected" & vbCrLf
'            MsgStr = MsgStr & "to a valid parallel printer port and the evaluation" & vbCrLf
'            MsgStr = MsgStr & "board is powered up properly."
'
'            MsgBox MsgStr, vbCritical + vbApplicationModal + vbOKOnly, "Error!!!"
'        End If
        
        CancelHit = False
    Else
        CancelHit = True
    End If
    'Return connection found flag
    FindConnection = ConnectionFound
End Function
