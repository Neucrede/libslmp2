package net.libslmp.melcli4j;

import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.PointerByReference;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Implementation of MELSECClient interface.
 * 
 * @author Neucrede <neucrede@sina.com> 
 */
public class MELSECClientImpl implements MELSECClient {
    static private MelcliLibrary libInstance = null;
    static private final String OS_NAME = System.getProperty("os.name");
    
    synchronized static MelcliLibrary getLibInstance() {
        if (libInstance == null) {
            if (OS_NAME.toLowerCase().startsWith("win")) {
                libInstance = MelcliLibraryWin32.INSTANCE;
            }
            else {
                libInstance = MelcliLibrary.INSTANCE;
            }
        }
        
        return libInstance;
    }
    
    
    private final Pointer pCtx;
    private final ByteOrder platByteOrder;

    public MELSECClientImpl(Pointer pCtx) {
        this.pCtx = pCtx;
        this.platByteOrder = ByteOrder.nativeOrder();
        getLibInstance();
    }

    private String getErrorMessage(int err) {
        StringBuilder sb = new StringBuilder();
        sb.append("(");
        sb.append(err);
        sb.append(") ");
        sb.append(libInstance.melcli_get_err_msg(err));
        return sb.toString();
    }

    @Override
    protected void finalize() throws Throwable {
        libInstance.melcli_free_context(pCtx);
        libInstance.melcli_uninit();

        super.finalize();
    }

    @Override
    public void connect() {
        int err = libInstance.melcli_connect(pCtx);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void disconnect() {
        libInstance.melcli_disconnect(pCtx);
    }

    @Override
    public List<Boolean> batchReadBit(String address, int n) {
        PointerByReference ppData = new PointerByReference();
        IntByReference pDataLen = new IntByReference();
        int err = libInstance.melcli_batch_read(pCtx, null,
                address, n, ppData, pDataLen);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }

        Pointer pData = null;
        ArrayList listData;
        
        try {
            pData = ppData.getPointer().getPointer(0);
            int numUnitsRead = pDataLen.getValue();
            byte[] data = pData.getByteArray(0, numUnitsRead);
            listData = new ArrayList<Boolean>(numUnitsRead);
            for (byte b : data) {
                listData.add(b != 0);
            }
        } 
        catch (Exception e) {
            throw e;
        } 
        finally {
            libInstance.melcli_free(pData);
        }

        return listData;
    }

    @Override
    public List<Short> batchReadWord(String address, int n) {
        PointerByReference ppData = new PointerByReference();
        IntByReference pDataLen = new IntByReference();
        int err = libInstance.melcli_batch_read(pCtx, null,
                address, n, ppData, pDataLen);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }

        Pointer pData = null;
        ArrayList listData;
        
        try {
            pData = ppData.getPointer().getPointer(0);
            int numUnitsRead = pDataLen.getValue() / 2;
            short[] data = pData.getShortArray(0, numUnitsRead);
            listData = new ArrayList<Short>(numUnitsRead);
            for (short s : data) {
                listData.add(s);
            }
        } 
        catch (Exception e) {
            throw e;
        } 
        finally {
            libInstance.melcli_free(pData);
        }

