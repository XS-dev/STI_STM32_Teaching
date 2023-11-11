VERSION 5.00
Begin VB.Form frmAmplitude 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   5295
   ClientLeft      =   15
   ClientTop       =   15
   ClientWidth     =   4230
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   5295
   ScaleWidth      =   4230
   Begin VB.OptionButton optUseRamp 
      Caption         =   "Enable Shaped Keying Function"
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
      Left            =   480
      TabIndex        =   23
      Top             =   3480
      Width           =   3255
   End
   Begin VB.OptionButton optUseFixed 
      Caption         =   "Use fixed value scale registers below"
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
      Left            =   360
      TabIndex        =   22
      Top             =   1440
      Value           =   -1  'True
      Width           =   3615
   End
   Begin VB.TextBox txtORRHex 
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
      Left            =   2520
      MaxLength       =   2
      TabIndex        =   21
      Text            =   "80"
      Top             =   4200
      Width           =   490
   End
   Begin VB.TextBox txtQChanHex 
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
      Left            =   2880
      MaxLength       =   3
      TabIndex        =   20
      Text            =   "000"
      Top             =   2520
      Width           =   685
   End
   Begin VB.TextBox txtIChanHex 
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
      Left            =   720
      MaxLength       =   3
      TabIndex        =   19
      Text            =   "000"
      Top             =   2520
      Width           =   685
   End
   Begin VB.TextBox txtORR2 
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
      TabIndex        =   18
      Text            =   "0000"
      Top             =   4200
      Width           =   640
   End
   Begin VB.TextBox txtORR1 
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
      TabIndex        =   17
      Text            =   "1000"
      Top             =   4200
      Width           =   640
   End
   Begin VB.TextBox txtQChan3 
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
      Left            =   3480
      MaxLength       =   4
      TabIndex        =   16
      Text            =   "0000"
      Top             =   1920
      Width           =   640
   End
   Begin VB.TextBox txtQChan2 
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
      Left            =   2880
      MaxLength       =   4
      TabIndex        =   15
      Text            =   "0000"
      Top             =   1920
      Width           =   640
   End
   Begin VB.TextBox txtQChan1 
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
      Left            =   2280
      MaxLength       =   4
      TabIndex        =   14
      Text            =   "0000"
      Top             =   1920
      Width           =   640
   End
   Begin VB.TextBox txtIChan3 
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
      Left            =   1320
      MaxLength       =   4
      TabIndex        =   13
      Text            =   "0000"
      Top             =   1920
      Width           =   640
   End
   Begin VB.TextBox txtIChan2 
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
      Left            =   720
      MaxLength       =   4
      TabIndex        =   12
      Text            =   "0000"
      Top             =   1920
      Width           =   640
   End
   Begin VB.TextBox txtIChan1 
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
      Left            =   120
      MaxLength       =   4
      TabIndex        =   11
      Text            =   "0000"
      Top             =   1920
      Width           =   640
   End
   Begin VB.Frame frmOutAmp 
      Caption         =   "Output Amplitude"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   120
      TabIndex        =   7
      Top             =   120
      Width           =   3975
      Begin VB.OptionButton optOutAmpFS 
         Caption         =   "Output amplitude is always full scale."
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
         Left            =   240
         TabIndex        =   9
         Top             =   600
         Width           =   3615
      End
      Begin VB.OptionButton optOutAmpProg 
         Caption         =   "Output amplitude is programmable."
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
         Left            =   240
         TabIndex        =   8
         Top             =   240
         Value           =   -1  'True
         Width           =   3375
      End
   End
   Begin VB.CommandButton cmdAmpLoad 
      Caption         =   "Send Amplitude Scaling Info To DUT"
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
      Left            =   240
      TabIndex        =   6
      Top             =   4800
      Width           =   3735
   End
   Begin VB.Line Line4 
      X1              =   4080
      X2              =   3720
      Y1              =   2400
      Y2              =   2520
   End
   Begin VB.Line Line3 
      X1              =   2280
      X2              =   2760
      Y1              =   2400
      Y2              =   2520
   End
   Begin VB.Line Line2 
      X1              =   600
      X2              =   120
      Y1              =   2520
      Y2              =   2400
   End
   Begin VB.Line Line1 
      X1              =   1560
      X2              =   1920
      Y1              =   2520
      Y2              =   2400
   End
   Begin VB.Label lblORREql 
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
      Left            =   2160
      TabIndex        =   10
      Top             =   4320
      Width           =   255
   End
   Begin VB.Line Line9 
      X1              =   120
      X2              =   4080
      Y1              =   3360
      Y2              =   3360
   End
   Begin VB.Label lblORRHex 
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
      Left            =   3120
      TabIndex        =   5
      Top             =   4320
      Width           =   375
   End
   Begin VB.Label lblQChanMult 
      Alignment       =   2  'Center
      Caption         =   "Q-Channel Multiplier"
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
      TabIndex        =   4
      Top             =   3000
      Width           =   1815
   End
   Begin VB.Label lblQChanHex 
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
      Left            =   3720
      TabIndex        =   3
      Top             =   2640
      Width           =   375
   End
   Begin VB.Label lblORR 
      Caption         =   "Ramp Rate Counter Register"
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
      Left            =   840
      TabIndex        =   2
      Top             =   3840
      Width           =   2655
   End
   Begin VB.Label lblIChanMult 
      Alignment       =   2  'Center
      Caption         =   "I-Channel Multiplier"
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
      TabIndex        =   1
      Top             =   3000
      Width           =   1815
   End
   Begin VB.Label lblIChanHex 
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
      Left            =   1560
      TabIndex        =   0
      Top             =   2640
      Width           =   375
   End
