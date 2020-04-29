/*
** init for ircd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:21:31 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:21:31 PM CEST botton vivien
*/

#define _XOPEN_SOURCE
#define _BSD_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <signal.h>
#include <fcntl.h>
#include "ircd.h"

void			init(t_ircd *ircd)
{
  struct sigaction      act;

  memset(&act, 0, sizeof(act));
  memset(ircd, 0, sizeof(*ircd));
  ircd->domain = strdup("127.0.0.1");
  act.sa_handler = SIG_IGN;
  sigaction(SIGPIPE, &act, NULL);
  ircd->epoll_fd = epoll_create(1);
}

int		listen_to_port(t_ircd *ircd, char *port)
{
  SOCKET	socket;
  struct epoll_event ev;
  t_client	*tmp;

  socket = listen_to(port);
  if (socket != -1)
   {
     tmp = xmalloc(sizeof(*tmp));
     memset(tmp, 0, sizeof(*tmp));
     tmp->socket = socket;
     tmp->in = accept_client;
     ev.events = EPOLLIN;
     ev.data.u64 = 0;
     ev.data.ptr = tmp;
     epoll_ctl(ircd->epoll_fd, EPOLL_CTL_ADD, socket, &ev);
   }
  return (socket);
}
