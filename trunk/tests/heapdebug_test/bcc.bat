bcc32 +..\..\bcc_debug.cfg -I..\..\heapdebug -c -oheapdebug_test.obj heapdebug_test.cpp
ilink32 +..\..\ilink_debug.cfg c0x32 heapdebug_test.obj, heapdebug_test.exe, , ..\..\heapdebug\BORLAND-i686-debug\heapdebug.lib import32.lib cw32i.lib
