/*
** client for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 02:40:41 PM CEST botton vivien
** Last update Sat 23 Apr 2011 02:40:41 PM CEST botton vivien
*/

#define _XOPEN_SOURCE
#define _BSD_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include "ircd.h"

static const t_cmd  gl_cmd[] = {
  {"NICK", 0, nick},
  {"USER", 0, user},
  {"PING", 0, ping},
  {"QUIT", 0, quit},
  {"JOIN", 1, join},
  {"PART", 1, part},
  {"WHO", 1, who},
  {"LIST", 1, list},
  {"TOPIC", 1, topic},
  {"PRIVMSG", 1, privmsg},
  {NULL, 0, NULL}
};

static int	treat_cmd(t_ircd *ircd, t_client *client, char **tab)
{
  size_t	i;
  int		size;
  char		buffer[512];

  for (size = 0; tab[size]; ++size);
  --size;
  for (i = 0; tab[0] && gl_cmd[i].cmd && strcasecmp(gl_cmd[i].cmd, tab[0]); ++i);
  if (!gl_cmd[i].cmd)
  {
   snprintf(buffer, 512, "%s :Unknown command", tab[0]);
   answer_error(ircd, client, ERR_UNKNOWNCOMMAND, buffer);
  }
  else if (gl_cmd[i].authenticated > client->authenticated)
   answer_error(ircd, client, ERR_NOTREGISTERED,
			":You have not registered");
  else
   {
     gl_cmd[i].func(ircd, client, tab, size);
     return (gl_cmd[i].func == quit);
   }
  return (0);
}

static int	treat_packet(t_ircd *ircd, t_client *client, t_packet *packet)
{
  char		*str;
  char		*tab[10];
  char		buffer[1024];
  int		i;

  i = 0;
  for (str = strtok_r(packet->data, " ", (char**)&buffer);
		  str && i < 10; str = strtok_r(NULL, " ", (char**)&buffer))
  {
    if (i > 0 && str[0] == ':')
    {
      tab[i] = str;
      str = strtok_r(NULL, "", (char**)&buffer);
      tab[i] = my_strcat(&tab[i][1], str);
    }
    else
      tab[i] = str;
    i++;
  }
  tab[i] = NULL;
  return ((tab[0]) ? treat_cmd(ircd, client,
			  (tab[0][0] == ':') ? &tab[1] : tab) : 0);
}

static void	fill_packet(t_packet *packet, t_client *client, int j)
{
 if (j + client->pos > 0 && client->buffer[j + client->pos - 1] == '\r')
   client->buffer[j + client->pos - 1] = '\0';
  client->buffer[j + client->pos] = '\0';
  memcpy(packet->data, client->buffer, client->pos);
  memcpy(&packet->data[client->pos], &client->buffer[client->pos], j);
  packet->size = j + client->pos;
}

static void	read_data_client(t_ircd *ircd, t_client *client)
{
  int		lu;
  int		i;
  int		j;
  t_packet	packet;

  lu = client->recv(client, &client->buffer[client->pos], 512);
  if (lu == -1 || lu == 0)
  {
    close_client(ircd, client);
    return ;
  }
  j = 0;
  for (i = 0; i < lu; ++i)
   {
     if (client->buffer[j + client->pos] == '\n')
     {
       fill_packet(&packet, client, j);
       memmove(client->buffer, &client->buffer[client->pos + j + 1], lu - i);
       client->pos = 0;
       j = 0;
       if (treat_packet(ircd, client, &packet))
	  return ;
     }
     j++;
   }
}

void		accept_client(t_ircd *ircd, t_client *serv)
{
  SOCKET	socket;
  struct epoll_event ev;
  t_client	*client;

  socket = accept(serv->socket, NULL, 0);
  if (socket == -1)
    return ;
  client = xmalloc(sizeof(*client));
  memset(client, 0, sizeof(*client));
  client->send = send_normal;
  client->recv = recv_normal;
  client->socket = socket;
  client->ip = strdup("127.0.0.1");
  client->next = ircd->clients;
  client->in = read_data_client;
  client->hangup = close_client;
  ircd->clients = client;
  ev.events = EPOLLIN | EPOLLHUP | EPOLLRDHUP;
  ev.data.u64 = 0;
  ev.data.ptr = client;
  if (epoll_ctl(ircd->epoll_fd, EPOLL_CTL_ADD, socket, &ev))
    close_client(ircd, client);
}
