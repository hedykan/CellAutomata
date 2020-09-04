#include <stdio.h>
#define SIZE 4
void print_cell(int *cell, int size);
void calc_cell(int *cell, int size);
int calc_cell_status(int *cell, int size, int local);
void copy_cell_value(int *cell, int *cell_arr, int size);

int main()
{
    int cell[SIZE] = {0, 0, 0, 0};
    print_cell(cell, SIZE);
    for(int i = 0; i < 10; i++)
    {
        calc_cell(cell, SIZE);
        print_cell(cell, SIZE);
        printf("\n");
    }
    return 0;
}

void print_cell(int *cell, int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%d", cell[i]);
    }
}

void calc_cell(int *cell, int size)
{
    int rule[8] = {1, 0, 1, 0, 1, 0, 1, 0}, num;
    int cell_arr[size];
    copy_cell_value(cell, cell_arr, size);
    for(int i = 0; i < size; i++)
    {
        num = calc_cell_status(cell_arr, size, i);
        cell[i] = rule[num];
    }
}

int calc_cell_status(int *cell, int size, int local)
{
    int left, mid, right, num;
    mid = local;
    right = local + 1;
    left = local - 1;
    if(right >= size)
        right = 0;
    if(left < 0)
        left = size - 1;

    num = (cell[left] * 4) + (cell[mid] * 2) + cell[right];
    return num;
}

void copy_cell_value(int *cell, int *cell_arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        cell_arr[i] = cell[i];
    }
}
