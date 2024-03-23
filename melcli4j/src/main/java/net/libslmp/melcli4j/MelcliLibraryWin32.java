package net.libslmp.melcli4j;

import com.sun.jna.Native;
import com.sun.jna.win32.StdCallLibrary;

/**
 * JNA library mapping.
 *
 * @author Neucrede <neucrede@sina.com>
 */
public interface MelcliLibraryWin32 extends MelcliLibrary, StdCallLibrary {
    MelcliLibraryWin32 INSTANCE = Native.load("melcli", MelcliLibraryWin32.class);
}
