/*
** server_main.c for  in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 21:18:15 2017 Baptiste Veyssiere
** Last update Sun May 21 22:52:04 2017 Baptiste Veyssiere
*/

#include "server.h"

static int	close_channel(int control_channel, int ret)
{
  if (ret == 2)
    {
      if (close(control_channel) == -1)
	return (1);
      return (0);
    }
  if (close(control_channel) == -1)
    exit(1);
  exit(ret);
}

int			server_main(int fd)
{
  int			control_channel;
  struct sockaddr_in	s_in;
  socklen_t		s_in_size;

  s_in_size = sizeof(s_in);
  while (!stop)
    {
      if ((control_channel =
	   accept(fd, (struct sockaddr *)&s_in, &s_in_size)) == -1)
	return (1);
      if (fork() == 0)
	{
	  if (close(fd) == -1)
	    exit(1);
	  if (server_pi(control_channel, inet_ntoa(s_in.sin_addr)) == 1)
	    close_channel(control_channel, 1);
	  close_channel(control_channel, 0);
	}
      else
	close_channel(control_channel, 2);
    }
  return (0);
}
