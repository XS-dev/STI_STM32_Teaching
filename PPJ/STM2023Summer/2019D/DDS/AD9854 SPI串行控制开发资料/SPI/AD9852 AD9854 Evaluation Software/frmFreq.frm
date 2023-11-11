VERSION 5.00
Begin VB.Form frmFrequency 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   7470
   ClientLeft      =   15
   ClientTop       =   15
   ClientWidth     =   9975
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   12
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
   ScaleHeight     =   7470
   ScaleWidth      =   9975
   Begin VB.CommandButton cmdShowTestWindow 
      Caption         =   "Test"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1680
      TabIndex        =   72
      Top             =   5760
      Visible         =   0   'False
      Width           =   855
   End
   Begin VB.Frame frmORamp 
      Caption         =   "Output Shaped Keying Pin"
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
      Left            =   7320
      TabIndex        =   67
      Top             =   6600
      Width           =   2535
      Begin VB.OptionButton optORampLo 
         Caption         =   "Low"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   1440
         TabIndex        =   71
         Top             =   360
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.OptionButton optORampHi 
         Caption         =   "High"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   480
         TabIndex        =   70
         Top             =   360
         Width           =   735
      End
   End
   Begin VB.Frame frmFData 
      Caption         =   "FSK/BPSK/Hold Pin"
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
      Left            =   7320
      TabIndex        =   66
      Top             =   5760
      Width           =   2535
      Begin VB.OptionButton optFDataLo 
         Caption         =   "Low"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   1440
         TabIndex        =   69
         Top             =   360
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.OptionButton optFDataHi 
         Caption         =   "High"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   480
         TabIndex        =   68
         Top             =   360
         Width           =   735
      End
   End
   Begin VB.Frame frmSpecMode 
      Caption         =   "Special Modes"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1575
      Left            =   120
      TabIndex        =   62
      Top             =   5760
      Width           =   2535
      Begin VB.CheckBox chkACC2 
         Caption         =   "Set Clr ACC2 Bit"
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
         Left            =   360
         TabIndex        =   65
         Top             =   1080
         Width           =   1815
      End
      Begin VB.CheckBox chkACC1 
         Caption         =   "Set Clr ACC1 Bit"
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
         Left            =   360
         TabIndex        =   64
         Top             =   720
         Width           =   1815
      End
      Begin VB.CheckBox chkTriangle 
         Caption         =   "Set Triangle Bit"
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
         Left            =   360
         TabIndex        =   63
         Top             =   360
         Width           =   1695
      End
   End
   Begin VB.CommandButton cmdReset 
      Caption         =   "Reset DUT and Initialize Registers"
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
      Left            =   2880
      TabIndex        =   61
      Top             =   6000
      Width           =   4215
   End
   Begin VB.TextBox txtPhAdj1_1 
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
      Left            =   4200
      MaxLength       =   2
      TabIndex        =   60
      Text            =   "00"
      Top             =   4440
      Width           =   380
   End
   Begin VB.TextBox txtPhAdj1_2 
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
      Left            =   4680
      MaxLength       =   4
      TabIndex        =   59
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtPhAdj1_3 
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
      Left            =   5400
      MaxLength       =   4
      TabIndex        =   58
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtPhAdj1_4 
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
      Left            =   6120
      MaxLength       =   4
      TabIndex        =   57
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtPhAdj2_2 
      Enabled         =   0   'False
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
      Left            =   7680
      MaxLength       =   4
      TabIndex        =   56
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtPhAdj2_3 
      Enabled         =   0   'False
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
      Left            =   8400
      MaxLength       =   4
      TabIndex        =   55
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtPhAdj2_4 
      Enabled         =   0   'False
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
      Left            =   9120
      MaxLength       =   4
      TabIndex        =   54
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtFSR1 
      Enabled         =   0   'False
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
      Left            =   240
      MaxLength       =   4
      TabIndex        =   53
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtFSR2 
      Enabled         =   0   'False
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
      Left            =   960
      MaxLength       =   4
      TabIndex        =   52
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtFSR5 
      Enabled         =   0   'False
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
      Left            =   3120
      MaxLength       =   4
      TabIndex        =   51
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtFSR4 
      Enabled         =   0   'False
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
      Left            =   2400
      MaxLength       =   4
      TabIndex        =   50
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtPhAdj2_1 
      Enabled         =   0   'False
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
      Left            =   7200
      MaxLength       =   2
      TabIndex        =   49
      Text            =   "00"
      Top             =   4440
      Width           =   380
   End
   Begin VB.TextBox txtFSR3 
      Enabled         =   0   'False
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
      Left            =   1680
      MaxLength       =   4
      TabIndex        =   48
      Text            =   "0000"
      Top             =   4440
      Width           =   640
   End
   Begin VB.TextBox txtPhAdj2Hex 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   8040
      MaxLength       =   4
      TabIndex        =   47
      Text            =   "0000"
      Top             =   5040
      Width           =   880
   End
   Begin VB.TextBox txtPhAdj1Hex 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   5040
      MaxLength       =   4
      TabIndex        =   46
      Text            =   "0000"
      Top             =   5040
      Width           =   880
   End
   Begin VB.TextBox txtFSRHex 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   1440
      MaxLength       =   5
      TabIndex        =   45
      Text            =   "00000"
      Top             =   5040
      Width           =   1100
   End
   Begin VB.TextBox txtFSWMHz 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   7800
      MaxLength       =   7
      TabIndex        =   44
      Text            =   "0.00000"
      Top             =   3120
      Width           =   1480
   End
   Begin VB.TextBox txtFSW6 
      Enabled         =   0   'False
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
      Left            =   6120
      MaxLength       =   8
      TabIndex        =   43
      Text            =   "00000000"
      Top             =   3120
      Width           =   1195
   End
   Begin VB.TextBox txtFSW5 
      Enabled         =   0   'False
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
      Left            =   4920
      MaxLength       =   8
      TabIndex        =   42
      Text            =   "00000000"
      Top             =   3120
      Width           =   1195
   End
   Begin VB.TextBox txtFSW4 
      Enabled         =   0   'False
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
      Left            =   3720
      MaxLength       =   8
      TabIndex        =   41
      Text            =   "00000000"
      Top             =   3120
      Width           =   1195
   End
   Begin VB.TextBox txtFSW3 
      Enabled         =   0   'False
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
      Left            =   2520
      MaxLength       =   8
      TabIndex        =   40
      Text            =   "00000000"
      Top             =   3120
      Width           =   1195
   End
   Begin VB.TextBox txtFSW2 
      Enabled         =   0   'False
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
      Left            =   1320
      MaxLength       =   8
      TabIndex        =   39
      Text            =   "00000000"
      Top             =   3120
      Width           =   1195
   End
   Begin VB.TextBox txtFSW1 
      Enabled         =   0   'False
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
      Left            =   120
      MaxLength       =   8
      TabIndex        =   38
      Text            =   "00000000"
      Top             =   3120
      Width           =   1195
   End
   Begin VB.TextBox txtFTW2MHz 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   7800
      MaxLength       =   7
      TabIndex        =   37
      Text            =   "0.00000"
      Top             =   2280
      Width           =   1480
   End
   Begin VB.TextBox txtFTW2_6 
      Enabled         =   0   'False
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
      Left            =   6120
      MaxLength       =   8
      TabIndex        =   36
      Text            =   "00000000"
      Top             =   2280
      Width           =   1195
   End
   Begin VB.TextBox txtFTW2_5 
      Enabled         =   0   'False
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
      Left            =   4920
      MaxLength       =   8
      TabIndex        =   35
      Text            =   "00000000"
      Top             =   2280
      Width           =   1195
   End
   Begin VB.TextBox txtFTW2_4 
      Enabled         =   0   'False
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
      Left            =   3720
      MaxLength       =   8
      TabIndex        =   34
      Text            =   "00000000"
      Top             =   2280
      Width           =   1195
   End
   Begin VB.TextBox txtFTW2_3 
      Enabled         =   0   'False
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
      Left            =   2520
      MaxLength       =   8
      TabIndex        =   33
      Text            =   "00000000"
      Top             =   2280
      Width           =   1195
   End
   Begin VB.TextBox txtFTW2_2 
      Enabled         =   0   'False
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
      Left            =   1320
      MaxLength       =   8
      TabIndex        =   32
      Text            =   "00000000"
      Top             =   2280
      Width           =   1195
   End
   Begin VB.TextBox txtFTW2_1 
      Enabled         =   0   'False
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
      Left            =   120
      MaxLength       =   8
      TabIndex        =   31
      Text            =   "00000000"
      Top             =   2280
      Width           =   1195
   End
   Begin VB.TextBox txtFTW1MHz 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   7800
      MaxLength       =   7
      TabIndex        =   30
      Text            =   "0.00000"
      Top             =   1440
      Width           =   1480
   End
   Begin VB.TextBox txtFTW1_6 
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
      Left            =   6120
      MaxLength       =   8
      TabIndex        =   29
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txtFTW1_5 
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
      Left            =   4920
      MaxLength       =   8
      TabIndex        =   28
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txtFTW1_4 
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
      Left            =   3720
      MaxLength       =   8
      TabIndex        =   27
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txtFTW1_3 
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
      Left            =   2520
      MaxLength       =   8
      TabIndex        =   26
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txtFTW1_2 
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
      Left            =   1320
      MaxLength       =   8
      TabIndex        =   25
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.TextBox txtFTW1_1 
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
      Left            =   120
      MaxLength       =   8
      TabIndex        =   24
      Text            =   "00000000"
      Top             =   1440
      Width           =   1195
   End
   Begin VB.CommandButton cmdLoad 
      Caption         =   "Send Mode, Frequency, Phase Info to DUT"
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
      Left            =   2880
      TabIndex        =   23
      Top             =   6720
      Width           =   4215
   End
   Begin VB.Frame frmMode 
      Caption         =   "Mode"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   9735
      Begin VB.OptionButton optBPSKmode 
         Caption         =   "BPSK Mode"
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
         Left            =   7800
         TabIndex        =   6
         Top             =   360
         Width           =   1455
      End
      Begin VB.OptionButton optChirpMode 
         Caption         =   "Chirp Mode"
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
         Left            =   6120
         TabIndex        =   5
         Top             =   360
         Width           =   1335
      End
      Begin VB.OptionButton optRampedFSK 
         Caption         =   "Ramped FSK"
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
         Left            =   4200
         TabIndex        =   4
         Top             =   360
         Width           =   1575
      End
      Begin VB.OptionButton optUnrampedFSK 
         Caption         =   "Unramped FSK"
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
         Left            =   2160
         TabIndex        =   2
         Top             =   360
         Width           =   1695
      End
      Begin VB.OptionButton optSingleTone 
         Caption         =   "Single Tone"
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
         Left            =   480
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   1335
      End
      Begin VB.Label lblMode 
         Alignment       =   2  'Center
         Caption         =   "Single Tone mode outputs the frequency determined by Frequency Tuning Word (FTW) #1."
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
         Left            =   120
         TabIndex        =   15
         Top             =   720
         Width           =   9495
      End
   End
   Begin VB.Line Line7 
      X1              =   120
      X2              =   9840
      Y1              =   5640
      Y2              =   5640
   End
   Begin VB.Line Line6 
      X1              =   9600
      X2              =   9000
      Y1              =   4920
      Y2              =   5040
   End
   Begin VB.Line Line5 
      X1              =   7320
      X2              =   7920
      Y1              =   4920
      Y2              =   5040
   End
   Begin VB.Line Line4 
      X1              =   6600
      X2              =   6000
      Y1              =   4920
      Y2              =   5040
   End
   Begin VB.Line Line3 
      X1              =   4320
      X2              =   4920
      Y1              =   4920
      Y2              =   5040
   End
   Begin VB.Line Line2 
      X1              =   360
      X2              =   1320
      Y1              =   4920
      Y2              =   5040
   End
   Begin VB.Line Line1 
      X1              =   3600
      X2              =   2640
      Y1              =   4920
      Y2              =   5040
   End
   Begin VB.Label lblFSWEql 
      Alignment       =   2  'Center
      Caption         =   "="
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   7440
      TabIndex        =   22
      Top             =   3240
      Width           =   255
   End
   Begin VB.Label lblFTW2Eql 
      Alignment       =   2  'Center
      Caption         =   "="
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   7440
      TabIndex        =   21
      Top             =   2400
      Width           =   255
   End
   Begin VB.Label lblFTW1Eql 
      Alignment       =   2  'Center
      Caption         =   "="
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   7440
      TabIndex        =   20
      Top             =   1560
      Width           =   255
   End
   Begin VB.Line Line9 
      X1              =   120
      X2              =   9840
      Y1              =   3960
      Y2              =   3960
   End
   Begin VB.Label lblPhAdj2Hex 
      Alignment       =   2  'Center
      Caption         =   "HEX"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   9120
      TabIndex        =   19
      Top             =   5160
      Width           =   375
   End
   Begin VB.Label lblPhAdj1Hex 
      Alignment       =   2  'Center
      Caption         =   "HEX"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   6120
      TabIndex        =   18
      Top             =   5160
      Width           =   375
   End
   Begin VB.Label lblPhAdj2 
      Alignment       =   2  'Center
      Caption         =   "Phase Adjust #2"
      Enabled         =   0   'False
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
      Left            =   7200
      TabIndex        =   17
      Top             =   4080
      Width           =   2535
   End
   Begin VB.Label lblPhAdj1 
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
      Left            =   4200
      TabIndex        =   16
      Top             =   4080
      Width           =   2535
   End
   Begin VB.Label lblFSR 
      Alignment       =   2  'Center
      Caption         =   "Freqency Step Rate Counter"
      Enabled         =   0   'False
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
      TabIndex        =   14
      Top             =   4080
      Width           =   3495
   End
   Begin VB.Label lblFSRHex 
      Alignment       =   2  'Center
      Caption         =   "HEX"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2640
      TabIndex        =   13
      Top             =   5160
      Width           =   375
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   15
      Left            =   7200
      TabIndex        =   12
      Top             =   3480
      Width           =   15
   End
   Begin VB.Label lblFSWMHz 
      Alignment       =   2  'Center
      Caption         =   "MHz"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   9360
      TabIndex        =   11
      Top             =   3240
      Width           =   495
   End
   Begin VB.Label lblFTW2MHz 
      Alignment       =   2  'Center
      Caption         =   "MHz"
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   9360
      TabIndex        =   10
      Top             =   2400
      Width           =   495
   End
   Begin VB.Label lblFTW1MHz 
      Alignment       =   2  'Center
      Caption         =   "MHz"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   9360
      TabIndex        =   9
      Top             =   1560
      Width           =   495
   End
   Begin VB.Label lblFSW 
      Alignment       =   2  'Center
      Caption         =   "Frequency Step Word"
      Enabled         =   0   'False
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
      Left            =   2760
      TabIndex        =   8
      Top             =   3600
      Width           =   1935
   End
   Begin VB.Label lblFTW2 
      Alignment       =   2  'Center
      Caption         =   "Frequency Tuning Word #2"
      Enabled         =   0   'False
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
      Left            =   2520
      TabIndex        =   7
      Top             =   2760
      Width           =   2415
   End
   Begin VB.Label lblFTW1 
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
      Height          =   255
      Left            =   2520
      TabIndex        =   3
      Top             =   1920
      Width           =   2415
   End
