VERSION 5.00
Begin VB.Form frmClock 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   3135
   ClientLeft      =   15
   ClientTop       =   15
   ClientWidth     =   9660
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
   MDIChild        =   -1  'True
   ScaleHeight     =   3135
   ScaleWidth      =   9660
   Begin VB.TextBox txtUDCLKHex 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5400
      MaxLength       =   8
      TabIndex        =   21
      Text            =   "00000040"
      Top             =   2040
      Width           =   1195
   End
   Begin VB.TextBox txtUDCLK4 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   8160
      MaxLength       =   8
      TabIndex        =   20
      Text            =   "01000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txtUDCLK3 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   6960
      MaxLength       =   8
      TabIndex        =   19
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txtUDCLK2 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5760
      MaxLength       =   8
      TabIndex        =   18
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txtUDCLK1 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   4560
      MaxLength       =   8
      TabIndex        =   17
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.Frame frmUDCLK 
      Caption         =   "Update Clock"
      Height          =   855
      Left            =   4560
      TabIndex        =   14
      Top             =   120
      Width           =   4815
      Begin VB.OptionButton optExternal 
         Caption         =   "Externally Supplied"
         Height          =   255
         Left            =   2640
         TabIndex        =   16
         Top             =   360
         Width           =   2055
      End
      Begin VB.OptionButton optInternal 
         Caption         =   "Internally Generated"
         Height          =   255
         Left            =   360
         TabIndex        =   15
         Top             =   360
         Value           =   -1  'True
         Width           =   2055
      End
   End
   Begin VB.CommandButton cmdSendUDCLK 
      Caption         =   "Send UDCLK Now"
      Height          =   375
      Left            =   7200
      TabIndex        =   13
      Top             =   2640
      Width           =   2175
   End
   Begin VB.CommandButton cmdLoadUDCLK 
      Caption         =   "Send UDCLK Info To DUT"
      Height          =   375
      Left            =   4560
      TabIndex        =   12
      Top             =   2640
      Width           =   2415
   End
   Begin VB.CommandButton cmdLoadPLL 
      Caption         =   "Send CLK Info To DUT"
      Height          =   375
      Left            =   240
      TabIndex        =   11
      Top             =   2640
      Width           =   3855
   End
   Begin VB.CheckBox chkBypassPLL 
      Caption         =   "Bypass the Ref Clock Multiplier"
      Height          =   375
      Left            =   600
      TabIndex        =   10
      Top             =   2160
      Value           =   1  'Checked
      Width           =   3135
   End
   Begin VB.TextBox txtUDCLKMHz 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7320
      MaxLength       =   8
      TabIndex        =   8
      Text            =   "76.92308"
      Top             =   2040
      Width           =   1195
   End
   Begin VB.TextBox txtClock 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   840
      MaxLength       =   6
      TabIndex        =   4
      Text            =   "10.000"
      Top             =   480
      Width           =   1335
   End
   Begin VB.TextBox txtPLL 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   3000
      MaxLength       =   2
      TabIndex        =   3
      Text            =   "01"
      Top             =   480
      Width           =   495
   End
   Begin VB.Frame frmPllGain 
      Enabled         =   0   'False
      Height          =   1095
      Left            =   240
      TabIndex        =   0
      Top             =   960
      Width           =   3855
      Begin VB.OptionButton optPLL_Lo 
         Caption         =   "VCO Lo Range (50 - 200 MHz)"
         Enabled         =   0   'False
         Height          =   495
         Left            =   240
         TabIndex        =   2
         Top             =   360
         Width           =   1695
      End
      Begin VB.OptionButton optPLL_Hi 
         Caption         =   "VCO Hi Range (200 - 300 MHz)"
         Enabled         =   0   'False
         Height          =   495
         Left            =   2040
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   1695
      End
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "MHz"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2280
      TabIndex        =   23
      Top             =   600
      Width           =   375
   End
   Begin VB.Line Line3 
      X1              =   4320
      X2              =   4320
      Y1              =   3000
      Y2              =   120
   End
   Begin VB.Line Line2 
      X1              =   9240
      X2              =   8760
      Y1              =   1920
      Y2              =   2040
   End
   Begin VB.Line Line1 
      X1              =   4680
      X2              =   5160
      Y1              =   1920
      Y2              =   2040
   End
   Begin VB.Label lblEql 
      Alignment       =   2  'Center
      Caption         =   "<=>"
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   6720
      TabIndex        =   22
      Top             =   2160
      Width           =   495
   End
   Begin VB.Label lblUDCLKMHz 
      Alignment       =   2  'Center
      Caption         =   "KHz"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   8640
      TabIndex        =   9
      Top             =   2160
      Width           =   375
   End
   Begin VB.Label lblUDCLK 
      Alignment       =   2  'Center
      Caption         =   "Update Clock Counter Register"
      Height          =   255
      Left            =   5520
      TabIndex        =   7
      Top             =   1080
      Width           =   2895
   End
   Begin VB.Label lblUDCLKHex 
      Alignment       =   2  'Center
      Caption         =   "HEX"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4920
      TabIndex        =   6
      Top             =   2160
      Width           =   375
   End
   Begin VB.Label lblClock 
      Alignment       =   2  'Center
      Caption         =   "Reference Clock and Multiplier"
      Height          =   255
      Left            =   720
      TabIndex        =   5
      Top             =   120
      Width           =   2895
   End
