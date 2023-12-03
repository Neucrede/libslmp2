VERSION 5.00
Begin VB.Form DlgRandomRead 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Random Read"
   ClientHeight    =   3975
   ClientLeft      =   2760
   ClientTop       =   3750
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
   Icon            =   "DlgRandomRead.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3975
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton cmdExecute 
      Caption         =   "&Read"
      Height          =   375
      Left            =   120
      TabIndex        =   8
      Top             =   3480
      Width           =   975
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
      TabIndex        =   7
      Top             =   1320
      Width           =   5775
   End
   Begin VB.CommandButton cmdDismiss 
      Caption         =   "&Dismiss"
      Height          =   375
      Left            =   4680
      TabIndex        =   6
      Top             =   3480
      Width           =   1215
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
      Top             =   3600
      Width           =   1095
   End
   Begin VB.TextBox txtPollPeriod 
      Height          =   285
      Left            =   2520
      MaxLength       =   4
      TabIndex        =   4
      Text            =   "200"
      Top             =   3600
      Width           =   735
   End
   Begin VB.Timer tmrPoll 
      Enabled         =   0   'False
      Left            =   5160
      Top             =   120
   End
   Begin VB.TextBox txtAddrs 
      Height          =   285
      Left            =   120
      TabIndex        =   2
      Text            =   "D100, D120, D105"
      Top             =   840
      Width           =   5775
   End
   Begin VB.ComboBox cmbType 
      Height          =   315
      ItemData        =   "DlgRandomRead.frx":000C
      Left            =   600
      List            =   "DlgRandomRead.frx":0016
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Label5 
      Caption         =   "msecs"
      Height          =   255
      Left            =   3360
      TabIndex        =   9
      Top             =   3600
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "Address of Units (separated by comma):"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   600
      Width           =   5175
   End
   Begin VB.Label Label1 
      Caption         =   "Type:"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   150
      Width           =   615
   End
End
Attribute VB_Name = "DlgRandomRead"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Function DoRead() As Boolean
    Dim arrAddrs() As String
    Dim result
    Dim strOutput As String
    Dim i As Integer

    On Error GoTo ErrHandler
    
    txtOutput.Text = ""
    
    arrAddrs = Split(txtAddrs.Text, ",")
    If UBound(arrAddrs) - LBound(arrAddrs) + 1 = 0 Then
        GoTo ReturnFalse
    End If
    
    For i = LBound(arrAddrs) To UBound(arrAddrs)
        arrAddrs(i) = Trim(arrAddrs(i))
    Next i
    
    Select Case cmbType.Text
        Case "Word":
            result = g_mc.RandomReadWord(arrAddrs)
        Case "DWord":
            result = g_mc.RandomReadDWord(arrAddrs)
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
ReturnFalse:
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
