mkdir BORLAND-i686-debug
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\cli_parser.obj cli_parser.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\ini_manager.obj ini_manager.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\library_manager.obj library_manager.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\message_handler.obj message_handler.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\timer.obj timer.cpp
del "BORLAND-i686-debug\subsystems.lib"
tlib "BORLAND-i686-debug\subsystems.lib" /a "BORLAND-i686-debug\cli_parser.obj" "BORLAND-i686-debug\ini_manager.obj" "BORLAND-i686-debug\library_manager.obj" "BORLAND-i686-debug\message_handler.obj" "BORLAND-i686-debug\timer.obj"
