VERSION 5.00
Begin VB.Form DlgBatchRead 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Batch Read"
   ClientHeight    =   3255
   ClientLeft      =   4515
   ClientTop       =   4845
   ClientWidth     =   6030
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "DlgBatchRead.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3255
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.Timer tmrPoll 
      Enabled         =   0   'False
      Left            =   5160
      Top             =   120
   End
   Begin VB.TextBox txtPollPeriod 
      Height          =   285
      Left            =   2520
      MaxLength       =   4
      TabIndex        =   6
      Text            =   "200"
      Top             =   2880
      Width           =   735
   End
   Begin VB.CheckBox chkPoll 
      Caption         =   "&Poll every"
      BeginProperty DataFormat 
         Type            =   5
         Format          =   ""
         HaveTrueFalseNull=   1
         TrueValue       =   "True"
         FalseValue      =   "False"
         NullValue       =   ""
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   2052
         SubFormatType   =   7
      EndProperty
      Height          =   255
      Left            =   1440
      TabIndex        =   5
      Top             =   2880
      Width           =   1095
   End
   Begin VB.CommandButton cmdDismiss 
      Caption         =   "&Dismiss"
      Height          =   375
      Left            =   4680
      TabIndex        =   7
      Top             =   2760
      Width           =   1215
   End
   Begin VB.TextBox txtOutput 
      BackColor       =   &H8000000F&
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2055
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Top             =   600
      Width           =   5775
   End
   Begin VB.ComboBox cmbType 
      Height          =   315
      ItemData        =   "DlgBatchRead.frx":000C
      Left            =   600
      List            =   "DlgBatchRead.frx":0019
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   150
      Width           =   1095
   End
   Begin VB.TextBox txtCount 
      Height          =   285
      Left            =   4200
      MaxLength       =   3
      TabIndex        =   2
      Text            =   "5"
      Top             =   165
      Width           =   615
   End
   Begin VB.TextBox txtAddr 
      Height          =   285
      Left            =   2520
      TabIndex        =   1
      Text            =   "M100"
      Top             =   165
      Width           =   975
   End
   Begin VB.CommandButton cmdExecute 
      Caption         =   "&Read"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   2760
      Width           =   975
   End
   Begin VB.Label Label5 
      Caption         =   "msecs"
      Height          =   255
      Left            =   3360
      TabIndex        =   11
      Top             =   2880
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "Type:"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   180
      Width           =   615
   End
   Begin VB.Label Label3 
      Caption         =   "Count:"
      Height          =   255
      Left            =   3600
      TabIndex        =   9
      Top             =   180
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "Address:"
      Height          =   255
      Left            =   1800
      TabIndex        =   8
      Top             =   180
      Width           =   735
   End
End
Attribute VB_Name = "DlgBatchRead"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Function DoRead() As Boolean
    Dim result
    Dim strAddr As String
    Dim cUnits As Integer
    Dim strOutput As String
    Dim i As Integer
    
    On Error GoTo ErrHandler
    
    strAddr = txtAddr.Text
    cUnits = txtCount.Text
    
    txtOutput.Text = ""
    
    Select Case cmbType.Text
        Case "Bit"
            result = g_mc.BatchReadBit(strAddr, cUnits)
            
        Case "Word"
            result = g_mc.BatchReadWord(strAddr, cUnits)
            
        Case "DWord"
            result = g_mc.BatchReadDWord(strAddr, cUnits)
            
        Case Else
            Err.Raise -1, Me, "Unexpected unit type."
    End Select
    
    For i = LBound(result) To UBound(result)
        strOutput = strOutput & "[" & i & "]" & vbTab & result(i) & vbCrLf
    Next i
    txtOutput.Text = strOutput
    
    DoRead = True
    Exit Function
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
    DoRead = False
End Function

Private Sub chkPoll_Click()
    Select Case chkPoll.value
        Case Unchecked
            tmrPoll.Enabled = False
        Case Checked
            Call txtPollPeriod_Change
            tmrPoll.Enabled = True
        Case Else
            Exit Sub
    End Select
End Sub

Private Sub cmdDismiss_Click()
    Unload Me
End Sub

Private Sub cmdExecute_Click()
    DoRead
End Sub

Private Sub Form_Load()
    cmbType.ListIndex = 0
End Sub

Private Sub tmrPoll_Timer()
    If Not DoRead() Then
        chkPoll.value = Unchecked
        tmrPoll.Enabled = False
    End If
End Sub

Private Sub txtPollPeriod_Change()
    Dim strText As String
    Dim iInterval As Integer
    
    strText = txtPollPeriod.Text
    If Len(strText) > 0 And IsNumeric(strText) Then
        iInterval = CInt(strText)
        If iInterval >= 0 Then
            tmrPoll.Interval = iInterval
        End If
    End If
End Sub