End
Attribute VB_Name = "frmClock"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit                         'Declare all variables.
Option Base 1                           'Lower array index = 1.

Public Sub UDCLK_Update(SrcVal As String)

'This procedure updates the Update Clock Counter Register text boxes
'depending upon values in either the associated Hex or MHz text boxes.
'Incoming parameter SrcVal tells the procedure which value (Hex or MHz)
'to use as the independent value.  All others are then dependent on it.

Dim TxtStr As String, TmpStr As String, OutStr As String
Dim I As Integer, J As Integer, IntWrd As Integer
Dim BitVal As Variant, BytVal As Variant
Dim SysClk As Single, FrqVal As Single

'If independent value is hex value.
If SrcVal = "Hex" Then

   'Get the hex value.
   TxtStr = txtUDCLKHex.Text
   
   'For the 4 binary bytes.
   For I = 1 To 4
   
      'Initialize.
      OutStr = ""
   
      'For each nibble.
      For J = 1 To 2
   
         'Get current hex digit.
         TmpStr = Mid(TxtStr, (I - 1) * 2 + J, 1)
      
         'Select correct binary nibble.
         Select Case TmpStr
      
            Case "0"
               OutStr = OutStr & "0000"
            Case "1"
               OutStr = OutStr & "0001"
            Case "2"
               OutStr = OutStr & "0010"
            Case "3"
               OutStr = OutStr & "0011"
            Case "4"
               OutStr = OutStr & "0100"
            Case "5"
               OutStr = OutStr & "0101"
            Case "6"
               OutStr = OutStr & "0110"
            Case "7"
               OutStr = OutStr & "0111"
            Case "8"
               OutStr = OutStr & "1000"
            Case "9"
               OutStr = OutStr & "1001"
            Case "A"
               OutStr = OutStr & "1010"
            Case "B"
               OutStr = OutStr & "1011"
            Case "C"
               OutStr = OutStr & "1100"
            Case "D"
               OutStr = OutStr & "1101"
            Case "E"
               OutStr = OutStr & "1110"
            Case "F"
               OutStr = OutStr & "1111"
            
         End Select
         
      Next J
      
      'Write to appropriate byte.
      Select Case I
      
         Case 1
            txtUDCLK1.Text = OutStr
         Case 2
            txtUDCLK2.Text = OutStr
         Case 3
            txtUDCLK3.Text = OutStr
         Case 4
            txtUDCLK4.Text = OutStr
            
      End Select
   
   Next I

   'Now update MHz text box.
   UDCLKMHz_Update

