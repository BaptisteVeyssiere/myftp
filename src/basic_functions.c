/*
** basic_functions.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Fri May 19 19:09:15 2017 Baptiste Veyssiere
** Last update Sun May 21 22:11:30 2017 Baptiste Veyssiere
*/

#include "server.h"

static void	finish_epur(int i, char *res, const char *str, int count)
{
  if (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
    res[count] = 0;
  res[strlen(res) - 1] = 0;
  res[strlen(res) - 1] = 0;
}

char	*epur_str(const char *str)
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
  finish_epur(i, res, str, count);
  return (res);
}

int	my_getnbr(const char *str)
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

int	reply(int control_channel, const char *code)
{
  if (write(control_channel, code, strlen(code)) < (int)strlen(code))
    return (1);
  return (0);
}

int	init_data(t_data *data, int control_channel, const char *ip)
{
  data->control_channel = control_channel;
  data->command = NULL;
  data->username = 0;
  data->password = 0;
  data->quit = 0;
  if (!(data->path = malloc(100)) ||
      !memset(data->path, 0, 100) ||
      !getcwd(data->path, 100))
    {
      free(data);
      return (1);
    }
  data->mode = 0;
  data->client_port = 0;
  data->client_ip = NULL;
  data->ip = (char*)ip;
  data->data_channel = -1;
  return (0);
}
