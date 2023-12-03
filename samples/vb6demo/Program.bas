Attribute VB_Name = "Program"
Option Explicit

Public g_mc As MELSECClient
Public g_bConnected As Boolean

Sub Main()
    g_bConnected = False
    Set g_mc = New MELSECClient
    
    FrmMain.Show
End Sub
