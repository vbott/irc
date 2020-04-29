/*
** topic for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 24 Apr 2011 03:11:06 PM CEST botton vivien
** Last update Sun 24 Apr 2011 03:11:06 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ircd.h"

t_channel	*get_channel_by_name(t_ircd *ircd, char *name)
{
  t_channel	*channel;

  for (channel = ircd->channels; channel; channel = channel->next)
   {
    if (!strcasecmp(channel->name, name))
      return (channel);
   }
  return (NULL);
}

static void	set_topic(t_ircd *ircd, t_client *client,
	       	t_channel *channel, char *topic)
{
  if (channel->topic)
    free(channel->topic);
  channel->topic = strdup(topic);
  snprintf(ircd->buffer, 512, "TOPIC %s :%s", channel->name, channel->topic);
  send_to_channel(ircd, channel, client, ircd->buffer);
}

static void	get_topic(t_ircd *ircd, t_client *client, t_channel *channel)
{
  if (channel->topic)
  {
    snprintf(ircd->buffer, 512, "%s :%s", channel->name, channel->topic);
    answer_error(ircd, client, RPL_TOPIC, ircd->buffer);
  }
  else
  {
    snprintf(ircd->buffer, 512, "%s :No topic is set", channel->name);
    answer_error(ircd, client, RPL_NOTOPIC, ircd->buffer);
  }
}

void		topic(t_ircd *ircd, t_client *client, char **arg, int size)
{
  t_channel	*channels;

  if (size < 1)
   answer_error(ircd, client, ERR_NEEDMOREPARAMS, ":Need more params");
  else if (size < 3)
  {
    channels = get_channel_by_name(ircd, arg[1]);
    if (channels && size < 2)
     get_topic(ircd, client, channels);
    else if (channels)
     set_topic(ircd, client, channels, arg[2]);
    else
     answer_error(ircd, client, ERR_NOSUCHCHANNEL, ":No such channel");
  }
}
