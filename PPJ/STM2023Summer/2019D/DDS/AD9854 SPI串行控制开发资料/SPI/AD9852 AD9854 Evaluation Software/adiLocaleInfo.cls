VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "adiLocaleInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Private Declare Function GetSystemDefaultLCID Lib "kernel32" () As Long
Private Declare Function GetUserDefaultLCID Lib "kernel32" () As Long
Private Declare Function ApiGetLocaleInfo Lib "kernel32" Alias "GetLocaleInfoA" (ByVal Locale As Long, ByVal LCType As Long, ByVal lpLCData As String, ByVal cchData As Long) As Long
Private Const LOCALE_SDECIMAL = &HE
Private Const LOCALE_STHOUSAND = &HF
Private Const LOCALE_ICENTURY = &H24
Private Const LOCALE_ICOUNTRY = &H5
Private Const LOCALE_ICURRDIGITS = &H19
Private Const LOCALE_ICURRENCY = &H1B
Private Const LOCALE_IDATE = &H21
Private Const LOCALE_IDAYLZERO = &H26
Private Const LOCALE_IDEFAULTCODEPAGE = &HB
Private Const LOCALE_IDEFAULTCOUNTRY = &HA
Private Const LOCALE_IDEFAULTLANGUAGE = &H9
Private Const LOCALE_IDIGITS = &H11
Private Const LOCALE_IINTLCURRDIGITS = &H1A
Private Const LOCALE_ILANGUAGE = &H1
Private Const LOCALE_ILDATE = &H22
Private Const LOCALE_ILZERO = &H12
Private Const LOCALE_IMEASURE = &HD
Private Const LOCALE_IMONLZERO = &H27
Private Const LOCALE_INEGCURR = &H1C
Private Const LOCALE_INEGSEPBYSPACE = &H57
Private Const LOCALE_INEGSIGNPOSN = &H53
Private Const LOCALE_INEGSYMPRECEDES = &H56
Private Const LOCALE_IPOSSEPBYSPACE = &H55
Private Const LOCALE_IPOSSIGNPOSN = &H52
Private Const LOCALE_IPOSSYMPRECEDES = &H54
Private Const LOCALE_ITIME = &H23
Private Const LOCALE_ITLZERO = &H25
Private Const LOCALE_NOUSEROVERRIDE = &H80000000
Private Const LOCALE_S1159 = &H28
Private Const LOCALE_S2359 = &H29
Private Const LOCALE_SABBREVCTRYNAME = &H7
Private Const LOCALE_SABBREVDAYNAME1 = &H31
Private Const LOCALE_SABBREVDAYNAME2 = &H32
Private Const LOCALE_SABBREVDAYNAME3 = &H33
Private Const LOCALE_SABBREVDAYNAME4 = &H34
Private Const LOCALE_SABBREVDAYNAME5 = &H35
Private Const LOCALE_SABBREVDAYNAME6 = &H36
Private Const LOCALE_SABBREVDAYNAME7 = &H37
Private Const LOCALE_SABBREVMONTHNAME1 = &H44
Private Const LOCALE_SABBREVMONTHNAME10 = &H4D
Private Const LOCALE_SABBREVMONTHNAME11 = &H4E
Private Const LOCALE_SABBREVMONTHNAME12 = &H4F
Private Const LOCALE_SABBREVMONTHNAME13 = &H100F
Private Const LOCALE_SABBREVMONTHNAME2 = &H45
Private Const LOCALE_SABBREVMONTHNAME3 = &H46
Private Const LOCALE_SABBREVMONTHNAME4 = &H47
Private Const LOCALE_SABBREVMONTHNAME5 = &H48
Private Const LOCALE_SABBREVMONTHNAME6 = &H49
Private Const LOCALE_SABBREVMONTHNAME7 = &H4A
Private Const LOCALE_SABBREVMONTHNAME8 = &H4B
Private Const LOCALE_SABBREVMONTHNAME9 = &H4C
Private Const LOCALE_SCOUNTRY = &H6
Private Const LOCALE_SCURRENCY = &H14
Private Const LOCALE_SDATE = &H1D
Private Const LOCALE_SDAYNAME1 = &H2A
Private Const LOCALE_SDAYNAME2 = &H2B
Private Const LOCALE_SDAYNAME3 = &H2C
Private Const LOCALE_SDAYNAME4 = &H2D
Private Const LOCALE_SDAYNAME5 = &H2E
Private Const LOCALE_SDAYNAME6 = &H2F
Private Const LOCALE_SDAYNAME7 = &H30
Private Const LOCALE_SENGCOUNTRY = &H1002
Private Const LOCALE_SENGLANGUAGE = &H1001
Private Const LOCALE_SGROUPING = &H10
Private Const LOCALE_SINTLSYMBOL = &H15
Private Const LOCALE_SLANGUAGE = &H2
Private Const LOCALE_SLIST = &HC
Private Const LOCALE_SLONGDATE = &H20
Private Const LOCALE_SMONDECIMALSEP = &H16
Private Const LOCALE_SMONGROUPING = &H18
Private Const LOCALE_SMONTHNAME1 = &H38
Private Const LOCALE_SMONTHNAME10 = &H41
Private Const LOCALE_SMONTHNAME11 = &H42
Private Const LOCALE_SMONTHNAME12 = &H43
Private Const LOCALE_SMONTHNAME2 = &H39
Private Const LOCALE_SMONTHNAME3 = &H3A
Private Const LOCALE_SMONTHNAME4 = &H3B
Private Const LOCALE_SMONTHNAME5 = &H3C
Private Const LOCALE_SMONTHNAME6 = &H3D
Private Const LOCALE_SMONTHNAME7 = &H3E
Private Const LOCALE_SMONTHNAME8 = &H3F
Private Const LOCALE_SMONTHNAME9 = &H40
Private Const LOCALE_SNATIVECTRYNAME = &H8
Private Const LOCALE_SNATIVEDIGITS = &H13
Private Const LOCALE_SNATIVELANGNAME = &H4
Private Const LOCALE_SMONTHOUSANDSEP = &H17
Private Const LOCALE_SNEGATIVESIGN = &H51
Private Const LOCALE_SPOSITIVESIGN = &H50
Private Const LOCALE_SSHORTDATE = &H1F
Private Const LOCALE_STIME = &H1E
Private Const LOCALE_STIMEFORMAT = &H1003
'local variable(s) to hold property value(s)
Private mvarSystemDefLCID As Long 'local copy
'local variable(s) to hold property value(s)
Private mvarUserDefLCID As Long 'local copy

