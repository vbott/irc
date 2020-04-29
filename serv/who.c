/*
** who for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 24 Apr 2011 11:42:53 AM CEST botton vivien
** Last update Sun 24 Apr 2011 11:42:53 AM CEST botton vivien
*/

#define _BSD_SOURCE
#include <string.h>
#include "ircd.h"

static void	who_channel(t_ircd *ircd, t_client *client, char *channel)
{
  t_channel	*list;
  t_client_list	*clients;
  char		buffer[512];

  list = get_channel_by_name(ircd, channel);
  if (!list)
    return ;
  for (clients = list->clients; clients; clients = clients->next)
      {
	snprintf(buffer, 512, "%s ~%s %s %s %s H :0 %s",
		       	channel, clients->client->realname,
clients->client->ip, ircd->domain, clients->client->nickname,
clients->client->realname);
	answer_error(ircd, client, RPL_WHOREPLY, buffer);
      }
}

static void	who_user(t_ircd *ircd, t_client *client, char *user)
{
  t_client	*clients;
  char		buffer[512];

  for (clients = ircd->clients; clients; clients = clients->next)
  {
   if (clients->nickname && strcasecmp(clients->nickname, user) == 0)
   {
    snprintf(buffer, 512, "%s ~%s %s %s %s H :0 %s", user, clients->realname,
clients->ip, ircd->domain, client->nickname,
client->realname);
	answer_error(ircd, client, RPL_WHOREPLY, buffer);
    break ;
   }
  }
}

void		who(t_ircd *ircd, t_client *client, char **arg, int size)
{
  char		buffer[512];

  if (size == 1)
  {
   if (arg[1][0] == '#')
    who_channel(ircd, client, arg[1]);
   else
    who_user(ircd, client, arg[1]);
  snprintf(buffer, 512, "%s :End of /WHO", arg[1]);
  answer_error(ircd, client, RPL_ENDOFWHO, buffer);
  }
 else
  answer_error(ircd, client, RPL_ENDOFWHO, ":End of /WHO");
}
