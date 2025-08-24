install:
	@echo Installation in progress. Please wait
	@$(CC) demonator.c -g0 -O0 -o /bin/demonator
	@chmod ugo+rx /bin/demonator
	@echo Installation was successfully completed
uninstall:
	@rm -f /bin/demonator
	@echo Uninstallation was successfully completed