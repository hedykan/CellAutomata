COMP = -std=c99
../cell.exe: main.o cell_fun.o print.o
	gcc main.o cell_fun.o print.o $(COMP) -o ../cell.exe -g
main.o: main.c
	gcc main.c $(COMP) -c -g
cell_fun.o: cell_fun.c
	gcc cell_fun.c $(COMP) -c -g
print.o: print.c
	gcc print.c $(COMP) -c -g
gdb: ../cell.exe
	gdb ../cell.exe
clean:
	rm *.o
