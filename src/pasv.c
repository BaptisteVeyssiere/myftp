/*
** pasv.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sat May 20 01:17:47 2017 Baptiste Veyssiere
** Last update Sun May 21 01:13:50 2017 Baptiste Veyssiere
*/

#include "server.h"

static char	*to_string(int nbr)
{
  char  *s;
  int   count;
  int   tmp;

  tmp = nbr;
  count = 1;
  while (tmp > 9)
    {
      ++count;
      tmp /= 10;
    }
  if (!(s = malloc(count + 1)) || !memset(s, 0, count + 1))
    return (NULL);
  while (--count >= 0)
    {
      s[count] = nbr % 10 + '0';
      nbr /= 10;
    }
  return (s);
}

static int	passive_reply(char *ip, int port, t_data *data)
{
  char  *port1;
  char  *port2;
  char  *str;
  int   i;
  int   length;

  if (!(port1 = to_string(port / 256)))
    return (1);
  if (!(port2 = to_string(port % 256)))
    {
      free(port1);
      return (1);
    }
  i = -1;
  while (ip[++i])
    if (ip[i] == '.')
      ip[i] = ',';
  length = strlen(ip) + strlen(port1) + strlen(port2) + 34;
  if (!(str = malloc(length)) || !memset(str, 0, length))
    {
      free(port1);
      free(port2);
      return (1);
    }
  strcat(str, "227 Entering Passive Mode (");
  strcat(str, ip);
  strcat(str, ",");
  strcat(str, port1);
  strcat(str, ",");
  strcat(str, port2);
  strcat(str, ").\r\n");
  i = reply(data->control_channel, str);
  free(str);
  free(port1);
  free(port2);
  return (i);
}

int	pasv(t_data *data)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  struct sockaddr_in	sin;
  int			fd;
  int			port;
  socklen_t		len;

  data->mode = 0;
  if (data->data_channel != -1 && close(data->data_channel) == -1)
    return (1);
  data->data_channel = -1;
  if (!(pe = getprotobyname("TCP")) ||
      (fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (1);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(0);
  s_in.sin_addr.s_addr = inet_addr(data->ip);
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1 ||
      getsockname(fd, (struct sockaddr *)&sin, &len) == -1 ||
      (port = ntohs(sin.sin_port)) == -1 ||
      passive_reply(data->ip, port, data))
    {
      if (close(fd) == -1)
	return (1);
      return (1);
    }
  data->data_channel = fd;
  data->mode = 2;
  return (0);
}