End
Attribute VB_Name = "frmFrequency"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit                         'Declare all variables.
Option Base 1                           'Lower array index = 1.

Public Sub FTW_Update(FrqTyp As String)

'This procedure updates tuning words for frequency #1, #2,
'or the FSW based upon the system clock.  The use of the
'decimal subtype insures 48-bit accuracy.

Dim BitVal As Variant, BytVal As Variant
Dim SysClk As Single, FrqVal As Single
Dim i As Integer, IntWrd As Integer
Dim TmpStr As String
Dim BVNeg As Boolean

'Get the system clock frequency.
GetSysClk SysClk

If SysClk > 0! Then

   'Get output frequency.
   If FrqTyp = "F1" Then
      FrqVal = CSng(txtFTW1MHz.Text)
   ElseIf FrqTyp = "F2" Then
      FrqVal = CSng(txtFTW2MHz.Text)
   Else
      FrqVal = CSng(txtFSWMHz.Text)
      If FrqVal < 0 Then
         BVNeg = True
         FrqVal = Abs(FrqVal)
      Else
         BVNeg = False
      End If
   End If

   'Compute the tuning word numeric value.
   'BitVal = CDec(FrqVal / SysClk * 2 ^ 48)
   BitVal = CDec(CDec(FrqVal) / CDec(SysClk) * 2 ^ 48)
   'Check to see if the number is negative
   'If so make positive and subtract 1 so that the binary value will
   'be calculated right
   If BVNeg Then
      BitVal = BitVal - 1
   End If
 
   'Convert to binary strings.
   For i = 40 To 0 Step -8
   
      'Compute binary byte value.
      BytVal = CDec(BitVal / 2 ^ i)

      'Truncate fractional portion.
      IntWrd = Fix(BytVal)
      
      'Reduce value.
      BitVal = CDec(BitVal - (IntWrd * 2 ^ i))
   
      'Build binary string.
      GetWrdStr IntWrd, TmpStr
      
      'Write to byte position.
      Select Case i
      
         Case 40
            If FrqTyp = "F1" Then
               txtFTW1_1.Text = TmpStr
            ElseIf FrqTyp = "F2" Then
               txtFTW2_1.Text = TmpStr
            Else
               'If the number is negative then complement the binary string
               'so it will display corectly in 2's complement form
               If BVNeg Then
                   TmpStr = ComplBinStr(TmpStr)
               End If
               txtFSW1.Text = TmpStr
            End If
         
         Case 32
            If FrqTyp = "F1" Then
               txtFTW1_2.Text = TmpStr
            ElseIf FrqTyp = "F2" Then
               txtFTW2_2.Text = TmpStr
            Else
               'If the number is negative then complement the binary string
               'so it will display corectly in 2's complement form
               If BVNeg Then
                   TmpStr = ComplBinStr(TmpStr)
               End If
               txtFSW2.Text = TmpStr
            End If
         
         Case 24
            If FrqTyp = "F1" Then
               txtFTW1_3.Text = TmpStr
            ElseIf FrqTyp = "F2" Then
               txtFTW2_3.Text = TmpStr
            Else
               'If the number is negative then complement the binary string
               'so it will display corectly in 2's complement form
               If BVNeg Then
                   TmpStr = ComplBinStr(TmpStr)
               End If
               txtFSW3.Text = TmpStr
            End If
         
         Case 16
            If FrqTyp = "F1" Then
               txtFTW1_4.Text = TmpStr
            ElseIf FrqTyp = "F2" Then
               txtFTW2_4.Text = TmpStr
            Else
               'If the number is negative then complement the binary string
               'so it will display corectly in 2's complement form
               If BVNeg Then
                   TmpStr = ComplBinStr(TmpStr)
               End If
               txtFSW4.Text = TmpStr
            End If
         
         Case 8
            If FrqTyp = "F1" Then
               txtFTW1_5.Text = TmpStr
            ElseIf FrqTyp = "F2" Then
               txtFTW2_5.Text = TmpStr
            Else
               'If the number is negative then complement the binary string
               'so it will display corectly in 2's complement form
               If BVNeg Then
                   TmpStr = ComplBinStr(TmpStr)
               End If
               txtFSW5.Text = TmpStr
            End If
         
         Case 0
            If FrqTyp = "F1" Then
               txtFTW1_6.Text = TmpStr
            ElseIf FrqTyp = "F2" Then
               txtFTW2_6.Text = TmpStr
            Else
               'If the number is negative then complement the binary string
               'so it will display corectly in 2's complement form
               If BVNeg Then
                   TmpStr = ComplBinStr(TmpStr)
               End If
               txtFSW6.Text = TmpStr
            End If
         
      End Select
      
   Next i

