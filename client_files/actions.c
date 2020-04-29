/*
** handle_keys.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Fri Apr 22 15:19:01 2011 cailleux carole
** Last update Fri Apr 22 15:19:01 2011 cailleux carole
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include "client.h"

void				quit(void)
{
  gtk_main_quit();
}

void				on_enter(t_widgets *widgets)
{
  const gchar			*text;

  text = gtk_entry_get_text(widgets->msg);
  if (!text || !text[0])
    return ;
  parse_cmd((char *)text, widgets);
  gtk_entry_set_text(widgets->msg, "");
}

gboolean			handle_key(GtkWidget *widget, GdkEventKey *event,
					   gpointer widgets)
{
  (void)widget;
  if (event->keyval == GDK_Escape)
    gtk_main_quit();
  else if (event->keyval == GDK_Return)
    on_enter(widgets);
  else
    return (FALSE);
  return (TRUE);
}

void				connect_server(GtkWidget *widget, gpointer data)
{
  const gchar			*nick;
  const gchar			*ip;
  const gchar			*port;
  t_widgets			*widgets;

  (void)widget;
  widgets = (t_widgets *)data;
  nick = gtk_entry_get_text(widgets->nickname);
  ip = gtk_entry_get_text(widgets->ip);
  port = gtk_entry_get_text(widgets->port);
  if (!ip[0] || !nick[0] || widgets->list)
    return ;
  append_text("Connecting to ", widgets->content);
  append_text((char *)ip, widgets->content);
  append_text(" port ", widgets->content);
  if (port[0])
    append_text((char *)port, widgets->content);
  else
    append_text("6667", widgets->content);
  append_text("...\n", widgets->content);
  do_connect(widgets, (char *)ip, (char *)port);
}
