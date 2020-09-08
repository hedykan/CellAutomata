#define SIZE 4

struct Cell
{
    int status;
    int status_size;
    int status_group[8];
};

void print_cell(int *cell, int size);
void calc_cell(int *cell, int size);
int calc_cell_status(int *cell, int size, int local);
void copy_cell_value(int *cell, int *cell_arr, int size);
