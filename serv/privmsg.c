/*
** privmsg for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 09:54:57 PM CEST botton vivien
** Last update Sat 23 Apr 2011 09:54:57 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <string.h>
#include "ircd.h"

static void	send_msg_channel(t_ircd *ircd, t_client *client,
char *receiver, char *msg)
{
  t_channel_list *list;
  t_client_list  *users;

  for (list = client->channels; list; list = list->next)
    if (strcasecmp(list->channel->name, receiver) == 0)
    {
      snprintf(ircd->buffer, 480,
      "PRIVMSG %s :%s", receiver, msg);
      for (users = list->channel->clients; users; users = users->next)
      {
        if (users->client != client)
	  answer_origin(ircd, client, users->client, ircd->buffer);
      }
      break ;
    }
 if (list == NULL)
   answer_error(ircd, client, ERR_CANNOTSENDTOCHAN, ":Cannot send to chan");
}

static void	send_msg_user(t_ircd *ircd, t_client *client,
char *receiver, char *msg)
{
  t_client	*list;

  for (list = ircd->clients; list; list = list->next)
  {
    if (list->nickname
    && strcasecmp(list->nickname, receiver) == 0)
    {
       snprintf(ircd->buffer, 480,
       "PRIVMSG %s :%s", receiver, msg);
       answer_origin(ircd, client, list, ircd->buffer);
       break ;
    }
  }
  if (!list)
   answer_error(ircd, client, ERR_NOSUCHNICK, ":No such nick");
}

void		privmsg(t_ircd *ircd, t_client *client, char **arg, int size)
{
 char		*chan;
 char		buffer[1024];

 if (size < 1)
  answer_error(ircd, client, ERR_NORECIPIENT, ":No recipient");
else if (size < 2)
  answer_error(ircd, client, ERR_NOTEXTTOSEND, ":No text to send");
 else
 {
   for (chan = strtok_r(arg[1], ",", (char**)buffer);
		   chan; chan = strtok_r(NULL, ",", (char**)buffer))
    {
     if (chan[0] == '#')
      send_msg_channel(ircd, client, chan, arg[2]);
     else
      send_msg_user(ircd, client, chan, arg[2]);
    }
 }
}
