/*
** basic_functions.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Fri May 19 19:09:15 2017 Baptiste Veyssiere
** Last update Fri May 19 23:12:27 2017 Baptiste Veyssiere
*/

#include "server.h"

char    *epur_str(const char *str)
{
  char  *res;
  int   i;
  int   count;

  count = 0;
  i = -1;
  while (str[++i])
    if (str[i] != ' ' && str[i] != '\t')
      ++count;
    else if (i > 0 && str[i - 1] != ' ' && str[i - 1] != '\t')
      ++count;
  if (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
    --count;
  if (!(res = malloc(count + 1)) || !memset(res, 0, count + 1))
    return (NULL);
  i = -1;
  count = -1;
  while (str[++i])
    if (str[i] != ' ' && str[i] != '\t')
      res[++count] = str[i];
    else if (i > 0 && str[i - 1] != ' ' && str[i - 1] != '\t')
      res[++count] = ' ';
  if (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
    res[count] = 0;
  res[strlen(res) - 1] = 0;
  res[strlen(res) - 1] = 0;
  return (res);
}

int     my_getnbr(const char *str)
{
  int   nbr;
  int   i;
  int   dec;

  i = -1;
  while (str[++i] && str[i] != ',' && str[i] != '.');
  dec = 1;
  nbr = 0;
  while (--i >= 0)
    {
      nbr += (str[i] - '0') * dec;
      dec *= 10;
    }
  return (nbr);
}
