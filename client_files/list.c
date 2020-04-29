/*
** list.c for my_ftp in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sat Apr 23 20:52:44 2011 cailleux carole
** Last update Sat Apr 23 20:52:44 2011 cailleux carole
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include <sys/epoll.h>
#include <string.h>
#include "client.h"

void                    new_server_to_list(t_server **list)
{
  t_server              *new;

  new = malloc(sizeof(t_server));
  new->index = 0;
  new->fd = 0;
  new->next = *list;
  *list = new;
}

void                    free_list(t_server *list)
{
  t_server              *prev;

  prev = NULL;
  while (list)
    {
      prev = list;
      list = list->next;
      free(prev);
    }
  if (!prev)
    free(prev);
}
