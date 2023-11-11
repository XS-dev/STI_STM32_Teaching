VERSION 5.00
Object = "{9504898C-33FD-11D1-8F93-EC6D05C10000}#1.0#0"; "dxocx.dll"
Begin VB.Form frmLPTSelect 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Select Port"
   ClientHeight    =   3885
   ClientLeft      =   5025
   ClientTop       =   4185
   ClientWidth     =   5235
   Icon            =   "frmDXLPTSelect.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3885
   ScaleWidth      =   5235
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.Frame fraPortList 
      BorderStyle     =   0  'None
      Caption         =   "Frame1"
      Height          =   1815
      Left            =   0
      TabIndex        =   1
      Top             =   960
      Width           =   4455
      Begin VB.CommandButton cmdAdd 
         Caption         =   "&Add Port"
         Height          =   375
         Left            =   120
         TabIndex        =   7
         Top             =   1440
         Width           =   855
      End
      Begin VB.CommandButton cmdRefresh 
         Caption         =   "Refresh"
         Height          =   375
         Left            =   1080
         TabIndex        =   6
         Top             =   1440
         Width           =   855
      End
      Begin VB.CommandButton cmdOK 
         Caption         =   "&Ok"
         Default         =   -1  'True
         Enabled         =   0   'False
         Height          =   375
         Left            =   2040
         TabIndex        =   4
         Top             =   1440
         Width           =   1095
      End
      Begin VB.CommandButton cmdCancel 
         Cancel          =   -1  'True
         Caption         =   "&Cancel"
         Height          =   375
         Left            =   3240
         TabIndex        =   3
         Top             =   1440
         Width           =   1095
      End
      Begin VB.ListBox lstLPTPorts 
         Height          =   1035
         ItemData        =   "frmDXLPTSelect.frx":000C
         Left            =   120
         List            =   "frmDXLPTSelect.frx":001C
         TabIndex        =   2
         Top             =   240
         Width           =   4215
      End
      Begin VB.Label lblPort 
         Caption         =   " Port                    Address        Type"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   0
         Width           =   4215
      End
   End
   Begin DXOCXLibCtl.DxControl dxcParallelPort 
      Left            =   240
      OleObjectBlob   =   "frmDXLPTSelect.frx":00BF
      Top             =   3000
   End
   Begin VB.Image imgIcon 
      Height          =   480
      Left            =   240
      Picture         =   "frmDXLPTSelect.frx":00E3
      Top             =   240
      Width           =   480
   End
   Begin VB.Label lblSPDMessage 
      AutoSize        =   -1  'True
      Caption         =   "Select a parallel printer port."
      Height          =   195
      Left            =   960
      TabIndex        =   0
      Top             =   120
      Width           =   1965
   End
End
Attribute VB_Name = "frmLPTSelect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'***************************************************************************
'* LPTSelect Dialog Form                                                   *
'***************************************************************************
'* This dialog was designed to be used with the Driver X 3.4 Active X      *
'* Control.                                                                *
'* This dialog will supply all Port I/O Functions for accessing the        *
'* printer ports, if a function needed isn't supported this form may be    *
'* modified to supply the needed function as long as the revision is       *
'* and documented.                                                         *
'***************************************************************************
'* Revision 1.0 beta                               Last Modified: 07/16/99 *
'* Revision 1.1 beta                               Last Modified: 08/10/99 *
'* Modification: Removed LPTAddrs array now uses listbox instead           *
'*               Added a product specific device name                      *
'* Revision 1.11 beta                              Last Modified: 08/30/99 *
'* Revision 1.12 Added a WinXP compatability and better error checking     *
'                                                  Last Modified: 09/26/02 *
'* Modification: Added LPTSelect() and LPTGetPortCount methods             *
'***************************************************************************

Private PPDeviceName As String
Private CancelHit As Boolean
'Private LPTAddrs(1 To 4) As Integer

Private PortNotFound As Integer

Public Enum dxLPTRegs
    lpt_bp0_DataReg = 0&
    lpt_bp1_StatusReg = 1&
    lpt_bp2_ControlReg = 2&
End Enum

'After loading the form this property can be checked to see
'if the driver loaded correctly and the status
Public DriverStartupResults As Integer

'Declare Private property variables
Private m_BaseAddr As Long
'Must be set in the load event to a valid device name that appears in the
'registry
Private m_DeviceName As String

