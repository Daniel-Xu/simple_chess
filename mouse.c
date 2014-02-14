#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"

extern fbscr_t fb_v;
mouse_event m_event;
extern u32_t current_color;
extern char chess_board[BOARD_X*BOARD_Y];
extern char current_player;
extern char diff;

static u32_t cursor_pixel[C_W*C_H] = 
{
 
    BORD,T___,T___,T___,T___,T___,T___,T___,T___,T___,
    BORD,BORD,T___,T___,T___,T___,T___,T___,T___,T___,
    BORD,X___,BORD,T___,T___,T___,T___,T___,T___,T___,
    BORD,X___,X___,BORD,T___,T___,T___,T___,T___,T___,
    BORD,X___,X___,X___,BORD,T___,T___,T___,T___,T___,
    BORD,X___,X___,X___,X___,BORD,T___,T___,T___,T___,
    BORD,X___,X___,X___,X___,X___,BORD,T___,T___,T___,
    BORD,X___,X___,X___,X___,X___,X___,BORD,T___,T___,
    BORD,X___,X___,X___,X___,X___,X___,X___,BORD,T___,
    BORD,X___,X___,X___,X___,X___,X___,X___,X___,BORD,
    BORD,X___,X___,X___,X___,X___,BORD,BORD,BORD,BORD,
    BORD,X___,X___,BORD,X___,X___,BORD,T___,T___,T___,
    BORD,X___,BORD,T___,BORD,X___,X___,BORD,T___,T___,
    BORD,BORD,T___,T___,BORD,X___,X___,BORD,T___,T___,
    T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
    T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
    T___,T___,T___,T___,T___,T___,BORD,BORD,T___,T___,
}  ; 

static int shape_save[C_H*C_W];

int save_shape(int x, int y)
{   
    int i, j;
    
    for (i = 0; i < C_H; i++){
        for(j = 0; j < C_W; j++){
            shape_save[i*C_W+j] = *((u32_t *)fb_v.memo + x +j + (y+i)*fb_v.w);
        }
    }
    

    return 0;
}

int restore(int x, int y)
{
    int i = 0;
    int j = 0;
    
    for(i = 0; i < C_H; i++){
        for(j = 0; j < C_W; j++){
            print_one_pixel(x+j, y+i, shape_save[j+i*C_W]);
        }
    }

    return 0;
}




int draw_cursor(int x, int y)
{
    int i = 0;
    int j = 0;

    save_shape(x, y);

    for(i = 0; i < C_H; i++){
        for(j = 0; j < C_W; j++){
            print_one_pixel(x+j, y+i, cursor_pixel[j+i*C_W]);
        }
    }

    return 0;
}

int get_mouse_data(int fd, mouse_event *p)
{
    int n;
    char buf[8];

    n = read(fd, buf, 8);
    if(n > 0){
        p->dx = buf[1];
        p->dy = -buf[2];
        p->button = (buf[0]&0x07);
    }

    return n;
}

int clear_board(int x, int y){
    int i;

    if((x > 25) && (x < 75) && (y > 575) && (y < 625)){
        current_color = WHITE;
        current_player = 2;
        diff = current_player;
        for(i = 0; i < BOARD_Y*BOARD_X; i++){
            chess_board[i] = 0;
        }
        print_board(); 
        draw_cursor(x,y);
        return 0;
    }
    return -1;   
}
int mouse_doing()
{
    int mx = 512;
    int my = 367;
    int fd = 0;
    char cursor_press = 0;
    int flag = 0;

    fd = open("/dev/input/mice", O_RDWR|O_NONBLOCK);
    if(fd == -1){
        perror("open");
        exit(0);
    }
    draw_cursor(mx, my);

    while(1){
        if(get_mouse_data(fd, &m_event) > 0){
            restore(mx, my);
            mx += m_event.dx;
            my += m_event.dy;
            
            if(mx < 0){
                mx = 0;
            }else if(mx > fb_v.w - C_W){
                mx = fb_v.w - C_W;
             }

            if(my < 0){
                my = 0;
            }else if(my > fb_v.h - C_H){
                my = fb_v.h - C_H;
             }
            draw_cursor(mx, my);    
            switch(m_event.button){
        
                case 0  :  if(cursor_press == 1){
                                cursor_press = 0;
                                if(flag == 0){
                                  flag = chess_doing(mx, my);
                                  if((diff == 1)){    
                                    print_circle(80, 230, 10, DARK_YELLOW);
                                    print_circle(80, 130, 10, 0x00ffff00);
                                  } 
                                  if(diff == 2){
                                    print_circle(80, 130, 10, DARK_YELLOW);
                                    print_circle(80, 230, 10, 0x00ffff00);                                    
                                   }
                                }else{
                                    flag = clear_board(mx, my);
                                 }
                           }
                           break;
                case 1  :  cursor_press = 1; break;         // chess_doing(mx, my);while(get_mouse_data(fd, &m_event)&&(m_event.button == 1));break;
                case 2  :  break;
                case 3  :  break;
                default :  break;
            }
            if(flag > 0){
                print_smile();
                print_circle(50, 700, 25, current_color);
            }
        }
        usleep(1000);
    }
    return 0;
}