End If

End Sub

Public Sub FTWMHz_Update(FrqTyp As String)

'This procedure calculates a frequency based upon
'the system clock and the tuning word values.

Dim BitVal As Variant, BitWrd As Variant, FulScl As Variant
Dim TmpStr As String, FmtStr As String, TxtStr As String
Dim SysClk As Single, FrqVal As Single
Dim BitLen As Integer, Wrd As Integer
Dim i As Integer, J As Integer

'Initial value - decimal subtype.
BitVal = CDec(0)

'For each tuning word byte.
For i = 1 To 6

   'Get current byte string.
   Select Case i
   
      Case 1
         If FrqTyp = "F1" Then
            TxtStr = txtFTW1_1.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = txtFTW2_1.Text
         Else
            TxtStr = txtFSW1.Text
         End If
         
      Case 2
         If FrqTyp = "F1" Then
            TxtStr = txtFTW1_2.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = txtFTW2_2.Text
         Else
            TxtStr = txtFSW2.Text
         End If
        
      Case 3
         If FrqTyp = "F1" Then
            TxtStr = txtFTW1_3.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = txtFTW2_3.Text
         Else
            TxtStr = txtFSW3.Text
         End If
         
      Case 4
         If FrqTyp = "F1" Then
            TxtStr = txtFTW1_4.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = txtFTW2_4.Text
         Else
            TxtStr = txtFSW4.Text
         End If

      Case 5
         If FrqTyp = "F1" Then
            TxtStr = txtFTW1_5.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = txtFTW2_5.Text
         Else
            TxtStr = txtFSW5.Text
         End If

      Case 6
         If FrqTyp = "F1" Then
            TxtStr = txtFTW1_6.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = txtFTW2_6.Text
         Else
            TxtStr = txtFSW6.Text
         End If
         
   End Select
      
   'Initialize.
   Wrd = 0
   
   'Compute numeric value.
   For J = 1 To 8

      TmpStr = Mid(TxtStr, J, 1)
      If TmpStr = "1" Then Wrd = Wrd + 2 ^ (J * -1 + 8)

   Next J

   'Compute running total.
   BitLen = (i * -1 + 6) * 8
   BitWrd = CDec(Wrd * 2 ^ BitLen)
   BitVal = BitVal + BitWrd
   
Next i

'Get system clock frequency.
GetSysClk SysClk

'Set full scale.
FulScl = CDec(2 ^ 48)

'Establish frequency value.
FrqVal = CSng(BitVal / FulScl * SysClk)

'Determine format string.
If FrqVal >= 100! Then
   FmtStr = "000.000"
ElseIf FrqVal >= 10! Then
   FmtStr = "00.0000"
Else
   FmtStr = "0.00000"
End If

'Display value.
If FrqTyp = "F1" Then
   txtFTW1MHz.Text = Format(FrqVal, FmtStr)
ElseIf FrqTyp = "F2" Then
   txtFTW2MHz.Text = Format(FrqVal, FmtStr)
Else
   txtFSWMHz.Text = Format(FrqVal, FmtStr)
End If

End Sub
Public Sub FTWMHz_Update1(FrqTyp As String)

'This procedure calculates a frequency based upon
'the system clock and the tuning word values.

Dim BitVal As Variant, BitWrd As Variant, FulScl As Variant
Dim TmpStr As String, FmtStr As String, TxtStr As String
Dim SysClk As Single, FrqVal As Single
Dim BitLen As Integer, Wrd As Integer
Dim i As Integer, J As Integer
Dim NegVal As Boolean 'Used to flag if the msb is positive

'Initial value - decimal subtype.
BitVal = CDec(0)

'For each tuning word byte.
For i = 1 To 6

   'Get current byte string.
   Select Case i
   
      Case 1
         If FrqTyp = "F1" Then
            TxtStr = TxtStr & txtFTW1_1.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = TxtStr & txtFTW2_1.Text
         Else
            TxtStr = TxtStr & txtFSW1.Text
            'Detect if the number is negative
            If Left(txtFSW1.Text, 1) = "1" And optChirpMode.Value Then
                NegVal = True
            End If
         End If
         
      Case 2
         If FrqTyp = "F1" Then
            TxtStr = TxtStr & txtFTW1_2.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = TxtStr & txtFTW2_2.Text
         Else
            TxtStr = TxtStr & txtFSW2.Text
         End If
        
      Case 3
         If FrqTyp = "F1" Then
            TxtStr = TxtStr & txtFTW1_3.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = TxtStr & txtFTW2_3.Text
         Else
            TxtStr = TxtStr & txtFSW3.Text
         End If
         
      Case 4
         If FrqTyp = "F1" Then
            TxtStr = TxtStr & txtFTW1_4.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = TxtStr & txtFTW2_4.Text
         Else
            TxtStr = TxtStr & txtFSW4.Text
         End If

      Case 5
         If FrqTyp = "F1" Then
            TxtStr = TxtStr & txtFTW1_5.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = TxtStr & txtFTW2_5.Text
         Else
            TxtStr = TxtStr & txtFSW5.Text
         End If

      Case 6
         If FrqTyp = "F1" Then
            TxtStr = TxtStr & txtFTW1_6.Text
         ElseIf FrqTyp = "F2" Then
            TxtStr = TxtStr & txtFTW2_6.Text
         Else
            TxtStr = TxtStr & txtFSW6.Text
         End If
         
   End Select
            
   'Initialize.
'   Wrd = 0
'
'   'Compute numeric value.
'   For J = 1 To 8
'
'      TmpStr = Mid(TxtStr, J, 1)
'      If TmpStr = "1" Then Wrd = Wrd + 2 ^ (J * -1 + 8)
'
'   Next J
'
'   'Compute running total.
'   BitLen = (i * -1 + 6) * 8
'   BitWrd = CDec(Wrd * 2 ^ BitLen)
'   BitVal = BitVal + BitWrd
   
Next i

'If the value is marked negative compliment all bits
If NegVal Then
    'Step through all bits
    For J = 1 To Len(TxtStr)
        If Mid(TxtStr, J, 1) = "1" Then
            TmpStr = TmpStr & "0"
        Else
            TmpStr = TmpStr & "1"
        End If
    Next
Else
    TmpStr = TxtStr
End If

'Initialize the value
BitVal = CDec(0)

'Convert to decimal
i = Len(TmpStr) - 1
For J = 0 To i
    If Mid(TmpStr, (i - J) + 1, 1) = "1" Then
        BitVal = BitVal + CDec(2 ^ J)
    End If
Next J

'If the value was a negative then subtract 1
If NegVal = True Then
    BitVal = BitVal - 1
End If

'Get system clock frequency.
GetSysClk SysClk

'Set full scale.
FulScl = CDec(2 ^ 48)

'Establish frequency value.
FrqVal = CSng(BitVal / FulScl * SysClk)

If NegVal Then
    FrqVal = -FrqVal
End If

'Determine format string.
If FrqVal >= 100! Then
   FmtStr = "000.000"
ElseIf FrqVal >= 10! Then
   FmtStr = "00.0000"
Else
   FmtStr = "0.00000"
End If

'Display value.
If FrqTyp = "F1" Then
   txtFTW1MHz.Text = Format(FrqVal, FmtStr)
ElseIf FrqTyp = "F2" Then
   txtFTW2MHz.Text = Format(FrqVal, FmtStr)
Else
   txtFSWMHz.Text = Format(FrqVal, FmtStr)
End If

End Sub




Public Sub PhAdj_Update(PhNum As String)

'This procedure updates the 14-bit binary number
'for phase adjust #1 and #2 based on the hex value.

Dim HexStr As String, TmpStr As String, BytStr As String
Dim i As Integer

'Get hex value string.
If PhNum = "1" Then
   HexStr = txtPhAdj1Hex.Text
Else
   HexStr = txtPhAdj2Hex.Text
End If

'If needed then prepend with zeros.
If Len(HexStr) < 4 Then

   HexStr = String(4 - Len(HexStr), 48) & HexStr

   'Rewrite to screen.
   If PhNum = "1" Then
      txtPhAdj1Hex.Text = HexStr
   Else
      txtPhAdj2Hex.Text = HexStr
   End If
   
End If

'Process first hex digit.
TmpStr = Mid(HexStr, 1, 1)

'Must be less than 3.
If Val("&H" & TmpStr) > 3 Then

   TmpStr = "3"
   
   'Rewrite value.
   If PhNum = "1" Then
      txtPhAdj1Hex.Text = TmpStr & Mid(HexStr, 2, 3)
   Else
      txtPhAdj2Hex.Text = TmpStr & Mid(HexStr, 2, 3)
   End If
   
End If

'Append binary digits.
Select Case TmpStr

   Case "0"
      BytStr = "00"
   Case "1"
      BytStr = "01"
   Case "2"
      BytStr = "10"
   Case "3"
      BytStr = "11"
         
End Select

