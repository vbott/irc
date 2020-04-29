/*
** connect.c for my_ftp in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Fri Apr 22 22:09:39 2011 cailleux carole
** Last update Fri Apr 22 22:09:39 2011 cailleux carole
*/

#define _BSD_SOURCE
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "client.h"

void			send_packet(char *packet, int fd)
{
  int			nbwrite;

  if (!packet)
    return ;
  nbwrite = write(fd, packet, strlen(packet));
  if (nbwrite <= 0)
    {
      perror("write");
      exit(EXIT_FAILURE);
    }
}

void			send_user(char *nick, char *serv, int fd)
{
  char			buf[512];

  snprintf(buf, 512, "NICK %s\r\n", nick);
  send_packet(buf, fd);
  snprintf(buf, 512, "USER %s %s %s :%s\r\n", nick, nick, serv, nick);
  send_packet(buf, fd);
}

void			do_connect(t_widgets *widgets, char *ip,
				   char *port)
{
  struct epoll_event	event;
  t_server		*old;

  new_server_to_list(&(widgets->list));
  widgets->list->fd = connect_to(ip, ((port[0]) ? port : "6667"));
  if (widgets->list->fd == -1)
    {
      old = widgets->list;
      widgets->list = widgets->list->next;
      free(old);
      return ;
    }
  event.events = EPOLLIN | EPOLLRDHUP;
  event.data.u64 = 0;
  event.data.ptr = widgets->list;
  if (epoll_ctl(widgets->epfd, EPOLL_CTL_ADD, widgets->list->fd, &event) == -1)
    {
      close(widgets->list->fd);
      free_list(widgets->list);
      exit(EXIT_FAILURE);
    }
  send_user((char *)get_entry(widgets->nickname),
	    (char *)get_entry(widgets->ip), widgets->list->fd);
  widgets->nick = strdup((char *)get_entry(widgets->nickname));
}
