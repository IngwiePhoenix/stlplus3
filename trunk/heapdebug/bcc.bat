mkdir BORLAND-i686-debug
bcc32 -c +..\bcc_debug.cfg -oBORLAND-i686-debug\heapdebug.obj heapdebug.cpp
del "BORLAND-i686-debug\heapdebug.lib"
tlib "BORLAND-i686-debug\heapdebug.lib" /a "BORLAND-i686-debug\heapdebug.obj"
