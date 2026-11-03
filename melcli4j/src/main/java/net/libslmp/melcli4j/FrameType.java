package net.libslmp.melcli4j;

/**
 *
 * @author neucrede
 */
public enum FrameType {
    ST(1),
    MT(2);
    
    public final int value;
    
    public int toInt() {
        return value;
    }
    
    private FrameType(int value) {
        this.value = value;
    }
    
}
