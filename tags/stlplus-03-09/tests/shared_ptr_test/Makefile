IMAGE     := shared_ptr_test
CXXFLAGS = -std=c++0x
ifeq ($(MONOLITHIC),on)
LIBRARIES := ../../../stlplus3/source
else
LIBRARIES := ../../strings ../../persistence ../../containers ../../portability
endif
include ../../../makefiles/gcc.mak