'Process remaining hex digits.
For i = 2 To 4

   TmpStr = Mid(HexStr, i, 1)
   
   Select Case TmpStr
   
      Case "0"
         BytStr = BytStr & "0000"
      Case "1"
         BytStr = BytStr & "0001"
      Case "2"
         BytStr = BytStr & "0010"
      Case "3"
         BytStr = BytStr & "0011"
      Case "4"
         BytStr = BytStr & "0100"
      Case "5"
         BytStr = BytStr & "0101"
      Case "6"
         BytStr = BytStr & "0110"
      Case "7"
         BytStr = BytStr & "0111"
      Case "8"
         BytStr = BytStr & "1000"
      Case "9"
         BytStr = BytStr & "1001"
      Case "A"
         BytStr = BytStr & "1010"
      Case "B"
         BytStr = BytStr & "1011"
      Case "C"
         BytStr = BytStr & "1100"
      Case "D"
         BytStr = BytStr & "1101"
      Case "E"
         BytStr = BytStr & "1110"
      Case "F"
         BytStr = BytStr & "1111"
      
   End Select
   
Next i

'Write out binary values.
If PhNum = "1" Then
   txtPhAdj1_1.Text = Mid(BytStr, 1, 2)
   txtPhAdj1_2.Text = Mid(BytStr, 3, 4)
   txtPhAdj1_3.Text = Mid(BytStr, 7, 4)
   txtPhAdj1_4.Text = Mid(BytStr, 11, 4)
Else
   txtPhAdj2_1.Text = Mid(BytStr, 1, 2)
   txtPhAdj2_2.Text = Mid(BytStr, 3, 4)
   txtPhAdj2_3.Text = Mid(BytStr, 7, 4)
   txtPhAdj2_4.Text = Mid(BytStr, 11, 4)
End If

End Sub

Public Sub PhAdjHex_Update(PhNum As String)

'This procedure calculates the hex equivalent
'of the 14-bit binary Phase Adjust Register.

Dim TxtStr As String, TmpStr As String, HexStr As String
Dim i As Integer, J As Integer, Wrd As Integer

'For the first two binary MSB's.
If PhNum = "1" Then
   TxtStr = txtPhAdj1_1.Text
Else
   TxtStr = txtPhAdj2_1.Text
End If

'Initialize.
Wrd = 0

'Compute numeric value.
For i = 1 To 2

   TmpStr = Mid(TxtStr, i, 1)
   If TmpStr = "1" Then Wrd = Wrd + 2 ^ (i * -1 + 2)

Next i

'Select hex digit.
Select Case Wrd
   
   Case 0
      HexStr = "0"
   Case 1
      HexStr = "1"
   Case 2
      HexStr = "2"
   Case 3
      HexStr = "3"

End Select

'For the three remaining nibbles.
For i = 2 To 4

   'Get current nibble string.
   Select Case i
   
      Case 2
         If PhNum = "1" Then
            TxtStr = txtPhAdj1_2.Text
         Else
            TxtStr = txtPhAdj2_2.Text
         End If
      Case 3
         If PhNum = "1" Then
            TxtStr = txtPhAdj1_3.Text
         Else
            TxtStr = txtPhAdj2_3.Text
         End If
      Case 4
         If PhNum = "1" Then
            TxtStr = txtPhAdj1_4.Text
         Else
            TxtStr = txtPhAdj2_4.Text
         End If
         
   End Select
      
   'Initialize.
   Wrd = 0
   
   'Compute numeric value.
   For J = 1 To 4

      TmpStr = Mid(TxtStr, J, 1)
      If TmpStr = "1" Then Wrd = Wrd + 2 ^ (J * -1 + 4)
   
   Next J
   
   'Select hex digit.
   Select Case Wrd
   
      Case 0
         HexStr = HexStr & "0"
      Case 1
         HexStr = HexStr & "1"
      Case 2
         HexStr = HexStr & "2"
      Case 3
         HexStr = HexStr & "3"
      Case 4
         HexStr = HexStr & "4"
      Case 5
         HexStr = HexStr & "5"
      Case 6
         HexStr = HexStr & "6"
      Case 7
         HexStr = HexStr & "7"
      Case 8
         HexStr = HexStr & "8"
      Case 9
         HexStr = HexStr & "9"
      Case 10
         HexStr = HexStr & "A"
      Case 11
         HexStr = HexStr & "B"
      Case 12
         HexStr = HexStr & "C"
      Case 13
         HexStr = HexStr & "D"
      Case 14
         HexStr = HexStr & "E"
      Case 15
         HexStr = HexStr & "F"

   End Select

Next i

'Display hex value.
If PhNum = "1" Then
   txtPhAdj1Hex.Text = HexStr
Else
   txtPhAdj2Hex.Text = HexStr
End If

End Sub

Public Sub FSR_Update()

'This procedure updates the 20-bit binary number
'for frequency step rate based on the hex value.

Dim HexStr As String, TmpStr As String, BytStr As String
Dim i As Integer

'Get hex value string.
HexStr = txtFSRHex.Text

'If needed then prepend with zeros.
If Len(HexStr) < 5 Then

   HexStr = String(4 - Len(HexStr), 48) & HexStr

   'Rewrite to screen.
   txtFSRHex.Text = HexStr
   
End If

'Initialize byte string.
BytStr = ""

'Process hex digits.
For i = 1 To 5

   TmpStr = Mid(HexStr, i, 1)
   
   Select Case TmpStr
   
      Case "0"
         BytStr = BytStr & "0000"
      Case "1"
         BytStr = BytStr & "0001"
      Case "2"
         BytStr = BytStr & "0010"
      Case "3"
         BytStr = BytStr & "0011"
      Case "4"
         BytStr = BytStr & "0100"
      Case "5"
         BytStr = BytStr & "0101"
      Case "6"
         BytStr = BytStr & "0110"
      Case "7"
         BytStr = BytStr & "0111"
      Case "8"
         BytStr = BytStr & "1000"
      Case "9"
         BytStr = BytStr & "1001"
      Case "A"
         BytStr = BytStr & "1010"
      Case "B"
         BytStr = BytStr & "1011"
      Case "C"
         BytStr = BytStr & "1100"
      Case "D"
         BytStr = BytStr & "1101"
      Case "E"
         BytStr = BytStr & "1110"
      Case "F"
         BytStr = BytStr & "1111"
      
   End Select
   
Next i

'Write out binary values.
txtFSR1.Text = Mid(BytStr, 1, 4)
txtFSR2.Text = Mid(BytStr, 5, 4)
txtFSR3.Text = Mid(BytStr, 9, 4)
txtFSR4.Text = Mid(BytStr, 13, 4)
txtFSR5.Text = Mid(BytStr, 17, 4)
   
End Sub

Public Sub FSRHex_Update()

'This procedure calculates the hex equivalent
'of the 20-bit binary Frequency Step Rate.

Dim TxtStr As String, TmpStr As String, HexStr As String
Dim i As Integer, J As Integer, Wrd As Integer

'Initialize.
HexStr = ""

'For five hex digits.
For i = 1 To 5

   'Get current binary bits.
   Select Case i
      
      Case 1
         TxtStr = txtFSR1.Text
      Case 2
         TxtStr = txtFSR2.Text
      Case 3
         TxtStr = txtFSR3.Text
      Case 4
         TxtStr = txtFSR4.Text
      Case 5
         TxtStr = txtFSR5.Text
         
   End Select
   
   'Initialize.
   Wrd = 0

   'Compute numeric value.
   For J = 1 To 4

      TmpStr = Mid(TxtStr, J, 1)
      If TmpStr = "1" Then Wrd = Wrd + 2 ^ (J * -1 + 4)

   Next J

   'Select hex digit.
   Select Case Wrd
   
      Case 0
         HexStr = HexStr & "0"
      Case 1
         HexStr = HexStr & "1"
      Case 2
         HexStr = HexStr & "2"
      Case 3
         HexStr = HexStr & "3"
      Case 4
         HexStr = HexStr & "4"
      Case 5
         HexStr = HexStr & "5"
      Case 6
         HexStr = HexStr & "6"
      Case 7
         HexStr = HexStr & "7"
      Case 8
         HexStr = HexStr & "8"
      Case 9
         HexStr = HexStr & "9"
      Case 10
         HexStr = HexStr & "A"
      Case 11
         HexStr = HexStr & "B"
      Case 12
         HexStr = HexStr & "C"
      Case 13
         HexStr = HexStr & "D"
      Case 14
         HexStr = HexStr & "E"
      Case 15
         HexStr = HexStr & "F"

   End Select

Next i

'Display value.
txtFSRHex.Text = HexStr
   
End Sub

Public Sub cmdLoad_Click()

Dim IntVal As Integer
Dim TmpStr As String