'Else if independent value is MHz value.
ElseIf SrcVal = "MHz" Then

   'Get the system clock frequency.
   GetSysClk SysClk

   'If system clock is valid.
   If SysClk > 0 Then
   
      'Get UDCLK MHz frequency value.
      FrqVal = Val(txtUDCLKMHz.Text)
            
      'Convert to megahertz if necessary.
      If lblUDCLKMHz.Caption = "KHz" Then
              
         FrqVal = FrqVal / 1000
         
      ElseIf lblUDCLKMHz.Caption = "Hz" Then
      
         FrqVal = FrqVal / 1000000
         
      End If

      'Compute the tuning word numeric value.
      BitVal = CDec((SysClk / 2) / FrqVal - 1)
      
      'Convert to binary strings.
      For I = 24 To 0 Step -8
   
         'Compute binary byte value.
         BytVal = CDec(BitVal / 2 ^ I)

         'Truncate fractional portion.
         IntWrd = Fix(BytVal)
      
         'Reduce value.
         BitVal = CDec(BitVal - (IntWrd * 2 ^ I))
   
         'Build binary string.
         GetWrdStr IntWrd, TmpStr
      
         'Write to byte position.
         Select Case I

            Case 24
               txtUDCLK1.Text = TmpStr
            Case 16
               txtUDCLK2.Text = TmpStr
            Case 8
               txtUDCLK3.Text = TmpStr
            Case 0
               txtUDCLK4.Text = TmpStr
         
         End Select
      
      Next I
      
      'Now update hex text box.
      UDCLKHex_Update
   
   End If
      
End If

End Sub

Public Sub UDCLKMHz_Update()

'This procedure updates the MHz text box
'for the Update Clock Counter Registers.

Dim SysClk As Single, FrqVal As Single
Dim TmpStr As String, UntStr As String
Dim I As Integer, Index As Integer
Dim BitVal As Variant

'Get the system clock frequency.
GetSysClk SysClk

If SysClk > 0 Then

   TmpStr = ""
   
   TmpStr = TmpStr & txtUDCLK1.Text
   TmpStr = TmpStr & txtUDCLK2.Text
   TmpStr = TmpStr & txtUDCLK3.Text
   TmpStr = TmpStr & txtUDCLK4.Text

   Index = 0
   BitVal = CDec(0)
   
   For I = 32 To 1 Step -1
   
      If Mid(TmpStr, I, 1) = "1" Then
      
         BitVal = CDec(BitVal + 2 ^ Index)
         
      End If
      
      Index = Index + 1
    
   Next I
   
   'Add one.
   BitVal = CDec(BitVal + 1)
   
   'Update Clock is 1/2 of System Clock
   'divided by register value plus one.
   FrqVal = (SysClk / 2) / BitVal
   
   'Establish current units.
   UntStr = "MHz"
   
   'Multiply and change units if needed.
   If FrqVal < 1 Then
   
      FrqVal = FrqVal * 1000
      
      UntStr = "KHz"
      
      If FrqVal < 1 Then
   
         FrqVal = FrqVal * 1000
      
         UntStr = "Hz"
      
      End If
      
   End If
         
   'Now display with proper resolution.
   If FrqVal >= 100 Then

      txtUDCLKMHz.Text = Format(FrqVal, "000.0000")

   ElseIf FrqVal >= 10 Then

      txtUDCLKMHz.Text = Format(FrqVal, "00.00000")

   Else

      txtUDCLKMHz.Text = Format(FrqVal, "0.000000")
         
   End If
   
   'Update units label if needed.
   If lblUDCLKMHz.Caption <> UntStr Then
   
      lblUDCLKMHz.Caption = UntStr
      
      End If
   
End If

End Sub

Public Sub UDCLKHex_Update()

'This procedure updates the hex text box
'for the Update Clock Counter Registers.

Dim I As Integer, J As Integer, Wrd As Integer
Dim TxtStr As String, TmpStr As String, HexStr As String

'Initialize.
HexStr = ""

