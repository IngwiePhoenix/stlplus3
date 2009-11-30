all clean tidy:
ifeq ($(MONOLITHIC),on)
	$(MAKE) -C source $@
else
	$(MAKE) -C portability $@
	$(MAKE) -C persistence $@
	$(MAKE) -C strings $@
	$(MAKE) -C subsystems $@
endif
	@if [ -d tests ]; then $(MAKE) -C tests $@; fi