'If parallel mode.
If PMode = 16 Then

    'Write Phase Adjust #1 registers.
    TmpStr = "00" & txtPhAdj1_1.Text & txtPhAdj1_2.Text
    IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
    PWrite IntVal, 0
    
    TmpStr = txtPhAdj1_3.Text & txtPhAdj1_4.Text
    IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
    PWrite IntVal, 1
         
   If optBPSKmode.Value = True Then
   
      'Write Phase Adjust #2 registers.
      TmpStr = "00" & txtPhAdj2_1.Text & txtPhAdj2_2.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 2
   
      TmpStr = txtPhAdj2_3.Text & txtPhAdj2_4.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 3
         
   End If
      
   'Write FTW1 registers.
   TmpStr = txtFTW1_1.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 4
   
   TmpStr = txtFTW1_2.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 5
  
   TmpStr = txtFTW1_3.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 6
   
   TmpStr = txtFTW1_4.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 7
   
   TmpStr = txtFTW1_5.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 8
   
   TmpStr = txtFTW1_6.Text
   IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
   PWrite IntVal, 9
      
   If (optUnrampedFSK.Value = True) Or (optRampedFSK.Value = True) Then
   
      'Write FTW2 registers.
      TmpStr = txtFTW2_1.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 10
   
      TmpStr = txtFTW2_2.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 11
   
      TmpStr = txtFTW2_3.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 12
   
      TmpStr = txtFTW2_4.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 13
   
      TmpStr = txtFTW2_5.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 14
      
      TmpStr = txtFTW2_6.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 15
         
      End If
      
   If (optRampedFSK.Value = True) Or (optChirpMode.Value = True) Then
   
      'Write FSW registers.
      TmpStr = txtFSW1.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 16
   
      TmpStr = txtFSW2.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 17
   
      TmpStr = txtFSW3.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 18
   
      TmpStr = txtFSW4.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 19
   
      TmpStr = txtFSW5.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 20
   
      TmpStr = txtFSW6.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 21
         
      'Write FSR registers.
      TmpStr = "0000" & txtFSR1.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 26
    
      TmpStr = txtFSR2.Text & txtFSR3.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 27
    
      TmpStr = txtFSR4.Text & txtFSR5.Text
      IntFrmBinStr IntVal, TmpStr, Len(TmpStr)
      PWrite IntVal, 28
         
      End If
      
   'Write mode control register 31.
   If optSingleTone.Value = True Then
      IntVal = 0
   ElseIf optUnrampedFSK.Value = True Then
      IntVal = 2
   ElseIf optRampedFSK.Value = True Then
      IntVal = 4
   ElseIf optChirpMode.Value = True Then
      IntVal = 6
   ElseIf optBPSKmode.Value = True Then
      IntVal = 8
   End If
      
   If chkTriangle.Value = 1 Then IntVal = IntVal + 32
   If chkACC2.Value = 1 Then IntVal = IntVal + 64
   If chkACC1.Value = 1 Then IntVal = IntVal + 128
      
   If frmClock.optInternal.Value = True Then IntVal = IntVal + 1
   If frmControl.chkSrcQDac.Value = 1 Then IntVal = IntVal + 16
      
   PWrite IntVal, 31
      
'Serial mode.
Else

    'Write Phase Adjust #1 registers.
    TmpStr = "00" & txtPhAdj1_1.Text & txtPhAdj1_2.Text
    TmpStr = TmpStr & txtPhAdj1_3.Text & txtPhAdj1_4.Text
    SWrite TmpStr, "0000"
       
   If optBPSKmode.Value = True Then
   
      'Write Phase Adjust #2 registers.
      TmpStr = "00" & txtPhAdj2_1.Text & txtPhAdj2_2.Text
      TmpStr = TmpStr & txtPhAdj2_3.Text & txtPhAdj2_4.Text
      SWrite TmpStr, "0001"
         
   End If
      
   'Write FTW #1 registers.
   TmpStr = txtFTW1_1.Text & txtFTW1_2.Text
   TmpStr = TmpStr & txtFTW1_3.Text & txtFTW1_4.Text
   TmpStr = TmpStr & txtFTW1_5.Text & txtFTW1_6.Text
   SWrite TmpStr, "0010"
      
   If (optUnrampedFSK.Value = True) Or (optRampedFSK.Value = True) Then
   
      'Write FTW #2 registers.
      TmpStr = txtFTW2_1.Text & txtFTW2_2.Text
      TmpStr = TmpStr & txtFTW2_3.Text & txtFTW2_4.Text
      TmpStr = TmpStr & txtFTW2_5.Text & txtFTW2_6.Text
      SWrite TmpStr, "0011"
      
      End If
      
   If (optRampedFSK.Value = True) Or (optChirpMode.Value = True) Then
   
      'Write FSW registers.
      TmpStr = txtFSW1.Text & txtFSW2.Text
      TmpStr = TmpStr & txtFSW3.Text & txtFSW4.Text
      TmpStr = TmpStr & txtFSW5.Text & txtFSW6.Text
      SWrite TmpStr, "0100"
      
      'Write FSR registers.
      TmpStr = "0000" & txtFSR1.Text & txtFSR2.Text & txtFSR3.Text
      TmpStr = TmpStr & txtFSR4.Text & txtFSR5.Text
      SWrite TmpStr, "0110"
      
      End If
      
   'Get control regsiter string.
   GetSerMdeStr TmpStr
   
   'Write updated control register.
   SWrite TmpStr, "0111"
      
End If

End Sub

Public Sub cmdReset_Click()
    
    PMode = 16
    LSB1st = 0
    
    FData = 0
    ORamp = 0
    
    RBE = 0&
    
    'Initialize latch lines and RBE.
    Call frmLPTSelect.LptOutput(lpt_bp2_ControlReg, 11&)
    Deelay DeelayValue
    
    'Set data bus low.
    Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
    Deelay DeelayValue
    LatchData
    
    'Set address bus low.
    Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255&)
    Deelay DeelayValue
    LatchAddr
    
    'Set WRBAR,RDBAR,RESET,PMODE high.
    'Set UDCLK,FDATA,ORAMP low.
    Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 232&)
    Deelay DeelayValue
    LatchCtrl
    
    'Set WRBAR,RDBAR,PMODE high.
    'Set RESET,UDCLK,FDATA,ORAMP low.
    Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 236&)
    Deelay DeelayValue
    LatchCtrl
    
    'Reset frequency form.
    txtFTW1MHz.Text = Format(0, "0.00000")
'    txtFTW1MHz.Text = "0.00000"
    FTW_Update "F1"
    
    txtFTW2MHz.Text = Format(0, "0.00000")
'    txtFTW2MHz.Text = "0.00000"
    FTW_Update "F2"
    
    txtFSWMHz.Text = Format(0, "0.00000")
'    txtFSWMHz.Text = "0.00000"
    FTW_Update "FSW"
    
    txtFSRHex.Text = "00000"
    FSR_Update
    
    txtPhAdj1Hex.Text = "0000"
    PhAdj_Update "1"
    
    txtPhAdj2Hex.Text = "0000"
    PhAdj_Update "2"
    
    chkTriangle.Value = 0
    chkACC1.Value = 0
    chkACC2.Value = 0
    
    optSingleTone.Value = True
    optFDataLo.Value = True
    optORampLo.Value = True
    
    'Reset clock form.
    frmClock.optPLL_Hi.Value = True
    frmClock.optInternal.Value = True
    frmClock.chkBypassPLL.Value = 1
    
    OldPll = "04"
    
    frmClock.txtUDCLKHex.Text = "00000040"
    frmClock.UDCLK_Update "Hex"
    frmClock.UDCLKMHz_Update
    
    'Reset amplitude form.
    frmAmplitude.optOutAmpProg.Value = True
    frmAmplitude.optUseFixed.Value = True
    
    frmAmplitude.txtIChanHex.Text = "000"
    frmAmplitude.Chan_Update "I"
    
    frmAmplitude.txtQChanHex.Text = "000"
    frmAmplitude.Chan_Update "Q"
    
    frmAmplitude.txtORRHex.Text = "80"
    frmAmplitude.ORR_Update
    
    'Reset control form.
    frmControl.chkAllDacPwrDwn.Value = 0
    frmControl.chkCompPwrDwn.Value = 1
    frmControl.chkFulDigPwrDwn.Value = 0
    frmControl.chkPllPwrDwn.Value = 0
    frmControl.chkQDacPwrDwn.Value = 0
    
    frmControl.chkBypInvSinc.Value = 0
    frmControl.chkSrcQDac.Value = 0
    
    frmControl.chkLSB1st.Value = 0
    frmControl.optParallel.Value = True
    
    frmControl.txtQDacHex.Text = "000"
    frmControl.QDac_Update
    
End Sub

Private Sub cmdShowTestWindow_Click()
    If frmTest.Visible Then
        frmTest.ZOrder
    Else
        frmTest.Show
    End If
End Sub

Public Sub Form_Load()

Height = 7500
Width = 10095
Left = 100
Top = 100

End Sub

Public Sub optBPSKmode_Click()

Dim A As String, B As String, C As String

A = "BPSK mode outputs FTW #1 plus the value of"
B = Space(1)
C = "Phase Adjust #1 or #2 based on the BPSK pin."

'change mode label
lblMode.Caption = A & B & C

'disable FTW #2
txtFTW2_1.Enabled = False
txtFTW2_2.Enabled = False
txtFTW2_3.Enabled = False
txtFTW2_4.Enabled = False
txtFTW2_5.Enabled = False
txtFTW2_6.Enabled = False
txtFTW2MHz.Enabled = False
lblFTW2.Enabled = False
lblFTW2Eql.Enabled = False
lblFTW2MHz.Enabled = False

'disable FSW
txtFSW1.Enabled = False
txtFSW2.Enabled = False
txtFSW3.Enabled = False
txtFSW4.Enabled = False
txtFSW5.Enabled = False
txtFSW6.Enabled = False
txtFSWMHz.Enabled = False
lblFSW.Enabled = False
lblFSWEql.Enabled = False
lblFSWMHz.Enabled = False

'disable FSR
txtFSR1.Enabled = False
txtFSR2.Enabled = False
txtFSR3.Enabled = False
txtFSR4.Enabled = False
txtFSR5.Enabled = False
txtFSRHex.Enabled = False
lblFSR.Enabled = False
lblFSRHex.Enabled = False

'enable Phase Adjust #1
txtPhAdj1_1.Enabled = True
txtPhAdj1_2.Enabled = True
txtPhAdj1_3.Enabled = True
txtPhAdj1_4.Enabled = True
txtPhAdj1Hex.Enabled = True
lblPhAdj1.Enabled = True
lblPhAdj1Hex.Enabled = True