'For the eight hex digits.
For I = 1 To 8

   'Get current nibble string.
   Select Case I
   
      Case 1
         TxtStr = Mid(txtUDCLK1.Text, 1, 4)
      Case 2
         TxtStr = Mid(txtUDCLK1.Text, 5, 4)
      Case 3
         TxtStr = Mid(txtUDCLK2.Text, 1, 4)
      Case 4
         TxtStr = Mid(txtUDCLK2.Text, 5, 4)
      Case 5
         TxtStr = Mid(txtUDCLK3.Text, 1, 4)
      Case 6
         TxtStr = Mid(txtUDCLK3.Text, 5, 4)
      Case 7
         TxtStr = Mid(txtUDCLK4.Text, 1, 4)
      Case 8
         TxtStr = Mid(txtUDCLK4.Text, 5, 4)
         
   End Select
      
   'Initialize.
   Wrd = 0
   
   'Compute numeric value.
   For J = 1 To 4

      TmpStr = Mid(TxtStr, J, 1)
      If TmpStr = "1" Then Wrd = Wrd + 2 ^ (J * -1 + 4)
   
   Next J
   
   'Select hex digit.
   Select Case Wrd
   
      Case 0
         HexStr = HexStr & "0"
      Case 1
         HexStr = HexStr & "1"
      Case 2
         HexStr = HexStr & "2"
      Case 3
         HexStr = HexStr & "3"
      Case 4
         HexStr = HexStr & "4"
      Case 5
         HexStr = HexStr & "5"
      Case 6
         HexStr = HexStr & "6"
      Case 7
         HexStr = HexStr & "7"
      Case 8
         HexStr = HexStr & "8"
      Case 9
         HexStr = HexStr & "9"
      Case 10
         HexStr = HexStr & "A"
      Case 11
         HexStr = HexStr & "B"
      Case 12
         HexStr = HexStr & "C"
      Case 13
         HexStr = HexStr & "D"
      Case 14
         HexStr = HexStr & "E"
      Case 15
         HexStr = HexStr & "F"

   End Select

Next I

'Display hex value.
txtUDCLKHex.Text = HexStr

End Sub

Public Sub chkBypassPLL_Click()

'If checkbox is checked.
If chkBypassPLL.Value = 1 Then

   OldPll = txtPLL.Text
   
   txtPLL.Text = "01"
   
   frmPllGain.Enabled = False
   optPLL_Lo.Enabled = False
   optPLL_Hi.Enabled = False
   txtPLL.Enabled = False
   
Else

   txtPLL.Enabled = True
   optPLL_Lo.Enabled = True
   optPLL_Hi.Enabled = True
   frmPllGain.Enabled = True

   txtPLL.Text = OldPll
   
End If

frmFrequency.FTWMHz_Update "F1"
frmFrequency.FTWMHz_Update "F2"
frmFrequency.FTWMHz_Update "FSW"
      
UDCLKMHz_Update

End Sub

Public Sub cmdLoadPLL_Click()

Dim IntVal As Integer
Dim TmpStr As String

'If parallel mode.
If PMode = 16 Then

   'Write control register 30H.
   If chkBypassPLL.Value = 1 Then
      IntVal = Val(OldPll)
      IntVal = IntVal + 32
   Else
      IntVal = Val(txtPLL.Text)
   End If
   
   If optPLL_Hi.Value = True Then IntVal = IntVal + 64
   
   PWrite IntVal, 30
      
'Serial mode.
Else

   'Get control register string.
   GetSerMdeStr TmpStr
   
   'Write updated control register.
   SWrite TmpStr, "0111"
      
End If

End Sub

Public Sub cmdLoadUDCLK_Click()

'This procedure loads Update Clock info into the DUT registers.
'It can only be accessed if UDCLK is specified as "internally
'generated" since otherwise, the command button is disabled.

Dim IntVal As Integer
Dim TmpStr As String

'If parallel mode.
If PMode = 16 Then

   'Write Update Clock registers.
   TmpStr = txtUDCLK1.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 22

   TmpStr = txtUDCLK2.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 23

   TmpStr = txtUDCLK3.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 24

   TmpStr = txtUDCLK4.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 25
      
   'Write mode control register 31.
   If frmFrequency.optSingleTone.Value = True Then
      IntVal = 0
   ElseIf frmFrequency.optUnrampedFSK.Value = True Then
      IntVal = 2
   ElseIf frmFrequency.optRampedFSK.Value = True Then
      IntVal = 4
   ElseIf frmFrequency.optChirpMode.Value = True Then
      IntVal = 6
   ElseIf frmFrequency.optBPSKmode.Value = True Then
      IntVal = 8
   End If
      
   If frmFrequency.chkTriangle.Value = 1 Then IntVal = IntVal + 32
   If frmFrequency.chkACC2.Value = 1 Then IntVal = IntVal + 64
   If frmFrequency.chkACC1.Value = 1 Then IntVal = IntVal + 128
      
   If optInternal.Value = True Then IntVal = IntVal + 1
   If frmControl.chkSrcQDac.Value = 1 Then IntVal = IntVal + 16
      
   PWrite IntVal, 31

