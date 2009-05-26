bcc32 +..\..\bcc_debug.cfg -I..\..\strings;..\..\persistence;..\..\containers;..\..\portability -c -obool_vector_test.obj bool_vector_test.cpp
ilink32 +..\..\ilink_debug.cfg c0x32 bool_vector_test.obj, bool_vector_test.exe, , ..\..\strings\BORLAND-i686-debug\strings.lib ..\..\persistence\BORLAND-i686-debug\persistence.lib ..\..\portability\BORLAND-i686-debug\portability.lib import32.lib cw32i.lib
