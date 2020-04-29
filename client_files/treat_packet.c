/*
** treat_packet.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun Apr 24 22:58:11 2011 cailleux carole
** Last update Sun Apr 24 22:58:11 2011 cailleux carole
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

void		send_to_manage(char **tab, t_widgets *widgets)
{
  char          *prefix;

  prefix = NULL;
  if (tab[0] && tab[0][0] == ':')
    {
      prefix = tab[0];
      if (tab[1])
        manage_packet(&tab[1], widgets, prefix);
    }
  else if (tab[0])
    manage_packet(tab, widgets, prefix);
}

void		treat_packet(t_packet *packet, t_widgets *widgets)
{
  char		*str;
  char		*tab[10];
  char		buffer[1024];
  int		i;

  i = 0;
  for (str = strtok_r(packet->data, " ", (char**)&buffer);
       str && i < 10; str = strtok_r(NULL, " ", (char**)&buffer))
    {
      if (i > 0 && str[0] == ':')
        {
          tab[i] = str;
          str = strtok_r(NULL, "", (char**)&buffer);
          tab[i] = my_strcat(&tab[i][1], str);
        }
      else
        tab[i] = str;
      i++;
    }
  tab[i] = NULL;
  send_to_manage(tab, widgets);
}
