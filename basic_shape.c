#include <stdio.h>
#include <stdlib.h>
#include "common.h"

extern fbscr_t fb_v;

void swap(int *p, int *q)
{
    int tmp;

    tmp = *q;
    *q = *p;
    *p = tmp;
}

int print_one_pixel(int x, int y, int color)
{
    *((u32_t *)fb_v.memo+y*fb_v.w+x) = color;

    return 0;
}

int print_line(int x1, int y1, int x2, int y2, int color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p;
    int inc = (dx*dy >0) ? 1 : -1;
    
    if(abs(dx) > abs(dy)){
        if(dx < 0){
            swap(&x1, &x2);
            swap(&y1, &y2);
            dx = -dx;
            dy = -dy;
        }
        dy = abs(dy);
        p = 2*dy - dx;

        while(x1 <= x2){
            print_one_pixel(x1, y1, color);
            x1++;
        
        if(p < 0){
            p += 2*dy;
        }else{
                y1 += inc;
                p += 2*(dy-dx);
            }
        }
    }else{
        if(dy < 0){
            swap(&x1, &x2);
            swap(&y1, &y2);
            dx = -dx;
            dy = -dy;
        }
        dx = abs(dx);
        p = 2*dx - dy;

        while(y1 <= y2){
            print_one_pixel(x1, y1, color);
            y1++;
        
        if(p < 0){
            p += 2*dx;
        }else{
                x1 += inc;
                p += 2*(dx-dy);
            }
        }
    
     }
    return 0;
}

int print_circle(int x0, int y0, int r, int color)
{
    int x = 0;
    int y = r;
    int p = 3 - 2 * r;

    while(x <= y){
#if 0   
        // 1/4 cirle-right_down
        print_one_pixel(x0+x, y0+y, color);
        print_one_pixel(x0+y, y0+x, color);
        // 1/4 cirle-right_up
        print_one_pixel(x0+x, y0-y, color);
        print_one_pixel(x0+y, y0-x, color);

        print_one_pixel(x0-x, y0+y, color);
        print_one_pixel(x0-y, y0+x, color);
        
        print_one_pixel(x0-y, y0-x, color);
        print_one_pixel(x0-x, y0-y, color);
#endif 
        print_line(x0-x, y0+y, x0+x, y0+y, color);
        print_line(x0-y, y0+x, x0+y, y0+x, color);
        
        print_line(x0-x, y0-y, x0+x, y0-y, color);
        print_line(x0-y, y0-x, x0+y, y0-x, color);


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