'enable Phase Adjust #2
txtPhAdj2_1.Enabled = True
txtPhAdj2_2.Enabled = True
txtPhAdj2_3.Enabled = True
txtPhAdj2_4.Enabled = True
txtPhAdj2Hex.Enabled = True
lblPhAdj2.Enabled = True
lblPhAdj2Hex.Enabled = True

End Sub

Public Sub optChirpMode_Click()

Dim A As String, B As String, C As String

A = "Chirp mode allows unrestricted frequency"
B = Space(1)
C = "step/rate updates in high-speed real-time fashion."

'change mode label
lblMode.Caption = A & B & C

'disable FTW #2
txtFTW2_1.Enabled = False
txtFTW2_2.Enabled = False
txtFTW2_3.Enabled = False
txtFTW2_4.Enabled = False
txtFTW2_5.Enabled = False
txtFTW2_6.Enabled = False
txtFTW2MHz.Enabled = False
lblFTW2.Enabled = False
lblFTW2Eql.Enabled = False
lblFTW2MHz.Enabled = False

'enable FSW
txtFSW1.Enabled = True
txtFSW2.Enabled = True
txtFSW3.Enabled = True
txtFSW4.Enabled = True
txtFSW5.Enabled = True
txtFSW6.Enabled = True
txtFSWMHz.Enabled = True
lblFSW.Enabled = True
lblFSWEql.Enabled = True
lblFSWMHz.Enabled = True

'enable FSR
txtFSR1.Enabled = True
txtFSR2.Enabled = True
txtFSR3.Enabled = True
txtFSR4.Enabled = True
txtFSR5.Enabled = True
txtFSRHex.Enabled = True
lblFSR.Enabled = True
lblFSRHex.Enabled = True

'disable Phase Adjust #1
'txtPhAdj1_1.Enabled = False
'txtPhAdj1_2.Enabled = False
'txtPhAdj1_3.Enabled = False
'txtPhAdj1_4.Enabled = False
'txtPhAdj1Hex.Enabled = False
'lblPhAdj1.Enabled = False
'lblPhAdj1Hex.Enabled = False

'disable Phase Adjust #2
txtPhAdj2_1.Enabled = False
txtPhAdj2_2.Enabled = False
txtPhAdj2_3.Enabled = False
txtPhAdj2_4.Enabled = False
txtPhAdj2Hex.Enabled = False
lblPhAdj2.Enabled = False
lblPhAdj2Hex.Enabled = False

End Sub

Public Sub optRampedFSK_Click()

Dim A As String, B As String, C As String

A = "Ramped FSK adds programmable step and rate"
B = Space(1)
C = "frequency ramping between frequencies."

'change mode label
lblMode.Caption = A & B & C

'enable FTW #2
txtFTW2_1.Enabled = True
txtFTW2_2.Enabled = True
txtFTW2_3.Enabled = True
txtFTW2_4.Enabled = True
txtFTW2_5.Enabled = True
txtFTW2_6.Enabled = True
txtFTW2MHz.Enabled = True
lblFTW2.Enabled = True
lblFTW2Eql.Enabled = True
lblFTW2MHz.Enabled = True

'enable FSW
txtFSW1.Enabled = True
txtFSW2.Enabled = True
txtFSW3.Enabled = True
txtFSW4.Enabled = True
txtFSW5.Enabled = True
txtFSW6.Enabled = True
txtFSWMHz.Enabled = True
lblFSW.Enabled = True
lblFSWEql.Enabled = True
lblFSWMHz.Enabled = True

If txtFSWMHz.Text Then
    'If the frequecy step value is negative make it positive
    txtFSWMHz.Text = Abs(txtFSWMHz.Text)
    txtFSWMHz_KeyPress 13
End If

'enable FSR
txtFSR1.Enabled = True
txtFSR2.Enabled = True
txtFSR3.Enabled = True
txtFSR4.Enabled = True
txtFSR5.Enabled = True
txtFSRHex.Enabled = True
lblFSR.Enabled = True
lblFSRHex.Enabled = True

'disable Phase Adjust #1
'txtPhAdj1_1.Enabled = False
'txtPhAdj1_2.Enabled = False
'txtPhAdj1_3.Enabled = False
'txtPhAdj1_4.Enabled = False
'txtPhAdj1Hex.Enabled = False
'lblPhAdj1.Enabled = False
'lblPhAdj1Hex.Enabled = False

'disable Phase Adjust #2
txtPhAdj2_1.Enabled = False
txtPhAdj2_2.Enabled = False
txtPhAdj2_3.Enabled = False
txtPhAdj2_4.Enabled = False
txtPhAdj2Hex.Enabled = False
lblPhAdj2.Enabled = False
lblPhAdj2Hex.Enabled = False

End Sub

Public Sub optSingleTone_Click()

Dim A As String, B As String, C As String

A = "Single Tone mode outputs the frequency"
B = Space(1)
C = "determined by Frequency Tuning Word (FTW) #1."

'change mode label
lblMode.Caption = A & B & C

'disable FTW #2
txtFTW2_1.Enabled = False
txtFTW2_2.Enabled = False
txtFTW2_3.Enabled = False
txtFTW2_4.Enabled = False
txtFTW2_5.Enabled = False
txtFTW2_6.Enabled = False
txtFTW2MHz.Enabled = False
lblFTW2.Enabled = False
lblFTW2Eql.Enabled = False
lblFTW2MHz.Enabled = False

'disable FSW
txtFSW1.Enabled = False
txtFSW2.Enabled = False
txtFSW3.Enabled = False
txtFSW4.Enabled = False
txtFSW5.Enabled = False
txtFSW6.Enabled = False
txtFSWMHz.Enabled = False
lblFSW.Enabled = False
lblFSWEql.Enabled = False
lblFSWMHz.Enabled = False

'disable FSR
txtFSR1.Enabled = False
txtFSR2.Enabled = False
txtFSR3.Enabled = False
txtFSR4.Enabled = False
txtFSR5.Enabled = False
txtFSRHex.Enabled = False
lblFSR.Enabled = False
lblFSRHex.Enabled = False

'disable Phase Adjust #1
'txtPhAdj1_1.Enabled = False
'txtPhAdj1_2.Enabled = False
'txtPhAdj1_3.Enabled = False
'txtPhAdj1_4.Enabled = False
'txtPhAdj1Hex.Enabled = False
'lblPhAdj1.Enabled = False
'lblPhAdj1Hex.Enabled = False

'disable Phase Adjust #2
txtPhAdj2_1.Enabled = False
txtPhAdj2_2.Enabled = False
txtPhAdj2_3.Enabled = False
txtPhAdj2_4.Enabled = False
txtPhAdj2Hex.Enabled = False
lblPhAdj2.Enabled = False
lblPhAdj2Hex.Enabled = False

End Sub

Public Sub optUnrampedFSK_Click()

Dim A As String, B As String, C As String

A = "Unramped FSK outputs either FTW #1 or FTW #2"
B = Space(1)
C = "based upon the state of the FSK pin."

'change mode label
lblMode.Caption = A & B & C

'enable FTW #2
txtFTW2_1.Enabled = True
txtFTW2_2.Enabled = True
txtFTW2_3.Enabled = True
txtFTW2_4.Enabled = True
txtFTW2_5.Enabled = True
txtFTW2_6.Enabled = True
txtFTW2MHz.Enabled = True
lblFTW2.Enabled = True
lblFTW2Eql.Enabled = True
lblFTW2MHz.Enabled = True

'disable FSW
txtFSW1.Enabled = False
txtFSW2.Enabled = False
txtFSW3.Enabled = False
txtFSW4.Enabled = False
txtFSW5.Enabled = False
txtFSW6.Enabled = False
txtFSWMHz.Enabled = False
lblFSW.Enabled = False
lblFSWEql.Enabled = False
lblFSWMHz.Enabled = False

'disable FSR
txtFSR1.Enabled = False
txtFSR2.Enabled = False
txtFSR3.Enabled = False
txtFSR4.Enabled = False
txtFSR5.Enabled = False
txtFSRHex.Enabled = False
lblFSR.Enabled = False
lblFSRHex.Enabled = False

'disable Phase Adjust #1
'txtPhAdj1_1.Enabled = False
'txtPhAdj1_2.Enabled = False
'txtPhAdj1_3.Enabled = False
'txtPhAdj1_4.Enabled = False
'txtPhAdj1Hex.Enabled = False
'lblPhAdj1.Enabled = False
'lblPhAdj1Hex.Enabled = False

'disable Phase Adjust #2
txtPhAdj2_1.Enabled = False
txtPhAdj2_2.Enabled = False
txtPhAdj2_3.Enabled = False
txtPhAdj2_4.Enabled = False
txtPhAdj2Hex.Enabled = False
lblPhAdj2.Enabled = False
lblPhAdj2Hex.Enabled = False

End Sub

Public Sub optFDataHi_Click()

Dim LCtl As Long

FData = 64

'If parallel mode.
If PMode = 16 Then

   'Set WRBAR,RDBAR,PMODE high.
   'Set RESET,UDCLK low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(19 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

Else

   'Set CS,SCLK high.
   'Set RESET,UDCLK,PMODE low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(3 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

End If

End Sub

Public Sub optFDataLo_Click()

Dim LCtl As Long

FData = 0

'If parallel mode.
If PMode = 16 Then

   'Set WRBAR,RDBAR,PMODE high.
   'Set RESET,UDCLK low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(19 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

Else

   'Set CS,SCLK high.
   'Set RESET,UDCLK,PMODE low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(3 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

End If

End Sub

Public Sub optORampHi_Click()

Dim LCtl As Long

ORamp = 32

'If parallel mode.
If PMode = 16 Then

   'Set WRBAR,RDBAR,PMODE high.
   'Set RESET,UDCLK low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(19 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

Else

   'Set CS,SCLK high.
   'Set RESET,UDCLK,PMODE low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(3 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