'This function will test the address passed and return a
'True if the port address is a Standard Parallel Printer Port or
'a False if it is not or doesn't exist.
'Public Function TestForSPP(ByVal BaseAddress As Integer) As Boolean
'    Dim ReadBackVal As Long
'
'    'Set the Data Outputs Enabled bit write to control port
'    Out32 BaseAddress + 2, &HF
'
'    'Write the test value to the port base address
'    Out32 BaseAddress, &H55
'    'Readback a value from the port base address
'    ReadBackVal = Inp32(BaseAddress)
'
'    'Check to see if the port exists
'    If ReadBackVal = &H55 Then
'        'Write the test value to the port base address
'        Out32 BaseAddress, &HAA
'        'Readback a value from the port base address
'        ReadBackVal = Inp32(BaseAddress)
'        If ReadBackVal = &HAA Then
'            'Yes it does exist
'            TestForSPP = True
'        Else
'            'Test passed
'            TestForSPP = False
'        End If
'    End If
'End Function

Private Function TestForSPP() As Boolean
    Dim ReadBackVal As Long

    'Set the Data Outputs Enabled bit write to control port
    LptOutput lpt_bp2_ControlReg, &HF

    'Write the test value to the port base address
    LptOutput lpt_bp0_DataReg, &H55
    'Readback a value from the port base address
    ReadBackVal = LptInput(lpt_bp0_DataReg)

    'Check to see if the port exists
    If ReadBackVal = &H55 Then
        'Write the test value to the port base address
        LptOutput lpt_bp0_DataReg, &HAA
        'Readback a value from the port base address
        ReadBackVal = LptInput(lpt_bp0_DataReg)
        If ReadBackVal = &HAA Then
            'Yes it does exist
            TestForSPP = True
        Else
            'Test passed
            TestForSPP = False
        End If
    End If
End Function

Private Sub cmdAdd_Click()
    Dim retval As String
    Dim MsgBoxRetVal As Integer
    Dim OldAddress As Long
    
    Dim msg As String
    
    msg = "The address you entered will now be tested!!!" & Chr(13)
    msg = msg & "Only test port addresses that you know are parallel ports." & Chr(13)
    msg = msg & "Testing a port address other than a valid parallel printer port" & Chr(13)
    msg = msg & "address can cause the system to crash and even system damage!" & Chr(13)
    msg = msg & "Press " & Chr(34) & "OK" & Chr(34) & " to continue or " & Chr(34) & "Cancel" & Chr(34) & " to cancel now."
    
    'Show an input box
    retval = InputBox("Please enter the port address in hex.", "Add a Non-Standard Parallel Printer Port")
    retval = "&H" & retval
    
    If retval <> "" Then
        If IsNumeric(retval) Then
            'Check to see if the port is allready in the list
            If IsPortListed(CLng(retval)) Then
                Exit Sub
            End If
            
            'Display the warning message
            MsgBoxRetVal = MsgBox(msg, vbApplicationModal + vbCritical + vbOKCancel, "Warning!!!")
            If MsgBoxRetVal = vbOK Then
                'Store the currently selected address
                OldAddress = LPTBaseAddress
                
                'Plug in the user defined address
                LPTBaseAddress = CLng(retval)
                
                'Test the user definded parallel port
                If TestForSPP Then
                    'If a user defined parallel port has been added then
                    'erase its list entry
                    If lstLPTPorts.Tag = "UDAdded" Then
                        lstLPTPorts.RemoveItem (lstLPTPorts.ListCount - 1)
                    End If
                    
                    lstLPTPorts.AddItem "User Defined" & "     " & Hex(retval) & " Hex        SPP"
                    lstLPTPorts.ItemData(lstLPTPorts.ListCount - 1) = CLng(retval)
                    'LPTAddrs(lstLPTPorts.ListCount) = CLng(retval)
                    lstLPTPorts.Tag = "UDAdded"
                Else
                    'The address failed so show a failure box
                    msg = "The parallel port at address " & Chr(34) _
                          & Hex(CLng(retval)) & " Hex" & Chr(34) & _
                          " failed the Standard Parallel Port test." & Chr(13)
                    msg = msg & "Check your port's address to make sure you typed it right."
                    MsgBox msg, vbInformation + vbApplicationModal + vbOKOnly, "Test Failed!"
                End If
                
                'Reselect the previously selected port
                LPTBaseAddress = OldAddress
            End If
        End If
    End If

End Sub

Private Sub cmdCancel_Click()
    'Hide the dialog
    Me.Hide
    CancelHit = True
