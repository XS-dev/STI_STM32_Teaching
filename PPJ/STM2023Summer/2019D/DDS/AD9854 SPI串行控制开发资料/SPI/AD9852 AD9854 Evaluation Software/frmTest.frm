VERSION 5.00
Begin VB.Form frmTest 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Test Form"
   ClientHeight    =   1695
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3765
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   1695
   ScaleWidth      =   3765
   Begin VB.Frame fraTest 
      Height          =   1455
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3495
      Begin VB.Timer tmrToggleACCBits 
         Interval        =   1
         Left            =   2760
         Top             =   240
      End
      Begin VB.CheckBox chkACC2 
         Caption         =   "Toggle ACC2"
         Height          =   255
         Left            =   360
         TabIndex        =   3
         Top             =   480
         Width           =   1335
      End
      Begin VB.CheckBox chkACC1 
         Caption         =   "Toggle ACC1"
         Height          =   255
         Left            =   360
         TabIndex        =   2
         Top             =   240
         Width           =   1335
      End
      Begin VB.CheckBox chkToggleACCBits 
         Caption         =   "Begin Toggleing ACC Bits"
         Height          =   495
         Left            =   240
         Style           =   1  'Graphical
         TabIndex        =   1
         Top             =   840
         Width           =   3015
      End
   End
End
Attribute VB_Name = "frmTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Frame1_DragDrop(Source As Control, X As Single, Y As Single)

End Sub

Private Sub chkToggleACCBits_Click()
    If chkToggleACCBits Then
        chkToggleACCBits.Caption = "Stop Toggleing ACC Bits"
    Else
        chkToggleACCBits.Caption = "Begin Toggleing ACC Bits"
    End If
End Sub

Private Sub tmrToggleACCBits_Timer()
    If (chkACC1.Value Or chkACC2.Value) Then
        chkToggleACCBits.Enabled = True
    Else
        If chkToggleACCBits.Value = 0 Then
            chkToggleACCBits.Enabled = False
        End If
    End If
    If chkToggleACCBits.Value Then
        If chkACC1.Value Then
            If frmFrequency.chkACC1.Value Then
                frmFrequency.chkACC1.Value = 0
            Else
                frmFrequency.chkACC1.Value = 1
            End If
        End If
        If chkACC2.Value Then
            If frmFrequency.chkACC2.Value Then
                frmFrequency.chkACC2.Value = 0
            Else
                frmFrequency.chkACC2.Value = 1
            End If
        End If
        
        'Load the new bit values
        frmFrequency.cmdLoad_Click
        'Send update clock
        frmClock.cmdSendUDCLK_Click
    End If
End Sub
