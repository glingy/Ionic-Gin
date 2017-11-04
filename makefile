all:
	if [ -a ionicGin ]; then rm ionicGin; fi;
	gcc *.c -lncurses -I. -o ionicGin
	./ionicGin