End Sub

Private Sub cmdOK_Click()
    'Hide the dialog
    Me.Hide
End Sub

Private Sub cmdRefresh_Click()
    'Refresh the list
    RefreshLPTList
End Sub

Private Sub Form_Load()
    Dim sMsg As String
    Dim cntr As Integer
    'Initialize the private property variables
    m_BaseAddr = -1
    
    If DevName <> "" Then
        'Use the product
        m_DeviceName = DevName
    Else
        'Initialize the forms internal variables
        m_DeviceName = "AD9854PP" 'Name this whatever the product name is plus PP
                                  'Ex: AD9854PP
    End If
    
    'Initialize the Driver X Driver
    'Check to see if the driver is configured
    'dxcParallelPort.ConfigureDriver
'    If dxcParallelPort.IsDriverConfigured() = False Then
'        'Display an error message
'        MsgBox "The driver is not configured!!!" & Chr(13) & "Quiting program now!!!", vbApplicationModal + vbCritical + vbOKOnly, "Critical Error!!!"
'    End If
'
'    'Check to see if the device is running
'    If dxcParallelPort.IsDeviceRunning(m_DeviceName) = False Then
'        If dxcParallelPort.StartDevice(m_DeviceName) = False Then
'            MsgBox "Can't start device " & Chr(34) & m_DeviceName & Chr(34) & ".", vbApplicationModal + vbCritical + vbOKOnly, "Fatal Error"
'            'End
'        End If
'    End If
'
'    'Connect to the device
'    If dxcParallelPort.ConnectDevice(m_DeviceName) = False Then
'        'Alert the user
'        MsgBox "Failed to connect to the device: " & m_DeviceName, vbApplicationModal + vbCritical + vbOKOnly, "Fatal Error"
'    Else
'        'Print "Connecting to the device PPort378"
'    End If
    Screen.MousePointer = 11
    For cntr = 0 To 110
        DriverStartupResults = StartupDrvDevice(m_DeviceName)
        If DriverStartupResults = 0 Then
            Exit For
        End If
        lsfDelay (0.5)
    Next cntr
    Screen.MousePointer = 0
    
    Select Case DriverStartupResults
        Case 0 'Sucess
        Case -1 'Failure
            sMsg = "DriverX was not configured." & vbCrLf & vbCrLf & _
                   "An attempt has been made to configure the DriverX driver." & vbCrLf & _
                   "Please reboot so that windows will load the driver."

            MsgBox sMsg, vbApplicationModal + vbCritical, "Fatal Error - Ending Program!"
            End
        Case -2 'Failure
            sMsg = "DriverX was not configured." & vbCrLf & vbCrLf & _
                   "An attempt has been made to configure the DriverX driver" & vbCrLf & _
                   "and the attempt has failed." & vbCrLf & vbCrLf & _
                   "This can be caused by 2 things:" & vbCrLf & _
                   "* If you are not logged in with administrative rights" & vbCrLf & _
                   "  and you are running Windows NT,2K or XP." & vbCrLf & _
                   "* If the file driverx.sys is not located in the WINSYS\SYSTEM32\DRIVERS" & vbCrLf & _
                   "  directory." & vbCrLf & vbCrLf & _
                   "Try reinstalling the software with adminstrative rights."

            MsgBox sMsg, vbApplicationModal + vbCritical, "Fatal Error - Ending Program!"
            End
        Case -3 'Failure
            sMsg = "Could not start DriverX" & vbCrLf & vbCrLf & _
                   "This error may occur on Windows XP machines." & vbCrLf & _
                   "If so, try running the software again."

            MsgBox sMsg, vbApplicationModal + vbCritical, "Fatal Error - Ending Program!"
            End
    End Select
    
    'Detect and update the list of parallel ports
    RefreshLPTList
End Sub
'Delays program execution by the DelayTime
'Input:  DelayTime - Time to delay in Seconds (1ms Resolution in WinNT, 55ms Resolution in Win95)
Private Sub lsfDelay(ByVal DelayTime As Single)
    Dim Start As Single
    Dim OldTimerVal As Single
    Dim EndTime As Single
    Dim Midnight As Boolean
    Dim DelayCntr As Long 'used to make sure that
    
    Midnight = False 'Assume it isn't midnight
    Start = Timer   ' Set start time.
    OldTimerVal = Start 'Set the current timer val
    'Calculate the end time
    EndTime = Start + DelayTime
    
    'Setup the delay cntr
    DelayCntr = 0
    
    Do
        'Check for midnight
        If Timer < OldTimerVal Then
            EndTime = EndTime - OldTimerVal
            DelayCntr = 1000 'It is past midnight so refresh the OldTimerVal
        End If
        
        If DelayCntr >= 1000 Then
            OldTimerVal = Timer 'Get the current timer value
            DelayCntr = 0 'Reset the counter
        End If
           
        'Increment the delay counter
        DelayCntr = DelayCntr + 1
        
        DoEvents   ' Yield to other processes.
    Loop While Timer < EndTime
