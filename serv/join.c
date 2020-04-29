/*
** join for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 05:57:21 PM CEST botton vivien
** Last update Sat 23 Apr 2011 05:57:21 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <string.h>
#include "ircd.h"

static int		is_not_in(t_channel *channel, t_client *client)
{
  t_channel_list *list;

  for (list = client->channels; list; list = list->next)
  {
    if (strcasecmp(list->channel->name, channel->name) == 0)
      return (0);
  }
  return (1);
}

static t_channel	*create_channel(t_ircd *ircd, char *name, char *pass)
{
  t_channel	*chan;

  chan = xmalloc(sizeof(*chan));
  memset(chan, 0, sizeof(*chan));
  chan->name = strdup(name);
  chan->password = (pass) ? strdup(pass) : NULL;
  chan->next = ircd->channels;
  ircd->channels = chan;
  return (chan);
}

static void		add_channel(t_client_list *add,
	       	t_channel_list *chan, t_channel     *tmp, t_client *client)
{
 add->client = client;
 add->next = tmp->clients;
 tmp->clients = add;
 chan->channel = tmp;
 chan->next = client->channels;
}

static void		join_channel(t_ircd *ircd, t_client *client,
		char *channel, char *pass)
{
  t_channel	*tmp;
  t_client_list *add;
  t_channel_list *chan;
  char		buffer[512];

  if (channel[0] != '#')
  {
    answer_error(ircd, client, ERR_NOSUCHCHANNEL, ":No such channel");
    return ;
  }
  tmp = get_channel_by_name(ircd, channel);
  if (tmp == NULL)
    tmp = create_channel(ircd, channel, pass);
  if (is_not_in(tmp, client))
  {
    add = xmalloc(sizeof(*add));
    chan = xmalloc(sizeof(*chan));
    add_channel(add, chan, tmp, client);
    client->channels = chan;
    tmp->nb_users++;
    snprintf(buffer, 512, "JOIN :%s", channel);
    send_to_channel(ircd, tmp, client, buffer);
  }
}

void		join(t_ircd *ircd, t_client *client, char **arg, int size)
{
 char		*chan;
 char		buffer[512];

 if (size < 1)
  answer_error(ircd, client, ERR_NEEDMOREPARAMS, ":Need more params");
 else
 {
   for (chan = strtok_r(arg[1], ",", (char**)buffer); chan;
	chan = strtok_r(NULL, ",", (char**)buffer))
      join_channel(ircd, client, chan, arg[2]);
 }
}
