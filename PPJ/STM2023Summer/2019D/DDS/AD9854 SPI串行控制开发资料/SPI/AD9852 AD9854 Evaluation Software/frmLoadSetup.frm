VERSION 5.00
Begin VB.Form frmLoadSetup 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Load Setup File"
   ClientHeight    =   3375
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5955
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
   ScaleHeight     =   3375
   ScaleWidth      =   5955
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox txtFileToOpen 
      Height          =   375
      Left            =   1200
      TabIndex        =   7
      Top             =   2400
      Width           =   4575
   End
   Begin VB.FileListBox filListLoad 
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
      Left            =   135
      Pattern         =   "*.54s"
      TabIndex        =   6
      Top             =   570
      Width           =   2640
   End
   Begin VB.CommandButton cmdCancelLoad 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3840
      TabIndex        =   3
      Top             =   2880
      Width           =   1935
   End
   Begin VB.CommandButton cmdLoadSetup 
      Caption         =   "Load"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   2880
      Width           =   1935
   End
   Begin VB.DirListBox dirListLoad 
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
      Left            =   2880
      TabIndex        =   1
      Top             =   600
      Width           =   2895
   End
   Begin VB.DriveListBox drvListLoad 
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
      Left            =   1080
      TabIndex        =   0
      Top             =   120
      Width           =   4695
   End
   Begin VB.Label Label1 
      Caption         =   "File Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   2520
      Width           =   975
   End
   Begin VB.Label lblDir 
      Caption         =   "Look in:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   120
      Width           =   735
   End
End
Attribute VB_Name = "frmLoadSetup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub cmdCancelLoad_Click()

    frmLoadSetup.Hide
    Unload frmLoadSetup
    
End Sub


Private Sub cmdLoadSetup_Click()
    
    Call filListLoad_DblClick
    
End Sub

Private Sub cmdLoadSetup_KeyPress(KeyAscii As Integer)
    
    If KeyAscii = 13 Then
        Call cmdLoadSetup_Click
    End If
        
End Sub

Private Sub dirListLoad_Change()
    
    filListLoad.Path = dirListLoad.Path
    txtFileToOpen.Text = filListLoad.Path
    
End Sub

Private Sub drvListLoad_Change()

    dirListLoad.Path = drvListLoad.Drive
    
End Sub



Private Sub filListLoad_Click()
    
    txtFileToOpen.Text = filListLoad.FileName
    
End Sub

