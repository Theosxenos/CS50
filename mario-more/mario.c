//#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

void build_pyramid(int height);
void build_left_pyramid(int row, int height);
void build_right_pyramid(int row, int height);

int get_int(char *prompt)
{
    int number;
    char input[100];
    
    printf("%s", prompt);
    fgets(input, sizeof(input), stdin);
    
    // Convert the input char* to an integer
    number = atoi(input);
    
    return number;
}

void print_block(int block_amount, int padding_left, int padding_right);

int main(void)
{
    int height;
    do
    {
        height  = get_int("Height: ");
    } while(height <= 0);
    build_pyramid(height);
}

void print_block(int block_amount, int padding_left, int padding_right)
{
    for (int i = 0; i < padding_left; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < block_amount; i++)
    {
        printf("#");
    }
    for (int i = 0; i < padding_right; i++)
    {
        printf(" ");
    }
}


void build_pyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        build_left_pyramid(i, height);
        build_right_pyramid(i, height);
        printf("\n");
    }
 
}

void build_left_pyramid(int row, int height)
{
    print_block(row, height - row, 1);
}

void build_right_pyramid(int row, int height)
{
    print_block(row, 1, 0);
}
