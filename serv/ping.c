/*
** ping for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 03:13:25 PM CEST botton vivien
** Last update Sat 23 Apr 2011 03:13:25 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ircd.h"

void            ping(t_ircd *ircd, t_client *client, char **arg, int size)
{
  t_packet	*packet;
  int		packet_size;

  if (size < 1)
   answer_error(ircd, client, ERR_NOORIGIN, ":No origin specified");
  else
   {
     packet = xmalloc(sizeof(*packet));
     packet_size = snprintf(packet->data, 510,
		     ":127.0.0.1 PONG 127.0.0.1 %s\r\n", arg[1]);
     if (packet_size != -1)
       add_packet(ircd, client, packet, packet_size);
     else
       free(packet);
   }
}
