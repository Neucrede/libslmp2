package net.libslmp.melcli4j;

import com.sun.jna.Structure;
import java.util.Arrays;
import java.util.List;

/**
 * JNA wrapper class for native struct melcli_timeout.
 *
 * @author Neucrede <neucrede@sina.com>
 */
public class Timeout extends Structure {

    public int connectionTimeout;
    public int receiveTimeout;
    public int frameTimeout;
    public int frameTimer;

    public Timeout() {
        super();
        
        connectionTimeout = 1;
        receiveTimeout = 1;
        frameTimeout = 500;
        frameTimer = 5;
    }
    
    public Timeout(int connectionTimeout, int receiveTimeout, int frameTimeout, int frameTimer) {
        super();
        
        this.connectionTimeout = connectionTimeout;
        this.receiveTimeout = receiveTimeout;
        this.frameTimeout = frameTimeout;
        this.frameTimer = frameTimer;
    }
    
    @Override
    public List<String> getFieldOrder() {
        return Arrays.asList(
                "connectionTimeout",
                "receiveTimeout",
                "frameTimeout",
                "frameTimer");
    }

    public int getConnectionTimeout() {
        return connectionTimeout;
    }

    public void setConnectionTimeout(int connectionTimeout) {
        this.connectionTimeout = connectionTimeout;
    }

    public int getReceiveTimeout() {
        return receiveTimeout;
    }

    public void setReceiveTimeout(int receiveTimeout) {
        this.receiveTimeout = receiveTimeout;
    }

    public int getFrameTimeout() {
        return frameTimeout;
    }

    public void setFrameTimeout(int frameTimeout) {
        this.frameTimeout = frameTimeout;
    }

    public int getFrameTimer() {
        return frameTimer;
    }

    public void setFrameTimer(int frameTimer) {
        this.frameTimer = frameTimer;
    }

    public static class ByReference extends Timeout implements Structure.ByReference {
    }

    public static class ByValue extends Timeout implements Structure.ByValue {
    }
}