Private Sub filListLoad_DblClick()

    Dim LoadInfo, LoadVal, FileName As String
    If txtFileToOpen.Text = "" Then
        MsgBox "Please enter a file name to load."
    Else: txtFileToOpen.Text = filListLoad.FileName
    
        Call frmFrequency.resetTheDut
    
        FileName = dirListLoad.Path & "\" & txtFileToOpen.Text
    
        'Read the file line by line and set the values
            Open FileName For Input As #33
            Input #33, LoadInfo
            If LoadInfo = "AD9854" Then
                frmLoadSetup.Tag = "Valid"
             
            'Form: Amplitude
                Input #33, LoadInfo, LoadVal
                If LoadVal = True Then
                    frmAmplitude.optOutAmpProg = True
                Else
                    frmAmplitude.optOutAmpFS = True
                End If
                
                Input #33, LoadInfo, LoadVal
                If LoadVal = True Then
                    frmAmplitude.optUseFixed = True
                Else
                    frmAmplitude.optUseRamp = True
                End If
         
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtIChan1 = LoadVal
        
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtIChan2 = LoadVal
        
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtIChan3 = LoadVal
        
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtIChanHex = LoadVal
        
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtQChan1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtQChan2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtQChan3 = LoadVal
             
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtQChanHex = LoadVal
        
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtORR1 = LoadVal
        
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtORR2 = LoadVal
        
                Input #33, LoadInfo, LoadVal
                frmAmplitude.txtORRHex = LoadVal
                
                'Send amplitude information to the DUT
                Call frmAmplitude.sendAmplitudeToDUT
            
                'Form: Clock
                Input #33, LoadInfo, LoadVal
                frmClock.chkBypassPLL = LoadVal
            
                Input #33, LoadInfo, LoadVal
                If LoadVal = True Then
                    frmClock.optPLL_Lo = True
                Else
                    frmClock.optPLL_Hi = True
                End If
                
                Input #33, LoadInfo, LoadVal
                frmClock.txtClock = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmClock.txtPLL = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmClock.txtUDCLK1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmClock.txtUDCLK2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmClock.txtUDCLK3 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmClock.txtUDCLK4 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmClock.txtUDCLKHex = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmClock.txtUDCLKMHz = LoadVal
                
                Input #33, LoadInfo, LoadVal
                If LoadVal = True Then
                    frmClock.optInternal = True
                Else
                    frmClock.optExternal = True
                End If
                
                'Send clock information to the DUT
                Call frmClock.sendClockToDUT
            
                'Form: Control
                Input #33, LoadInfo, LoadVal
                If LoadVal = "Parallel" Then
                    frmControl.optParallel = True
                Else
                    If LoadVal = "TwoWire" Then
                        frmControl.opt2WireSerial = True
                    Else
                        If LoadVal = "ThreeWire" Then
                            frmControl.opt3WireSerial = True
                    
                        End If
                    End If
                End If
            
                Input #33, LoadInfo, LoadVal
                frmControl.chkLSB1st = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.chkCompPwrDwn = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.chkPllPwrDwn = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.chkQDacPwrDwn = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.chkAllDacPwrDwn = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.chkFulDigPwrDwn = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.chkBypInvSinc = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.chkSrcQDac = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.txtQDac1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.txtQDac2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.txtQDac3 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmControl.txtQDacHex = LoadVal
                
                'Send control information to the DUT
                Call frmControl.sendControlToDUT
            
                'Form: Frequency
                Input #33, LoadInfo, LoadVal
                If LoadVal = "Single Tone" Then
                    frmFrequency.optSingleTone = True
                Else
                    If LoadVal = "Unramped FSK" Then
                        frmFrequency.optUnrampedFSK = True
                    Else
                        If LoadVal = "Ramped FSK" Then
                            frmFrequency.optRampedFSK = True
                        Else
                            If LoadVal = "Chirp" Then
                                frmFrequency.optChirpMode = True
                            Else
                                If LoadVal = "BPSK" Then
                                    frmFrequency.optBPSKmode = True
                                End If
                            End If
                        End If
                    End If
                End If
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW1_1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW1_2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW1_3 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW1_4 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW1_5 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW1_6 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW1MHz = LoadVal
                       
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW2_1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW2_2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW2_3 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW2_4 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW2_5 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW2_6 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFTW2MHz = LoadVal
        
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSW1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSW2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSW3 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSW4 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSW5 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSW6 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSWMHz = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSR1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSR2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSR3 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSR4 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSR5 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtFSRHex = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj1_1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj1_2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj1_3 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj1_4 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj1Hex = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj2_1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj2_2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj2_3 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj2_4 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.txtPhAdj2Hex = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.chkTriangle = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.chkACC1 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                frmFrequency.chkACC2 = LoadVal
            
                Input #33, LoadInfo, LoadVal
                If LoadVal = True Then
                    frmFrequency.optFDataHi = True
                Else
                    frmFrequency.optFDataLo = True
                End If
            
                Input #33, LoadInfo, LoadVal
                If LoadVal = True Then
                    frmFrequency.optORampHi = True
                Else
                    frmFrequency.optORampLo = True
                End If
                
                Close 33
                
                frmLoadSetup.Hide
                Unload frmLoadSetup
                
                'Send the information to the DUT
                Call frmFrequency.sendFreqToDUT
                
            Else: frmLoadSetup.Tag = "Invalid"
            End If
                If frmLoadSetup.Tag = "Invalid" Then
                    Close 33
                    MsgBox "Error: The file you have chosen is not a valid setup file"
                End If
        End If
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

Private Sub txtFileToOpen_KeyPress(KeyAscii As Integer)
    
    If KeyAscii = 13 Then
        Call cmdLoadSetup_Click
    End If
    
End Sub
