VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.5#0"; "comctl32.ocx"
Begin VB.Form DlgBatchWrite 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Batch Write"
   ClientHeight    =   3495
   ClientLeft      =   -15
   ClientTop       =   -15
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
   Icon            =   "DlgBatchWrite.frx":0000
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3495
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton cmdWriteRandomValues 
      Caption         =   "Write &Random Values"
      Height          =   375
      Left            =   1200
      TabIndex        =   5
      Top             =   3000
      Width           =   2175
   End
   Begin ComctlLib.ListView lstData 
      Height          =   2055
      Left            =   120
      TabIndex        =   3
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
         Text            =   "Index"
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
   Begin VB.CommandButton cmdExecute 
      Caption         =   "&Write"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   3000
      Width           =   975
   End
   Begin VB.TextBox txtAddr 
      Height          =   285
      Left            =   2520
      TabIndex        =   1
      Text            =   "M100"
      Top             =   165
      Width           =   975
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
   Begin VB.ComboBox cmbType 
      Height          =   315
      ItemData        =   "DlgBatchWrite.frx":000C
      Left            =   600
      List            =   "DlgBatchWrite.frx":0019
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   150
      Width           =   1095
   End
   Begin VB.CommandButton cmdDismiss 
      Caption         =   "&Dismiss"
      Height          =   375
      Left            =   4680
      TabIndex        =   6
      Top             =   3000
      Width           =   1215
   End
   Begin VB.Label Label4 
      Caption         =   "Click on Index Number to Edit"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   600
      Width           =   4095
   End
   Begin VB.Label Label2 
      Caption         =   "Address:"
      Height          =   255
      Left            =   1800
      TabIndex        =   9
      Top             =   180
      Width           =   735
   End
   Begin VB.Label Label3 
      Caption         =   "Count:"
      Height          =   255
      Left            =   3600
      TabIndex        =   8
      Top             =   180
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "Type:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   180
      Width           =   615
   End
End
Attribute VB_Name = "DlgBatchWrite"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim bFlipFlop As Boolean

Private Sub UpdateList()
    Dim i, n As Integer
    Dim item
    
    On Error GoTo ErrHandler

    lstData.ListItems.Clear
    
    If Len(txtCount.Text) = 0 Or Not IsNumeric(txtCount.Text) Then
        Exit Sub
    End If
    
    For i = 1 To txtCount.Text
        Set item = lstData.ListItems.Add()
        item.Text = i
        item.SubItems(1) = "0"
    Next i
    
    Exit Sub
    
ErrHandler:
    txtCount.Text = ""
End Sub

Private Sub cmdDismiss_Click()
    Unload Me
End Sub

Private Sub cmdExecute_Click()
    Dim strAddr As String
    Dim cUnits As Integer
    Dim i As Integer
    Dim arrBits() As Boolean
    Dim arrWords() As Integer
    Dim arrDWords() As Long
    Dim itm
    
    On Error GoTo ErrHandler
    
    strAddr = txtAddr.Text
    cUnits = txtCount.Text
        
    Select Case cmbType.Text
        Case "Bit"
            ReDim arrBits(1 To cUnits)
            For Each itm In lstData.ListItems
                arrBits(itm.Index) = itm.SubItems(1)
            Next itm
            
            g_mc.BatchWriteBit strAddr, arrBits
            
        Case "Word"
            ReDim arrWords(1 To cUnits)
            For Each itm In lstData.ListItems
                arrWords(itm.Index) = itm.SubItems(1)
            Next itm
            
            g_mc.BatchWriteWord strAddr, arrWords
            
        Case "DWord"
            ReDim arrDWords(1 To cUnits)
            For Each itm In lstData.ListItems
                arrDWords(itm.Index) = itm.SubItems(1)
            Next itm
            
            g_mc.BatchWriteDWord strAddr, arrDWords
            
        Case Else
            Err.Raise -1, Me, "Unexpected unit type."
    End Select
    
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub

Private Sub cmdWriteRandomValues_Click()
    Dim s As Single
    Dim itm
    
    Select Case cmbType.Text
        Case "Bit"
            For Each itm In lstData.ListItems
                s = Rnd()
                itm.SubItems(1) = (s > 0.5)
            Next itm
            
        Case "Word"
            For Each itm In lstData.ListItems
                s = Rnd()
                itm.SubItems(1) = CInt((s - 0.5) * 65534#)
            Next itm
            
        Case "DWord"
            For Each itm In lstData.ListItems
                s = Rnd()
                itm.SubItems(1) = CLng((s - 0.5) * 4294967294#)
            Next itm
            
        Case Else
            Err.Raise -1, Me, "Unexpected unit type."
    End Select
    
    Call cmdExecute_Click
End Sub

Private Sub Form_Load()
    cmbType.ListIndex = 0
    bFlipFlop = True
    UpdateList
End Sub

Private Sub lstData_ItemClick(ByVal item As ComctlLib.ListItem)
    Dim value As String
    
    On Error Resume Next
    
    bFlipFlop = Not bFlipFlop
    If bFlipFlop Then
        Exit Sub
    End If
    
    value = InputBox("Specify a value for the unit at index " & item.Index, "Change value")
    
    If Len(value) > 0 And IsNumeric(value) Then
        lstData.ListItems.item(item.Index).SubItems(1) = value
    End If
End Sub

Private Sub txtCount_Change()
    UpdateList
End Sub
