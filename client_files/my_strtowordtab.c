/*
** my_strtowordtab.c for my_ftp in /home/audrade/work/my_ftp/client_files
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Fri Apr  1 12:29:15 2011 cailleux carole
** Last update Fri Apr  1 12:29:15 2011 cailleux carole
*/

#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "client.h"

int		len_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}

void            skip_void_char(int *i, char *str)
{
  while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
    (*i)++;
}

int             long_tab(char *str)
{
  int           i;
  int           count;

  if (!str)
    return (0);
  i = 0;
  count = 1;
  skip_void_char(&i, str);
  while (str[i])
    {
      if (str[i] == '\t' || str[i] == ' ')
	count++;
      skip_void_char(&i, str);
      i++;
    }
  if (str[my_strlen(str) - 1] == ' ' || str[my_strlen(str) - 1] == '\t')
    count--;
  return (count);
}

int             long_word(char *str)
{
  int           i;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\t')
    i++;
  return (i);
}

char		**my_strtowordtab(char *str)
{
  char		**res;
  int		i;
  int		j;
  int		k;

  if (!str || !str[0])
    return (NULL);
  res = xmalloc(sizeof(*res) * (long_tab(str) + 1));
  i = 0;
  j = 0;
  k = 0;
  skip_void_char(&k, str);
  while (str[k])
    {
      j = 0;
      res[i] = xmalloc(sizeof(char) * (long_word(&str[k]) + 1));
      while (str[k] && str[k] != ' ' && str[k] != '\t')
	res[i][j++] = str[k++];
      res[i][j] = '\0';
      skip_void_char(&k, str);
      i++;
    }
  res[i] = NULL;
  return (res);
}
