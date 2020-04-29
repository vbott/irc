##
## Makefile for 42sh in /u/all/castel_a/cu/42sh/current
##
## Made by botton vivien
## Login   <botton_v@epitech.net>
##
## Started on  Tue Mar 30 18:15:50 2010 vivien botton
## Last update Sun May 23 23:33:47 2010 vivien botton
##

SERV	= ../serveur

SRCS_SERV = control_op.c \
	init.c \
	main.c \
	answer.c \
	functions.c \
	client.c \
	delete.c \
	user.c \
	nick.c \
	ping.c \
	join.c \
	part.c \
	privmsg.c \
	who.c \
	list.c \
	topic.c \
	quit.c \
	../common/utils.c \
	../common/xfunctions.c \
	../common/xnet2.c \
	../common/xnet.c

OBJS_SERV = $(SRCS_SERV:.c=.o)

CC	= clang 

RM	= rm -f

CFLAGS	+= -ansi -Wall -Wextra -pipe -g3 -O2 -I../common/ -I.

all	: $(SERV)

$(SERV)	: $(OBJS_SERV)
	$(CC) -o $(SERV) $(OBJS_SERV) $(LIBS)

clean	:
	$(RM) $(OBJS_SERV)

fclean	: clean
	$(RM) $(SERV)

re	: fclean all

#.c.o	:
#	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
