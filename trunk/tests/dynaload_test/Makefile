IMAGE     := dynaload_test
ifeq ($(MONOLITHIC),on)
LIBRARIES := ../../../stlplus3/source
else
LIBRARIES := ../../portability
endif
include ../../../makefiles/gcc.mak
ifeq ($(PLATFORM),GNU)
LOADLIBES += -ldl
endif


