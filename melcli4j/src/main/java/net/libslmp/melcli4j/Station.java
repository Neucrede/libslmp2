package net.libslmp.melcli4j;

import com.sun.jna.Structure;
import java.util.Arrays;
import java.util.List;

/**
 * JNA wrapper class for native struct melcli_station.
 *
 * @author Neucrede <neucrede@sina.com>
 */
public class Station extends Structure {

    public byte networkNumber;
    public byte nodeNumber;
    public short destinationProcessorNumber;
    public byte destinationProcessorSubNumber;
    public short largeNodeNumber;
    
    public Station() {
        super();
        
        // MELCLI_CONNECTED_STATION
        networkNumber = 0;
        nodeNumber = (byte)0xFF;
        destinationProcessorNumber = (short)0x03FF;
        destinationProcessorSubNumber = 0;
        largeNodeNumber = 0;
    }
    
    @Override
    public List<String> getFieldOrder() {
        return Arrays.asList(
                "networkNumber", 
                "nodeNumber",
                "destinationProcessorNumber",
                "destinationProcessorSubNumber",
                "largeNodeNumber");
    }

    public Station(byte networkNumber, byte nodeNumber, short destinationProcessorNumber, byte destinationProcessorSubNumber, short largeNodeNumber) {
        super();
        
        this.networkNumber = networkNumber;
        this.nodeNumber = nodeNumber;
        this.destinationProcessorNumber = destinationProcessorNumber;
        this.destinationProcessorSubNumber = destinationProcessorSubNumber;
        this.largeNodeNumber = largeNodeNumber;
    }

    public byte getNetworkNumber() {
        return networkNumber;
    }

    public void setNetworkNumber(byte networkNumber) {
        this.networkNumber = networkNumber;
    }

    public byte getNodeNumber() {
        return nodeNumber;
    }

    public void setNodeNumber(byte nodeNumber) {
        this.nodeNumber = nodeNumber;
    }

    public short getDestinationProcessorNumber() {
        return destinationProcessorNumber;
    }

    public void setDestinationProcessorNumber(short destinationProcessorNumber) {
        this.destinationProcessorNumber = destinationProcessorNumber;
    }

    public byte getDestinationProcessorSubNumber() {
        return destinationProcessorSubNumber;
    }

    public void setDestinationProcessorSubNumber(byte destinationProcessorSubNumber) {
        this.destinationProcessorSubNumber = destinationProcessorSubNumber;
    }

    public short getLargeNodeNumber() {
        return largeNodeNumber;
    }

    public void setLargeNodeNumber(short largeNodeNumber) {
        this.largeNodeNumber = largeNodeNumber;
    }
    
    public static class ByReference extends Station implements Structure.ByReference {
    }

    public static class ByValue extends Station implements Structure.ByValue {
    }
}