End If

End Sub

Public Sub optORampLo_Click()

Dim LCtl As Long

ORamp = 0

'If parallel mode.
If PMode = 16 Then

   'Set WRBAR,RDBAR,PMODE high.
   'Set RESET,UDCLK low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(19 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

Else

   'Set CS,SCLK high.
   'Set RESET,UDCLK,PMODE low.
   'Set FDATA,ORAMP accordingly.
   LCtl = CLng(3 + FData + ORamp)
   Call frmLPTSelect.LptOutput(lpt_bp0_DataReg, 255& - LCtl)
   Deelay DeelayValue
   LatchCtrl

End If

End Sub

Private Sub txtFSWMHz_GotFocus()
    'Select all the text
    SelectAllTxt txtFSWMHz
End Sub

Private Sub txtFTW1MHz_GotFocus()
    'Select all the text
    SelectAllTxt txtFTW1MHz
End Sub

Private Sub txtFTW2MHz_GotFocus()
    'Select all the text
    SelectAllTxt txtFTW2MHz
End Sub

Public Sub txtPhAdj1_1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtPhAdj1_1.Text) < 2 Then
      
         txtPhAdj1_1.Text = txtPhAdj1_1.Text & String(2 - Len(txtPhAdj1_1.Text), 48)
         
      End If
      
      PhAdjHex_Update "1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj1_2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtPhAdj1_2.Text) < 4 Then
      
         txtPhAdj1_2.Text = txtPhAdj1_2.Text & String(4 - Len(txtPhAdj1_2.Text), 48)
         
      End If
      
      PhAdjHex_Update "1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj1_3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtPhAdj1_3.Text) < 4 Then
      
         txtPhAdj1_3.Text = txtPhAdj1_3.Text & String(4 - Len(txtPhAdj1_3.Text), 48)
         
      End If
      
      PhAdjHex_Update "1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj1_4_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtPhAdj1_4.Text) < 4 Then
      
         txtPhAdj1_4.Text = txtPhAdj1_4.Text & String(4 - Len(txtPhAdj1_4.Text), 48)
         
      End If
      
      PhAdjHex_Update "1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj1Hex_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only hex
'characters "0" to "F" plus BS, DEL, and CR.

Select Case KeyAscii
      
   Case Is < 8, 9 To 12, 14 To 47, 58 To 64, 71 To 96, Is > 102
   
      KeyAscii = 0
      
   Case 97 To 102
   
      KeyAscii = KeyAscii - 32
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtPhAdj1Hex.Text) < 4 Then
      
         txtPhAdj1Hex.Text = String(4 - Len(txtPhAdj1Hex.Text), 48) & txtPhAdj1Hex.Text
         
      End If
      
      PhAdj_Update "1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj2_1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtPhAdj2_1.Text) < 4 Then
      
         txtPhAdj2_1.Text = txtPhAdj2_1.Text & String(4 - Len(txtPhAdj2_1.Text), 48)
         
      End If
      
      PhAdjHex_Update "2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj2_2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtPhAdj2_2.Text) < 4 Then
      
         txtPhAdj2_2.Text = txtPhAdj2_2.Text & String(4 - Len(txtPhAdj2_2.Text), 48)
         
      End If
      
      PhAdjHex_Update "2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj2_3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtPhAdj2_3.Text) < 4 Then
      
         txtPhAdj2_3.Text = txtPhAdj2_3.Text & String(4 - Len(txtPhAdj2_3.Text), 48)
         
      End If
      
      PhAdjHex_Update "2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj2_4_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtPhAdj2_4.Text) < 4 Then
      
         txtPhAdj2_4.Text = txtPhAdj2_4.Text & String(4 - Len(txtPhAdj2_4.Text), 48)
         
      End If
      
      PhAdjHex_Update "2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtPhAdj2Hex_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only hex
'characters "0" to "F" plus BS, DEL, and CR.

Select Case KeyAscii
      
   Case Is < 8, 9 To 12, 14 To 47, 58 To 64, 71 To 96, Is > 102
   
      KeyAscii = 0
      
   Case 97 To 102
   
      KeyAscii = KeyAscii - 32
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtPhAdj2Hex.Text) < 4 Then
      
         txtPhAdj2Hex.Text = String(4 - Len(txtPhAdj2Hex.Text), 48) & txtPhAdj2Hex.Text
         
      End If
      
      PhAdj_Update "2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSR1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtFSR1.Text) < 4 Then
      
         txtFSR1.Text = txtFSR1.Text & String(4 - Len(txtFSR1.Text), 48)
         
      End If
      
      FSRHex_Update

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSR2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtFSR2.Text) < 4 Then
      
         txtFSR2.Text = txtFSR2.Text & String(4 - Len(txtFSR2.Text), 48)
         
      End If
      
      FSRHex_Update

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSR3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtFSR3.Text) < 4 Then
      
         txtFSR3.Text = txtFSR3.Text & String(4 - Len(txtFSR3.Text), 48)
         
      End If
      
      FSRHex_Update

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSR4_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtFSR4.Text) < 4 Then
      
         txtFSR4.Text = txtFSR4.Text & String(4 - Len(txtFSR4.Text), 48)
         
      End If
      
      FSRHex_Update

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSR5_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      'Append zeros if necessary.
      If Len(txtFSR5.Text) < 4 Then
      
         txtFSR5.Text = txtFSR5.Text & String(4 - Len(txtFSR5.Text), 48)
         
      End If
      
      FSRHex_Update

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSRHex_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only hex
'characters "0" to "F" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, 58 To 64, 71 To 96, Is > 102
   
      KeyAscii = 0
      
   Case 97 To 102
   
      KeyAscii = KeyAscii - 32
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFSRHex.Text) < 5 Then
      
         txtFSRHex.Text = String(5 - Len(txtFSRHex.Text), 48) & txtFSRHex.Text
         
      End If
      
      FSR_Update

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW1_1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW1_1.Text) < 8 Then
      
         txtFTW1_1.Text = txtFTW1_1.Text & String(8 - Len(txtFTW1_1.Text), 48)
         
      End If
      
      FTWMHz_Update "F1"
      
      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW1_2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW1_2.Text) < 8 Then
      
         txtFTW1_2.Text = txtFTW1_2.Text & String(8 - Len(txtFTW1_2.Text), 48)
         
      End If
      
      FTWMHz_Update "F1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW1_3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW1_3.Text) < 8 Then
      
         txtFTW1_3.Text = txtFTW1_3.Text & String(8 - Len(txtFTW1_3.Text), 48)
         
      End If
      
      FTWMHz_Update "F1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW1_4_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW1_4.Text) < 8 Then
      
         txtFTW1_4.Text = txtFTW1_4.Text & String(8 - Len(txtFTW1_4.Text), 48)
         
      End If
      
      FTWMHz_Update "F1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW1_5_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW1_5.Text) < 8 Then
      
         txtFTW1_5.Text = txtFTW1_5.Text & String(8 - Len(txtFTW1_5.Text), 48)
         
      End If
      
      FTWMHz_Update "F1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW1_6_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW1_6.Text) < 8 Then
      
         txtFTW1_6.Text = txtFTW1_6.Text & String(8 - Len(txtFTW1_6.Text), 48)
         
      End If
      
      FTWMHz_Update "F1"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW1MHz_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only numeric
'characters "0" thru "9" plus "." and BS, DEL, and CR.

Dim FrqVal As Single

Select Case KeyAscii
    Case MyLocInfo.iDecSep 'Pass the decimal seperator
        'Check to see if a Decimal Seperator is allready in the string
        If InStr(1, txtFTW1MHz.Text, MyLocInfo.sDecSep) And txtFTW1MHz.SelLength <> Len(txtFTW1MHz.Text) Then
            'If so then trash the key
            KeyAscii = 0
        End If
    '   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
    '
    '      KeyAscii = 0
       
    Case 0 To 12 'Control Keys
    Case 14 To 32  'Control Keys
    Case 48 To 57 'Numeric Keys
    Case 13
    
        KeyAscii = 0
        
        If Not IsNumeric(txtFTW1MHz.Text) Then
            FrqVal = 0
        Else
            FrqVal = CSng(txtFTW1MHz.Text)
        End If
        
        
        'Determine the suggested maximum output frequency
        'and display a warning if the value entered by the
        'user exceeds this maximum value. If the value entered
        'by the user exceeds the system clock frequency then
        'the output frequency defaults to nyquist
        
        Dim ClkVal As Single
        Dim MaxVal As Single
        Dim MsgStr As String
        
        Call GetSysClk(ClkVal)
        MaxVal = 0.4 * ClkVal
        If (FrqVal > MaxVal) Then
         
            MsgStr = "Suggested frequency tuning word: < " & MaxVal & " MHz"
            Call MsgBox(MsgStr, 0, "Warning!")
            
            If FrqVal > ClkVal Then
                
                MsgStr = "Please enter a frequency below the system clock frequency (" & ClkVal & " MHz)"
                Call MsgBox(MsgStr, 0, "Warning!")
                
            End If
            
        End If
        
        If FrqVal >= 100 Then
            
            txtFTW1MHz.Text = Format(FrqVal, "000.000")
        
        ElseIf FrqVal >= 10 Then
            
            txtFTW1MHz.Text = Format(FrqVal, "00.0000")
            
        Else
            
            txtFTW1MHz.Text = Format(FrqVal, "0.00000")
            
        End If
        If FrqVal <= ClkVal Then
            
            FTW_Update "F1"
            cmdLoad.SetFocus
            
        End If
        
    Case Else 'Trash all other keys
       KeyAscii = 0
End Select

End Sub

