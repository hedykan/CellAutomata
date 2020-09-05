cell.exe: main.o cell_fun.o
	gcc main.o cell_fun.o -o ../cell.exe
main.o: main.c
	gcc main.c -c
cell_fun.o: cell_fun.c
	gcc cell_fun.c -c
clean:
	rm *.o
