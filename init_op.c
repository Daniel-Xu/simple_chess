#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "common.h"

fbscr_t fb_v;

u32_t current_color ;
char chess_board[BOARD_X*BOARD_Y];
char current_player;
char diff = 0;

int init_screen(void)
{
	int fd = 0;
	u32_t *p = NULL;
//	int i = 0;	
   	struct fb_var_screeninfo fb_var_scr;

	
	/*open----fd : file descriptor*/
	fd = open("/dev/fb0", O_RDWR);
	if(fd == -1){
		perror("open");
		exit(0);
	}
	/*get the device info*/
	if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var_scr) == -1){
		perror("ioctl");
		exit(0);
	}
	/*information detail, the struct info can be found in <liux/fb.h>*/
	fb_v.w = fb_var_scr.xres;
	fb_v.h = fb_var_scr.yres;
	fb_v.bpp = fb_var_scr.bits_per_pixel;
	
	printf("x= %d\ty= %d\tbpp= %d\n", fb_v.w, fb_v.h, fb_v.bpp);
	
	/*mapping*/		
	p =  mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8, PROT_READ|PROT_WRITE, MAP_SHARED, fd,0);
	
	if(p == MAP_FAILED){
		perror("mmap");
		exit(0);
	}
	
	/*save p to struct*/
	fb_v.memo = p;
	/*close device file, include <unistd.h>*/
	close(fd);

    current_color = WHITE;
    current_player = 2;
    diff = current_player;
	/*refresh the screen*/
	memset(p, 0x00, fb_v.w*fb_v.h*fb_v.bpp/8);	//get by char ,so /8;

	
/*	for(i = 0; i < 100; i++){
		*(p+(1024*(50+i))+400) = 0x00ffff00;
		*(p+(1024*(50+i))+401) = 0x00ffff00;
		*(p+(1024*(50+i))+402) = 0x00ffff00;
		*(p+(1024*(50+i))+403) = 0x00ffff00;
		*(p+(1024*(50+i))+404) = 0x00ffff00;
		*(p+(1024*(50+i))+405) = 0x00ffff00;
		*(p+(1024*(50+i))+406) = 0x00ffff00;
		*(p+(1024*(50+i))+407) = 0x00ffff00;
	}*/		
	return 0;
}