'Serial mode.
Else

   'Write Update Clock registers.
   TmpStr = txtUDCLK1.Text & txtUDCLK2.Text
   TmpStr = TmpStr & txtUDCLK3.Text & txtUDCLK4.Text
   SWrite TmpStr, "0101"
      
   'Get control register string.
   GetSerMdeStr TmpStr
      
   'Write updated control register.
   SWrite TmpStr, "0111"
   
End If

End Sub

Public Sub cmdSendUDCLK_Click()

Dim LCtl As Long

'If parallel mode.
If PMode = 16 Then

   'Set WRBAR,RDBAR,UDCLK,PMODE high.
   'Set RESET low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(27 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

   'Set WRBAR,RDBAR,PMODE high.
   'Set RESET,UDCLK low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(19 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

Else

   'Set CS,SCLK,UDCLK high.
   'Set RESET,PMODE low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(11 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

   'Set CS,SCLK high.
   'Set RESET,UDCLK,PMODE low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(3 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

End If

End Sub

Public Sub Form_Load()

Height = 3165
Width = 9750
Left = 100
Top = 100

'Initialize the Clock Frequency Text boxes
txtClock.Text = Format(10, "0.000")
txtUDCLKMHz.Text = Format(76.92308, "0.00000")

End Sub

Public Sub optExternal_Click()

Dim IntVal As Integer
Dim TmpStr As String

'disable UDCLK text boxes, etc
txtUDCLK1.Enabled = False
txtUDCLK2.Enabled = False
txtUDCLK3.Enabled = False
txtUDCLK4.Enabled = False
txtUDCLKHex.Enabled = False
txtUDCLKMHz.Enabled = False
lblUDCLK.Enabled = False
lblUDCLKHex.Enabled = False
lblUDCLKMHz.Enabled = False
lblEql.Enabled = False
cmdLoadUDCLK.Enabled = False

'If parallel mode.
If PMode = 16 Then

   'Write mode control register 31.
   If frmFrequency.optSingleTone.Value = True Then
      IntVal = 0
   ElseIf frmFrequency.optUnrampedFSK.Value = True Then
      IntVal = 2
   ElseIf frmFrequency.optRampedFSK.Value = True Then
      IntVal = 4
   ElseIf frmFrequency.optChirpMode.Value = True Then
      IntVal = 6
   ElseIf frmFrequency.optBPSKmode.Value = True Then
      IntVal = 8
   End If
      
   If frmFrequency.chkTriangle.Value = 1 Then IntVal = IntVal + 32
   If frmFrequency.chkACC2.Value = 1 Then IntVal = IntVal + 64
   If frmFrequency.chkACC1.Value = 1 Then IntVal = IntVal + 128
      
   If frmControl.chkSrcQDac.Value = 1 Then IntVal = IntVal + 16
      
   PWrite IntVal, 31

'Serial mode.
Else

   'Get control register string.
   GetSerMdeStr TmpStr
      
   'Write updated control register.
   SWrite TmpStr, "0111"
   
End If

End Sub

Public Sub optInternal_Click()

Dim IntVal As Integer
Dim TmpStr As String

'enable UDCLK text boxes, etc
txtUDCLK1.Enabled = True
txtUDCLK2.Enabled = True
txtUDCLK3.Enabled = True
txtUDCLK4.Enabled = True
txtUDCLKHex.Enabled = True
txtUDCLKMHz.Enabled = True
lblUDCLK.Enabled = True
lblUDCLKHex.Enabled = True
lblUDCLKMHz.Enabled = True
lblEql.Enabled = True
cmdLoadUDCLK.Enabled = True

