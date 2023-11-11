VERSION 5.00
Begin VB.MDIForm MDI_Main 
   AutoShowChildren=   0   'False
   BackColor       =   &H8000000C&
   Caption         =   "AD9852/54 Customer Evaluation Software"
   ClientHeight    =   7380
   ClientLeft      =   2175
   ClientTop       =   2640
   ClientWidth     =   10380
   Icon            =   "MDI_Main.frx":0000
   LinkTopic       =   "MDIForm1"
   Begin VB.Menu mnuFile 
      Caption         =   "&Setup File"
      Begin VB.Menu mnuLoadSetup 
         Caption         =   "&Load Setup File"
      End
      Begin VB.Menu mnuSaveSetup 
         Caption         =   "&Save Setup File"
      End
      Begin VB.Menu mnuSaveRegisterInfo 
         Caption         =   "Save &Registers"
      End
   End
   Begin VB.Menu mnuPPort 
      Caption         =   "&Parallel Port"
      Begin VB.Menu mnuPPortSelPPort 
         Caption         =   "&Select Parallel Port"
      End
      Begin VB.Menu mnuPPortFndPPort 
         Caption         =   "&Find Parallel Port"
      End
      Begin VB.Menu mnuPPortChkPPortCon 
         Caption         =   "&Check Parallel Port Connection"
      End
   End
   Begin VB.Menu mnuMode 
      Caption         =   "&Mode and Frequency"
   End
   Begin VB.Menu mnuClock 
      Caption         =   "&Clock and Amplitude"
   End
   Begin VB.Menu mnuReadBackRegister 
      Caption         =   "&Register Readback"
   End
   Begin VB.Menu mnuAbout 
      Caption         =   "&About"
   End
   Begin VB.Menu mnuQuit 
      Caption         =   "&Quit"
   End
   Begin VB.Menu mnuReset 
      Caption         =   "Reset"
      Visible         =   0   'False
   End
End
Attribute VB_Name = "MDI_Main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit                         'Declare all variables.
Option Base 1                           'Lower array index = 1.

Dim LocaleInfo As adiLocaleInfo

Public Sub MDIForm_Load()
   'string varaiable to hold the lptselectdialog message
   Dim LPTMenuMsg As String
'   Dim FndCnct As Boolean
'   Dim fndcnctcancelhit As Boolean
   
   'Setup the localeinfo object
   Set LocaleInfo = New adiLocaleInfo
   'Use the users locale info
   LocaleInfo.LCID = UserDef
   
   'Get the locale info used in the program
   MyLocInfo.sCountry = LocaleInfo.GetLocaleInfo(adiCountry)
   MyLocInfo.sDecSep = LocaleInfo.GetLocaleInfo(adiDecimalSep)
   MyLocInfo.iDecSep = Asc(MyLocInfo.sDecSep)
   MyLocInfo.sNegSign = LocaleInfo.GetLocaleInfo(adiNegSign)
   
   'Release the localeinfo object
   Set LocaleInfo = Nothing
   
   'Display debug info
   If DebugFlag Then
      frmDebug.txtCountry = MyLocInfo.sCountry
   End If
   
   'Set window size to normal.
   MDI_Main.WindowState = 0

   'Set window dimensions.
   Height = 8400
   Width = 10500
   'Center in the screen using largest height and width
   Top = (Screen.Height - 9500) / 2 '200
   Left = (Screen.Width - Me.Width) / 2 '200
   'Make sure that the form isn't too high
   If Top < 0 Then Top = 0

'    Height = 9500

   'Initialize global variables.
   LPTPort = &H3BC
   LSB1st = 0
   PMode = 16
   FData = 0
   ORamp = 0
   RBE = 0&

   'Initialize PLL value to four.
   OldPll = "04"
   
   'Build the dialog message
   LPTMenuMsg = "Select a parallel printer port." & vbCrLf
   LPTMenuMsg = LPTMenuMsg & "Use device "
   
   'Initialize the LPT Port selection menu
   Call frmLPTSelect.LPTSelectDialog("LPT Port Selection Menu", "Select a LPT - (Parallel Printer) port.", False, 1)
   'Set the form up to center in the main window
   'frmLPTSelect.StartUpPosition = 1
      
   'Initialize parallel port.
   InitPort

   'Load all forms.
   Load frmFrequency
   Load frmClock
   Load frmControl
   Load frmAmplitude
   Load frmReadBack
   Load frmAbout

   'Show first form.
   frmFrequency.Show

   'Set focus.
   frmFrequency.cmdLoad.SetFocus

   'Check for a connection
    mnuPPortFndPPort_Click
'   FndCnct = FindConnection(fndcnctcancelhit)
'    If fndcnctcancelhit = False And FndCnct = False Then
'        MsgBox "No conneciton found!!!", vbInformation + vbOKOnly + vbApplicationModal, "Warning!!!"
'    End If

End Sub

Private Sub MDIForm_Unload(Cancel As Integer)
   'Unload Non Mdi Forms
   Unload frmLPTSelect
   Unload frmDebug
   Unload frmAbout
End Sub

Public Sub mnuAbout_Click()

   frmAbout.Show 1
   
End Sub

Private Sub mnuLoadSetup_Click()
    
    Load frmLoadSetup
    frmLoadSetup.Show
    ChDrive App.Path
    ChDir App.Path
    frmLoadSetup.txtFileToOpen.SetFocus
    frmLoadSetup.txtFileToOpen.Text = ""
        