End
Attribute VB_Name = "frmAmplitude"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Option Explicit                         'Declare all variables.
Option Base 1                           'Lower array index = 1.

Public Sub Chan_Update(ChTyp As String)

'This procedure updates the 12-bit binary number
'for I/Q channel fixed output amplitude.

Dim HexStr As String, TmpStr As String, BytStr As String
Dim I As Integer

'Get hex value string.
If ChTyp = "I" Then
   HexStr = txtIChanHex.Text
Else
   HexStr = txtQChanHex.Text
End If

'If needed then prepend with zeros.
If Len(HexStr) < 3 Then

   HexStr = String(3 - Len(HexStr), 48) & HexStr

   'Rewrite to screen.
   If ChTyp = "I" Then
      txtIChanHex.Text = HexStr
   Else
      txtQChanHex.Text = HexStr
   End If
   
End If

'Initialize byte string.
BytStr = ""

'Process hex digits.
For I = 1 To 3

   TmpStr = Mid(HexStr, I, 1)
   
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
   
Next I

'Write out binary values.
If ChTyp = "I" Then
   txtIChan1.Text = Mid(BytStr, 1, 4)
   txtIChan2.Text = Mid(BytStr, 5, 4)
   txtIChan3.Text = Mid(BytStr, 9, 4)
Else
   txtQChan1.Text = Mid(BytStr, 1, 4)
   txtQChan2.Text = Mid(BytStr, 5, 4)
   txtQChan3.Text = Mid(BytStr, 9, 4)
End If

End Sub

Public Sub ChanHex_Update(ChTyp As String)

'This procedure calculates the hex equivalent
'of the 12-bit binary fixed output amplitude.

Dim TxtStr As String, TmpStr As String, HexStr As String
Dim I As Integer, J As Integer, Wrd As Integer

'Initialize.
HexStr = ""

