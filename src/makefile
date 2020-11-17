dzravi: main.c
	gcc -O2 -s main.c log.c tcp_connection.c -o main.exe -lWs2_32
debug:
	gcc main.c log.c tcp_connection.c -o main.exe -lWs2_32
run:
	main.exe 80
clean:
	del main.exe
