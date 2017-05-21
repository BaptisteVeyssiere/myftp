/*
** port.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Fri May 19 19:13:04 2017 Baptiste Veyssiere
** Last update Sun May 21 00:38:15 2017 Baptiste Veyssiere
*/

#include "server.h"

static char	*get_ip(const char *str)
{
  char  *ip;
  int   count;
  int   i;

  count = 0;
  i = -1;
  while (count != 4 && str[++i])
    if (str[i] == ',')
      ++count;
  if (!(ip = malloc(i + 1)) || !memset(ip, 0, i + 1))
    return (NULL);
  count = -1;
  while (str[++count] && count < i)
    if (str[count] != ',')
      ip[count] = str[count];
    else
      ip[count] = '.';
  return (ip);
}

static int	check_active_param(char *str)
{
  int   i;
  int   count;

  i = -1;
  count = 0;
  while (str[++i])
    if (str[i] == ' ' || str[i] == '\t')
      return (1);
    else if (str[i] < '0' || str[i] > '9')
      {
        if (str[i] == ',')
          ++count;
        else
          return (1);
      }
  if (count != 5)
    return (1);
  return (0);
}

static int	get_port(const char *str)
{
  int   port1;
  int   port2;
  int   port;
  int   i;

  port1 = my_getnbr(str);
  i = strlen(str);
  while (--i >= 0 && str[i] != ',');
  port2 = my_getnbr(str + i + 1);
  port = port1 * 256 + port2;
  return (port);
}

static int	check_ip_port(const char *ip, int port)
{
  int   i;

  if (port < 1024)
    return (1);
  i = -1;
  if (my_getnbr(ip) > 255)
    return (1);
  while (ip[++i] && ip[i] != '.');
  if (my_getnbr(&ip[i + 1]) > 255)
    return (1);
  while (ip[++i] && ip[i] != '.');
  if (my_getnbr(&ip[i + 1]) > 255)
    return (1);
  while (ip[++i] && ip[i] != '.');
  if (my_getnbr(&ip[i + 1]) > 255)
    return (1);
  return (0);
}

int     port(t_data *data)
{
  char  *ip;
  int   port;

  data->mode = 0;
  if (data->data_channel != -1 && close(data->data_channel) == -1)
    return (1);
  data->data_channel = -1;
  if (check_active_param(data->command + 5))
    return (reply(data->control_channel, "500 Illegal PORT command.\r\n"));
  if (!(ip = get_ip(data->command + 5)))
    return (1);
  port = get_port(data->command + strlen(ip) + 6);
  if (check_ip_port(ip, port))
    return (reply(data->control_channel, "500 Illegal PORT command.\r\n"));
  data->mode = 1;
  data->client_port = port;
  if (data->client_ip)
    free(data->client_ip);
  data->client_ip = ip;
  return (reply(data->control_channel, "200 PORT command successful. Consider using PASV.\r\n"));
}
