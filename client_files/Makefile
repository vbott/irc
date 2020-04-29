##
## Makefile for my_irc in /home
##
## Made by botton vivien
## Login   <botton_v@epitech.net>
##
## Started on  Tue Mar 30 18:15:50 2010 vivien botton
## Last update Sun May 23 23:33:47 2010 vivien botton
##

NAME		= client

SRCS		= main.c		\
	      	actions.c		\
	      	connect.c		\
		official_join.c		\
		official_functions.c	\
	     	edit_text.c		\
		treat_packet.c		\
		my_strlen.c		\
	      	manage_widgets.c	\
		handle_packet.c		\
		change_tab.c		\
		cmd.c			\
		list.c			\
		my_strtowordtab.c	\
		send_msg.c		\
		channels.c		\
		../common/utils.c	\
		../common/xnet.c	\
		../common/xfunctions.c

OBJS		= $(SRCS:.c=.o)

CC		= clang 

RM		= rm -f

VAR		= `pkg-config --cflags gtk+-2.0`

CFLAGS	+= -ansi -W -Wall -Wextra -pipe -O2 $(VAR)

LDFLAGS  = `pkg-config --libs gtk+-2.0`

all		: $(NAME)

$(NAME)		: $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)
		cp $(NAME) ..

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)
		$(RM) ../$(NAME)

re		: fclean all