'For three hex digits.
For I = 1 To 3

   'Get current binary bits.
   Select Case I
      
      Case 1
         If ChTyp = "I" Then
            TxtStr = txtIChan1.Text
         Else
            TxtStr = txtQChan1.Text
         End If
      Case 2
         If ChTyp = "I" Then
            TxtStr = txtIChan2.Text
         Else
            TxtStr = txtQChan2.Text
         End If
      Case 3
         If ChTyp = "I" Then
            TxtStr = txtIChan3.Text
         Else
            TxtStr = txtQChan3.Text
         End If
         
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

'Display value.
If ChTyp = "I" Then
   txtIChanHex.Text = HexStr
Else
   txtQChanHex.Text = HexStr
End If

End Sub

Public Sub ORR_Update()

'This procedure updates the 8-bit binary number
'for output amplitude ramp rate.

Dim HexStr As String, TmpStr As String, BytStr As String
Dim I As Integer

'Get hex value string.
HexStr = txtORRHex.Text

'If needed then prepend with zeros.
If Len(HexStr) < 2 Then

   HexStr = String(2 - Len(HexStr), 48) & HexStr

   'Rewrite to screen.
   txtORRHex.Text = HexStr
   
End If

'Initialize byte string.
BytStr = ""

'Process hex digits.
For I = 1 To 2

   TmpStr = Mid(HexStr, I, 1)
   
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
   
Next I

'Write out binary values.
txtORR1.Text = Mid(BytStr, 1, 4)
txtORR2.Text = Mid(BytStr, 5, 4)

End Sub

Public Sub ORRHex_Update()

'This procedure calculates the hex equivalent
'of the 8-bit binary output amplitude ramp rate.

Dim TxtStr As String, TmpStr As String, HexStr As String
Dim I As Integer, J As Integer, Wrd As Integer

'Initialize.
HexStr = ""

'For two hex digits.
For I = 1 To 2

   'Get current binary bits.
   Select Case I
      
      Case 1
         TxtStr = txtORR1.Text
      Case 2
         TxtStr = txtORR2.Text
         
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

'Display value.
txtORRHex.Text = HexStr

End Sub

Public Sub cmdAmpLoad_Click()

Dim IntVal As Integer
Dim TmpStr As String

'If parallel mode.
If PMode = 16 Then

   'Write I channel.
   TmpStr = "0000" & txtIChan1.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 33

   TmpStr = txtIChan2.Text & txtIChan3.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 34
      
   'Write Q channel.
   TmpStr = "0000" & txtQChan1.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 35

   TmpStr = txtQChan2.Text & txtQChan3.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 36
      
   'Write ramp rate registers.
   TmpStr = txtORR1.Text & txtORR2.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 37
      
   'Write control register 32
   If frmControl.chkBypInvSinc.Value = 0 Then
      IntVal = 0
   Else
      IntVal = 64
   End If

   If optOutAmpProg.Value = True Then
      IntVal = IntVal + 32
      End If
         
   If optUseRamp.Value = True Then
      IntVal = IntVal + 16
      End If
         
   If frmControl.chkLSB1st = 1 Then
      IntVal = IntVal + 2
      End If
         
   If frmControl.opt3WireSerial = True Then
      IntVal = IntVal + 1
      End If
         
   'Write control byte.
   PWrite IntVal, 32
      
'Else serial mode.
Else

   TmpStr = "0000" & txtIChan1.Text & txtIChan2.Text & txtIChan3.Text
   SWrite TmpStr, "1000"
      
   TmpStr = "0000" & txtQChan1.Text & txtQChan2.Text & txtQChan3.Text
   SWrite TmpStr, "1001"
      
   TmpStr = txtORR1.Text & txtORR2.Text
   SWrite TmpStr, "1010"
      
   'Get control register string.
   GetSerMdeStr TmpStr
      
   'Write updated control register.
   SWrite TmpStr, "0111"
      
End If

End Sub

Public Sub Form_Load()

Height = 5325
Width = 4350
Left = 100
Top = 3375

End Sub

