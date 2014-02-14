#this is chess makefile

src = main.c init_op.c basic_shape.c print_board.c mouse.c chess_op.c

para = -Wall -g 

app : $(src)
	gcc $(src) -o app $(para)
clean : 
	rm -rf *.o
	rm -rf app
	rm -rf *~
