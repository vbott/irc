/*
** quit for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 05:13:28 PM CEST botton vivien
** Last update Sat 23 Apr 2011 05:13:28 PM CEST botton vivien
*/

#include "ircd.h"

void	quit(t_ircd *ircd, t_client *client,
	char **arg, int size)
{
   close_client(ircd, client);
   (void)(arg);
   (void)(size);
}
