bcc32 +..\..\bcc_debug.cfg -I..\..\portability -c -odynaload_test.obj dynaload_test.cpp
ilink32 +..\..\ilink_debug.cfg c0x32 dynaload_test.obj, dynaload_test.exe, , ..\..\portability\BORLAND-i686-debug\portability.lib import32.lib cw32i.lib
