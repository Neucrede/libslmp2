VERSION 5.00
Begin VB.Form FrmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Neucrede's MELSECClient Demo Application"
   ClientHeight    =   4575
   ClientLeft      =   45
   ClientTop       =   330
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
   Icon            =   "FrmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4575
   ScaleWidth      =   6030
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin VB.Timer tmrUpdateUI 
      Interval        =   100
      Left            =   3840
      Top             =   0
   End
   Begin VB.Frame sbFunctions 
      Caption         =   "Functions"
      Height          =   2415
      Left            =   120
      TabIndex        =   17
      Top             =   2040
      Width           =   5775
      Begin VB.CommandButton cmdLoopbackTest 
         Caption         =   "Loopback &Test"
         Height          =   375
         Left            =   240
         TabIndex        =   13
         Top             =   1800
         Width           =   2535
      End
      Begin VB.CommandButton cmdClearError 
         Caption         =   "Clear Err&or"
         Height          =   375
         Left            =   3000
         TabIndex        =   12
         Top             =   1320
         Width           =   2535
      End
      Begin VB.CommandButton cmdRemote 
         Caption         =   "Remote Contro&l..."
         Height          =   375
         Left            =   240
         TabIndex        =   11
         Top             =   1320
         Width           =   2535
      End
      Begin VB.CommandButton cmdRandomWrite 
         Caption         =   "Random Wr&ite..."
         Height          =   375
         Left            =   3000
         TabIndex        =   10
         Top             =   840
         Width           =   2535
      End
      Begin VB.CommandButton cmdRandomRead 
         Caption         =   "Random R&ead..."
         Height          =   375
         Left            =   240
         TabIndex        =   9
         Top             =   840
         Width           =   2535
      End
      Begin VB.CommandButton cmdBatchWrite 
         Caption         =   "Batch &Write..."
         Height          =   375
         Left            =   3000
         TabIndex        =   8
         Top             =   360
         Width           =   2535
      End
      Begin VB.CommandButton cmdBatchRead 
         Caption         =   "Batch &Read..."
         Height          =   375
         Left            =   240
         TabIndex        =   7
         Top             =   360
         Width           =   2535
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Connection"
      Height          =   1815
      Left            =   120
      TabIndex        =   14
      Top             =   120
      Width           =   5775
      Begin VB.CommandButton cmdConnect 
         Caption         =   "&Connect"
         Height          =   375
         Left            =   3000
         TabIndex        =   5
         Top             =   1200
         Width           =   1215
      End
      Begin VB.ComboBox cmbProtocol 
         Height          =   315
         ItemData        =   "FrmMain.frx":0442
         Left            =   1080
         List            =   "FrmMain.frx":044C
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   1230
         Width           =   1335
      End
      Begin VB.CommandButton cmdDisconnect 
         Caption         =   "&Disconnect"
         Height          =   375
         Left            =   4320
         TabIndex        =   6
         Top             =   1200
         Width           =   1215
      End
      Begin VB.TextBox txtLocalPort 
         Height          =   285
         Left            =   4800
         MaxLength       =   5
         TabIndex        =   3
         Text            =   "0"
         Top             =   720
         Width           =   735
      End
      Begin VB.TextBox txtLocalIPAddr 
         Height          =   285
         Left            =   1800
         TabIndex        =   2
         Text            =   "0.0.0.0"
         Top             =   720
         Width           =   1455
      End
      Begin VB.TextBox txtRemoteIPAddr 
         Height          =   285
         Left            =   1800
         TabIndex        =   0
         Text            =   "192.168.128.200"
         Top             =   285
         Width           =   1455
      End
      Begin VB.TextBox txtRemotePort 
         Height          =   285
         Left            =   4800
         MaxLength       =   5
         TabIndex        =   1
         Text            =   "8888"
         Top             =   285
         Width           =   735
      End
      Begin VB.Label Label5 
         Caption         =   "Protocol:"
         Height          =   255
         Left            =   240
         TabIndex        =   20
         Top             =   1260
         Width           =   855
      End
      Begin VB.Label Label4 
         Caption         =   "Local Port:"
         Height          =   255
         Left            =   3720
         TabIndex        =   19
         Top             =   735
         Width           =   975
      End
      Begin VB.Label Label3 
         Caption         =   "Local IP Address:"
         Height          =   255
         Left            =   240
         TabIndex        =   18
         Top             =   735
         Width           =   1455
      End
      Begin VB.Label Label1 
         Caption         =   "Remote IP Address:"
         Height          =   255
         Left            =   240
         TabIndex        =   16
         Top             =   300
         Width           =   1455
      End
      Begin VB.Label Label2 
         Caption         =   "Remote Port:"
         Height          =   255
         Left            =   3720
         TabIndex        =   15
         Top             =   300
         Width           =   975
      End
   End
