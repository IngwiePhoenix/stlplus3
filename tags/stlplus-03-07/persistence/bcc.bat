mkdir BORLAND-i686-debug
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_bool.obj persistent_bool.cpp
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_contexts.obj persistent_contexts.cpp
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_cstring.obj persistent_cstring.cpp
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_exceptions.obj persistent_exceptions.cpp
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_float.obj persistent_float.cpp
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_inf.obj persistent_inf.cpp
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_int.obj persistent_int.cpp
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_string.obj persistent_string.cpp
bcc32 -I..\portability;..\containers -c +..\bcc.cfg -oBORLAND-i686-debug\persistent_vector.obj persistent_vector.cpp
del /Q "BORLAND-i686-debug\persistence.lib"
tlib "BORLAND-i686-debug\persistence.lib" /a "BORLAND-i686-debug\persistent_bool.obj" "BORLAND-i686-debug\persistent_contexts.obj" "BORLAND-i686-debug\persistent_cstring.obj" "BORLAND-i686-debug\persistent_exceptions.obj" "BORLAND-i686-debug\persistent_float.obj" "BORLAND-i686-debug\persistent_inf.obj" "BORLAND-i686-debug\persistent_int.obj" "BORLAND-i686-debug\persistent_string.obj" "BORLAND-i686-debug\persistent_vector.obj" 
