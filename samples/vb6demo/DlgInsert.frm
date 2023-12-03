VERSION 5.00
Begin VB.Form DlgInsert 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Insert"
   ClientHeight    =   1575
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   3870
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "DlgInsert.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1575
   ScaleWidth      =   3870
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.TextBox txtValue 
      Height          =   285
      Left            =   120
      TabIndex        =   1
      Top             =   1080
      Width           =   2415
   End
   Begin VB.TextBox txtAddr 
      Height          =   285
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   2415
   End
   Begin VB.CommandButton CancelButton 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2760
      TabIndex        =   3
      Top             =   600
      Width           =   975
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Enabled         =   0   'False
      Height          =   375
      Left            =   2760
      TabIndex        =   2
      Top             =   120
      Width           =   975
   End
   Begin VB.Label Label2 
      Caption         =   "Value (Signed Decimal):"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   840
      Width           =   1815
   End
   Begin VB.Label Label1 
      Caption         =   "Address:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   135
      Width           =   1815
   End
End
Attribute VB_Name = "DlgInsert"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Public strAddr As String
Public strValue As String
Public bOk As Boolean

Private Sub UpdateUI()
    OKButton.Enabled = _
        Len(txtAddr.Text) > 0 _
        And Len(txtValue.Text) > 0 _
        And IsNumeric(txtValue.Text)
End Sub

Private Sub CancelButton_Click()
    bOk = False
    Me.Hide
End Sub

Private Sub Form_Load()
    bOk = False
End Sub

Private Sub OKButton_Click()
    bOk = True
    strAddr = txtAddr.Text
    strValue = txtValue.Text
    
    Me.Hide
End Sub

Private Sub txtAddr_Change()
    Call UpdateUI
End Sub

Private Sub txtValue_Change()
    Call UpdateUI
End Sub
