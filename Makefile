##
## Makefile for my_irc
##
## Made by
## Login
##
## Started on  Sun Feb 14 20:23:42 2010
## Last update Mon Feb 15 16:52:27 2010 vivien botton
##

all	:
	make all -C ./serv/
	make all -C ./client_files/
clean	:
	make clean -C ./serv/
	make clean -C ./client_files/

fclean	: clean
	make fclean -C ./serv/
	make fclean -C ./client_files/

re	: fclean all