End
Attribute VB_Name = "FrmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdBatchRead_Click()
    If Not g_bConnected Then
        MsgBox "The connection has not yet been established.", vbExclamation, "Warning"
    Else
        DlgBatchRead.Show vbModal
    End If
End Sub

Private Sub cmdBatchWrite_Click()
    If Not g_bConnected Then
        MsgBox "The connection has not yet been established.", vbExclamation, "Warning"
    Else
        DlgBatchWrite.Show vbModal
    End If
End Sub

Private Sub cmdClearError_Click()
    On Error GoTo ErrHandler
    
    g_mc.ClearError
    MsgBox "Succeeded.", vbExclamation, "Clear Error"
    
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub

Private Sub cmdConnect_Click()
    On Error GoTo ErrHandler
    
    Me.MousePointer = vbHourglass
    
    Select Case cmbProtocol.Text
        Case "TCP/IP"
            g_mc.Protocol = TCPIP
        Case Else
            g_mc.Protocol = UDPIP
    End Select
    
    With g_mc
        .RemoteIPAddress = txtRemoteIPAddr.Text
        .RemotePort = txtRemotePort.Text
        .LocalIPAddress = txtLocalIPAddr.Text
        .LocalPort = txtLocalPort.Text
    End With
    
    g_bConnected = g_mc.Connect()
    
    If Not g_bConnected Then
        MsgBox "Failed to connect.", vbExclamation, "Warning"
    End If
    
    GoTo Done
    
ErrHandler:
    g_bConnected = False
    MsgBox Err.Description, vbExclamation, "Error"
    
Done:
    Me.MousePointer = vbDefault
End Sub

Private Sub cmdDisconnect_Click()
    On Error GoTo ErrHandler

    g_mc.Disconnect
    
    GoTo Done
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
    
Done:
    g_bConnected = False
End Sub

Private Sub cmdLoopbackTest_Click()
    On Error GoTo ErrHandler
    
    If g_mc.LoopbackTest() Then
        MsgBox "Test passed.", vbExclamation, "Loopback Test"
    Else
        MsgBox "Test failed.", vbExclamation, "Loopback Test"
    End If
    
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub

Private Sub cmdRandomRead_Click()
    If Not g_bConnected Then
        MsgBox "The connection has not yet been established.", vbExclamation, "Warning"
    Else
        DlgRandomRead.Show vbModal
    End If
End Sub

Private Sub cmdRandomWrite_Click()
    If Not g_bConnected Then
        MsgBox "The connection has not yet been established.", vbExclamation, "Warning"
    Else
        DlgRandomWrite.Show vbModal
    End If
End Sub

Private Sub cmdRemote_Click()
    If Not g_bConnected Then
        MsgBox "The connection has not yet been established.", vbExclamation, "Warning"
    Else
        DlgRemoteControl.Show vbModal
    End If
End Sub

Private Sub Form_Load()
    cmbProtocol.ListIndex = 0
End Sub

Private Sub Form_Unload(Cancel As Integer)
    On Error Resume Next
    g_mc.Disconnect
    Set g_mc = Nothing
End Sub

Private Sub tmrUpdateUI_Timer()
    Dim bUdpIp As Boolean
    
    bUdpIp = (cmbProtocol.Text = "UDP/IP")
    cmbProtocol.Enabled = Not g_bConnected
    txtRemoteIPAddr.Enabled = Not g_bConnected
    txtRemotePort.Enabled = Not g_bConnected
    txtLocalIPAddr.Enabled = (Not g_bConnected) And bUdpIp
    txtLocalPort.Enabled = (Not g_bConnected) And bUdpIp
    cmdConnect.Enabled = Not g_bConnected
    cmdDisconnect.Enabled = g_bConnected
End Sub
