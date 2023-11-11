Attribute VB_Name = "modNumBase"
Option Explicit

'Converts a Decimal number to a binary string
'Note - Converts floating point numbers to integer values
Public Function cbaseDec2Bin(ByVal Number As Variant, ByVal NumBits As Integer) As String
    Dim cntr As Integer
    Dim TempDec As Variant
    Dim iBitVal As Integer
    TempDec = CDec(0)
    
    If Not IsNumeric(Number) Then
        'Raise an error
        Err.Raise 5, "cbaseDec2Bin()", "Invalid Parameter: Number can only be a whole number no fractional numbers."
    Else
        'Truncate the fractional part of number off
        TempDec = DecFix(Number)
        
        'Convert the value to a binary string
        For cntr = NumBits - 1 To 0 Step -1
            'Get the first bit value
            iBitVal = DecFix(TempDec / 2 ^ cntr)
            'Check the string value of the bit to the output string
            If iBitVal = 1 Then
                cbaseDec2Bin = cbaseDec2Bin & "1"
                'Trim off the bit checked
                TempDec = TempDec - (2 ^ cntr)
            Else
                cbaseDec2Bin = cbaseDec2Bin & "0"
            End If
        Next cntr
        'The return string has been assembled
    End If
End Function
'02/08/00 - Replaced "." with "GetDecSeperator(False)" for internationalization
'Truncates the fractional portion off of a decimal value
Public Function DecFix(ByVal Number As Variant) As Variant
    Dim ConvertStr As String
    
    If InStr(1, CStr(Number), GetDecSeperator(False)) And (InStr(1, CStr(Number), GetDecSeperator(False)) <> Len(CStr(Number))) Then
        'Truncate the fractional part of the number
        ConvertStr = Left(CStr(Number), InStr(1, CStr(Number), GetDecSeperator(False)) - 1)
    Else
        ConvertStr = CStr(Number)
    End If
    
    'Return the truncated value
    DecFix = CDec(ConvertStr)
End Function
'Converts a binary string into a decimal value
Public Function cbaseBinS2Dec(ByVal BinStr As String) As Variant
    Dim BSLen As Integer
    Dim retval As Variant
    Dim cntr As Integer
    Dim ChrPtr As Integer
    
    If Len(BinStr) > 111 And IsNumeric(BinStr) Then
        'Error
        Err.Raise 5, "cbaseBinS2Dec()", "To many bits: Can only convert 111 bit string!!!"
    Else
        'Get the length of the string
        BSLen = Len(BinStr)
        
        'Initailize retval as a decimal value
        retval = CDec(0)
        
        'Inirialize the charater ptr
        ChrPtr = BSLen
        
        'Convert then string
        For cntr = 0 To BSLen - 1
            
            'If the character is a "1" then add the bit
            If Mid(BinStr, ChrPtr, 1) = "1" Then
                retval = retval + 2 ^ cntr
            End If
            
            'Decrement the character pointer
            ChrPtr = ChrPtr - 1
        Next cntr
            
        cbaseBinS2Dec = retval
    End If
End Function

'Converts a decimal value to a hex string
'Inputs
'   Num - Number to be converted
'   DigitsToDisplay - Number of digits to display
Public Function cbaseHex(ByVal Num As Variant, Optional ByVal DigitsToDisplay As Integer = 0) As String
    Dim Digits2Add As Integer
    Const MaxLongVal = 2147483647
'    Dim iCntr As Integer
'    Dim iNibble As Integer
'    Dim sNibble As Integer
    Dim dCNum As Variant
    dCNum = CDec(0)
    
    If IsNumeric(Num) Then
        'Convert the value to hex
'        cbaseHex = Hex(DecFix(Num))
        dCNum = Num
        Do
            'Convert the first nibble to hex
            cbaseHex = Hex(DecMod(dCNum, 16)) & cbaseHex
            'Remove the first nibble from the value
            dCNum = DecFix(dCNum / 16)
        Loop While dCNum <> 0
        
        
        'Add on any leading 0's that are needed
        If DigitsToDisplay > Len(cbaseHex) Then
            'Calculate the digits to add
            Digits2Add = DigitsToDisplay - Len(cbaseHex)
            'Add the missing digits to the output string
            cbaseHex = String(Digits2Add, 48) & cbaseHex
        End If
    Else
        'Error
        Err.Raise 5, "cbaseHex()", "Num can only be a numeric value."
        Exit Function
    End If
End Function

'Converts a hex string into a decimal value properly
Public Function cbaseHexStr2Dec(ByVal HexStr As String) As Variant
    Dim cntr As Integer
    Dim sNibble As String
    Dim iNibble As Integer
    Dim retval As Variant
    
    retval = CDec(0)
    
    'Initialize nibble as a decimal value
'    Nibble = 0
    
    'Loop through all of the nibbles
    For cntr = 0 To Len(HexStr) - 1
        'Get the first nibble
        sNibble = Right(HexStr, 1)
        'Trimm off the LSN
        HexStr = Left(HexStr, Len(HexStr) - 1)
        
        'Check the current character to see if it is a valid character
        Select Case Asc(sNibble)
            Case 48 To 57
            Case 65 To 70
            Case 97 To 102
            Case Else
                'If not raise an error and exit the function
                Err.Raise 13, "cbaseHexStr2Dec()", "Type mismatch - Invalid input string."
                Exit Function
        End Select
        
        'Convert the nibble to an integer
        iNibble = CInt("&h" & sNibble)
        If cntr = 0 Then
            'Add the LSN
            retval = iNibble
        Else
            'Add up the nibbles
            retval = retval + (iNibble * (16 ^ cntr))
        End If
    Next cntr
    
    'Return the calcualted integer value
    cbaseHexStr2Dec = retval
End Function
'Performs the modulos function on Decimal values
'divides Num by Divisor and returns the remainder
Public Function DecMod(ByVal Num As Variant, ByVal Divisor As Variant) As Variant
    Dim TempVal As Variant
    'Initialize as a decimal value
    TempVal = CDec(0)
    
    'Do the division
    TempVal = Num / Divisor
    
    'Calculate the remainder
    DecMod = (TempVal - DecFix(TempVal)) * Divisor
End Function

'Returns the decimal seperator in either ascii code or
'the character
Private Function GetDecSeperator(ByVal RetAsciiCode As Boolean) As Variant
    If RetAsciiCode Then
        GetDecSeperator = Asc(Mid(Format(0, "Fixed"), 2, 1))
    Else
        GetDecSeperator = Mid(Format(0, "Fixed"), 2, 1)
    End If
End Function

