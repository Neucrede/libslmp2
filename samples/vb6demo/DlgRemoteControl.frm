VERSION 5.00
Begin VB.Form DlgRemoteControl 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Remote Control"
   ClientHeight    =   3150
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
   Icon            =   "DlgRemoteControl.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3150
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '所有者中心
   Begin VB.CommandButton cmdReadTypeName 
      Caption         =   "Read Processor &Type"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   1080
      Width           =   2655
   End
   Begin VB.CommandButton cmdRemoteReset 
      Caption         =   "R&eset"
      Height          =   375
      Left            =   4800
      TabIndex        =   3
      Top             =   240
      Width           =   1095
   End
   Begin VB.CommandButton cmdRemotePause 
      Caption         =   "&Pause"
      Height          =   375
      Left            =   3240
      TabIndex        =   2
      Top             =   240
      Width           =   1095
   End
   Begin VB.CommandButton cmdRemoteStop 
      Caption         =   "&Stop"
      Height          =   375
      Left            =   1680
      TabIndex        =   1
      Top             =   240
      Width           =   1095
   End
   Begin VB.CommandButton cmdRemoteRun 
      Caption         =   "&Run"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1095
   End
   Begin VB.CommandButton cmdDismiss 
      Caption         =   "&Dismiss"
      Height          =   375
      Left            =   4680
      TabIndex        =   5
      Top             =   2640
      Width           =   1215
   End
End
Attribute VB_Name = "DlgRemoteControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Private Sub cmdDismiss_Click()
    Unload Me
End Sub

Private Sub cmdReadTypeName_Click()
    Dim strType As String

    On Error GoTo ErrHandler
    
    strType = g_mc.RemoteReadTypeName()
    MsgBox strType, vbExclamation, "Processor Type"
    
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub

Private Sub cmdRemotePause_Click()
    On Error GoTo ErrHandler
    
    g_mc.RemotePause
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub

Private Sub cmdRemoteReset_Click()
    On Error GoTo ErrHandler
    
    g_mc.RemoteReset
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub

Private Sub cmdRemoteRun_Click()
    On Error GoTo ErrHandler
    
    g_mc.RemoteRun
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub

Private Sub cmdRemoteStop_Click()
    On Error GoTo ErrHandler
    
    g_mc.RemoteStop
    Exit Sub
    
ErrHandler:
    MsgBox Err.Description, vbExclamation, "Error"
End Sub
