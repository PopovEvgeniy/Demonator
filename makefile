install:
	@echo Installation in progress. Please wait
	@$(CC) demonator.c -g0 -O0 -o /bin/demonator
	@chmod ugo+rx /bin/demonator
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/demonator
	@echo Uninstallation successfully complete