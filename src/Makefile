../cell.exe: main.o cell_fun.o print.o
	gcc main.o cell_fun.o print.o -o ../cell.exe -g
main.o: main.c
	gcc main.c -c -g
cell_fun.o: cell_fun.c
	gcc cell_fun.c -c -g
print.o: print.c
	gcc print.c -c -g
gdb: ../cell.exe
	gdb ../cell.exe
clean:
	rm *.o
