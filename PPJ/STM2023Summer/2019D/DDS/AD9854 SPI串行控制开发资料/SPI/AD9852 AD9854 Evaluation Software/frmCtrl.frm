VERSION 5.00
Begin VB.Form frmControl 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   5295
   ClientLeft      =   15
   ClientTop       =   15
   ClientWidth     =   5175
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   5295
   ScaleWidth      =   5175
   Begin VB.CommandButton cmdIOReset 
      Caption         =   "I/O Reset"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   22
      Top             =   1920
      Width           =   1455
   End
   Begin VB.Frame frmPwrDwn 
      Caption         =   "Power Down"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1815
      Left            =   2160
      TabIndex        =   16
      Top             =   120
      Width           =   2895
      Begin VB.CheckBox chkFulDigPwrDwn 
         Caption         =   "Full Digital Power Down"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   21
         Top             =   1440
         Width           =   2415
      End
      Begin VB.CheckBox chkAllDacPwrDwn 
         Caption         =   "All DAC Power Down"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   20
         Top             =   1080
         Width           =   2175
      End
      Begin VB.CheckBox chkQDacPwrDwn 
         Caption         =   "Q-DAC Power Down"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   19
         Top             =   720
         Width           =   2175
      End
      Begin VB.CheckBox chkPllPwrDwn 
         Caption         =   "PLL Power Down (Hidden)"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   18
         Top             =   1800
         Visible         =   0   'False
         Width           =   1935
      End
      Begin VB.CheckBox chkCompPwrDwn 
         Caption         =   "Comparator Power Down"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   17
         Top             =   360
         Value           =   1  'Checked
         Width           =   2535
      End
   End
   Begin VB.CheckBox chkBypInvSinc 
      Caption         =   "Bypass Inverse Sinc Filter"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2280
      TabIndex        =   15
      Top             =   2160
      Width           =   2655
   End
   Begin VB.TextBox txtQDacHex 
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
      Left            =   3120
      MaxLength       =   3
      TabIndex        =   14
      Text            =   "000"
      Top             =   4200
      Width           =   685
   End
   Begin VB.TextBox txtQDac3 
      Enabled         =   0   'False
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
      Left            =   2040
      MaxLength       =   4
      TabIndex        =   13
      Text            =   "0000"
      Top             =   4200
      Width           =   640
   End
   Begin VB.TextBox txtQDac2 
      Enabled         =   0   'False
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
      Left            =   1440
      MaxLength       =   4
      TabIndex        =   12
      Text            =   "0000"
      Top             =   4200
      Width           =   640
   End
   Begin VB.TextBox txtQDac1 
      Enabled         =   0   'False
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
      Left            =   840
      MaxLength       =   4
      TabIndex        =   11
      Text            =   "0000"
      Top             =   4200
      Width           =   640
   End
   Begin VB.CommandButton cmdCtrlLoad 
      Caption         =   "Send Control Info To DUT"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   120
      TabIndex        =   10
      Top             =   2760
      Width           =   4935
   End
   Begin VB.Frame frmComm 
      Caption         =   "Communications"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2415
      Left            =   120
      TabIndex        =   5
      Top             =   120
      Width           =   1935
      Begin VB.OptionButton optParallel 
         Caption         =   "Parallel"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   9
         Top             =   360
         Value           =   -1  'True
         Width           =   975
      End
      Begin VB.CheckBox chkLSB1st 
         Caption         =   "LSB 1st Mode"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   1440
         Width           =   1575
      End
      Begin VB.OptionButton opt3WireSerial 
         Caption         =   "3-Wire Serial"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   1080
         Width           =   1455
      End
      Begin VB.OptionButton opt2WireSerial 
         Caption         =   "2-Wire Serial"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   720
         Width           =   1455
      End
   End
   Begin VB.CheckBox chkSrcQDac 
      Caption         =   "Source Q-DAC From Register Below"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   840
      TabIndex        =   1
      Top             =   3480
      Width           =   3615
   End
   Begin VB.CommandButton cmdQDacLoad 
      Caption         =   "Send Q-DAC Source Info To DUT"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   720
      TabIndex        =   0
      Top             =   4800
      Width           =   3735
   End
   Begin VB.Line Line1 
      X1              =   120
      X2              =   5040
      Y1              =   3360
      Y2              =   3360
   End
   Begin VB.Label lblQDac 
      Alignment       =   2  'Center
      Caption         =   "Q-DAC Register"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   960
      TabIndex        =   4
      Top             =   3840
      Width           =   1575
   End
   Begin VB.Label lblQDacEql 
      Alignment       =   2  'Center
      Caption         =   "="
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2760
      TabIndex        =   3
      Top             =   4320
      Width           =   255
   End
   Begin VB.Label lblQDacHex 
      Alignment       =   2  'Center
      Caption         =   "HEX"
      Enabled         =   0   'False
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
      Left            =   3960
      TabIndex        =   2
      Top             =   4320
      Width           =   375
   End
End
Attribute VB_Name = "frmControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit                         'Declare all variables.
Option Base 1                           'Lower array index = 1.

Private IOSelectFlag As Boolean

Public Sub QDac_Update()

