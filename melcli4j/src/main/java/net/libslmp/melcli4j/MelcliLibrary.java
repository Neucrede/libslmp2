package net.libslmp.melcli4j;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.PointerByReference;

/**
 * JNA library mapping.
 *
 * @author Neucrede <neucrede@sina.com>
 */
public interface MelcliLibrary extends Library {
    MelcliLibrary INSTANCE = Native.load("melcli", MelcliLibrary.class);
    
    int melcli_init();
    int melcli_uninit();
    String melcli_get_err_msg(int err);
    Pointer melcli_new_context(int type, String remoteIPAddress, int remotePort,
            String localIPAddress, int localPort, Station.ByReference station,
            Timeout.ByReference timeout);
    void melcli_free_context(Pointer ctx);
    int melcli_connect(Pointer ctx);
    void melcli_disconnect(Pointer ctx);
    void melcli_free(Pointer p);
    int melcli_batch_read(Pointer ctx, Pointer station, String addr,
            int n, PointerByReference data, IntByReference dataLen);
    int melcli_batch_write(Pointer ctx, Pointer station, String addr,
            int n, byte[] data);
    int melcli_random_read_word(Pointer ctx, Pointer station,
            String[] addrs, PointerByReference data, IntByReference dataLen);
    int melcli_random_read_dword(Pointer ctx, Pointer station,
            String[] addrs, PointerByReference data, IntByReference dataLen);
    int melcli_random_write_word(Pointer ctx, Pointer station,
            String[] addrs, byte[] data);
    int melcli_random_write_dword(Pointer ctx, Pointer station,
            String[] addrs, byte[] data);
    int melcli_remote_run(Pointer ctx, Pointer station, int flag);
    int melcli_remote_stop(Pointer ctx, Pointer station);
    int melcli_remote_reset(Pointer ctx, Pointer station);
    int melcli_remote_pause(Pointer ctx, Pointer station, int flag);
    int melcli_remote_latch_clear(Pointer ctx, Pointer station, int flag);
    int melcli_remote_read_type_name(Pointer ctx, Pointer station,
            PointerByReference typeName, IntByReference typeCode);
    int melcli_clear_error_code(Pointer ctx, Pointer station);
    int melcli_self_test(Pointer ctx, Pointer station);
}
