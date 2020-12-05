../cell.exe: main.o cell_fun.o
	gcc main.o cell_fun.o -o ../cell.exe -g
main.o: main.c
	gcc main.c -c
cell_fun.o: cell_fun.c
	gcc cell_fun.c -c
gdb: ../cell.exe
	gdb ../cell.exe
clean:
	rm *.o