'This procedure updates the 12-bit binary number
'for the QDac output.

Dim HexStr As String, TmpStr As String, BytStr As String
Dim i As Integer

'Get hex value string.
HexStr = txtQDacHex.Text

'If needed then prepend with zeros.
If Len(HexStr) < 3 Then

   HexStr = String(3 - Len(HexStr), 48) & HexStr

   'Rewrite to screen.
   txtQDacHex.Text = HexStr
   
End If

'Initialize byte string.
BytStr = ""

'Process hex digits.
For i = 1 To 3

   TmpStr = Mid(HexStr, i, 1)
   
   Select Case TmpStr
   
      Case "0"
         BytStr = BytStr & "0000"
      Case "1"
         BytStr = BytStr & "0001"
      Case "2"
         BytStr = BytStr & "0010"
      Case "3"
         BytStr = BytStr & "0011"
      Case "4"
         BytStr = BytStr & "0100"
      Case "5"
         BytStr = BytStr & "0101"
      Case "6"
         BytStr = BytStr & "0110"
      Case "7"
         BytStr = BytStr & "0111"
      Case "8"
         BytStr = BytStr & "1000"
      Case "9"
         BytStr = BytStr & "1001"
      Case "A"
         BytStr = BytStr & "1010"
      Case "B"
         BytStr = BytStr & "1011"
      Case "C"
         BytStr = BytStr & "1100"
      Case "D"
         BytStr = BytStr & "1101"
      Case "E"
         BytStr = BytStr & "1110"
      Case "F"
         BytStr = BytStr & "1111"
      
   End Select
   
Next i

'Write out binary values.
txtQDac1.Text = Mid(BytStr, 1, 4)
txtQDac2.Text = Mid(BytStr, 5, 4)
txtQDac3.Text = Mid(BytStr, 9, 4)

End Sub

Public Sub QDacHex_Update()

'This procedure calculates the hex equivalent
'of the 12-bit binary QDac output.

Dim TxtStr As String, TmpStr As String, HexStr As String
Dim i As Integer, J As Integer, Wrd As Integer

'Initialize.
HexStr = ""

'For three hex digits.
For i = 1 To 3

   'Get current binary bits.
   Select Case i
      
      Case 1
         TxtStr = txtQDac1.Text
      Case 2
         TxtStr = txtQDac2.Text
      Case 3
         TxtStr = txtQDac3.Text
         
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

Next i

'Display value.
txtQDacHex.Text = HexStr

End Sub

Public Sub chkSrcQDac_Click()

'If check box is checked.
If chkSrcQDac.Value = 1 Then

   txtQDac1.Enabled = True
   txtQDac2.Enabled = True
   txtQDac3.Enabled = True
   txtQDacHex.Enabled = True
   lblQDac.Enabled = True
   lblQDacEql.Enabled = True
   lblQDacHex.Enabled = True
   
Else

   txtQDac1.Enabled = False
   txtQDac2.Enabled = False
   txtQDac3.Enabled = False
   txtQDacHex.Enabled = False
   lblQDac.Enabled = False
   lblQDacEql.Enabled = False
   lblQDacHex.Enabled = False
   
End If

End Sub

Public Sub cmdIOReset_Click()

   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 251&)
   Deelay DeelayValue
   LatchAddr

   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
   Deelay DeelayValue
   LatchAddr

End Sub

Public Sub cmdQDacLoad_Click()

Dim TmpStr As String
Dim IntVal As Integer

'If parallel mode.
If PMode = 16 Then

   TmpStr = "0000" & txtQDac1.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 38

   TmpStr = txtQDac2.Text & txtQDac3.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 39
      
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
      
   If frmFrequency.chkTriangle.Value = 1 Then
      IntVal = IntVal + 32
      End If
         
   If frmFrequency.chkACC2.Value = 1 Then
      IntVal = IntVal + 64
      End If
         
   If frmFrequency.chkACC1.Value = 1 Then
      IntVal = IntVal + 128
      End If
      
   If frmClock.optInternal.Value = True Then
      IntVal = IntVal + 1
      End If
         
   If chkSrcQDac.Value = 1 Then IntVal = IntVal + 16
   
   PWrite IntVal, 31
      
'Serial mode.
Else

   TmpStr = "0000" & txtQDac1.Text
   TmpStr = TmpStr & txtQDac2.Text & txtQDac3.Text
   SWrite TmpStr, "1011"

   'Get control register string.
   GetSerMdeStr TmpStr
      
   'Write updated control register.
   SWrite TmpStr, "0111"

End If

End Sub

Public Sub cmdCtrlLoad_Click()

Dim TmpStr As String
Dim IntVal As Integer

