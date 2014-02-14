#ifndef _COMMON_H_
#define _COMMON_H_

typedef unsigned char u8_t;
typedef unsigned int u32_t;

typedef struct{
	int w;
	int h;
	int bpp;
	
	void *memo;
}fbscr_t;
/**/
typedef struct {

    int dx;
    int dy;
    int dz;
    
    int button;

}mouse_event;
/**/
int init_screen(void);

int print_one_pixel(int, int, int);
int print_line(int, int, int, int, int);
int print_circle(int , int , int , int);
int print_board(void);
int draw_cursor(int , int );
int print_smile(void);

int restore(int , int );
int save_shape(int , int );

int mouse_doing(void);
int get_mouse_data(int , mouse_event *);
int chess_doing(int , int); 
int chess_sort(int , int );
int print_logical(void);
int check_one(int , int );
int chess_vic(void);
/**/
#define RED   0x00ff0000
#define GREEN 0x0000ff00
#define BLUE  0x000000ff
#define WHITE 0x00ffffff
#define BLACK 0x0
#define BLUE_N 0x001e90ff  
#define DARK_YELLOW  0x00eeb422
/**/
#define space 80
#define ST_X 200
#define ST_Y 40
#define BOARD_X 29
#define BOARD_Y 24
#define SPACE 30
/**/
#define C_W  10
#define C_H  17
#define T___ DARK_YELLOW
#define X___ 0x00ffffff
#define BORD 0x00ffffff

#endif
