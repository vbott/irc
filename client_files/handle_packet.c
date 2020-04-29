/*
** handle_packet.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sat Apr 23 20:55:16 2011 cailleux carole
** Last update Sat Apr 23 20:55:16 2011 cailleux carole
*/

#define _BSD_SOURCE
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include <sys/epoll.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "client.h"

static const t_cmds		cmds[] = {
  {"JOIN", &irc_join, 2},
  {"QUIT", &irc_quit, 1},
  {"PRIVMSG", &irc_privmsg, 1},
  {"NOTICE", &irc_notice, 1},
  {"PART", &irc_part, 1},
  {"TOPIC", &irc_topic, 1}
};

char            *my_strcat(char *str1, char *str2)
{
  int           size1;
  int           size2;
  char          *ret;

  size1 = (str1) ? strlen(str1) : 0;
  size2 = (str2) ? strlen(str2) : 0;
  ret = xmalloc((size1 + size2 + 2) * sizeof(char));
  if (str1)
    memcpy(ret, str1, size1);
  if (str2)
    {
      ret[size1++] = ' ';
      memcpy(&ret[size1], str2, size2);
    }
  ret[size1 + size2] = '\0';
  return (ret);
}

void		manage_packet(char **tab, t_widgets *widgets, char *prefix)
{
  int		i;

  for (i = 0 ; i < 6 ; i++)
    {
      if (!strcmp(cmds[i].cmd, tab[0]))
	{
	  cmds[i].ptr(widgets, tab, prefix);
	  return ;
	}
    }
   i = 0;
   while (tab[i])
    i++;
   if (i > 0)
   {
    i--;
    append_text(tab[i], widgets->content);
    append_text("\n", widgets->content);
   }
}

static void	fill_packet(t_packet *packet, t_server *server, int j)
{
 if (j + server->index > 0 && server->buf[j + server->index - 1] == '\r')
   server->buf[j + server->index - 1] = '\0';
  server->buf[j + server->index] = '\0';
  memcpy(packet->data, server->buf, server->index);
  memcpy(&packet->data[server->index], &server->buf[server->index], j);
  packet->size = j + server->index;
}

void                    show_msg(t_widgets *widgets, t_server *server)
{
  int                   nbread;
  int                   i;
  int                   j;
  t_packet              packet;

  nbread = recv(server->fd, &server->buf[server->index], 512, 0);
  if (nbread == 0 || nbread == -1)
    exit(EXIT_FAILURE);
  server->buf[server->index + nbread] = '\0';
  j = 0;
  for (i = 0 ; i < nbread ; i++)
    {
      if (server->buf[j + server->index] == '\n')
        {
          fill_packet(&packet, server, j);
          memmove(server->buf, &server->buf[server->index + j + 1],
		  nbread - i);
          server->index = 0;
          j = 0;
          treat_packet(&packet, widgets);
        }
      ++j;
    }
}

gboolean                get_packet(gpointer data)
{
  struct epoll_event    event[100];
  t_server              *cpy;
  int                   nbfd;
  t_widgets		*widget;
  int			i;

  widget = (t_widgets *)data;
  if (widget->list == NULL)
    return (TRUE);
  nbfd = epoll_wait(widget->epfd, event, 100, 0);
  for (i = 0; i < nbfd; i++)
  {
      cpy = (t_server *)event[i].data.ptr;
      if (event[i].events & EPOLLRDHUP)
        {
	  epoll_ctl(widget->epfd, EPOLL_CTL_DEL, cpy->fd, NULL);
	  close(cpy->fd);
          return (TRUE);
        }
      else if (event[i].events & EPOLLIN)
        show_msg(data, cpy);
  }
  return (TRUE);
}
