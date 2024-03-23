package net.libslmp.melcli4j;

import java.util.List;
import java.util.Map;

/**
 * MELSECClient interface.
 * 
 * @author Neucrede <neucrede@sina.com> 
 */
public interface MELSECClient {
    /**
     * Connect to remote target.
     * 
     * @throws RuntimeException
     */
    void connect();
    
    /**
     * Shutdown connection.
     */
    void disconnect();
    
    /**
     * Read bit device units consecutively.
     * 
     * @param address Address string.
     * @param n Number of units.
     * @return List of values read.
     * 
     * @throws RuntimeException
     */
    List<Boolean> batchReadBit(String address, int n);
    
    /**
     * Read word device units consecutively.
     * 
     * @param address Address string.
     * @param n Number of units.
     * @return List of values read.
     * 
     * @throws RuntimeException
     */
    List<Short> batchReadWord(String address, int n);
    
    /**
     * Read double-word device units consecutively.
     * 
     * @param address Address string.
     * @param n Number of units.
     * @return List of values read.
     * 
     * @throws RuntimeException
     */
    List<Integer> batchReadDWord(String address, int n);
    
    /**
     * Write bit device units consecutively.
     * 
     * @param address Address string.
     * @param listData List of values to be written.
     * 
     * @throws IllegalArgumentException
     * @throws RuntimeException
     */
    void batchWriteBit(String address, List<Boolean> listData);
    
    /**
     * Write word device units consecutively.
     * 
     * @param address Address string.
     * @param listData List of values to be written.
     * 
     * @throws IllegalArgumentException
     * @throws RuntimeException
     */
    void batchWriteWord(String address, List<Short> listData);
    
    /**
     * Write double-word device units consecutively.
     * 
     * @param address Address string.
     * @param listData List of values to be written.
     * 
     * @throws IllegalArgumentException
     * @throws RuntimeException
     */
    void batchWriteDWord(String address, List<Integer> listData);
    
    /**
     * Read specified device units as words.
     * 
     * @param listAddress List of address strings.
     * @return A Map object that maps the address of a unit to its value.
     * 
     * @throws IllegalArgumentException
     * @throws RuntimeException
     */
    Map<String, Short> randomReadWord(List<String> listAddress);
    
    /**
     * Read specified device units as words.
     * 
     * @param listAddress List of address strings.
     * @return A Map object that maps the address of a unit to its value.
     * 
     * @throws IllegalArgumentException
     * @throws RuntimeException
     */
    Map<String, Integer> randomReadDWord(List<String> listAddress);
    
    /**
     * Write specified device units.
     * 
     * @param mapData Map object that maps the address of a unit to the value to 
     * be written.
     * 
     * @throws IllegalArgumentException
     * @throws RuntimeException
     */
    void randomWriteWord(Map<String, Short> mapData);
    
    /**
     * Write specified device units.
     * 
     * @param mapData Map object that maps the address of a unit to the value to 
     * be written.
     * 
     * @throws IllegalArgumentException
     * @throws RuntimeException
     */
    void randomWriteDWord(Map<String, Integer> mapData);
    
    /**
     * Issue a remote RUN command to the remote target.
     * 
     * @throws RuntimeException
     */
    void remoteRun();
    
    /**
     * Issue a remote STOP command to the remote target.
     * 
     * @throws RuntimeException
     */
    void remoteStop();
    
    /**
     * Issue a remote RESET command to the remote target.
     * 
     * @throws RuntimeException
     */
    void remoteReset();
    
    /**
     * Issue a remote PAUSE command to the remote target.
     * 
     * @throws RuntimeException
     */
    void remotePause();
    
    /**
     * Issue a remote latch-clear command to the remote target.
     * 
     * @throws RuntimeException
     */
    void remoteLatchClear();
    
    /**
     * Read processor type of the remote target.
     * 
     * @return TypeName class that stores model name and type code.
     * 
     * @throws RuntimeException
     */
    TypeName remoteReadTypeName();
    
    /**
     * Clear error code.
     */
    void clearError();
    
    /**
     * Perform loopback test.
     */
    void loopbackTest();
}
