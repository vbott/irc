/*
** answer for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 08:56:21 PM CEST botton vivien
** Last update Sat 23 Apr 2011 08:56:21 PM CEST botton vivien
*/

#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <string.h>
#include "ircd.h"

void		add_packet(t_ircd *ircd, t_client *client,
		t_packet *packet, int size)
{
 t_packet	*tmp;
 struct epoll_event event;

 packet->size = size;
 packet->next = NULL;
 for (tmp = client->packets; tmp && tmp->next ;
    tmp = tmp->next);
 if (tmp)
   tmp->next = packet;
 else
   client->packets = packet;
 if (!client->out)
  {
   client->out = send_data_client;
   event.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP;
   event.data.u64 = 0;
   event.data.ptr = client;
   epoll_ctl(ircd->epoll_fd,
    EPOLL_CTL_MOD, client->socket, &event);
  }
}

void		answer_error(t_ircd *ircd, t_client *client,
		int code, char *data)
{
  t_packet	*packet;
  int		size;

  packet = xmalloc(sizeof(*packet));
  size = snprintf(packet->data, 512,
		  ":%s %d %s %.410s\r\n", ircd->domain, code,
		  (client->nickname) ? client->nickname : "*", data);
  if (size != -1)
    add_packet(ircd, client, packet, size);
  else
    free(packet);
}

void		answer_origin(t_ircd *ircd, t_client *origin,
t_client *client, char *data)
{
  t_packet	*packet;
  int		size;

  packet = xmalloc(sizeof(*packet));
  size = snprintf(packet->data, 512,
		  ":%s!%s@%s %.410s\r\n", origin->nickname,
		  origin->username, origin->ip, data);
  if (size != -1)
    add_packet(ircd, client, packet, size);
  else
    free(packet);
}

void		answer(t_ircd *ircd, t_client *client, char *data)
{
  answer_origin(ircd, client, client, data);
}