End Sub

'Public Sub mnuLPT1_Click()
'
'   mnuPRN.Checked = False
'   mnuLPT2.Checked = False
'   mnuLPT1.Checked = True
'
'   LPTPort = &H378
'   InitPort
'
'End Sub
'
'Public Sub mnuLPT2_Click()
'
'   mnuPRN.Checked = False
'   mnuLPT2.Checked = True
'   mnuLPT1.Checked = False
'
'   LPTPort = &H278
'   InitPort
'
'End Sub
'
'Public Sub mnuPRN_Click()
'
'   mnuPRN.Checked = True
'   mnuLPT2.Checked = False
'   mnuLPT1.Checked = False
'
'   LPTPort = &H3BC
'   InitPort
'
'End Sub

Public Sub mnuClock_Click()

   If MDI_Main.WindowState = 0 Then

      Height = 9500
      Width = 10150
      
      End If
   
   frmFrequency.Hide
   frmReadBack.Hide

   frmClock.Show
   frmControl.Show
   frmAmplitude.Show
   
   frmClock.cmdLoadPLL.SetFocus

End Sub

Public Sub mnuMode_Click()

   If MDI_Main.WindowState = 0 Then

      Height = 8400
      Width = 10495
      
      End If
   
   frmClock.Hide
   frmControl.Hide
   frmAmplitude.Hide
   frmReadBack.Hide

   frmFrequency.Show
   
   frmFrequency.cmdLoad.SetFocus
   
End Sub

Public Sub mnuReadBack_Click()

   If MDI_Main.WindowState = 0 Then
   
      Height = 7650
      Width = 9750
      
      End If
   
   frmFrequency.Hide
   frmClock.Hide
   frmControl.Hide
   frmAmplitude.Hide

   frmReadBack.Show
   
   frmReadBack.cmdReadBack.SetFocus
   
End Sub

Private Sub mnuPPortChkPPortCon_Click()
    Dim MsgStr As String
    Dim MsgBoxRetVal As Integer
    
    'Initialize the message string
    MsgStr = vbNullString
    
    'Display a message box
    MsgStr = MsgStr & "This operation will reset the AD9852/54 and the software!!!" & vbCrLf & vbCrLf
    MsgStr = MsgStr & "Do you want to continue?"
    MsgBoxRetVal = MsgBox(MsgStr, vbQuestion + vbApplicationModal + vbYesNo, "Check Connection?")
    If MsgBoxRetVal = vbNo Then
        'If the user clicks no then exit the funtion now
        Exit Sub
    End If
    
    MsgStr = vbNullString
    'Check connection to the evaluation board
    If CheckConnection() Then
        MsgStr = MsgStr & "The currently selected parallel port is connected" & vbCrLf
        MsgStr = MsgStr & "to a functioning evaluation board."
        MsgBox MsgStr, vbApplicationModal + vbInformation + vbDefaultButton1 + vbOKOnly, "Connection OK!!!"
    Else
        MsgStr = MsgStr & "The currently selected parallel port is not" & vbCrLf
        MsgStr = MsgStr & "properly connected to an evaluaiton board." & vbCrLf & vbCrLf
        MsgStr = MsgStr & "Make sure that the parallel port cable is connected" & vbCrLf
        MsgStr = MsgStr & "and the evaluation board is powered up or try another" & vbCrLf
        MsgStr = MsgStr & "parallel port."
        MsgBox MsgStr, vbApplicationModal + vbExclamation + vbOKOnly, "Bad Connection!!!"
    End If
End Sub

Private Sub mnuPPortFndPPort_Click()
    Dim FndCnct As Boolean
    Dim FndCnctCancelHit As Boolean
   
    'Check for a connection
'    If frmLPTSelect.LPTGetPortCount() > 1 Then
    FndCnct = FindConnection(FndCnctCancelHit)
    If FndCnctCancelHit = False And FndCnct = False Then
        MsgBox "No conneciton found!!!", vbInformation + vbOKOnly + vbApplicationModal, "Warning!!!"
    End If
'    End If
End Sub

Private Sub mnuPPortSelPPort_Click()
    Call frmLPTSelect.LPTSelectDialog("LPT Port Selection Menu", "Select a LPT - (Parallel Printer) port.", True)
End Sub

Public Sub mnuQuit_Click()
'9
   'Make sure that the unload event occurs
   Unload Me
   End

End Sub

Private Sub mnuReadBackRegister_Click()
    
    Call mnuReadBack_Click
    
End Sub

Private Sub mnuReset_Click()
    
    frmFrequency.cmdReset_Click
End Sub

Private Sub mnuSaveRegisterInfo_Click()

    Load frmSaveRegister
    frmSaveRegister.Show
    ChDrive App.Path
    ChDir App.Path
    frmSaveRegister.txtFileToSaveReg.SetFocus
    frmSaveRegister.txtFileToSaveReg.Text = ""

End Sub

Private Sub mnuSaveSetup_Click()

    Load frmSaveSetup
    frmSaveSetup.Show
    ChDrive App.Path
    ChDir App.Path
    frmSaveSetup.txtFileToSave.SetFocus
    frmSaveSetup.txtFileToSave.Text = ""
    
End Sub



