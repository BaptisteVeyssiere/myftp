/*
** main.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 21:02:12 2017 Baptiste Veyssiere
** Last update Thu May 18 14:23:59 2017 Baptiste Veyssiere
*/

#include "server.h"

static int	stoi(char *str)
{
  int		nbr;
  int		i;

  if (str == NULL)
    return (-1);
  i = -1;
  while (str[++i])
    if (str[i] < '0' || str[i] > '9')
      return (-1);
  nbr = atoi(str);
  return (nbr);
}

static int		init_server(int port, const char *path)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;

  if (!(pe = getprotobyname("TCP")) ||
      (fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (1);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1 ||
      listen(fd, QUEUE_SIZE) == -1 ||
      server_main(fd, path) == 1)
    {
      if (close(fd) == -1)
	return (1);
      return (1);
    }
  if (close(fd) == -1)
    return (1);
  return (0);
}

static int	check_path(const char *path)
{
  DIR	*dir;

  dir = opendir(path);
  if (dir)
    {
      if (closedir(dir) == -1)
	return (-1);
      return (1);
    }
  else if (ENOENT == errno)
    return (0);
  else
    return (-1);
  return (0);
}

int	main(int argc, char **argv)
{
  int	port;
  int	ret;

  if (argc != 3)
    {
      write(1, USAGE, strlen(USAGE));
      return (0);
    }
  if ((port = stoi(argv[1])) == -1 ||
      (ret = check_path(argv[2])) == -1)
    return (1);
  if (ret == 0)
    {
      write(1, "The directory does not exist\n", 29);
      return (0);
    }
  else if (chdir(argv[2]) == -1)
    return (1);
  if (init_server(port, argv[2]) == 1)
    return (1);
  return (0);
}
