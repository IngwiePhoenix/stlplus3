IMAGE     := dynaload_test
ifeq ($(MONOLITHIC),on)
LIBRARIES := ../../../stlplus3/source
else
LIBRARIES := ../../portability
endif
include ../../../makefiles/gcc.mak
ifeq ($(PLATFORM),GNULINUX)
LOADLIBES += -ldl
endif


