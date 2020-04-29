/*
** official_functions.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun Apr 24 18:41:01 2011 cailleux carole
** Last update Sun Apr 24 18:41:01 2011 cailleux carole
*/

#define _BSD_SOURCE
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "client.h"

void			irc_quit(t_widgets *widgets, char **args, char *prefix)
{
  (void)widgets;
  (void)args;
  (void)prefix;
}

void			irc_privmsg(t_widgets *widgets, char **args,
				    char *prefix)
{
  int			size;
  t_tabs		*tab;
  char			*nickname;
  char			buffer[512];

  size = len_tab(args);
  if (size == 3 && prefix)
    {
      tab = get_tab_by_channel(widgets, args[1]);
      nickname = strtok(&prefix[1], "!");
      if (nickname && tab)
	{
	  snprintf(buffer, 512, "%s: %s\n", nickname, args[2]);
	  append_text(buffer, tab->text);
	}
    }
}

void			irc_notice(t_widgets *widgets, char **args,
	       		char *prefix)
{
  int			i;

  (void)prefix;
  i = 0;
  while (args[i])
    i++;
  if (i > 0)
    {
      i--;
      append_text(args[i], widgets->content);
      append_text("\n", widgets->content);
    }
}

void			irc_part(t_widgets *widgets, char **args, char *prefix)
{
  int			size;
  t_tabs		*tab;
  char			*nickname;
  char			buffer[512];

  size = len_tab(args);
  if (size == 3 && prefix)
  {
   tab = get_tab_by_channel(widgets, args[1]);
   nickname = strtok(&prefix[1], "!");
   if (tab && nickname)
   {
     if (strcmp(nickname, widgets->nick))
       snprintf(buffer, 512, "%s have left channel %s (%s)\n", nickname,
		       args[1], args[2]);
     else
       snprintf(buffer, 512, "You have left channel %s (%s)\n",
		       args[1], args[2]);
     append_text(buffer, tab->text);
   }
  }
}

void			irc_topic(t_widgets *widgets, char **args,
	       		char *prefix)
{
  int			size;
  t_tabs		*tab;
  char			*nickname;
  char			buffer[512];

  size = len_tab(args);
  if (size == 3 && prefix)
  {
   tab = get_tab_by_channel(widgets, args[1]);
   nickname = strtok(&prefix[1], "!");
   if (tab && nickname)
   {
     snprintf(buffer, 512, "%s has changed the topic to :%s \n", nickname,
		     args[2]);
     append_text(buffer, tab->text);
   }
  }
}
