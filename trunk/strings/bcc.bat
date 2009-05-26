mkdir BORLAND-i686-debug
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\print_address.obj print_address.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\print_bool.obj print_bool.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\print_cstring.obj print_cstring.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\print_float.obj print_float.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\print_inf.obj print_inf.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\print_int.obj print_int.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\print_string.obj print_string.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\print_vector.obj print_vector.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_address.obj string_address.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_bool.obj string_bool.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_cstring.obj string_cstring.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_float.obj string_float.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_inf.obj string_inf.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_int.obj string_int.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_string.obj string_string.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_utilities.obj string_utilities.cpp
bcc32 -I..\portability;..\containers -c +..\bcc_debug.cfg -oBORLAND-i686-debug\string_vector.obj string_vector.cpp
del "BORLAND-i686-debug\strings.lib"
tlib "BORLAND-i686-debug\strings.lib" /a "BORLAND-i686-debug\print_address.obj" "BORLAND-i686-debug\print_bool.obj" "BORLAND-i686-debug\print_cstring.obj" "BORLAND-i686-debug\print_float.obj" "BORLAND-i686-debug\print_inf.obj" "BORLAND-i686-debug\print_int.obj" "BORLAND-i686-debug\print_string.obj" "BORLAND-i686-debug\print_vector.obj" "BORLAND-i686-debug\string_address.obj" "BORLAND-i686-debug\string_bool.obj" "BORLAND-i686-debug\string_cstring.obj" "BORLAND-i686-debug\string_float.obj" "BORLAND-i686-debug\string_inf.obj" "BORLAND-i686-debug\string_int.obj" "BORLAND-i686-debug\string_string.obj" "BORLAND-i686-debug\string_utilities.obj" "BORLAND-i686-debug\string_vector.obj" 
