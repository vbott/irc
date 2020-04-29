/*
** user for my_irc in /home/snap/projects/my_irc_cv/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 23 Apr 2011 02:40:28 PM CEST botton vivien
** Last update Sat 23 Apr 2011 02:40:28 PM CEST botton vivien
*/

#define _BSD_SOURCE
#include <string.h>
#include "ircd.h"

static void	send_motd(t_ircd *ircd, t_client *client)
{
  FILE		*file;
  char		buffer[81];

  file = fopen("./motd", "r");
  if (file)
  {
    answer_error(ircd, client, RPL_MOTDSTART, ":hello");
    while (fgets(buffer, 80, file))
      answer_error(ircd, client, RPL_MOTD, buffer);
    answer_error(ircd, client, RPL_ENDOFMOTD, ":end of /MOTD");
    fclose(file);
   }
   else
    answer_error(ircd, client, ERR_NOMOTD, "MOTD file is missing");
}

void		user(t_ircd *ircd, t_client *client, char **arg, int size)
{
  if (size < 4)
   answer_error(ircd, client, ERR_NEEDMOREPARAMS, ":Need more params");
  else if (client->nickname)
  {
    if (client->authenticated)
      answer_error(ircd, client, ERR_ALREADYREGISTRED, ":Already registered");
    else
    {
      client->username = strdup(arg[2]);
      client->realname = strdup(arg[4]);
      client->authenticated = 1;
      send_motd(ircd, client);
   }
  }
 }
