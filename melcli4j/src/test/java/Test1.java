
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import net.libslmp.melcli4j.MELSECClient;
import net.libslmp.melcli4j.MELSECClientBuilder;
import org.junit.jupiter.api.Test;
import net.libslmp.melcli4j.Protocol;
import net.libslmp.melcli4j.TypeName;

public class Test1 {
    
    private static MELSECClient mc;

    public Test1() {
        
    }

    @org.junit.jupiter.api.BeforeAll
    public static void setUpClass() throws Exception {
        MELSECClientBuilder mcb = new MELSECClientBuilder();
        mc = mcb.remoteIPAddress("192.168.128.200").remotePort(8888).protocol(Protocol.TCPIP).build();
        
        System.out.println("Connecting...");
        mc.connect();
    }

    @org.junit.jupiter.api.AfterAll
    public static void tearDownClass() throws Exception {
        System.out.println("Disconnect");
        mc.disconnect();
    }

    @org.junit.jupiter.api.BeforeEach
    public void setUp() throws Exception {
    }

    @org.junit.jupiter.api.AfterEach
    public void tearDown() throws Exception {
    }

    // TODO add test methods here.
    // The methods must be annotated with annotation @Test. For example:
    //
    // @Test
    // public void hello() {}
    
    @Test
    public void testBatchRead() {
        System.out.println("Testing batch read functions. ");
        
        System.out.println("Reading 32 bits starting from Y0.");
        List<Boolean> data = mc.batchReadBit("Y0", 32);
        System.out.println(data);

        System.out.println("Reading 32 words starting from D1000.");
        List<Short> dataW = mc.batchReadWord("D1000", 32);
        System.out.println(dataW);

        System.out.println("Reading 16 double-words starting from D1000.");
        List<Integer> dataDW = mc.batchReadDWord("D1000", 16);
        System.out.println(dataDW);
    }

    @Test
    public void testBatchWrite() {
        System.out.println("Testing batch write functions. ");
        
        List<Boolean> listData = Arrays.asList(true, false, true, false, true, true);
        System.out.print("Writing Y0..Y5 with ");
        System.out.println(listData);
        mc.batchWriteBit("Y0", listData);
        
        System.out.println("Reading back: ");
        List<Boolean> data = mc.batchReadBit("Y0", 6);
        System.out.println(data);

        List<Short> listDataW = Arrays.asList((short) 123, (short) 555);
        System.out.print("Writing D1..D2 with ");
        System.out.println(listDataW);
        mc.batchWriteWord("D1", listDataW);

        List<Short> dataW = mc.batchReadWord("D1", 2);
        System.out.print("Reading back: ");
        System.out.println(dataW);
    }

    @Test
    public void testRandomRead() {
        System.out.println("Testing random read functions. ");
        
        List<String> listAddr = Arrays.asList("D1", "D0", "Y0", "Y16");
        System.out.println(listAddr);
        
        System.out.print("Read as word array: ");
        Map<String, Short> mapData = mc.randomReadWord(listAddr);
        System.out.println(mapData);
        
        System.out.print("Read as double-word array: ");
        Map<String, Integer> mapDataDW = mc.randomReadDWord(listAddr);
        System.out.println(mapDataDW);
    }

    @Test
    public void testRandomWrite() {
        System.out.println("Testing random write functions. ");
        
        Map<String, Short> mapData = new HashMap<>();
        mapData.put("Y0", (short) 0x55AA);
        mapData.put("Y16", (short) 0xAA55);
        System.out.print("Random write ");
        System.out.println(mapData);
        mc.randomWriteWord(mapData);
        
        Map<String, Integer> mapDataDW = new HashMap<>();
        mapDataDW.put("D0", 0xAABBCCDD);
        mapDataDW.put("D10", 0xEEFF0011);
        System.out.print("Random write ");
        System.out.println(mapDataDW);
        mc.randomWriteDWord(mapDataDW);
    }

    @Test
    public void testRemote() {
        System.out.println("Testing remote control functions. ");
        
        System.out.println("Type name: ");
        TypeName tn = mc.remoteReadTypeName();
        System.out.println(tn);
        
        System.out.println("Latch clear");
        mc.remoteLatchClear();
        
        System.out.println("Stop");
        mc.remoteStop();
        
        System.out.println("Pause");
        mc.remotePause();
        
        System.out.println("Reset");
        mc.remoteReset();
        
        System.out.println("Run");
        mc.remoteRun();
    }
    
    @Test
    public void testClearError() {
        System.out.println("Testing clear error function.");
        mc.clearError();
    }
    
    @Test
    public void testLoopbackTest() {
        System.out.println("Loopback test.");
        mc.loopbackTest();
    }
}
