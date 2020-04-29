/*
** part for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 07:40:45 PM CEST botton vivien
** Last update Sat 23 Apr 2011 07:40:45 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ircd.h"

static void	delete_user_in_channel(t_channel *channel, t_client *client)
{
  t_client_list	*list;
  t_client_list	*prev;

  prev = NULL;
  for (list = channel->clients; list; list = list->next)
  {
   if (list->client == client)
   {
     if (prev)
      prev->next = list->next;
     else
      channel->clients = list->next;
     channel->nb_users--;
     free(list);
     break;
   }
   prev = list;
  }
}

void		leave_channel(t_ircd *ircd, t_client *client,
	       	char *chan, char *msg)
{
  t_channel_list	*list;
  t_channel_list	*prev;

  prev = NULL;
  for (list = client->channels; list; list = list->next)
  {
    if (strcasecmp(list->channel->name, chan) == 0)
     {
       if (prev)
         prev->next = list->next;
       else
	 client->channels = list->next;
       snprintf(ircd->buffer, 512,
		       "PART %s :%s", chan, (msg) ? msg : "is leaving");
       send_to_channel(ircd, list->channel, client, ircd->buffer);
       delete_user_in_channel(list->channel, client);
       if (list->channel->nb_users == 0)
	delete_channel(ircd, list->channel);
       free(list);
       break ;
     }
   prev = list;
  }
  if (!list)
    answer_error(ircd, client, ERR_NOTONCHANNEL, ":Not on channel");
}

void		part(t_ircd *ircd, t_client *client, char **arg, int size)
{
 char		*chan;
 char		buffer[512];

 if (size < 1)
  answer_error(ircd, client, ERR_NEEDMOREPARAMS, ":Need more params");
 else
 {
   for (chan = strtok_r(arg[1], ",", (char**)buffer); chan;
	chan = strtok_r(NULL, ",", (char**)buffer))
      leave_channel(ircd, client, chan, arg[2]);
 }
}
