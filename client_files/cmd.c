/*
** cmd.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sat Apr 23 23:49:44 2011 cailleux carole
** Last update Sat Apr 23 23:49:44 2011 cailleux carole
*/

#define _BSD_SOURCE
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include "client.h"

static const t_cmdcli		cmds[] = {
  {"JOIN", join_channel, 2},
  {"QUIT", quit_channel, 1}
};

void			launch_user_cmd(char **cmd, t_widgets *widgets)
{
  int			i;
  void			(*launch)(t_widgets *, char **);

  i = 0;
  launch = NULL;
  while (i < 2)
    {
      if (!strcasecmp(cmds[i].cmd, &cmd[0][1]))
	{
	  if (len_tab(cmd) != cmds[i].nb)
	    {
	      append_text("Incorrect number of arguments",
			  widgets->currenttab->text);
	      return ;
	    }
	  launch = cmds[i].ptr;
	}
      i++;
    }
  if (launch)
    launch(widgets, cmd);
  else
    append_text("Unknown command", widgets->currenttab->text);
}

void			free_tab(char **tab)
{
  int			i;

  if (!tab || !tab[0])
    return ;
  i = 0;
  while (tab[i])
    {
      free(tab[i]);
      i++;
    }
  free(tab);
}

void			write_in_chat(char *cmd, t_widgets *widgets)
{
  char			buf[512];

  if (widgets->currenttab->index == 0)
    append_text("No channel joined. Try /join #<channel>\n",
		widgets->currenttab->text);
  else
    {
      snprintf(buf, 512, "PRIVMSG %s :%s\r\n", widgets->currenttab->str, cmd);
      send_packet(buf, widgets->list->fd);
      snprintf(buf, 512, "%s: %s\r\n", widgets->nick, cmd);
      append_text(buf, widgets->currenttab->text);
    }
}

void			parse_cmd(char *cmd, t_widgets *widgets)
{
  int			i;
  char			**tab;

  if (!cmd || !widgets->list)
    return ;
  i = 0;
  if (cmd[0] == '/')
    {
      tab = my_strtowordtab(cmd);
      if (!tab || !tab[0] || !tab[1])
	{
	  free_tab(tab);
	  return ;
	}
      launch_user_cmd(tab, widgets);
      free_tab(tab);
    }
  else
    write_in_chat(cmd, widgets);
}
