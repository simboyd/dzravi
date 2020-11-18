libs = -lWs2_32
tunits = main.c tcp_connection.c log.c
dist = ../dist/

debug:
	gcc $(tunits) -o "$(dist)debug.exe" $(libs) -Wall -Werror -fmax-errors=4
prod:
	gcc -O2 -s $(tunits) -o "$(dist)main.exe" $(libs) -Wall -Werror -fmax-errors=4
run:
	"$(dist)debug.exe" 80
runprod:
	"$(dist)main.exe" 80
clean:
	del /F /Q /S "$(dist)*.*" > NUL
