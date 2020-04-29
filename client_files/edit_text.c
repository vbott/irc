/*
** edit_text.c for my_ftp in /home/audrade/work/graphic
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr 21 19:49:54 2011 cailleux carole
** Last update Thu Apr 21 19:49:54 2011 cailleux carole
*/

#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "client.h"

void			change_text(char *new, GtkTextView *widget)
{
  GtkTextBuffer		*buff;

  buff = gtk_text_buffer_new(NULL);
  gtk_text_buffer_set_text(buff, new, -1);
  gtk_text_view_set_buffer(widget, buff);
}

void			append_text(char *new, GtkTextView *widget)
{
  GtkTextBuffer		*buff;
  GtkTextIter		start;
  GtkTextIter		end;

  buff = gtk_text_view_get_buffer(widget);
  gtk_text_buffer_get_bounds(buff, &start, &end);
  gtk_text_buffer_insert(buff, &end, new, strlen(new));
  gtk_text_view_set_buffer(widget, buff);
}

gchar			*get_text(GtkTextView *widget)
{
  GtkTextBuffer		*buff;
  GtkTextIter		start;
  GtkTextIter		end;

  buff = gtk_text_view_get_buffer(widget);
  return (gtk_text_buffer_get_text(buff, &start, &end, 0));
}

const gchar		*get_entry(GtkEntry *widget)
{
  return (gtk_entry_get_text(widget));
}