        return listData;
    }

    @Override
    public List<Integer> batchReadDWord(String address, int n) {
        PointerByReference ppData = new PointerByReference();
        IntByReference pDataLen = new IntByReference();
        int err = libInstance.melcli_batch_read(pCtx, null,
                address, n, ppData, pDataLen);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }

        Pointer pData = null;
        ArrayList listData;
        
        try {
            pData = ppData.getPointer().getPointer(0);
            int numUnitsRead = pDataLen.getValue() / 4;
            int[] data = pData.getIntArray(0, numUnitsRead);
            listData = new ArrayList<Integer>(numUnitsRead);
            for (int i : data) {
                listData.add(i);
            }
        } 
        catch (Exception e) {
            throw e;
        } 
        finally {
            libInstance.melcli_free(pData);
        }

        return listData;
    }

    @Override
    public void batchWriteBit(String address, List<Boolean> listData) {
        if (listData.isEmpty()) {
            throw new IllegalArgumentException("Data list is empty.");
        }
        
        int n = listData.size();
        byte[] data = new byte[n];
        for (int i = 0; i != n; ++i) {
            data[i] = listData.get(i) ? (byte)(1) : (byte)(0);
        }
                
        int err = libInstance.melcli_batch_write(
                pCtx, null, address, n, data);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void batchWriteWord(String address, List<Short> listData) {
        if (listData.isEmpty()) {
            throw new IllegalArgumentException("Data list is empty.");
        }
        
        int n = listData.size();
        ByteBuffer buf = ByteBuffer.allocate(2 * n).order(platByteOrder);
        for (Short s : listData) {
            buf.putShort(s);
        }
        
        int err = libInstance.melcli_batch_write(
                pCtx, null, address, n, buf.array());
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void batchWriteDWord(String address, List<Integer> listData) {
        if (listData.isEmpty()) {
            throw new IllegalArgumentException("Data list is empty.");
        }
        
        int n = listData.size();
        ByteBuffer buf = ByteBuffer.allocate(4 * n).order(platByteOrder);
        for (Integer i : listData) {
            buf.putInt(i);
        }
        
        int err = libInstance.melcli_batch_write(
                pCtx, null, address, n, buf.array());
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public Map<String, Short> randomReadWord(List<String> listAddress) {
        if (listAddress.isEmpty()) {
            throw new IllegalArgumentException("Address list is empty.");
        }
        
        PointerByReference ppData = new PointerByReference();
        IntByReference pDataLen = new IntByReference();
        
        int err = libInstance.melcli_random_read_word(
                pCtx, null, listAddress.toArray(new String[0]), ppData, pDataLen);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
        
        Pointer pData = null;
        Map<String, Short> mapData;
        
        try {
            pData = ppData.getPointer().getPointer(0);
            int numUnitsRead = pDataLen.getValue() / 2;
            short[] data = pData.getShortArray(0, numUnitsRead);
            mapData = new HashMap<>(numUnitsRead);
            for (int i = 0; i != numUnitsRead; ++i) {
                mapData.put(listAddress.get(i), data[i]);
            }
        }
        catch (Exception e) {
            throw e;
        }
        finally {
            libInstance.melcli_free(pData);
        }
        
        return mapData;
    }

    @Override
    public Map<String, Integer> randomReadDWord(List<String> listAddress) {
        if (listAddress.isEmpty()) {
            throw new IllegalArgumentException("Address list is empty.");
        }
        
        PointerByReference ppData = new PointerByReference();
        IntByReference pDataLen = new IntByReference();
        
        int err = libInstance.melcli_random_read_word(
                pCtx, null, listAddress.toArray(new String[0]), ppData, pDataLen);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
        
        Pointer pData = null;
        Map<String, Integer> mapData;
        
        try {
            pData = ppData.getPointer().getPointer(0);
            int numUnitsRead = pDataLen.getValue() / 4;
            int[] data = pData.getIntArray(0, numUnitsRead);
            mapData = new HashMap<>(numUnitsRead);
            for (int i = 0; i != numUnitsRead; ++i) {
                mapData.put(listAddress.get(i), data[i]);
            }
        }
        catch (Exception e) {
            throw e;
        }
        finally {
            libInstance.melcli_free(pData);
        }
        
        return mapData;
    }

    @Override
    public void randomWriteWord(Map<String, Short> mapData) {
        if (mapData.isEmpty()) {
            throw new IllegalArgumentException("Data map is empty.");
        }        
        
        int n = mapData.size();
        String[] arrAddress = mapData.keySet().toArray(new String[0]);
                
        ByteBuffer buf = ByteBuffer.allocate(2 * n).order(platByteOrder);
        for (String addr : arrAddress) {
            buf.putShort(mapData.get(addr));
        }
        
        int err = libInstance.melcli_random_write_word(
                pCtx, null, arrAddress, buf.array());
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void randomWriteDWord(Map<String, Integer> mapData) {
        if (mapData.isEmpty()) {
            throw new IllegalArgumentException("Data map is empty.");
        }        
        
        int n = mapData.size();
        String[] arrAddress = mapData.keySet().toArray(new String[0]);
        
        ByteBuffer buf = ByteBuffer.allocate(4 * n).order(platByteOrder);
        for (String addr : arrAddress) {
            buf.putInt(mapData.get(addr));
        }
        
        int err = libInstance.melcli_random_write_word(
                pCtx, null, arrAddress, buf.array());
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void remoteRun() {
        int err = libInstance.melcli_remote_run(pCtx, null, 0);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void remoteStop() {
        int err = libInstance.melcli_remote_stop(pCtx, null);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void remoteReset() {
        int err = libInstance.melcli_remote_reset(pCtx, null);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void remotePause() {
        int err = libInstance.melcli_remote_pause(pCtx, null, 1);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void remoteLatchClear() {
        int err = libInstance.melcli_remote_latch_clear(pCtx, null, 1);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public TypeName remoteReadTypeName() {
        PointerByReference ppszModelName = new PointerByReference();
        IntByReference typeCode = new IntByReference();
        
        int err = libInstance.melcli_remote_read_type_name(
                pCtx, null, ppszModelName, typeCode);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
        
        Pointer szModelName = null;
        TypeName typeName;
        
        try {
            szModelName = ppszModelName.getPointer().getPointer(0);
            
            StringBuilder sb = new StringBuilder();
            for (int i = 0; ; ++i) {
                byte b = szModelName.getByte(i);
                if ((b != 0) && (b != 0x20 /* SPACE */)) {
                    sb.append((char)b);
                }
                else {
                    break;
                }
            }
            
            typeName = new TypeName(sb.toString(), typeCode.getValue());
        }
        catch (Exception e) {
            throw e;
        }
        finally {
            libInstance.melcli_free(szModelName);
        }
        
        return typeName;
    }

    @Override
    public void clearError() {
        int err = libInstance.melcli_clear_error_code(pCtx, null);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }

    @Override
    public void loopbackTest() {
        int err = libInstance.melcli_self_test(pCtx, null);
        if (err != 0) {
            throw new RuntimeException(getErrorMessage(err));
        }
    }
}
