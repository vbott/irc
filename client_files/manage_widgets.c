/*
** get_widgets.c for my_irc in /home/audrade/work/graphic
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr 21 20:00:03 2011 cailleux carole
** Last update Thu Apr 21 20:00:03 2011 cailleux carole
*/

#define _BSD_SOURCE
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/epoll.h>
#include <string.h>
#include "client.h"

int			set_epoll()
{
  int			res;

  if ((res = epoll_create(1)) == -1)
    {
      fprintf(stderr, "epoll_create failure\n");
      exit(EXIT_FAILURE);
    }
  return (res);
}

void			add_first_tab(t_widgets *widgets, GtkBuilder *p_builder)
{
  widgets->tabs = malloc(sizeof(t_tabs));
  widgets->tabs->tab = (GtkNotebook *)gtk_builder_get_object(p_builder,
							     "pageTab");
  widgets->tabs->text =
    (GtkTextView *)gtk_builder_get_object(p_builder, "contentText");
  widgets->tabs->name = (GtkLabel *)gtk_builder_get_object(p_builder,
							   "mainTab");
  widgets->tabs->index = 0;
  widgets->tabs->next = NULL;
  widgets->tabs->str = strdup("main");
  widgets->currenttab = widgets->tabs;
}

t_widgets		*get_widgets(GtkBuilder *p_builder)
{
  t_widgets		*res;

  res = malloc(sizeof(t_widgets));
  add_first_tab(res, p_builder);
  res->epfd = set_epoll();
  res->list = NULL;
  res->nick = NULL;
  res->topic = (GtkTextView *)gtk_builder_get_object(p_builder, "topicText");
  res->msg = (GtkEntry *)gtk_builder_get_object(p_builder, "sendText");
  res->send = (GtkButton *)gtk_builder_get_object(p_builder, "sendButton");
  res->ip = (GtkEntry *)gtk_builder_get_object(p_builder, "ipEntry");
  res->port = (GtkEntry *)gtk_builder_get_object(p_builder, "portEntry");
  res->content =
    (GtkTextView *)gtk_builder_get_object(p_builder, "contentText");
  res->userlist =
    (GtkTextView *)gtk_builder_get_object(p_builder, "usersText");
  res->channels =
    (GtkTextView *)gtk_builder_get_object(p_builder, "channelsText");
  res->nickname =
    (GtkEntry *)gtk_builder_get_object(p_builder, "nicknameEntry");
  res->connect =
    (GtkButton *)gtk_builder_get_object(p_builder, "connectButton");
  return (res);
}

void			set_signals(t_widgets *widgets, GtkWidget *p_win)
{
  g_signal_connect(G_OBJECT(p_win),
		   "delete-event", G_CALLBACK(quit), NULL);
  g_signal_connect(G_OBJECT(p_win),
		   "key_press_event", G_CALLBACK(handle_key), widgets);
  g_signal_connect(G_OBJECT(widgets->send),
		   "clicked", G_CALLBACK(send_msg), widgets);
  g_signal_connect(G_OBJECT(widgets->connect),
		   "clicked", G_CALLBACK(connect_server),
		   widgets);
}