End Sub

'Attemts to start the driver and the device
'Input: sDevName - The name of the DriverX device to start and connect
'Output: Returns -  0 = Successfull
'                  -1 = Driver Not Yet Configured
'                  -2 = Couldn't connect to device
'                  -3 = Device specified by sDevName could not be started
'                  -4 = Couldn't connect to device
Private Function StartupDrvDevice(ByVal sDevName As String) As Integer
    On Error GoTo ErrorHandler:
    
    'Initialize the forms internal variables
    
    'Initialize the Driver X Driver
    'Check to see if the driver is configured
    'dxcParallelPort.ConfigureDriver
    If dxcParallelPort.IsDriverConfigured() = False Then
        'Display an error message
        'MsgBox "The driver is not configured!!!" & Chr(13) & "Quiting program now!!!", vbApplicationModal + vbCritical + vbOKOnly, "Critical Error!!!"
        If dxcParallelPort.ConfigureDriver() = False Then 'Try to configure the driver
            StartupDrvDevice = -2
        Else
            StartupDrvDevice = -1
        End If
        'Exit the function now
        Exit Function
    Else
        StartupDrvDevice = 0
    End If
    
    'Check to see if the device is running
    If dxcParallelPort.IsDeviceRunning(sDevName) = False Then
        If dxcParallelPort.StartDevice(sDevName) = False Then
            'MsgBox "Can't start device " & Chr(34) & m_DeviceName & Chr(34) & ".", vbApplicationModal + vbCritical + vbOKOnly, "Fatal Error"
            StartupDrvDevice = -3
            'Exit the function now
            Exit Function
        Else
            StartupDrvDevice = 0
        End If
    Else
        StartupDrvDevice = 0
    End If
    
    'Connect to the device
    If dxcParallelPort.ConnectDevice(sDevName) = False Then
        'Alert the user
        'MsgBox "Failed to connect to the device: " & m_DeviceName, vbApplicationModal + vbCritical + vbOKOnly, "Fatal Error"
        StartupDrvDevice = -4
        'Exit the function now
        Exit Function
    Else
        StartupDrvDevice = 0
    End If
    
    Exit Function

ErrorHandler:
    'Continue on
    Resume Next
End Function

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If UnloadMode = vbFormControlMenu Then
        Cancel = True
        CancelHit = True
        Me.Hide
    Else
        'Cleanup all of the Driver X stuff
        CleanupDriverX
    End If
End Sub

