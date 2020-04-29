/*
** nick for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 02:40:57 PM CEST botton vivien
** Last update Sat 23 Apr 2011 02:40:57 PM CEST botton vivien
*/

#define _BSD_SOURCE
#define _XOPEN_SOURCE 700
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ircd.h"

int		nick_error(t_ircd *ircd, t_client *client, char **arg)
{
  int		i;
  t_client	*clients;

 for (i = 0; arg[1][i]; i++)
   if (arg[1][i] == ','
   || arg[1][i] == ':' || arg[1][i] == ' ')
     {
        answer_error(ircd, client, ERR_ERRONEUSNICKNAME, ":Erroneus nickname");
        return (1);
      }
  for (clients = ircd->clients; clients;
		  clients = clients->next)
  if (clients->nickname && !strncasecmp(clients->nickname, arg[1], 15))
  {
    answer_error(ircd, client, ERR_NICKNAMEINUSE, ":Already in use");
    return (1);
  }
  return (0);
}

void		nick(t_ircd *ircd, t_client *client, char **arg, int size)
{
  if (size < 1)
    answer_error(ircd, client, ERR_NONICKNAMEGIVEN, ":No nick given");
  else if (!nick_error(ircd, client, arg))
  {
    snprintf(ircd->buffer, 510, "NICK :%s", arg[1]);
    send_to_all_channel(ircd, client, ircd->buffer);
    if (client->nickname)
     free(client->nickname);
    client->nickname = strndup(arg[1], 15);
   }
}
