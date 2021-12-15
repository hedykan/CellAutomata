COMP = -std=c99
OBJ_FILE = main.o cell_print.o cell_create.o cell_calc.o cell_init.o cell_operate.o
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
cell_train.o: cell_train.c
	gcc cell_train.c $(COMP) -c -g
cell_operate.o : cell_operate.c
	gcc cell_operate.c $(COMP) -c -g
cell_init.o: cell_init.c
	gcc cell_init.c $(COMP) -c -g
gdb: ../cell.exe
	gdb ../cell.exe
clean:
	rm *.o
