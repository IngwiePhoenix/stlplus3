bcc32 +..\..\bcc.cfg -I..\..\strings;..\..\persistence;..\..\containers;..\..\portability -c -osmart_ptr_test.obj smart_ptr_test.cpp
ilink32 +..\..\ilink.cfg c0x32 smart_ptr_test.obj, smart_ptr_test.exe, , ..\..\strings\BORLAND-i686-debug\strings.lib ..\..\persistence\BORLAND-i686-debug\persistence.lib ..\..\portability\BORLAND-i686-debug\portability.lib import32.lib cw32i.lib
