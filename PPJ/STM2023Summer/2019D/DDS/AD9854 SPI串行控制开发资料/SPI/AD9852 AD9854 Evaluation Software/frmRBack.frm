VERSION 5.00
Begin VB.Form frmRBack 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   6750
   ClientLeft      =   15
   ClientTop       =   15
   ClientWidth     =   9255
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   6750
   ScaleWidth      =   9255
   Begin VB.TextBox txt0010_6 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   64
      Text            =   "00000000"
      Top             =   3840
      Width           =   1195
   End
   Begin VB.TextBox txt0010_5 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   63
      Text            =   "00000000"
      Top             =   3480
      Width           =   1195
   End
   Begin VB.TextBox txt0010_4 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   62
      Text            =   "00000000"
      Top             =   3120
      Width           =   1195
   End
   Begin VB.TextBox txt0010_3 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   61
      Text            =   "00000000"
      Top             =   2760
      Width           =   1195
   End
   Begin VB.CommandButton cmdReadBack 
      Caption         =   "Select Register Bank...Then Click To Readback Registers"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   3360
      TabIndex        =   60
      Top             =   5760
      Width           =   5655
   End
   Begin VB.OptionButton opt1011 
      Caption         =   "1011"
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
      Left            =   6600
      TabIndex        =   58
      Top             =   4680
      Width           =   735
   End
   Begin VB.OptionButton opt1010 
      Caption         =   "1010"
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
      Left            =   6600
      TabIndex        =   56
      Top             =   3720
      Width           =   735
   End
   Begin VB.OptionButton opt1001 
      Caption         =   "1001"
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
      Left            =   6600
      TabIndex        =   54
      Top             =   2880
      Width           =   735
   End
   Begin VB.OptionButton opt1000 
      Caption         =   "1000"
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
      Left            =   6600
      TabIndex        =   52
      Top             =   1920
      Width           =   735
   End
   Begin VB.OptionButton opt0111 
      Caption         =   "0111"
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
      Left            =   6600
      TabIndex        =   50
      Top             =   240
      Width           =   735
   End
   Begin VB.OptionButton opt0110 
      Caption         =   "0110"
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
      Left            =   3600
      TabIndex        =   48
      Top             =   4440
      Width           =   735
   End
   Begin VB.OptionButton opt0100 
      Caption         =   "0100"
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
      Left            =   3600
      TabIndex        =   45
      Top             =   240
      Width           =   735
   End
   Begin VB.OptionButton opt0011 
      Caption         =   "0011"
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
      Left            =   720
      TabIndex        =   43
      Top             =   4560
      Width           =   735
   End
   Begin VB.OptionButton opt0001 
      Caption         =   "0001"
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
      Left            =   720
      TabIndex        =   40
      Top             =   1200
      Width           =   735
   End
   Begin VB.TextBox txt1011_1 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   38
      Text            =   "00000000"
      Top             =   4560
      Width           =   1195
   End
   Begin VB.TextBox txt1011_2 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   37
      Text            =   "00000000"
      Top             =   4920
      Width           =   1195
   End
   Begin VB.TextBox txt1010_1 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   36
      Text            =   "00000000"
      Top             =   3840
      Width           =   1195
   End
   Begin VB.TextBox txt1001_1 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   35
      Text            =   "00000000"
      Top             =   2760
      Width           =   1195
   End
   Begin VB.TextBox txt1001_2 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   34
      Text            =   "00000000"
      Top             =   3120
      Width           =   1195
   End
   Begin VB.TextBox txt1000_1 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   33
      Text            =   "00000000"
      Top             =   1800
      Width           =   1195
   End
   Begin VB.TextBox txt1000_2 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   32
      Text            =   "00000000"
      Top             =   2160
      Width           =   1195
   End
   Begin VB.TextBox txt0111_1 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   31
      Text            =   "00000000"
      Top             =   120
      Width           =   1195
   End
   Begin VB.TextBox txt0111_2 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   30
      Text            =   "00000000"
      Top             =   480
      Width           =   1195
   End
   Begin VB.TextBox txt0111_3 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   29
      Text            =   "00000000"
      Top             =   840
      Width           =   1195
   End
   Begin VB.TextBox txt0111_4 
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
      Left            =   7800
      MaxLength       =   8
      TabIndex        =   28
      Text            =   "00000000"
      Top             =   1200
      Width           =   1195
   End
   Begin VB.TextBox txt0110_1 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   27
      Text            =   "00000000"
      Top             =   4200
      Width           =   1195
   End
   Begin VB.TextBox txt0110_2 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   26
      Text            =   "00000000"
      Top             =   4560
      Width           =   1195
   End
   Begin VB.TextBox txt0110_3 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   25
      Text            =   "00000000"
      Top             =   4920
      Width           =   1195
   End
   Begin VB.OptionButton opt0101 
      Caption         =   "0101"
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
      Left            =   3600
      TabIndex        =   24
      Top             =   2640
      Width           =   735
   End
   Begin VB.TextBox txt0101_1 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   23
      Text            =   "00000000"
      Top             =   2520
      Width           =   1195
   End
   Begin VB.TextBox txt0101_2 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   22
      Text            =   "00000000"
      Top             =   2880
      Width           =   1195
   End
   Begin VB.TextBox txt0101_3 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   21
      Text            =   "00000000"
      Top             =   3240
      Width           =   1195
   End
   Begin VB.TextBox txt0101_4 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   20
      Text            =   "00000000"
      Top             =   3600
      Width           =   1195
   End
   Begin VB.TextBox txt0100_6 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   19
      Text            =   "00000000"
      Top             =   1920
      Width           =   1195
   End
   Begin VB.TextBox txt0100_5 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   18
      Text            =   "00000000"
      Top             =   1560
      Width           =   1195
   End
   Begin VB.TextBox txt0100_4 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   17
      Text            =   "00000000"
      Top             =   1200
      Width           =   1195
   End
   Begin VB.TextBox txt0100_3 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   16
      Text            =   "00000000"
      Top             =   840
      Width           =   1195
   End
   Begin VB.TextBox txt0100_2 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   15
      Text            =   "00000000"
      Top             =   480
      Width           =   1195
   End
   Begin VB.TextBox txt0100_1 
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
      Left            =   4800
      MaxLength       =   8
      TabIndex        =   14
      Text            =   "00000000"
      Top             =   120
      Width           =   1195
   End
   Begin VB.TextBox txt0011_6 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   13
      Text            =   "00000000"
      Top             =   6240
      Width           =   1195
   End
   Begin VB.TextBox txt0011_5 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   12
      Text            =   "00000000"
      Top             =   5880
      Width           =   1195
   End
   Begin VB.TextBox txt0011_4 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   11
      Text            =   "00000000"
      Top             =   5520
      Width           =   1195
   End
   Begin VB.TextBox txt0011_3 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   10
      Text            =   "00000000"
      Top             =   5160
      Width           =   1195
   End
   Begin VB.TextBox txt0011_2 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   9
      Text            =   "00000000"
      Top             =   4800
      Width           =   1195
   End
   Begin VB.TextBox txt0011_1 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   8
      Text            =   "00000000"
      Top             =   4440
      Width           =   1195
   End
   Begin VB.OptionButton opt0010 
      Caption         =   "0010"
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
      Left            =   720
      TabIndex        =   7
      Top             =   2160
      Width           =   735
   End
   Begin VB.TextBox txt0010_2 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   6
      Text            =   "00000000"
      Top             =   2400
      Width           =   1195
   End
   Begin VB.TextBox txt0010_1 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   5
      Text            =   "00000000"
      Top             =   2040
      Width           =   1195
   End
   Begin VB.TextBox txt0001_2 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   4
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txt0001_1 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   3
      Text            =   "00000000"
      Top             =   1080
      Width           =   1195
   End
   Begin VB.OptionButton opt0000 
      Caption         =   "0000"
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
      Left            =   720
      TabIndex        =   2
      Top             =   240
      Value           =   -1  'True
      Width           =   735
   End
   Begin VB.TextBox txt0000_2 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   1
      Text            =   "00000000"
      Top             =   480
      Width           =   1195
   End
   Begin VB.TextBox txt0000_1 
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
      Left            =   1800
      MaxLength       =   8
      TabIndex        =   0
      Text            =   "00000000"
      Top             =   120
      Width           =   1195
   End
   Begin VB.Line Line4 
      X1              =   3240
      X2              =   9120
      Y1              =   5400
      Y2              =   5400
   End
   Begin VB.Label Label12 
      Alignment       =   2  'Center
      Caption         =   "Q-DAC Register"
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
      Left            =   6240
      TabIndex        =   59
      Top             =   5040
      Width           =   1455
   End
   Begin VB.Label Label11 
      Alignment       =   2  'Center
      Caption         =   "Ramp Rate"
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
      Left            =   6360
      TabIndex        =   57
      Top             =   4080
      Width           =   1215
   End
   Begin VB.Label Label10 
      Alignment       =   2  'Center
      Caption         =   "Q-Chan Multiplier"
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
      Left            =   6240
      TabIndex        =   55
      Top             =   3240
      Width           =   1575
   End
   Begin VB.Label Label9 
      Alignment       =   2  'Center
      Caption         =   "I-Chan Multiplier"
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
      Left            =   6240
      TabIndex        =   53
      Top             =   2280
      Width           =   1575
   End
   Begin VB.Label Label8 
      Alignment       =   2  'Center
      Caption         =   "Control Register"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   6360
      TabIndex        =   51
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label Label7 
      Alignment       =   2  'Center
      Caption         =   "Frequency Step Rate"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3360
      TabIndex        =   49
      Top             =   4800
      Width           =   1215
   End
   Begin VB.Label Label6 
      Alignment       =   2  'Center
      Caption         =   "Update Clock Counter"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3360
      TabIndex        =   47
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label Label5 
      Alignment       =   2  'Center
      Caption         =   "Frequency Step Word"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3360
      TabIndex        =   46
      Top             =   600
      Width           =   1215
   End
   Begin VB.Label Label4 
      Alignment       =   2  'Center
      Caption         =   "Frequency Tuning Word #2"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   360
      TabIndex        =   44
      Top             =   4920
      Width           =   1215
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      Caption         =   "Frequency Tuning Word #1"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   360
      TabIndex        =   42
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Caption         =   "Phase Adjust #2"
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
      TabIndex        =   41
      Top             =   1560
      Width           =   1455
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Phase Adjust #1"
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
      TabIndex        =   39
      Top             =   600
      Width           =   1455
   End
   Begin VB.Line Line10 
      X1              =   6240
      X2              =   9120
      Y1              =   4440
      Y2              =   4440
   End
   Begin VB.Line Line9 
      X1              =   6240
      X2              =   9120
      Y1              =   3600
      Y2              =   3600
   End
   Begin VB.Line Line8 
      X1              =   6240
      X2              =   9120
      Y1              =   2640
      Y2              =   2640
   End
   Begin VB.Line Line7 
      X1              =   6240
      X2              =   9120
      Y1              =   1680
      Y2              =   1680
   End
   Begin VB.Line Line6 
      X1              =   3240
      X2              =   6120
      Y1              =   4080
      Y2              =   4080
   End
   Begin VB.Line Line5 
      X1              =   3240
      X2              =   6120
      Y1              =   2400
      Y2              =   2400
   End
   Begin VB.Line Line3 
      X1              =   120
      X2              =   3120
      Y1              =   4320
      Y2              =   4320
   End
   Begin VB.Line Line2 
      X1              =   120
      X2              =   3120
      Y1              =   1920
      Y2              =   1920
   End
   Begin VB.Line Line1 
      X1              =   120
      X2              =   3120
      Y1              =   960
      Y2              =   960
   End
