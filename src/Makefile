COMP = -std=c99
OBJ_FILE = main.o cell_print.o cell_create.o cell_calc.o
../cell.exe: $(OBJ_FILE)
	gcc $(OBJ_FILE) $(COMP) -o ../cell.exe -g
main.o: main.c
	gcc main.c $(COMP) -c -g
cell_create.o: cell_create.c
	gcc cell_create.c $(COMP) -c -g
cell_calc.o: cell_calc.c
	gcc cell_calc.c $(comp) -c -g
cell_print.o: cell_print.c
	gcc cell_print.c $(COMP) -c -g
gdb: ../cell.exe
	gdb ../cell.exe
clean:
	rm *.o
