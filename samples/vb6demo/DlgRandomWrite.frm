VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.5#0"; "comctl32.ocx"
Begin VB.Form DlgRandomWrite 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Random Write"
   ClientHeight    =   3495
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
   Icon            =   "DlgRandomWrite.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3495
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton cmdEdit 
      Caption         =   "&Edit..."
      Height          =   375
      Left            =   3120
      TabIndex        =   9
      Top             =   360
      Width           =   855
   End
   Begin VB.Timer tmrUpdateUI 
      Interval        =   100
      Left            =   2880
      Top             =   3000
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "&Clear"
      Height          =   375
      Left            =   5040
      TabIndex        =   4
      Top             =   360
      Width           =   855
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "D&elete"
      Height          =   375
      Left            =   4080
      TabIndex        =   3
      ToolTipText     =   "Delete"
      Top             =   360
      Width           =   855
   End
   Begin VB.CommandButton cmdInsert 
      Caption         =   "&Insert..."
      Height          =   375
      Left            =   2160
      TabIndex        =   2
      ToolTipText     =   "Insert"
      Top             =   360
      Width           =   855
   End
   Begin VB.CommandButton cmdDismiss 
      Caption         =   "&Dismiss"
      Height          =   375
      Left            =   4680
      TabIndex        =   6
      Top             =   3000
      Width           =   1215
   End
   Begin VB.CommandButton cmdExecute 
      Caption         =   "&Write"
      Height          =   375
      Left            =   120
      TabIndex        =   5
      Top             =   3000
      Width           =   975
   End
   Begin VB.ComboBox cmbType 
      Height          =   315
      ItemData        =   "DlgRandomWrite.frx":000C
      Left            =   600
      List            =   "DlgRandomWrite.frx":0016
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   120
      Width           =   1095
   End
   Begin ComctlLib.ListView lstData 
      Height          =   2055
      Left            =   120
      TabIndex        =   1
      Top             =   840
      Width           =   5775
      _ExtentX        =   10186
      _ExtentY        =   3625
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      _Version        =   327682
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   2
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   "#"
         Object.Tag             =   ""
         Text            =   "Address"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   "Value"
         Object.Tag             =   ""
         Text            =   "Value (Signed Decimal)"
         Object.Width           =   5080
      EndProperty
   End
   Begin VB.Label Label2 
      Caption         =   "Data"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   600
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   "Type:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   150
      Width           =   615
   End
End
Attribute VB_Name = "DlgRandomWrite"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Dim bFlipFlop As Boolean

Private Sub cmdClear_Click()
    lstData.ListItems.Clear
End Sub

Private Sub cmdDelete_Click()
    lstData.ListItems.Remove lstData.SelectedItem.Index
End Sub

Private Sub cmdDismiss_Click()
    Unload Me
End Sub

Private Sub cmdEdit_Click()
    Dim value As String
    
    On Error Resume Next
    
    value = InputBox("Changing value of unit " & lstData.SelectedItem.Text, _
        "Edit", lstData.SelectedItem.SubItems(1))
    
    If Len(value) > 0 And IsNumeric(value) Then
        lstData.SelectedItem.SubItems(1) = value
    End If
End Sub

Private Sub cmdExecute_Click()
    Dim cUnits As Integer
    Dim i As Integer
    Dim arrAddrs() As String
    Dim arrWords() As Integer
    Dim arrDWords() As Long
    Dim itm
    
    On Error GoTo ErrHandler
    
    cUnits = lstData.ListItems.Count
    
    ReDim arrAddrs(1 To cUnits)
    For Each itm In lstData.ListItems
        arrAddrs(itm.Index) = itm.Text
    Next itm
    
    Select Case cmbType.Text
        Case "Word"
            ReDim arrWords(1 To cUnits)
            For Each itm In lstData.ListItems
                arrWords(itm.Index) = itm.SubItems(1)
            Next itm
            
            g_mc.RandomWriteWord arrAddrs, arrWords
            
        Case "DWord"
            ReDim arrDWords(1 To cUnits)
            For Each itm In lstData.ListItems
                arrDWords(itm.Index) = itm.SubItems(1)
            Next itm
            
            g_mc.RandomWriteDWord arrAddrs, arrDWords
            
        Case Else
            Err.Raise -1, Me, "Unexpected unit type."
    End Select
    
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub

Private Sub cmdInsert_Click()
    Dim item

    DlgInsert.Show vbModal
    
    If Not DlgInsert.bOk Then
        GoTo Done
    End If
    
    Set item = lstData.ListItems.Add()
    item.Text = DlgInsert.strAddr
    item.SubItems(1) = DlgInsert.strValue
    
Done:
    Unload DlgInsert
End Sub

Private Sub Form_Load()
    cmbType.ListIndex = 0
    bFlipFlop = True
End Sub


Private Sub tmrUpdateUI_Timer()
    Dim b As Boolean

    If lstData.ListItems.Count = 0 Then
        cmdDelete.Enabled = False
        cmdClear.Enabled = False
        cmdExecute.Enabled = False
        cmdEdit.Enabled = False
    Else
        b = (lstData.SelectedItem.Index > 0)
        cmdDelete.Enabled = b
        cmdClear.Enabled = b
        cmdExecute.Enabled = b
        cmdEdit.Enabled = b
    End If
End Sub
