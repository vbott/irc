/*
** change_tab.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sat Apr 23 23:25:34 2011 cailleux carole
** Last update Sat Apr 23 23:25:34 2011 cailleux carole
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <string.h>
#include "client.h"

void			add_tab(t_widgets *widgets, const gchar *name)
{
  t_tabs		*new;
  GtkWidget		*text;
  GtkTextBuffer		*buf;
  GtkWidget		*label;

  new = malloc(sizeof(t_tabs));
  buf = gtk_text_buffer_new(NULL);
  text = gtk_text_view_new();
  gtk_text_view_set_editable((GtkTextView *)text, FALSE);
  label = gtk_label_new(name);
  gtk_text_view_set_buffer((GtkTextView *)text, buf);
  new->index = gtk_notebook_append_page(widgets->tabs->tab, text, label);
  new->text = (GtkTextView *)text;
  new->str = (char *)name;
  new->name = (GtkLabel *)label;
  new->tab = widgets->tabs->tab;
  new->next = widgets->tabs;
  widgets->tabs = new;
  widgets->currenttab = new;
  gtk_widget_show((GtkWidget *)widgets->tabs->tab);
  gtk_widget_show_all(widgets->window);
}