'This function will show the LPTSelect form and displaying the title and message
'specified.  When a port is selected and the ok button is pressed then the
'form will hide and return the port's base address.  If the cancel button is
'pressed then the dialog will return -2.  If no ports then the dialog will return -1.
'If the port specified by DefualtPort is not found then the dialog will
'display an error message and wait for user input.
'Inputs:
'       DefaultLPT: 1=LPT1,2=LPT2 or User Defined,3=LPT3 or User Defined,4=User Defined
'       ShowDialog: True = Show the dialog, False = Don't Show the Dialog
Public Function LPTSelectDialog(ByVal Title As String, ByVal Message As String, Optional ShowDialog = True, Optional DefaultLPT) As Integer

    'Initialize the form
    Me.Caption = Title
    lblSPDMessage.Caption = Message

    If Not IsMissing(DefaultLPT) Then
        'If the user has defined a default lptport then select it
        If IsNumeric(DefaultLPT) Then
            If DefaultLPT > 0 And DefaultLPT < 4 Then
                If DefaultLPT <= lstLPTPorts.ListCount Then 'DefaultLPT - 1 = LPTAddrs(DefaultLPT)<> 0
                    'Select the lpt port
                    lstLPTPorts.ListIndex = DefaultLPT - 1
                Else
                    'Signal that the port wasn't found
                    PortNotFound = -2
                End If
            Else
                'Signal that the port wasn't found
                PortNotFound = -2
            End If
            
            If PortNotFound = -2 Then
                 'The specified port wasn't found
                Me.lblSPDMessage.Caption = "Unable to detect the port specifed, please pick" & Chr(13) & "another port." '
                'Make sure the dialog box will be displayed
                ShowDialog = True
                
                'Unselect the last selected parallel port
                lstLPTPorts.ListIndex = -1
                
                'Disable the OK button so the user can't hit OK without selecting a port.
                cmdOK.Enabled = False
           End If
        Else
            'Eject with an error
            Err.Raise 13, , "Type Mismatch!!!"
        End If
    Else
        'If the user selects not to show the dialog and doesn't select a
        'defualt port for the dialog to be shown.
        If ShowDialog = False And lstLPTPorts.ListIndex = -1 Then
            'Show the dialog because the user hasn't previously selected
            'a port
            ShowDialog = True
        End If
    End If

    If ShowDialog Then
        If PortNotFound = -1 Then
            'If a port wasn't found then disable the list box
            lstLPTPorts.Enabled = False
            'Display port not found message
            Me.lblSPDMessage.Caption = "Unable to detect any local LPT ports!!!"
        
        End If

        'Adjust the objects on the form to accomidate the message label
        'before showing the form dialog
        If lblSPDMessage.Height > imgIcon.Height Then
            fraPortList.Top = lblSPDMessage.Top + lblSPDMessage.Height + 100
        Else
            fraPortList.Top = imgIcon.Height + imgIcon.Top + 100
        End If
        
        Me.Height = fraPortList.Top + fraPortList.Height + 500
        If Me.Width < lblSPDMessage.Width + 220 Then
            Me.Width = lblSPDMessage.Left + lblSPDMessage.Width + 220
        Else
            Me.Width = fraPortList.Width + 100
        End If
        
        'Show the form modaly and wait for user input
        Me.Show 1
    End If

    If PortNotFound = -1 Then
        LPTSelectDialog = -1
    Else
        If CancelHit = True Then
            LPTSelectDialog = -2
        Else
            'Return the selected port
            LPTSelectDialog = lstLPTPorts.ItemData(lstLPTPorts.ListIndex) 'LPTAddrs(lstLPTPorts.ListIndex + 1)
            'Set the selected base address
            LPTBaseAddress = lstLPTPorts.ItemData(lstLPTPorts.ListIndex) 'LPTAddrs(lstLPTPorts.ListIndex + 1)
        End If
    End If

    'Reset cancel hit
    CancelHit = False

    'Hide the dialog form
    Me.Hide
    'Unload the dialog form
'    Unload Me

End Function

Private Sub lstLPTPorts_Click()
    If lstLPTPorts.ListIndex <> -1 Then
        cmdOK.Enabled = True
    End If
End Sub

Public Property Get LPTBaseAddress() As Long
    'Return the current value
    LPTBaseAddress = m_BaseAddr
End Property

Private Property Let LPTBaseAddress(ByVal newBaseAddr As Long)
    Dim retval As Boolean
    
    'Ignore if the person tries to assign an invalid value
    If newBaseAddr <> -1 Then
        'Unmap the current ports
        retval = dxcParallelPort.UnmapPorts(0)
        
        'Set the new address to be used
        If dxcParallelPort.MapPorts2(newBaseAddr, 3, -1) Then
            'Record the new base address
            m_BaseAddr = newBaseAddr
        Else
            'Display an error message
            MsgBox "Couldn't map device to port address " & newBaseAddr & " Hex!", vbApplicationModal + vbCritical + vbOKOnly, "Critical Error!"
        End If
    End If
        
End Property
'This function allows output to the port selected from the LPT port list
Public Sub LptOutput(ByVal Register As dxLPTRegs, ByVal Data As Integer)
    'Output the data to the specified register
    dxcParallelPort.outp Register, Data
End Sub
'This function allows input from the port selected from the LPT port list
Public Function LptInput(ByVal Register As dxLPTRegs) As Integer
    'Input the data from the specifed register
    LptInput = (dxcParallelPort.inp(Register) And &HFF)
End Function

'This function will do nothing but cleanup the driverx stuff
Private Sub CleanupDriverX()
    Dim Dummy As Boolean
    'Unmap the ports
    Dummy = dxcParallelPort.UnmapPorts(0)
    'Stop the device
    Dummy = dxcParallelPort.StopDevice(DeviceName)
    'Disconnect the device
    dxcParallelPort.DisconnectDevice
