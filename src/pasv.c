/*
** pasv.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sat May 20 01:17:47 2017 Baptiste Veyssiere
** Last update Sun May 21 22:15:25 2017 Baptiste Veyssiere
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

static int	free_port(char *port1, char *port2, int ret)
{
  free(port1);
  free(port2);
  return (ret);
}

static void	fill_str(char *str, char *buf, char *port1, char *port2)
{
  strcat(str, "227 Entering Passive Mode (");
  strcat(str, buf);
  strcat(str, ",");
  strcat(str, port1);
  strcat(str, ",");
  strcat(str, port2);
  strcat(str, ").\r\n");
}

static int	passive_reply(char *ip, int port, t_data *data)
{
  char  *port1;
  char  *port2;
  char  *str;
  int   i;
  int   length;
  char	buf[16];

  if (!(port1 = to_string(port / 256)) ||
      !(port2 = to_string(port % 256)))
    return (1);
  if (!memset(buf, 0, 16))
    return (free_port(port1, port2, 1));
  strcat(buf, ip);
  i = -1;
  while (buf[++i])
    if (buf[i] == '.')
      buf[i] = ',';
  length = strlen(buf) + strlen(port1) + strlen(port2) + 34;
  if (!(str = malloc(length)) || !memset(str, 0, length))
    return (free_port(port1, port2, 1));
  fill_str(str, buf, port1, port2);
  i = reply(data->control_channel, str);
  free(str);
  return (free_port(port1, port2, 0));
}

int	pasv(t_data *data)
{

  struct sockaddr_in	s_in;
  struct sockaddr_in	sin;
  int			fd;
  int			port;
  socklen_t		len;


  if (pasv_init(data, &fd, &s_in))
    return (1);
  len = sizeof(sin);
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1 ||
      getsockname(fd, (struct sockaddr *)&sin, &len) == -1 ||
      (port = ntohs(sin.sin_port)) == -1 ||
      listen(fd, QUEUE_SIZE) == -1 ||
      passive_reply(data->ip, port, data))
    {
      close(fd);
      return (1);
    }
  data->data_channel = fd;
  data->mode = 2;
  return (0);
}