Public Enum adiLCType
    adiDecimalSep = LOCALE_SDECIMAL
    adiThousandSep = LOCALE_STHOUSAND
    adiLangIndicator = LOCALE_ILANGUAGE
    adiLocLang = LOCALE_SLANGUAGE
    adiLanguage = LOCALE_SENGLANGUAGE
    adiCountry = LOCALE_SENGCOUNTRY
    adiListSep = LOCALE_SLIST
    adiMeasureUnits = LOCALE_IMEASURE
    adiGoupingSep = LOCALE_SGROUPING
    adiFractDigits = LOCALE_IDIGITS
    adiLeadZeros = LOCALE_ILZERO
    adiNegSign = LOCALE_SNEGATIVESIGN
End Enum

Public Enum adiLCID
    UserDef = 1
    SystemDef = 2
End Enum

'local variable(s) to hold property value(s)
Private mvarLCID As adiLCID 'local copy
Public Property Let LCID(ByVal vData As adiLCID)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.LCID = 5
    If vData = UserDef Then
        mvarLCID = mvarUserDefLCID
    Else
        mvarLCID = mvarSystemDefLCID
    End If
End Property


Public Property Get LCID() As adiLCID
Attribute LCID.VB_UserMemId = 0
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.LCID
    LCID = mvarLCID
End Property

Private Property Let UserDefLCID(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.UserDefLCID = 5
    mvarUserDefLCID = vData
End Property

Public Property Get UserDefLCID() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.UserDefLCID
    UserDefLCID = mvarUserDefLCID
End Property

Public Function GetLocaleInfo(ByVal LCType As adiLCType) As String
    Dim RetVal As String
    Dim StrLen As Long
    
    'Get the length the string needs to be
    StrLen = ApiGetLocaleInfo(mvarLCID, LCType, RetVal, 0)
    
    StrLen = StrLen
    
    'Resize the string
    RetVal = String(StrLen, vbNull)
    
    'Get the Locale Info requested
    StrLen = ApiGetLocaleInfo(LCID, LCType, RetVal, StrLen)
    
    If StrLen <> 0 Then
        GetLocaleInfo = Left(RetVal, Len(RetVal) - 1)
    Else
        GetLocaleInfo = ""
    End If
End Function

Private Property Let SystemDefLCID(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.LCID = 5
    mvarSystemDefLCID = vData
End Property


Public Property Get SystemDefLCID() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.LCID
    LCID = mvarSystemDefLCID
End Property

Private Sub Class_Initialize()
    'Get the LCID's for the system
    mvarSystemDefLCID = GetSystemDefaultLCID()
    mvarUserDefLCID = GetUserDefaultLCID()
    
    'Initialize the default values of properties
    mvarLCID = mvarUserDefLCID
End Sub
