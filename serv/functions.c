/*
** functions for functions in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Fri 22 Apr 2011 07:38:51 PM CEST botton vivien
** Last update Fri 22 Apr 2011 07:38:51 PM CEST botton vivien
*/

#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <string.h>
#include "ircd.h"

void		send_data_client(t_ircd *ircd,
	       	t_client *client)
{
  t_packet	*packet;
  struct epoll_event event;

  packet = client->packets;
  if (packet)
  {
    client->packets = packet->next;
    client->send(client, packet->data, packet->size);
    free(packet);
  }
  if (!client->packets)
  {
    client->out = NULL;
    event.events = EPOLLIN | EPOLLRDHUP;
    event.data.u64 = 0;
    event.data.ptr = client;
    epoll_ctl(ircd->epoll_fd,
		    EPOLL_CTL_MOD, client->socket, &event);
  }
}

void		send_to_channel(t_ircd *ircd, t_channel *channel,
t_client *origin, char *data)
{
  t_client_list	*client;

  for (client = channel->clients; client; client = client->next)
  {
    answer_origin(ircd, origin, client->client, data);
  }
}

void		send_to_all_channel(t_ircd *ircd, t_client *client, char *data)
{
  t_channel_list	*channel;

  for (channel = client->channels; channel; channel = channel->next)
  {
    send_to_channel(ircd, channel->channel, client, data);
  }
}