End Sub

'This function will refresh the LPT list by detecting the parallel ports
'It will not remove user defined parallel ports from the list nor will it
'test the user defined ports to be sure they still exist
Public Sub RefreshLPTList()
    Dim OldBaseAddress As Long
    
    Dim cntr As Integer
    Dim LPTCntr As Integer
    Dim BaseAddrs(1 To 4) As Integer
    Dim ReadBackVal As Long
    
    Dim OldUdp As String 'Old user defined port list item
    Dim OldUdpBAddr As String 'Old user defined port base address
    
    'Disable the Ok button because this will deselect the any
    'ports that have been selected
    cmdOK.Enabled = False
    
    'Initialize Port Found flag
    PortNotFound = -1

    'Initialize the baseaddrs() array
    BaseAddrs(1) = &H3BC
    BaseAddrs(2) = &H378
    BaseAddrs(3) = &H278

    'Store the old base address
    OldBaseAddress = LPTBaseAddress
    
    'If a user defined port is on the list store its list item
    If lstLPTPorts.Tag = "UDAdded" Then
        OldUdp = lstLPTPorts.List(lstLPTPorts.ListCount - 1)
        OldUdpBAddr = lstLPTPorts.ItemData(lstLPTPorts.ListCount - 1)
    End If
    
    'Clear the items in the list
    lstLPTPorts.Clear
    
    'Detect the standard parallel ports
    'Loop through and test each address
    For cntr = 1 To 3
        'Set the new base address
        LPTBaseAddress = BaseAddrs(cntr)
        
        'Check to see if the port exists
        If TestForSPP() Then
            'Increment the LPT counter
            LPTCntr = LPTCntr + 1
            'Add an item to the list  box
            If m_BaseAddr = &H3BC Then
                'If 3bc is detected then adjust item added so items will line up
                lstLPTPorts.AddItem "LPT" & LPTCntr & "                 " & Hex(BaseAddrs(cntr)) & " Hex       SPP"
            Else
                lstLPTPorts.AddItem "LPT" & LPTCntr & "                 " & Hex(BaseAddrs(cntr)) & " Hex        SPP"
            End If

            'Record the base address of the LPT Port found
            lstLPTPorts.ItemData(LPTCntr - 1) = BaseAddrs(cntr)
'            LPTAddrs(LPTCntr) = BaseAddrs(cntr)
            'Clear the portnotfound flag
            PortNotFound = 0
        End If
    Next cntr

    'If a user defined port was in the list add it back
    If lstLPTPorts.Tag = "UDAdded" Then
        lstLPTPorts.AddItem OldUdp
        'Restore the base address
        lstLPTPorts.ItemData(lstLPTPorts.ListCount - 1) = OldUdpBAddr
    End If
    
    'Restore the old base address
    LPTBaseAddress = OldBaseAddress
End Sub

'This function will check to see if the address passed is allready listed
'port list
Private Function IsPortListed(ByVal Addr As Long) As Boolean
    Dim LstCntr As Integer
    
    'Initialize the return value
    IsPortListed = False
    
    'Check each address stored in the address array
    For LstCntr = 0 To lstLPTPorts.ListCount - 1 ' 4
        If lstLPTPorts.ItemData(LstCntr) = Addr Then 'LPTAddrs(LstCntr)
            'Signal that the address is in the list
            IsPortListed = True
            'Exit the for loop
            Exit For
        End If
    Next LstCntr
    
End Function

'Selects the specified port in the list
'The first port in the list is port 0
'The last port in the list is at GetPortCount()-1
'Added on 08/30/99
Public Function LPTSelectPort(ByVal ListNumber As Integer) As Boolean
    On Error GoTo ErrorHandler
    If ListNumber <= (lstLPTPorts.ListCount - 1) Then
        'Hilight the port in the listbox
        lstLPTPorts.ListIndex = ListNumber
        
        'Select the LPT Port
        LPTBaseAddress = lstLPTPorts.ItemData(lstLPTPorts.ListIndex)
            
        'Return True
        LPTSelectPort = True
    Else
        'Invalid port specified return false
        LPTSelectPort = False
    End If
    Exit Function
    'If any errors occur return false
ErrorHandler:
    LPTSelectPort = False
End Function

'Gets the number of ports in the listbox on the form
'Added on 08/30/99
Public Function LPTGetPortCount()
    'Return the number of ports detected and added
    LPTGetPortCount = lstLPTPorts.ListCount
End Function
