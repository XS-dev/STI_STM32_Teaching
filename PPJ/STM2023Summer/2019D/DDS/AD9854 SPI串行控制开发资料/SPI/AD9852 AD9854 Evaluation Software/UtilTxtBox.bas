Attribute VB_Name = "TextUitl"
'This module contains textbox uitlity function that help
'make text boxes more useful

'This function will take the value passed to a textbox's keypress function
'and filter out all keys but the control keys and numeric keys
Public Function NumericFilter(ByVal KeyAscii As Integer) As Integer
    Select Case KeyAscii
        Case 0 To 32  'Control Keys
        Case 43, 45   'Plus and minus keys
        Case 48 To 57 'Numeric Keys
        Case 46       'Period Key
        Case 69, 101 ' E key - make it a capitol E
            KeyAscii = 69
        Case Else     'Trash all other keys hit
            KeyAscii = 0
    End Select
    
    'Return the KeyAscii value
    NumericFilter = KeyAscii
End Function

Public Function BuildTextStr(Tbox As TextBox, ByVal KeyAscii As Integer) As String
    Dim Str As String
    Dim StartTextLen As Long
    Dim EndTextLen As Long
    
    'is the text box empty?
    If Len(Tbox.Text) = 0 Then
        If KeyAscii = 8 Then 'was the backspace key hit
            'do nothing
            Str = ""
        Else
            If Tbox.Tag = "46" Then 'Was the delete key hit?
                'Do nothing
                Str = ""
            Else
                If KeyAscii = 0 Then 'Was any usable key hit?
                    'Do nothing
                    Str = ""
                Else
                    Str = Chr(KeyAscii)
                End If
            End If
        End If
    Else 'The text box isn't empty
        If Tbox.SelLength > 0 Then 'Is any text slected
            'Is all of the text selected?
            If Tbox.SelText = Tbox.Text Then
                If KeyAscii = 8 Then 'Was the backspace key hit?
                    'Do nothing
                    Str = "" 'Delete the entire string
                Else
                    If Tbox.Tag = "46" Then 'Was the delete key hit?
                        'Do nothing
                        Str = "" 'Delete the entire string
                    Else
                        If KeyAscii = 0 Then 'Was a usable key hit?
                            'Do nothing
                            Str = Tbox.Text 'Return the text
                        Else
                            Str = Chr(KeyAscii)
                        End If
                    End If
                End If
            Else 'Not all of the text was selected
                'Calculate the lengths of the start text and end text
                StartLen = Tbox.SelStart
                EndTextLen = Len(Tbox.Text) - (Tbox.SelLength + Tbox.SelStart)
                
                If KeyAscii = 8 Then 'Was the backspace key hit?
                    'Just delete the the selected text
                    Str = Left(Tbox.Text, StartLen) & Right(Tbox.Text, EndTextLen)
                Else
                    If Tbox.Tag = "46" Then 'Was the delete key hit
                        'Just delete the the selected text
                        Str = Left(Tbox.Text, StartLen) & Right(Tbox.Text, EndTextLen)
                    Else
                        If KeyAscii = 0 Then 'Was a usable key hit?
                            'Do nothing
                            Str = Tbox.Text 'Return the text
                        Else
                            'Just replace selected text with the key pressed
                            Str = Left(Tbox.Text, StartLen) & Chr(KeyAscii) & Right(Tbox.Text, EndTextLen)
                        End If
                    End If
                End If
            End If
        Else 'No text is selected
            'Calculate the lengths of the start text and end text
            StartLen = Tbox.SelStart
            EndTextLen = Len(Tbox.Text) - (Tbox.SelLength + Tbox.SelStart)
            
            If KeyAscii = 8 Then 'Was the backspace key hit?
                'Is the cursor at the beginning of the text?
                If Tbox.SelStart <> 0 Then
                    'Delete the char before the cursor
                    Str = Left(Tbox.Text, StartLen - 1) & Right(Tbox.Text, EndTextLen)
                Else
                    'Do nothing
                    Str = Tbox.Text
                End If
            Else
                If Tbox.Tag = "46" Then 'Was the delete key hit?
                    'Is the cursor at the end of the text
                    If Tbox.SelStart = Len(Tbox.Text) Then
                        'Do nothing
                        Str = Tbox.Text
                    Else
                        'Delete the char after the cursor
                        Str = Left(Tbox.Text, StartLen) & Right(Tbox.Text, EndTextLen - 1)
                    End If
                Else
                    If KeyAscii = 0 Then 'Was the key pressed usefull
                        'Do nothing
                        Str = Tbox.Text
                    Else
                        'Just insert the key pressed into the string
                        Str = Left(Tbox.Text, StartLen) & Chr(KeyAscii) & Right(Tbox.Text, EndTextLen)
                    End If
                End If
            End If
        End If
    End If
    
    'reset the tag property to ""
    Tbox.Tag = ""
    
    BuildTextStr = Str
End Function

'Selects all text in the text box passed
Public Sub SelectAllTxt(Tbox As TextBox)
    'Select all text in the textbox
    Tbox.SelStart = 0
    Tbox.SelLength = Len(Tbox)
End Sub

