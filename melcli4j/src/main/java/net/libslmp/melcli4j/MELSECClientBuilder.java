package net.libslmp.melcli4j;

import com.sun.jna.Pointer;

/**
 * Builder class used to create MELSECClientImpl instances.
 *
 * @author Neucrede <neucrede@sina.com> 
 */
public class MELSECClientBuilder {

    private Protocol protocol;
    private String remoteIPAddress;
    private int remotePort;
    private String localIPAddress;
    private int localPort;
    private Station.ByReference station;
    private Timeout.ByReference timeout;

    public MELSECClientBuilder() {
        protocol = Protocol.TCPIP;
        remoteIPAddress = "127.0.0.1";
        remotePort = 8888;
        localIPAddress = "0.0.0.0";
        localPort = 0;
        station = new Station.ByReference();
        timeout = new Timeout.ByReference();
    }

    public MELSECClientBuilder protocol(Protocol protocol) {
        this.protocol = protocol;
        return this;
    }

    public MELSECClientBuilder remoteIPAddress(String remoteIPAddress) {
        this.remoteIPAddress = remoteIPAddress;
        return this;
    }

    public MELSECClientBuilder remotePort(int remotePort) {
        this.remotePort = remotePort;
        return this;
    }

    public MELSECClientBuilder localIPAddress(String localIPAddress) {
        this.localIPAddress = localIPAddress;
        return this;
    }

    public MELSECClientBuilder localPort(int localPort) {
        this.localPort = localPort;
        return this;
    }

    public MELSECClientBuilder networkNumber(byte networkNumber) {
        station.setNetworkNumber(networkNumber);
        return this;
    }

    public MELSECClientBuilder nodeNumber(byte nodeNumber) {
        station.setNodeNumber(nodeNumber);
        return this;
    }

    public MELSECClientBuilder destinationProcessorNumber(short destinationProcessorNumber) {
        station.setDestinationProcessorNumber(destinationProcessorNumber);
        return this;
    }

    public MELSECClientBuilder connectionTimeout(int connectionTimeout) {
        timeout.setConnectionTimeout(connectionTimeout);
        return this;
    }

    public MELSECClientBuilder receiveTimeout(int receiveTimeout) {
        timeout.setReceiveTimeout(receiveTimeout);
        return this;
    }

    public MELSECClientBuilder frameTimeout(int frameTimeout) {
        timeout.setFrameTimeout(frameTimeout);
        return this;
    }

    public MELSECClientBuilder frameTimer(int frameTimer) {
        timeout.setFrameTimer(frameTimer);
        return this;
    }

    public MELSECClient build() {
        MelcliLibrary inst = MELSECClientImpl.getLibInstance();
        
        if (inst.melcli_init() != 0) {
            throw new RuntimeException("libmelcli initialization failed.");
        }
        
        Pointer pCtx = inst.melcli_new_context(protocol.toInt(), 
                remoteIPAddress, remotePort, localIPAddress, localPort, station, 
                timeout);
        if (pCtx == Pointer.NULL) {
            inst.melcli_uninit();
            throw new IllegalArgumentException();
        }
        
        return new MELSECClientImpl(pCtx);
    }
}
