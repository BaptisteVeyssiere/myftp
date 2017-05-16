/*
** server_pi.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 00:24:41 2017 Baptiste Veyssiere
** Last update Wed May 17 00:44:13 2017 Baptiste Veyssiere
*/

#include <stdio.h>

void	user(const char *command)
{
  (void)command;
  printf("user\n");
}

void	pass(const char *command)
{
  (void)command;
  printf("pass\n");
}

void	cwd(const char *command)
{
  (void)command;
  printf("cwd\n");
}

void	cdup(const char *command)
{
  (void)command;
  printf("cdup\n");
}

void	quit(const char *command)
{
  (void)command;
  printf("quit\n");
}

void	dele(const char *command)
{
  (void)command;
  printf("dele\n");
}

void	pwd(const char *command)
{
  (void)command;
  printf("pwd\n");
}

void	pasv(const char *command)
{
  (void)command;
  printf("pasv\n");
}

void	port(const char *command)
{
  (void)command;
  printf("port\n");
}

void	help(const char *command)
{
  (void)command;
  printf("help\n");
}

void	noop(const char *command)
{
  (void)command;
  printf("noop\n");
}

void	retr(const char *command)
{
  (void)command;
  printf("retr\n");
}

void	stor(const char *command)
{
  (void)command;
  printf("stor\n");
}

void	list(const char *command)
{
  (void)command;
  printf("list\n");
}

static int	check_command(char *pattern, char *command)
{
  int		i;

  i = -1;
  while (pattern[++i] && command[i])
    if (pattern[i] != command[i])
      return (0);
  if (pattern[i])
    return (0);
  return (1);
}

void	server_pi(char *command)
{
  char	*buffer[14] =
    {"USER", "PASS", "CWD", "CDUP", "QUIT", "DELE", "PWD",
     "PASV", "PORT", "HELP", "NOOP", "RETR", "STOR", "LIST"};
  void	(*fptr[14])(const char *) =
    {
      user,
      pass,
      cwd,
      cdup,
      quit,
      dele,
      pwd,
      pasv,
      port,
      help,
      noop,
      retr,
      stor,
      list
    };
  int	i;

  i = -1;
  while (++i < 14)
    if (check_command(buffer[i], command))
      {
	fptr[i](command);
	break;
      }
  if (i == 14)
    printf ("Invalid command: %s\n", command);
}

int	main(int ac, char **av)
{
  if (ac != 2)
    return (1);
  server_pi(av[1]);
  return (0);
}
