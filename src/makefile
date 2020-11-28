libs = 
tunits = main.c tcp_connection.c log.c
dist = ../dist/

debug:
	gcc $(tunits) -o "$(dist)debug" $(libs) -Wall -Werror -fmax-errors=4
prod:
	gcc -O2 -s $(tunits) -o "$(dist)main" $(libs) -Wall -Werror -fmax-errors=4
run:
	sudo "$(dist)debug" 80
runprod:
	sudo "$(dist)main" 80
clean:
	rm ../dist/*