Public Sub txtFTW2_1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW2_1.Text) < 8 Then
      
         txtFTW2_1.Text = txtFTW2_1.Text & String(8 - Len(txtFTW2_1.Text), 48)
         
      End If
      
      FTWMHz_Update "F2"
      
      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW2_2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW2_2.Text) < 8 Then
      
         txtFTW2_2.Text = txtFTW2_2.Text & String(8 - Len(txtFTW2_2.Text), 48)
         
      End If
      
      FTWMHz_Update "F2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW2_3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW2_3.Text) < 8 Then
      
         txtFTW2_3.Text = txtFTW2_3.Text & String(8 - Len(txtFTW2_3.Text), 48)
         
      End If
      
      FTWMHz_Update "F2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW2_4_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW2_4.Text) < 8 Then
      
         txtFTW2_4.Text = txtFTW2_4.Text & String(8 - Len(txtFTW2_4.Text), 48)
         
      End If
      
      FTWMHz_Update "F2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW2_5_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW2_5.Text) < 8 Then
      
         txtFTW2_5.Text = txtFTW2_5.Text & String(8 - Len(txtFTW2_5.Text), 48)
         
      End If
      
      FTWMHz_Update "F2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW2_6_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFTW2_6.Text) < 8 Then
      
         txtFTW2_6.Text = txtFTW2_6.Text & String(8 - Len(txtFTW2_6.Text), 48)
         
      End If
      
      FTWMHz_Update "F2"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFTW2MHz_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only numeric
'characters "0" thru "9" plus "." and BS, DEL, and CR.

Dim FrqVal As Single

Select Case KeyAscii
    Case MyLocInfo.iDecSep 'Pass the decimal seperator
        'Check to see if a Decimal Seperator is allready in the string
        If InStr(1, txtFTW2MHz.Text, MyLocInfo.sDecSep) And txtFTW2MHz.SelLength <> Len(txtFTW2MHz.Text) Then
            'If so then trash the key
            KeyAscii = 0
        End If
    '   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
    '
    '      KeyAscii = 0
       
    Case 0 To 12 'Control Keys
    Case 14 To 32  'Control Keys
    Case 48 To 57 'Numeric Keys

'   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
'
'      KeyAscii = 0
'
    Case 13
    
        KeyAscii = 0
        
        If Not IsNumeric(txtFTW2MHz.Text) Then
            FrqVal = 0
        Else
            FrqVal = CSng(txtFTW2MHz.Text)
        End If
        
        'Determine the suggested maximum output frequency
        'and display a warning if the value entered by the
        'user exceeds this maximum value. If the value entered
        'by the user exceeds the system clock frequency then
        'the output frequency defaults to nyquist
        
        Dim ClkVal As Single
        Dim MaxVal As Single
        Dim MsgStr As String
        
        Call GetSysClk(ClkVal)
        MaxVal = 0.4 * ClkVal
        If (FrqVal > MaxVal) Then
            
            MsgStr = "Suggested frequency tuning word: < " & MaxVal & " MHz"
            Call MsgBox(MsgStr, 0, "Warning!")
            
            If FrqVal > ClkVal Then
            
               MsgStr = "Please enter a frequency below the system clock frequency (" & ClkVal & " MHz)"
               Call MsgBox(MsgStr, 0, "Warning!")
               
            End If
            
        End If
        
        If FrqVal >= 100 Then
        
            txtFTW2MHz.Text = Format(FrqVal, "000.000")
        
        ElseIf FrqVal >= 10 Then
        
            txtFTW2MHz.Text = Format(FrqVal, "00.0000")
        
        Else
        
            txtFTW2MHz.Text = Format(FrqVal, "0.00000")
           
        End If
        
        If FrqVal <= ClkVal Then
            FTW_Update "F2"
            cmdLoad.SetFocus
        End If
      
    Case Else
        'Trash all other keys
        KeyAscii = 0

End Select

End Sub
 
Public Sub txtFSW1_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFSW1.Text) < 8 Then
      
         txtFSW1.Text = txtFSW1.Text & String(8 - Len(txtFSW1.Text), 48)
         
      End If
      
      FTWMHz_Update1 "FSW"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSW2_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFSW2.Text) < 8 Then
      
         txtFSW2.Text = txtFSW2.Text & String(8 - Len(txtFSW2.Text), 48)
         
      End If
      
      FTWMHz_Update1 "FSW"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSW3_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFSW3.Text) < 8 Then
      
         txtFSW3.Text = txtFSW3.Text & String(8 - Len(txtFSW3.Text), 48)
         
      End If
      
      FTWMHz_Update1 "FSW"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSW4_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFSW4.Text) < 8 Then
      
         txtFSW4.Text = txtFSW4.Text & String(8 - Len(txtFSW4.Text), 48)
         
      End If
      
      FTWMHz_Update1 "FSW"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSW5_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFSW5.Text) < 8 Then
      
         txtFSW5.Text = txtFSW5.Text & String(8 - Len(txtFSW5.Text), 48)
         
      End If
      
      FTWMHz_Update1 "FSW"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSW6_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only binary
'characters "1" and "0" plus BS, DEL, and CR.

Select Case KeyAscii

   Case Is < 8, 9 To 12, 14 To 47, Is > 49
   
      KeyAscii = 0
      
   Case 13
   
      KeyAscii = 0
      
      If Len(txtFSW6.Text) < 8 Then
      
         txtFSW6.Text = txtFSW6.Text & String(8 - Len(txtFSW6.Text), 48)
         
      End If
      
      FTWMHz_Update1 "FSW"

      cmdLoad.SetFocus

End Select

End Sub

Public Sub txtFSWMHz_KeyPress(KeyAscii As Integer)

'This procedure screens text input allowing only numeric
'characters "0" thru "9" plus "." and BS, DEL, and CR.

Dim FrqVal As Single

Select Case KeyAscii
   
    Case MyLocInfo.iDecSep 'Pass the decimal seperator
        'Check to see if a Decimal Seperator is allready in the string
        If InStr(1, txtFSWMHz.Text, MyLocInfo.sDecSep) And txtFSWMHz.SelLength <> Len(txtFSWMHz.Text) Then
            'If so then trash the key
            KeyAscii = 0
        End If
    '   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
    '
    '      KeyAscii = 0
       
    Case 0 To 12 'Control Keys
    Case 14 To 32  'Control Keys
    Case 48 To 57 'Numeric Keys
    Case Asc(MyLocInfo.sNegSign)   ' "-" key
        'If in chirp mode the allow negative numbers
        If optChirpMode.Value Then
            'If the minus key has already been pressed then trash the key
            If InStr(1, txtFSWMHz, MyLocInfo.sNegSign) Then
                KeyAscii = False
            End If
        Else
            KeyAscii = 0
        End If
'   Case Is < 8, 9 To 12, 14 To 45, 47, Is > 57
'
'      KeyAscii = 0
'
    Case 13
    
        KeyAscii = 0
        
        If Not IsNumeric(txtFSWMHz.Text) Then
            FrqVal = 0
        Else
            FrqVal = CSng(txtFSWMHz.Text)
        End If
        
        'Determine the suggested maximum output frequency
        'and display a warning if the value entered by the
        'user exceeds this maximum value. If the value entered
        'by the user exceeds the system clock frequency then
        'the output frequency defaults to nyquist
        
        Dim ClkVal As Single
        Dim MaxVal As Single
        Dim MsgStr As String
        
        Call GetSysClk(ClkVal)
        MaxVal = 0.4 * ClkVal
        
        If optChirpMode.Value Then

            If (Abs(FrqVal) > frmFrequency.txtFTW1MHz) Then
                
                MsgStr = "Suggested frequency step: < " & frmFrequency.txtFTW1MHz & " MHz"
                Call MsgBox(MsgStr, 0, "Warning!")
                
                If Abs(FrqVal) > ClkVal Then
                
                    MsgStr = "Please enter a frequency below the system clock frequency (" & ClkVal & " MHz)"
                    Call MsgBox(MsgStr, 0, "Warning!")
                   
                End If
                
            End If
        
        ElseIf optRampedFSK.Value Then

            If (Abs(FrqVal) > frmFrequency.txtFTW2MHz) Then
                
                MsgStr = "Suggested frequency step: < " & frmFrequency.txtFTW2MHz & " MHz"
                Call MsgBox(MsgStr, 0, "Warning!")
                
                If Abs(FrqVal) > ClkVal Then
                
                    MsgStr = "Please enter a frequency below the system clock frequency (" & ClkVal & " MHz)"
                    Call MsgBox(MsgStr, 0, "Warning!")
                   
                End If
                
            End If
        End If
        
                
        If FrqVal >= 100 Then
        
            txtFSWMHz.Text = Format(FrqVal, "000.000")
        
        ElseIf FrqVal >= 10 Then
        
            txtFSWMHz.Text = Format(FrqVal, "00.0000")
        
        Else
        
            txtFSWMHz.Text = Format(FrqVal, "0.00000")
           
        End If
        
        If FrqVal <= ClkVal Then
            
            FTW_Update "FSW"
            cmdLoad.SetFocus
            
        End If

    'Trash all other keys
    Case Else
        KeyAscii = 0

End Select

End Sub

Sub sendFreqToDUT()

    Call cmdLoad_Click
    
End Sub
Public Sub resetTheDut()

    Call cmdReset_Click
    
End Sub

'Compliments a binary string
'Used to display the Frequency Step Word in 2's Compliment
Public Function ComplBinStr(ByVal BinStr) As String
    Dim cntr As Integer
    Dim NewStr As String
    
    For cntr = 1 To Len(BinStr)
        If Mid(BinStr, cntr, 1) = "1" Then
            NewStr = NewStr & "0"
        Else
            NewStr = NewStr & "1"
        End If
    Next
    
    ComplBinStr = NewStr
End Function
