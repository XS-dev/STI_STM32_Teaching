VERSION 5.00
Begin VB.Form frmSaveRegister 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Save Registers"
   ClientHeight    =   3405
   ClientLeft      =   45
   ClientTop       =   285
   ClientWidth     =   5835
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   3405
   ScaleWidth      =   5835
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdCancelRegSave 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3720
      TabIndex        =   5
      Top             =   2880
      Width           =   1935
   End
   Begin VB.CommandButton cmdRegSave 
      Caption         =   "Save"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   2880
      Width           =   1935
   End
   Begin VB.DirListBox dirListRegSave 
      Height          =   1665
      Left            =   3000
      TabIndex        =   3
      Top             =   600
      Width           =   2640
   End
   Begin VB.DriveListBox drvListRegSave 
      Height          =   315
      Left            =   840
      TabIndex        =   2
      Top             =   120
      Width           =   4815
   End
   Begin VB.TextBox txtFileToSaveReg 
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
      Left            =   1200
      TabIndex        =   1
      Text            =   "Registers.txt"
      Top             =   2400
      Width           =   4455
   End
   Begin VB.FileListBox filListRegSave 
      Height          =   1650
      Left            =   240
      Pattern         =   "*.txt; *.54s"
      TabIndex        =   0
      Top             =   600
      Width           =   2640
   End
   Begin VB.Label Label1 
      Caption         =   "Save in:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   120
      Width           =   855
   End
   Begin VB.Label lblFileName 
      Caption         =   "File Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   2520
      Width           =   975
   End
End
Attribute VB_Name = "frmSaveRegister"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdCancelRegSave_Click()
    
    frmSaveRegister.Hide
    
End Sub

Private Sub cmdRegSave_Click()
    Dim RegFileName, RegName, RegVal As String
    If Right(dirListRegSave.Path, 1) = "\" Then
        RegFileName = dirListRegSave.Path & txtFileToSaveReg.Text
    Else
        RegFileName = dirListRegSave.Path & "\" & txtFileToSaveReg.Text
    End If
    
    If Right(RegFileName, 4) = ".txt" Then
        RegFileName = RegFileName
    Else
        RegFileName = RegFileName & ".txt"
    End If
    Open RegFileName For Output As #99
    Write #99, "AD9854 Register State"
    Write #99, "---------------------------------------------------------------"
    Write #99, "Phase Adjust Register One ", frmReadBack.txt0000_1, frmReadBack.txt0000_2
    Write #99, "Phase Adjust Register Two ", frmReadBack.txt0001_1, frmReadBack.txt0001_2
    Write #99, "Frequency Tuning Word One ", frmReadBack.txt0010_1, frmReadBack.txt0010_2, frmReadBack.txt0010_3, frmReadBack.txt0010_4, frmReadBack.txt0010_5, frmReadBack.txt0010_6
    Write #99, "Frequency Tuning Word Two ", frmReadBack.txt0011_1, frmReadBack.txt0011_2, frmReadBack.txt0011_3, frmReadBack.txt0011_4, frmReadBack.txt0011_5, frmReadBack.txt0011_6
    Write #99, "Frequency Step Word       ", frmReadBack.txt0100_1, frmReadBack.txt0100_2, frmReadBack.txt0100_3, frmReadBack.txt0100_4, frmReadBack.txt0100_5, frmReadBack.txt0100_6
    Write #99, "Update Clock Counter      ", frmReadBack.txt0101_1, frmReadBack.txt0101_2, frmReadBack.txt0101_3, frmReadBack.txt0101_4
    Write #99, "Frequency Step Rate       ", frmReadBack.txt0110_1, frmReadBack.txt0110_2, frmReadBack.txt0110_3
    Write #99, "Control Register          ", frmReadBack.txt0111_1, frmReadBack.txt0111_2, frmReadBack.txt0111_3, frmReadBack.txt0111_4
    Write #99, "I-Channel Multiplier      ", frmReadBack.txt1000_1, frmReadBack.txt1000_2
    Write #99, "Q-Channel Multiplier      ", frmReadBack.txt1001_1, frmReadBack.txt1001_2
    Write #99, "Ramp Rate                 ", frmReadBack.txt1010_1
    Write #99, "Q-DAC Register            ", frmReadBack.txt1011_1, frmReadBack.txt1011_2
    
    frmSaveRegister.Hide
    Unload frmSaveRegister
    Close #99
End Sub

Private Sub cmdRegSave_KeyPress(KeyAscii As Integer)

    Call cmdRegSave_Click

End Sub

Private Sub dirListRegSave_Change()
    
    filListRegSave.Path = dirListRegSave.Path
    txtFileToSaveReg.Text = filListRegSave.FileName
    
End Sub

Private Sub drvListRegSave_Change()
    
    dirListRegSave.Path = drvListRegSave.Drive
    
End Sub

Private Sub filListRegSave_Click()

    txtFileToSaveReg.Text = filListRegSave.FileName
    
End Sub

Private Sub filListRegSave_DblClick()
    
    Call cmdRegSave_Click
    
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

Private Sub txtFileToSaveReg_KeyPress(KeyAscii As Integer)
    
    If KeyAscii = 13 Then
        Call cmdRegSave_Click
    End If
    
End Sub