End
Attribute VB_Name = "frmRBack"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit                         'Declare all variables.
Option Base 1                           'Lower array index = 1.

Public Sub cmdReadBack_Click()

Dim MsgStr As String, ResStr As String

If PMode = 16 Then

   MsgStr = "Must be in serial communications mode!"
   Call MsgBox(MsgStr, 0, "Error")
   
Else
   
   If opt0000.Value = True Then
      SRead ResStr, "0000"
      txt0000_1.Text = "00" & Mid(ResStr, 2, 6)
      txt0000_2.Text = Mid(ResStr, 9, 8)
   ElseIf opt0001.Value = True Then
      SRead ResStr, "0001"
      txt0001_1.Text = "00" & Mid(ResStr, 2, 6)
      txt0001_2.Text = Mid(ResStr, 9, 8)
   ElseIf opt0010.Value = True Then
      SRead ResStr, "0010"
      txt0010_1.Text = Mid(ResStr, 1, 8)
      txt0010_2.Text = Mid(ResStr, 9, 8)
      txt0010_3.Text = Mid(ResStr, 17, 8)
      txt0010_4.Text = Mid(ResStr, 25, 8)
      txt0010_5.Text = Mid(ResStr, 33, 8)
      txt0010_6.Text = Mid(ResStr, 41, 8)
   ElseIf opt0011.Value = True Then
      SRead ResStr, "0011"
      txt0011_1.Text = Mid(ResStr, 1, 8)
      txt0011_2.Text = Mid(ResStr, 9, 8)
      txt0011_3.Text = Mid(ResStr, 17, 8)
      txt0011_4.Text = Mid(ResStr, 25, 8)
      txt0011_5.Text = Mid(ResStr, 33, 8)
      txt0011_6.Text = Mid(ResStr, 41, 8)
   ElseIf opt0100.Value = True Then
      SRead ResStr, "0100"
      txt0100_1.Text = Mid(ResStr, 1, 8)
      txt0100_2.Text = Mid(ResStr, 9, 8)
      txt0100_3.Text = Mid(ResStr, 17, 8)
      txt0100_4.Text = Mid(ResStr, 25, 8)
      txt0100_5.Text = Mid(ResStr, 33, 8)
      txt0100_6.Text = Mid(ResStr, 41, 8)
   ElseIf opt0101.Value = True Then
      SRead ResStr, "0101"
      txt0101_1.Text = Mid(ResStr, 1, 8)
      txt0101_2.Text = Mid(ResStr, 9, 8)
      txt0101_3.Text = Mid(ResStr, 17, 8)
      txt0101_4.Text = Mid(ResStr, 25, 8)
   ElseIf opt0110.Value = True Then
      SRead ResStr, "0110"
      txt0110_1.Text = "0000" & Mid(ResStr, 5, 4)
      txt0110_2.Text = Mid(ResStr, 9, 8)
      txt0110_3.Text = Mid(ResStr, 17, 8)
   ElseIf opt0111.Value = True Then
      SRead ResStr, "0111"
      txt0111_1.Text = "000" & Mid(ResStr, 4, 5)
      txt0111_2.Text = Mid(ResStr, 9, 8)
      txt0111_3.Text = Mid(ResStr, 17, 8)
      txt0111_4.Text = Mid(ResStr, 25, 8)
   ElseIf opt1000.Value = True Then
      SRead ResStr, "1000"
      txt1000_1.Text = "0000" & Mid(ResStr, 5, 4)
      txt1000_2.Text = Mid(ResStr, 9, 8)
   ElseIf opt1001.Value = True Then
      SRead ResStr, "1001"
      txt1001_1.Text = "0000" & Mid(ResStr, 5, 4)
      txt1001_2.Text = Mid(ResStr, 9, 8)
   ElseIf opt1010.Value = True Then
      SRead ResStr, "1010"
      txt1010_1.Text = Mid(ResStr, 1, 8)
   ElseIf opt1011.Value = True Then
      SRead ResStr, "1011"
      txt1011_1.Text = "0000" & Mid(ResStr, 5, 4)
      txt1011_2.Text = Mid(ResStr, 9, 8)
   End If

End If

End Sub

Public Sub Form_Load()

Height = 6780
Width = 9345
Left = 100
Top = 100

End Sub