Public Sub optUseFixed_Click()

   'Disable ramp rate controls.
   txtORR1.Enabled = False
   txtORR2.Enabled = False
   txtORRHex.Enabled = False
   lblORR.Enabled = False
   lblORREql.Enabled = False
   lblORRHex.Enabled = False
   
   'Enable fixed value controls.
   txtIChan1.Enabled = True
   txtIChan2.Enabled = True
   txtIChan3.Enabled = True
   txtIChanHex.Enabled = True
   lblIChanHex.Enabled = True
   lblIChanMult.Enabled = True
   txtQChan1.Enabled = True
   txtQChan2.Enabled = True
   txtQChan3.Enabled = True
   txtQChanHex.Enabled = True
   lblQChanHex.Enabled = True
   lblQChanMult.Enabled = True
   
End Sub

Public Sub optOutAmpFS_Click()

   'Disable option controls.
   optUseFixed.Enabled = False
   optUseRamp.Enabled = False

   'Disable fixed value controls.
   txtIChan1.Enabled = False
   txtIChan2.Enabled = False
   txtIChan3.Enabled = False
   txtIChanHex.Enabled = False
   lblIChanHex.Enabled = False
   lblIChanMult.Enabled = False
   txtQChan1.Enabled = False
   txtQChan2.Enabled = False
   txtQChan3.Enabled = False
   txtQChanHex.Enabled = False
   lblQChanHex.Enabled = False
   lblQChanMult.Enabled = False
   
   'Disable ramp rate controls.
   txtORR1.Enabled = False
   txtORR2.Enabled = False
   txtORRHex.Enabled = False
   lblORR.Enabled = False
   lblORREql.Enabled = False
   lblORRHex.Enabled = False
   
End Sub

Public Sub optOutAmpProg_Click()

   'Enable option controls.
   optUseFixed.Enabled = True
   optUseRamp.Enabled = True

   If optUseFixed.Value = True Then
   
      'Enable fixed value controls.
      txtIChan1.Enabled = True
      txtIChan2.Enabled = True
      txtIChan3.Enabled = True
      txtIChanHex.Enabled = True
      lblIChanHex.Enabled = True
      lblIChanMult.Enabled = True
      txtQChan1.Enabled = True
      txtQChan2.Enabled = True
      txtQChan3.Enabled = True
      txtQChanHex.Enabled = True
      lblQChanHex.Enabled = True
      lblQChanMult.Enabled = True
      
   Else
   
      'Enable ramp rate controls.
      txtORR1.Enabled = True
      txtORR2.Enabled = True
      txtORRHex.Enabled = True
      lblORR.Enabled = True
      lblORREql.Enabled = True
      lblORRHex.Enabled = True
      
   End If
      
End Sub

Public Sub optUseRamp_Click()

   'Disable fixed value controls.
   txtIChan1.Enabled = False
   txtIChan2.Enabled = False
   txtIChan3.Enabled = False
   txtIChanHex.Enabled = False
   lblIChanHex.Enabled = False
   lblIChanMult.Enabled = False
   txtQChan1.Enabled = False
   txtQChan2.Enabled = False
   txtQChan3.Enabled = False
   txtQChanHex.Enabled = False
   lblQChanHex.Enabled = False
   lblQChanMult.Enabled = False
   
   'Enable ramp rate controls.
   txtORR1.Enabled = True
   txtORR2.Enabled = True
   txtORRHex.Enabled = True
   lblORR.Enabled = True
   lblORREql.Enabled = True
   lblORRHex.Enabled = True
   
End Sub

Public Sub txtIChan1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtIChan1.Text) < 4 Then
      
         txtIChan1.Text = txtIChan1.Text & String(4 - Len(txtIChan1.Text), 48)
         
      End If
      
      ChanHex_Update "I"
      cmdAmpLoad.SetFocus
End Select

End Sub

Public Sub txtIChan2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtIChan2.Text) < 4 Then
      
         txtIChan2.Text = txtIChan2.Text & String(4 - Len(txtIChan2.Text), 48)
         
      End If
      
      ChanHex_Update "I"
      cmdAmpLoad.SetFocus