'If parallel mode.
If PMode = 16 Then

   'Write mode control register 31.
   If frmFrequency.optSingleTone.Value = True Then
      IntVal = 1
   ElseIf frmFrequency.optUnrampedFSK.Value = True Then
      IntVal = 3
   ElseIf frmFrequency.optRampedFSK.Value = True Then
      IntVal = 5
   ElseIf frmFrequency.optChirpMode.Value = True Then
      IntVal = 7
   ElseIf frmFrequency.optBPSKmode.Value = True Then
      IntVal = 9
   End If
      
   If frmFrequency.chkTriangle.Value = 1 Then IntVal = IntVal + 32
   If frmFrequency.chkACC2.Value = 1 Then IntVal = IntVal + 64
   If frmFrequency.chkACC1.Value = 1 Then IntVal = IntVal + 128
      
   If frmControl.chkSrcQDac.Value = 1 Then IntVal = IntVal + 16
      
   PWrite IntVal, 31

'Serial mode.
Else

   'Get control register string.
   GetSerMdeStr TmpStr
      
   'Write updated control register.
   SWrite TmpStr, "0111"
   
End If

End Sub

Public Sub txtClock_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only numeric
'characters "0" thru "9" plus "." and BS, DEL, and CR.

Dim FrqVal As Single

Select Case KeyAscii

'   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
'
'      KeyAscii = 0
    Case MyLocInfo.iDecSep 'Pass the decimal seperator
        'Check to see if a Decimal Seperator is allready in the string
        If InStr(1, txtClock.Text, MyLocInfo.sDecSep) Then
            'If so then trash the key
            KeyAscii = 0
        End If
    '   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
    '
    '      KeyAscii = 0
       
    Case 0 To 12 'Control Keys
    Case 14 To 32  'Control Keys
    Case 48 To 57 'Numeric Keys
      
    Case 13
    
        KeyAscii = 0
        
        'Get current value.
        FrqVal = CSng(txtClock.Text)
        
        'Write out to maximum resolution.
        If FrqVal >= 100 Then
        
            txtClock.Text = Format(FrqVal, "000.00")
        
        ElseIf FrqVal >= 10 Then
        
            txtClock.Text = Format(FrqVal, "00.000")
        
        Else
        
            txtClock.Text = Format(FrqVal, "0.0000")
           
        End If
        
        'Update all frequencies.
        frmFrequency.FTWMHz_Update "F1"
        frmFrequency.FTWMHz_Update "F2"
        frmFrequency.FTWMHz_Update "FSW"
        
        UDCLKMHz_Update
        
        cmdLoadPLL.SetFocus

    'Trash all other keys
    Case Else
        KeyAscii = 0

End Select

End Sub

Public Sub txtPLL_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only numeric
'characters "0" thru "9" plus BS, DEL, and CR.

Dim PllVal As Integer

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 57
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Get current value.
      PllVal = Val(txtPLL.Text)
      
      'Adjust if not within range.
      If PllVal > 20 Then PllVal = 20
      If PllVal < 4 Then PllVal = 4

      'Write out to two places.
      If PllVal >= 10 Then
         txtPLL.Text = Format(PllVal, "00")
      Else
         txtPLL.Text = "0" & Format(PllVal, "0")
      End If

      'Update all frequencies.
      frmFrequency.FTWMHz_Update "F1"
      frmFrequency.FTWMHz_Update "F2"
      frmFrequency.FTWMHz_Update "FSW"
      
      UDCLKMHz_Update
      
      cmdLoadPLL.SetFocus

End Select

End Sub

Public Sub txtUDCLK1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append with zeros if needed.
      If Len(txtUDCLK1.Text) < 8 Then
      
         txtUDCLK1.Text = txtUDCLK1.Text & String(8 - Len(txtUDCLK1.Text), 48)
         
      End If
      
      'Update other registers.
      UDCLKHex_Update
      UDCLKMHz_Update
      
      cmdLoadUDCLK.SetFocus

End Select

End Sub

Public Sub txtUDCLK2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append with zeros if needed.
      If Len(txtUDCLK2.Text) < 8 Then
      
         txtUDCLK2.Text = txtUDCLK2.Text & String(8 - Len(txtUDCLK2.Text), 48)
         
      End If
      
      'Update other registers.
      UDCLKHex_Update
      UDCLKMHz_Update

      cmdLoadUDCLK.SetFocus

End Select

End Sub

Public Sub txtUDCLK3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append with zeros if needed.
      If Len(txtUDCLK3.Text) < 8 Then
      
         txtUDCLK3.Text = txtUDCLK3.Text & String(8 - Len(txtUDCLK3.Text), 48)
         
      End If
      
      'Update other registers.
      UDCLKHex_Update
      UDCLKMHz_Update

      cmdLoadUDCLK.SetFocus

