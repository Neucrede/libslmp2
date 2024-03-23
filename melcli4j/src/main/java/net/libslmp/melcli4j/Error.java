package net.libslmp.melcli4j;

/**
 * Error codes returned by libmelcli functions.
 * 
 * Extracted from melclidef.h header file.
 *
 * @author Neucrede <neucrede@sina.com> 
 */
public class Error {
    public static final int Success = 0;
    public static final int InvalidPointer = -1;
    public static final int InvalidArguments = -2;
    public static final int InvalidAddress = -3;
    public static final int UnitTypeNotSupported = -4;
    public static final int FailedToBuildRequestFrame = -5;
    public static final int OutOfMemory = -6;
    public static final int FailedToDecodeFrame = -7;
    public static final int FailedToEncodeCommand = -8;
    public static final int InconsistentAddressWidth = -9;
    public static final int FailedToConnect = -10;
    public static final int FailedToSendFrames = -11;
    public static final int FailedToReceiveFrames = -12;
    public static final int OperationFailed = -13;
    public static final int FrameSerialMismatch = -14;
    public static final int SelfTestFailed = -15;
}
