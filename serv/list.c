/*
** list for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 24 Apr 2011 01:16:58 PM CEST botton vivien
** Last update Sun 24 Apr 2011 01:16:58 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <string.h>
#include "ircd.h"

static void	list_channel(t_ircd *ircd, t_client *client, t_channel *chan)
{
  snprintf(ircd->buffer, 512, "%s %u:%s",
chan->name, chan->nb_users, (chan->topic) ? chan->topic : "");
  answer_error(ircd, client, RPL_LIST, ircd->buffer);
}

static void	list_all_channel(t_ircd *ircd, t_client *client)
{
  t_channel	*channels;

  for (channels = ircd->channels; channels; channels = channels->next)
  {
   list_channel(ircd, client, channels);
  }
}

static void	list_channels(t_ircd *ircd, t_client *client, char *channel)
{
  t_channel	*channels;

   channels = get_channel_by_name(ircd, channel);
   if (channels)
     list_channel(ircd, client, channels);
}

void		list(t_ircd *ircd, t_client *client, char **arg, int size)
{
  char		buffer[1024];
  char		*chan;

  answer_error(ircd, client, RPL_LISTSTART, "Channel :Users  Name");
  if (size < 1)
    list_all_channel(ircd, client);
  else
    {
      for (chan = strtok_r(arg[1], ",", (char**)buffer);
		      chan; chan = strtok_r(NULL, ",", (char**)buffer))
     {
       list_channels(ircd, client, chan);
     }
    }
 answer_error(ircd, client, RPL_LISTEND, ":End of /LIST");
}
