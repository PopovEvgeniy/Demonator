install:
	@echo Installation in progress. Please wait
	@gcc demonator.c -g0 -O0 -o demonator
	@chmod ugo+rx demonator
	@cp -f -p demonator /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/demonator
	@echo Uninstallation was successfuly complete