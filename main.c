#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <unistd.h>
#include <time.h>



int main(void)
{

	init_screen();	
/*    print_line(10, 20, 700, 100, RED);
    
    print_line(10, 10, 1000, 50, GREEN);

    for(i = 0; i < 100; i++){
        for(j = 0; j < 100; j++){
            print_one_pixel(100+j, 100+i, RED);
        }
    }
*/
    //print_line(10, 10, 100, 50, RED);
    //print_line(90, 40, 20, 20,  RED);
    //print_line(10, 10, 50, 100, RED);
    //print_line(40, 90 , 20, 20, RED);
    //print_line(100, 10, 10, 50, RED);
    //print_line(20, 40, 90, 20, RED);
    //print_line(10, 100, 50, 10, RED);
    //print_line(50, 10, 10, 100, RED);

    
    //i = 0;
    //while(i < 10){
        //print_circle(512, 360, i, BLACK);
        //i++;
        //}
    
      print_board(); 
/*    save_shape(100, 300);

    draw_cursor(100, 300);

    sleep(2);
    restore(100,300);
    draw_cursor(430,133);
*/

/*    int i = 0;
    int x = 0, y = 0;
    srand(time(NULL));
    for(i = 0; i < 100; i++){
        save_shape((x = (rand()%1024)), (y = (rand()%768)));
        draw_cursor(x, y);
        usleep(500000);
        restore(x, y);
        printf("%d\n", i);
    }
*/
    mouse_doing();
  //  print_smile();

    return 0; 

}
