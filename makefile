install:
	@echo Installation in progress. Please wait
	@gcc demonator.c -g0 -O0 -o /bin/demonator
	@chmod ugo+rx /bin/demonator
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/demonator
	@echo Uninstallation was successfuly complete