'If parallel mode.
If PMode = 16 Then

   IntVal = 0

   If chkFulDigPwrDwn.Value = 1 Then
      IntVal = IntVal + 1
      End If
      
   If chkAllDacPwrDwn.Value = 1 Then
      IntVal = IntVal + 2
      End If
      
   If chkQDacPwrDwn.Value = 1 Then
      IntVal = IntVal + 4
      End If
      
   If chkPllPwrDwn.Value = 1 Then
      IntVal = IntVal + 8
      End If
      
   If chkCompPwrDwn.Value = 1 Then
      IntVal = IntVal + 16
      End If
      
   PWrite IntVal, 29
   
   IntVal = 0
   
   If chkBypInvSinc.Value = 1 Then
      IntVal = IntVal + 64
      End If
         
   If chkLSB1st.Value = 1 Then
      IntVal = IntVal + 2
      LSB1st = 1
   Else
      LSB1st = 0
      End If
         
   If opt3WireSerial.Value = True Then
      IntVal = IntVal + 1
      End If
      
   If frmAmplitude.optOutAmpProg.Value = True Then
      IntVal = IntVal + 32
      End If
         
   If frmAmplitude.optUseRamp.Value = True Then
      IntVal = IntVal + 16
      End If

   PWrite IntVal, 32
      
'Serial mode.
Else

   'Get control register string.
   GetSerMdeStr TmpStr
      
   'Write updated control register.
   SWrite TmpStr, "0111"
   
   'Set or clear the flag.
   If chkLSB1st.Value = 1 Then
      LSB1st = 1
   Else
      LSB1st = 0
   End If
         
End If

End Sub

Public Sub Form_Load()

Height = 5325
Width = 5300
Left = 4550
Top = 3375

End Sub

Public Sub opt2WireSerial_Click()

Dim MsgStr As String

   If (opt2WireSerial.Value = True) And (frmClock.optInternal.Value = True) And IOSelectFlag = False Then
   
      MsgStr = "External Update Clock Mode is Recommended!"
      Call MsgBox(MsgStr, 0, "Warning!")
      
   End If

   chkLSB1st.Enabled = True
   cmdIOReset.Enabled = True

   SwitchToSerial
   
End Sub

Public Sub opt3WireSerial_Click()

Dim MsgStr As String

   If (opt3WireSerial.Value = True) And (frmClock.optInternal.Value = True) And IOSelectFlag = False Then
   
      MsgStr = "External Update Clock Mode is Recommended!"
      Call MsgBox(MsgStr, 0, "Warning!")
      
   End If
   
   chkLSB1st.Enabled = True
   cmdIOReset.Enabled = True

   SwitchToSerial
   
End Sub

Public Sub optParallel_Click()
 
   chkLSB1st.Enabled = False
   cmdIOReset.Enabled = False

   SwitchToParallel

End Sub

Public Sub txtQDac1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtQDac1.Text) < 4 Then
      
         txtQDac1.Text = txtQDac1.Text & String(4 - Len(txtQDac1.Text), 48)
         
      End If
      
      QDacHex_Update

      cmdQDacLoad.SetFocus

End Select

End Sub

Public Sub txtQDac2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtQDac2.Text) < 4 Then
      
         txtQDac2.Text = txtQDac2.Text & String(4 - Len(txtQDac2.Text), 48)
         
      End If
      
      QDacHex_Update

      cmdQDacLoad.SetFocus

End Select

End Sub

Public Sub txtQDac3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtQDac3.Text) < 4 Then
      
         txtQDac3.Text = txtQDac3.Text & String(4 - Len(txtQDac3.Text), 48)
         
      End If
      
      QDacHex_Update

      cmdQDacLoad.SetFocus

End Select

End Sub

Public Sub txtQDacHex_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only hex
'characters "0" to "F" plus BS, DEL, and CR.

Select Case KeyAscii
      
   Case Is < 8, 9 To 12, 14 To 47, 58 To 64, 71 To 96, Is > 102
   
      KeyAscii = 0
      
   Case 97 To 102
   
      KeyAscii = KeyAscii - 32
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtQDacHex.Text) < 3 Then
      
         txtQDacHex.Text = String(3 - Len(txtQDacHex.Text), 48) & txtQDacHex.Text
         
      End If
      
      QDac_Update
      
      cmdQDacLoad.SetFocus

End Select

End Sub
Sub sendControlToDUT()
    
    Call cmdIOReset_Click
    Call cmdCtrlLoad_Click
    Call cmdQDacLoad_Click
    
End Sub

'Selects the IOMode to use to communicate with the board
Public Sub SelectIOMode(ByVal SerialMode As AD985452IOMode)
    'Set the IOSelectFlag
    IOSelectFlag = True
    
    'Select the specifed mode
    Select Case SerialMode
        Case Two_Wire_Serial_Mode
            'Use the option button to do the job
            opt2WireSerial.Value = True
        Case Three_Wire_Serial_Mode
            'Use the option button to do the job
            opt3WireSerial = True
        Case Parallel_Mode
            'Use the option buton to do the job
            optParallel.Value = True
    End Select

    'Clear the IOSelectFlag
    IOSelectFlag = False
End Sub

'Gets the current IOMode being used to communicate with the board
Public Function GetIOMode() As Integer
    'Use the option buttons to determine the IO mode
    If opt2WireSerial.Value Then
        GetIOMode = Two_Wire_Serial_Mode
    ElseIf opt3WireSerial.Value Then
        GetIOMode = Three_Wire_Serial_Mode
    ElseIf optParallel.Value Then
        GetIOMode = Parallel_Mode
    End If
End Function
