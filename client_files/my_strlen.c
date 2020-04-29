/*
** my_strlen.c for my_irc in /home/audrade/work/my_irc_cv/client
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Sun Apr 24 14:41:47 2011 cailleux carole
** Last update Sun Apr 24 14:41:47 2011 cailleux carole
*/

#include <stdlib.h>
#include "client.h"

int		my_strlen(char *str)
{
  int		i;

  if (!str)
    return (0);
  i = 0;
  while (str[i])
    i++;
  return (i);
}
