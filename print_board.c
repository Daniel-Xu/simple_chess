#include <stdio.h>
#include "common.h"

int print_board(void)
{
    int i = 0, j = 0;
    /*backgroud*/
    for(i = 0; i < SPACE*BOARD_Y+70; i++){
        for(j = 20; j < SPACE*BOARD_X+500; j++){
            print_one_pixel(j, i, DARK_YELLOW);

        }
    }
    /*line*/
    for(i = ST_Y; i < ST_Y+SPACE*BOARD_Y; i += SPACE){
        print_line(ST_X, i, ST_X+(BOARD_X-1)*SPACE, i, 0x00ffffff);
    }
    /*row*/
    for(j = ST_X; j < ST_X+BOARD_X*SPACE; j += SPACE){
        print_line(j, ST_Y, j, ST_Y+(BOARD_Y-1)*SPACE, 0x00ffffff); 
    }
    
    print_circle(50, 100, 25, WHITE);
    print_circle(50, 200, 25, BLACK);
    
    return 0;
}

int print_half_cirle(int x0, int y0, int r, int color)
{
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;

    while(x <= y){
   
        // 1/4 cirle-right_down
        print_one_pixel(x0+x, y0+y, color);
        print_one_pixel(x0+y, y0+x, color);

        print_one_pixel(x0-x, y0+y, color);
        print_one_pixel(x0-y, y0+x, color);
        
        
        if(p < 0){
            p += 4 * x + 6;
        }else{
            p += 4 * (x-y) + 10;
            y--;
         }
         x++;
    }
    return 0;


}

int print_smile(void)
{
    print_circle(50 , 600, 25, BLUE); //0x00ff8c00);
    
    print_circle(40, 590, 5, 0x00ffff00);
    print_circle(60, 590, 5, 0x00ffff00);

    print_half_cirle(50, 610, 10, RED);    

    return 0;
}




