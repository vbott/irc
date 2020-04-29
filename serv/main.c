/*
** main for ircd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:21:42 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:21:42 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include "ircd.h"

char		*my_strcat(char *str1, char *str2)
{
  int		size1;
  int		size2;
  char		*ret;

  size1 = (str1) ? strlen(str1) : 0;
  size2 = (str2) ? strlen(str2) : 0;
  ret = xmalloc((size1 + size2 + 2) * sizeof(char));
  if (str1)
    memcpy(ret, str1, size1);
  if (str2)
  {
    ret[size1++] = ' ';
    memcpy(&ret[size1], str2, size2);
  }
  ret[size1 + size2] = '\0';
  return (ret);
}

static void	network_loop(t_ircd *ircd)
{
  int           	retval;
  struct epoll_event 	events[100];
  int           	i;
  t_client		*tmp;

  retval = 0;
  while (!ircd->stop && retval != -1)
   {
     retval = epoll_wait(ircd->epoll_fd, events, 100, -1);
     for (i = 0; i < retval; i++)
     {
	tmp = (t_client*) events[i].data.ptr;
	if (((events[i].events & EPOLLHUP)
	 || events[i].events & EPOLLRDHUP) && tmp->hangup)
	  tmp->hangup(ircd, tmp);
	else
	{
	  if (events[i].events & EPOLLIN && tmp->in)
	   tmp->in(ircd, tmp);
	  if (events[i].events & EPOLLOUT && tmp->out)
	   tmp->out(ircd, tmp);
	}
     }
   }
}

static void	daemonize()
{
  pid_t 	pid;
  pid_t		sid;

  pid = fork();
  if (pid == -1)
   return ;
  if (!pid)
  {
    setlogmask(LOG_UPTO(LOG_INFO));
    openlog("ircd", LOG_CONS | LOG_PERROR, LOG_USER);
    syslog(LOG_INFO, "%s daemon starting up", "ircd");
    sid = setsid();
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  }
  else
    exit(EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
  t_ircd	ircd;
  int		i;

  if (ac < 2)
  {
    fprintf(stderr, "usage : ./ircd port \n");
    return (EXIT_FAILURE);
  }
  init(&ircd);
  for (i = 1; i < ac; ++i)
  {
    if (strcmp(av[i], "-d") == 0)
      ircd.daemon = 1;
    else if (listen_to_port(&ircd, av[i]) == -1)
      return (EXIT_FAILURE);
  }
  if (ircd.daemon > 0)
   daemonize();
  network_loop(&ircd);
  return (EXIT_SUCCESS);
}
