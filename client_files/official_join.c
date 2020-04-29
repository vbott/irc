/*
** official_join.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun Apr 24 22:43:51 2011 cailleux carole
** Last update Sun Apr 24 22:43:51 2011 cailleux carole
*/

#define _BSD_SOURCE
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "client.h"

t_tabs		*get_tab_by_channel(t_widgets *widgets, char *channel)
{
  t_tabs                *ret;

  for (ret = widgets->tabs; ret; ret = ret->next)
    {
      if (strcasecmp(channel, (char*)gtk_label_get_text(ret->name)) == 0)
	return (ret);
    }
  return (ret);
}

void			have_joined(char *nick, t_widgets *widgets,
				    char *chan, GtkTextView *text)
{
  char                  buffer[512];

  if (strcmp(nick, widgets->nick))
    snprintf(buffer, 512, "%s have joined channel %s\n", nick, chan);
  append_text(buffer, text);
}

void			irc_join(t_widgets *widgets, char **args, char *prefix)
{
  int			size;
  t_tabs		*tab;
  char			*nickname;
  char			buffer[512];

  size = len_tab(args);
  printf("%s %d\n", prefix, size);
  if (size == 2 && prefix)
    {
      tab = get_tab_by_channel(widgets, args[1]);
      nickname = strtok(&prefix[1], "!");
      if (tab && nickname)
	have_joined(nickname, widgets, args[1], tab->text);
      else if (nickname)
        {
          snprintf(buffer, 512, "You have joined channel %s\n",
                   args[1]);
          if (args[1][0] == '#')
            add_tab(widgets, args[1]);
          else
            add_tab(widgets, nickname);
          append_text(buffer, widgets->tabs->text);
        }
    }
}
