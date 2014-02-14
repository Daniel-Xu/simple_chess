#include <stdio.h>
#include "common.h"

extern u32_t current_color;
extern char chess_board[BOARD_X*BOARD_Y];
extern char current_player;
extern char diff;

int chess_doing(int x, int y)
{
    int m_x = x;
    int m_y = y;
    int dx = (x-ST_X)%SPACE;
    int dy = (y-ST_Y)%SPACE;
    
    if(x < ST_X || x > ST_X+SPACE*(BOARD_X-1)){
        
        if((x > 25)&&(x < 75)&&(y > 75)&&(y < 125)&&(current_player == 1)){
            current_color = WHITE;
            current_player = 2;
        }    
        if((x > 25)&&(x < 75)&&(y > 175)&&(y < 225)&&(current_player == 2)){
            current_color = BLACK;
            current_player = 1;
        } 

        return 0;
     }


    if(y < ST_Y || y > ST_Y+SPACE*(BOARD_Y-1)){
        
        return 0;
    }

    /*adjust*/
    if(dx < SPACE/2){
        x -= dx;
    }else{
        x +=(SPACE-dx);
     }
    if(dy < SPACE/2){
        y -= dy;
    }else{
        y +=(SPACE-dy);
     
     }

    if((diff != current_player)&&(chess_board[(x-ST_X)/SPACE+BOARD_X*(y-ST_Y)/SPACE]) == 0){ 
        restore(m_x, m_y);
    //    restore(80, 230);
        print_circle(x, y, 13, current_color);
        diff = current_player;
        draw_cursor(m_x, m_y);
        chess_sort(x, y);
      //  draw_cursor(80, 130);
    }
   
   // print_logical();
    if(chess_vic() != 0){
      //  print_smile();
        return current_player;
    }
    return 0;
}

int chess_sort(int x, int y)
{
    int c_x = (x-ST_X)/SPACE;//logical value
    int c_y = (y-ST_Y)/SPACE;

    chess_board[c_x+c_y*BOARD_X] = current_player;
    return 0;
}

/*int print_logical(void)
{
    int i, j;
    
    for(j = 0; j < BOARD_Y; j++){
        for(i = 0; i < BOARD_X; i++){
            printf("%d", chess_board[i+j*BOARD_X]);
        }
    }
    return 0;
}*/

int check_one(int x, int y)
{
    int i = 0, j = 0;
    int cnt = 0;
    char player = chess_board[x+y*BOARD_X];
    char na[4] = {1, 0, 1, 1};
    char ma[4] = {0, 1, 1, -1};
    int sx = x;
    int sy = y;
    
    if(player == 0)
        return 0;
    for(j = 0; j < 4; j++){    //four direction
        x = sx;
        y = sy;
        cnt = 1;
        for(i = 1; i < 5; i++){  //four same chess
            x += na[j];
            y += ma[j];
            if(chess_board[x+y*BOARD_X] == player){
                cnt++;
            }else{
                break;
             }
                
            }
        if(cnt == 5){
            return player;
        }
    }
    return 0;
}

int chess_vic(void)
{
    int i = 0;
    int j = 0;
    int res = 0;

    for(j = 0; j < BOARD_Y; j++){
        for(i = 0; i < BOARD_X; i++){
            res = check_one(i, j);
            if(res != 0){
                return res;
            }
        }    
    }

    return 0;
}