End Select

End Sub

Public Sub txtIChan3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtIChan3.Text) < 4 Then
      
         txtIChan3.Text = txtIChan3.Text & String(4 - Len(txtIChan3.Text), 48)
         
      End If
      
      ChanHex_Update "I"
      cmdAmpLoad.SetFocus

End Select


End Sub

Public Sub txtIChanHex_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only hex
'characters "0" to "F" plus BS, DEL, and CR.

Select Case KeyAscii
      
   Case Is < 8, 9 To 12, 14 To 47, 58 To 64, 71 To 96, Is > 102
   
      KeyAscii = 0
      
   Case 97 To 102
   
      KeyAscii = KeyAscii - 32
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtIChanHex.Text) < 3 Then
      
         txtIChanHex.Text = String(3 - Len(txtIChanHex.Text), 48) & txtIChanHex.Text
         
      End If
      
      Chan_Update "I"
      cmdAmpLoad.SetFocus
      
End Select

End Sub

Public Sub txtORR1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtORR1.Text) < 4 Then
      
         txtORR1.Text = txtORR1.Text & String(4 - Len(txtORR1.Text), 48)
         
      End If
      
      ORRHex_Update
      cmdAmpLoad.SetFocus
      
End Select

End Sub

Public Sub txtORR2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtORR2.Text) < 4 Then
      
         txtORR2.Text = txtORR2.Text & String(4 - Len(txtORR2.Text), 48)
         
      End If
      
      ORRHex_Update
      cmdAmpLoad.SetFocus
      
End Select

End Sub

Public Sub txtORRHex_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only hex
'characters "0" to "F" plus BS, DEL, and CR.

Select Case KeyAscii
      
   Case Is < 8, 9 To 12, 14 To 47, 58 To 64, 71 To 96, Is > 102
   
      KeyAscii = 0
      
   Case 97 To 102
   
      KeyAscii = KeyAscii - 32
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtORRHex.Text) < 2 Then
      
         txtORRHex.Text = String(2 - Len(txtORRHex.Text), 48) & txtORRHex.Text
         
      End If
      
      ORR_Update
      cmdAmpLoad.SetFocus
      
End Select

End Sub

Public Sub txtQChan1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtQChan1.Text) < 4 Then
      
         txtQChan1.Text = txtQChan1.Text & String(4 - Len(txtQChan1.Text), 48)
         
      End If
      
      ChanHex_Update "Q"
      cmdAmpLoad.SetFocus

End Select

End Sub

Public Sub txtQChan2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtQChan2.Text) < 4 Then
      
         txtQChan2.Text = txtQChan2.Text & String(4 - Len(txtQChan2.Text), 48)
         
      End If
      
      ChanHex_Update "Q"
      cmdAmpLoad.SetFocus
      
End Select

End Sub

Public Sub txtQChan3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtQChan3.Text) < 4 Then
      
         txtQChan3.Text = txtQChan3.Text & String(4 - Len(txtQChan3.Text), 48)
         
      End If
      
      ChanHex_Update "Q"
      cmdAmpLoad.SetFocus
      
End Select

End Sub

Public Sub txtQChanHex_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only hex
'characters "0" to "F" plus BS, DEL, and CR.

Select Case KeyAscii
      
   Case Is < 8, 9 To 12, 14 To 47, 58 To 64, 71 To 96, Is > 102
   
      KeyAscii = 0
      
   Case 97 To 102
   
      KeyAscii = KeyAscii - 32
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtQChanHex.Text) < 3 Then
      
         txtQChanHex.Text = String(3 - Len(txtQChanHex.Text), 48) & txtQChanHex.Text
         
      End If
      
      Chan_Update "Q"
      cmdAmpLoad.SetFocus
      
End Select

End Sub
Sub sendAmplitudeToDUT()

    Call cmdAmpLoad_Click
    
End Sub


