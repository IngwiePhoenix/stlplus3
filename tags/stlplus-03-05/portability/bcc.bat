mkdir BORLAND-i686-debug
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\build.obj build.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\debug.obj debug.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\dprintf.obj dprintf.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\dynaload.obj dynaload.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\file_system.obj file_system.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\inf.obj inf.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\portability_fixes.obj portability_fixes.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\subprocesses.obj subprocesses.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\tcp_sockets.obj tcp_sockets.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\udp_sockets.obj udp_sockets.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\ip_sockets.obj ip_sockets.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\time.obj time.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\version.obj version.cpp
bcc32 -c +..\bcc.cfg -oBORLAND-i686-debug\wildcard.obj wildcard.cpp
del "BORLAND-i686-debug\portability.lib"
tlib "BORLAND-i686-debug\portability.lib" /a "BORLAND-i686-debug\build.obj" "BORLAND-i686-debug\debug.obj" "BORLAND-i686-debug\dprintf.obj" "BORLAND-i686-debug\dynaload.obj" "BORLAND-i686-debug\file_system.obj" "BORLAND-i686-debug\inf.obj" "BORLAND-i686-debug\portability_fixes.obj" "BORLAND-i686-debug\subprocesses.obj" "BORLAND-i686-debug\tcp_sockets.obj" "BORLAND-i686-debug\udp_sockets.obj" "BORLAND-i686-debug\ip_sockets.obj" "BORLAND-i686-debug\time.obj" "BORLAND-i686-debug\version.obj" "BORLAND-i686-debug\wildcard.obj" 
