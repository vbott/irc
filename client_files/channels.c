/*
** channels.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun Apr 24 14:14:28 2011 cailleux carole
** Last update Sun Apr 24 14:14:28 2011 cailleux carole
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "client.h"

void			join_channel(t_widgets *widgets, char **tab)
{
  char			buf[512];

  snprintf(buf, 512, "join %s\r\n", tab[1]);
  send_packet(buf, widgets->list->fd);
}

void			quit_channel(t_widgets *widgets, char **tab)
{
  t_tabs		*cpy;

  (void)tab;
  cpy = widgets->tabs;
  gtk_notebook_remove_page(widgets->tabs->tab,
			   gtk_notebook_get_current_page(widgets->tabs->tab));
}
