/*
** send_msg.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sat Apr 23 21:38:31 2011 cailleux carole
** Last update Sat Apr 23 21:38:31 2011 cailleux carole
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include "client.h"

void			send_msg(GtkWidget *widget, gpointer data)
{
  (void)widget;
  on_enter(data);
}
