package net.libslmp.melcli4j;

/**
 * Protocol types.
 *
 * @author Neucrede <neucrede@sina.com>
 */
public enum Protocol {
    TCPIP(1), UDPIP(2);

    private final int value;

    public int toInt() {
        return value;
    }
    
    private Protocol(int value) {
        this.value = value;
    }
}