End Select

End Sub

Public Sub txtUDCLK4_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append with zeros if needed.
      If Len(txtUDCLK4.Text) < 8 Then
        
         txtUDCLK4.Text = txtUDCLK4.Text & String(8 - Len(txtUDCLK4.Text), 48)
         
      End If
      
      'Update other registers.
      UDCLKHex_Update
      UDCLKMHz_Update

      cmdLoadUDCLK.SetFocus

End Select

End Sub

Public Sub txtUDCLKHex_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only hex
'characters "0" to "F" plus BS, DEL, and CR.

Select Case KeyAscii
      
   Case Is < 8, 9 To 12, 14 To 47, 58 To 64, 71 To 96, Is > 102
   
      KeyAscii = 0
      
   Case 97 To 102
   
      KeyAscii = KeyAscii - 32
      
   Case 13
   
      KeyAscii = 0
      
      'Prepend with zeros if needed.
      If Len(txtUDCLKHex.Text) < 8 Then
       
         txtUDCLKHex.Text = String(8 - Len(txtUDCLKHex.Text), 48) & txtUDCLKHex.Text
         
      End If
      
      'Update other registers.
      UDCLK_Update "Hex"

      cmdLoadUDCLK.SetFocus

End Select

End Sub

Public Sub txtUDCLKMHz_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only numeric
'characters "0" thru "9" plus "." and BS, DEL, and CR.

Dim FrqVal As Single

Select Case KeyAscii

    Case MyLocInfo.iDecSep 'Pass the decimal seperator
        'Check to see if a Decimal Seperator is allready in the string
        If InStr(1, txtUDCLKMHz.Text, MyLocInfo.sDecSep) Then
            'If so then trash the key
            KeyAscii = 0
        End If
    '   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
    '
    '      KeyAscii = 0
       
    Case 0 To 12 'Control Keys
    Case 14 To 32  'Control Keys
    Case 48 To 57 'Numeric Keys
    '   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
    '
    '      KeyAscii = 0
    '
    '   Case 0 To 7 '
    Case 13
    
    KeyAscii = 0
    
    'Get current value.
    FrqVal = CSng(txtUDCLKMHz.Text)
    
    'If 0 is entered set it to the lowest possible value
    If FrqVal = 0 Then
        lblUDCLKMHz.Caption = "Hz"
        FrqVal = 0.001164
    End If
    
    'Check if too big - increase units.
    If (lblUDCLKMHz.Caption = "Hz") And (FrqVal >= 1000) Then
        
        FrqVal = FrqVal / 1000
        
        lblUDCLKMHz.Caption = "KHz"
        
    End If
       
    If (lblUDCLKMHz.Caption = "KHz") And (FrqVal >= 1000) Then
    
        FrqVal = FrqVal / 1000
        
        lblUDCLKMHz.Caption = "MHz"
        
    End If
       
    'Check if too small - decrease units.
    If (lblUDCLKMHz.Caption = "MHz") And (FrqVal <= 1) Then
    
        FrqVal = FrqVal * 1000
        
        lblUDCLKMHz.Caption = "KHz"
        
    End If
       
    If (lblUDCLKMHz.Caption = "KHz") And (FrqVal <= 1) Then
    
        FrqVal = FrqVal * 1000
        
        lblUDCLKMHz.Caption = "Hz"
        
    End If
       
    'Now display with proper resolution.
    If FrqVal >= 100 Then
    
        txtUDCLKMHz.Text = Format(FrqVal, "000.0000")
    
    ElseIf FrqVal >= 10 Then
    
        txtUDCLKMHz.Text = Format(FrqVal, "00.00000")
    
    Else
    
        txtUDCLKMHz.Text = Format(FrqVal, "0.000000")
       
    End If
    
        'Now update other registers.
        UDCLK_Update "MHz"
        
        cmdLoadUDCLK.SetFocus

    Case Else
        'Trash all other keys
        KeyAscii = 0
End Select

End Sub

Sub sendClockToDUT()

    Call cmdLoadPLL_Click
    Call cmdLoadUDCLK_Click
    
End Sub
