/*
** delete for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 04:38:05 PM CEST botton vivien
** Last update Sat 23 Apr 2011 04:38:05 PM CEST botton vivien
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include "ircd.h"

void		delete_channel(t_ircd *ircd, t_channel *channel)
{
  t_channel	*cpy;
  t_channel	*prev;

  prev = NULL;
  for (cpy = ircd->channels; cpy; cpy = cpy->next)
  {
    if (cpy == channel)
    {
      if (prev)
        prev->next = cpy->next;
      else
	ircd->channels = cpy->next;
      if (cpy->name)
        free(cpy->name);
      if (cpy->password)
	free(cpy->password);
      if (cpy->topic)
	free(cpy->topic);
      free(cpy);
      break ;
    }
    prev = cpy;
  }
}

static void		delete_client_in_channel(t_ircd *ircd,
	       	t_client *client, t_channel *channel, char *msg)
{
  t_client_list *cpy;
  t_client_list	*prev;

  prev = NULL;
  for (cpy = channel->clients; cpy; cpy = cpy->next)
  {
   if (cpy->client == client)
   {
     if (prev)
       prev->next = cpy->next;
     else
       channel->clients = cpy->next;
     if (!channel->clients)
       delete_channel(ircd, channel);
   }
   else
    answer_origin(ircd, client, cpy->client, msg);
   prev = cpy;
  }
}

static void		delete_client_in_irc(t_ircd *ircd, t_client *client)
{
  t_client	*cpy;
  t_client	*prev;

  prev = NULL;
  for (cpy = ircd->clients; cpy; cpy = cpy->next)
  {
    if (cpy == client)
    {
      if (prev)
	prev->next = client->next;
      else
	ircd->clients = client->next;
      break ;
    }
  }
}

static void		delete_packet(t_client *client)
{
  t_packet		*cpy;

  while (client->packets)
  {
    cpy = client->packets;
    client->packets = client->packets->next;
    free(cpy);
  }
}

void		close_client(t_ircd *ircd, t_client *client)
{
  t_channel_list *channels;
  t_channel_list *cpy;

  epoll_ctl(ircd->epoll_fd, EPOLL_CTL_DEL, client->socket, NULL);
  xshutdown(client->socket, SHUT_RDWR);
  for (channels = client->channels; channels; )
   {
     cpy = channels;
     delete_client_in_channel(ircd, client, cpy->channel, "QUIT :Client quit");
     channels = channels->next;
     free(cpy);
   }
  delete_client_in_irc(ircd, client);
  delete_packet(client);
  if (client->nickname)
   free(client->nickname);
  if (client->username)
   free(client->username);
  if (client->realname)
   free(client->realname);
  close(client->socket);
  free(client);
}
