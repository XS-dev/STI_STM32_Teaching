VERSION 5.00
Begin VB.Form frmDebug 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Debug"
   ClientHeight    =   2895
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4470
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   2895
   ScaleWidth      =   4470
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Visible         =   0   'False
   Begin VB.TextBox txtCountry 
      Height          =   285
      Left            =   840
      Locked          =   -1  'True
      TabIndex        =   4
      Top             =   2400
      Width           =   3495
   End
   Begin VB.TextBox txtReadBackVals 
      BeginProperty Font 
         Name            =   "Terminal"
         Size            =   9
         Charset         =   255
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1215
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Top             =   840
      Width           =   4215
   End
   Begin VB.CheckBox chkOptoisolatorBoard 
      Caption         =   "Optoisolator Board Mode"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2175
   End
   Begin VB.Label lblCountry 
      Caption         =   "Country:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   2400
      Width           =   615
   End
   Begin VB.Label lblRDBVs 
      Caption         =   "CheckConnection() - Readback Values"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   4215
   End
End
Attribute VB_Name = "frmDebug"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long

Private Const GWL_HWNDPARENT = (-8)
Private OldParent As Long

Private Sub chkOptoisolatorBoard_Click()
    'Set the optoisolator board mode
    OptoBoardFlag = chkOptoisolatorBoard.Value
    If OptoBoardFlag Then
        DeelayValue = 15000
    Else
        DeelayValue = 500
    End If
End Sub

Private Sub Form_Load()
    Me.Top = 0
    Me.Left = 0
    
    'Make the form modeless "a tool window"
    OldParent = SetWindowLong(Me.hwnd, GWL_HWNDPARENT, MDI_Main.hwnd)
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'Make the form modeless "a tool window"
    Call SetWindowLong(Me.hwnd, GWL_HWNDPARENT, OldParent)

End Sub
