/*
** server_pi.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 00:24:41 2017 Baptiste Veyssiere
** Last update Fri May 19 00:36:15 2017 Baptiste Veyssiere
*/

#include "server.h"

int	pasv(t_data *data)
{
  (void)data;
  printf("pasv\n");
  return (0);
}

int	port(t_data *data)
{
  (void)data;
  printf("port\n");
  return (0);
}

int	retr(t_data *data)
{
  (void)data;
  printf("retr\n");
  return (0);
}

int	stor(t_data *data)
{
  (void)data;
  printf("stor\n");
  return (0);
}

int	list(t_data *data)
{
  (void)data;
  printf("list\n");
  return (0);
}

static int	check_command(char *pattern, char *command)
{
  int		i;

  i = -1;
  while (pattern[++i] && command[i])
    if (pattern[i] != toupper(command[i]))
      return (0);
  if (pattern[i])
    return (0);
  return (1);
}

static int	process_command(t_data *data)
{
  int		i;
  static char		*buffer[14] =
    {"USER", "PASS", "CWD ", "CDUP\r\n", "QUIT\r\n", "DELE ", "PWD\r\n",
     "PASV\r\n", "PORT ", "HELP", "NOOP\r\n", "RETR ", "STOR ", "LIST"};
  static int		(*fptr[14])(t_data*) =
    {user, pass, cwd, cdup, quit, dele, pwd, pasv, port,
     help, noop, retr, stor, list};

  i = -1;
  while (++i < 14)
    if (check_command(buffer[i], data->command))
      {
	if (i > 1 && i != 4 && (!data->username || !data->password))
	  i = 14;
	else
	  return(fptr[i](data));
      }
  if (reply(data->control_channel, "530 Please login with USER and PASS.\r\n") == 1)
    return (1);
  return (0);
}

static int	command_complete(char *command)
{
  int		length;

  length = strlen(command);
  if (length < 2)
    return (0);
  if (command[length - 1] == '\n' && command[length - 2] == '\r')
    return (1);
  return (0);
}

int reply(int control_channel, const char *code)
{
  if (write(control_channel, code, strlen(code)) < (int)strlen(code))
    return (1);
  return (0);
}

int	server_pi(int control_channel, const char *path)
{
  char		*next;
  int		bufferize;
  int		ret;
  t_data	*data;

  bufferize = 0;
  if (reply(control_channel, "220 Service ready for new user.\r\n"))
    return (1);
  if (!(data = malloc(sizeof(t_data))))
    return (1);
  data->control_channel = control_channel;
  data->command = NULL;
  data->username = 0;
  data->password = 0;
  data->quit = 0;
  data->path = (char*)path;
  data->mode = 0;
  while (1)
    {
      if (!(next = get_client_command(control_channel)))
	return (1);
      if (bufferize &&
	  !(data->command = concatenate_string(data->command, next)))
	{
	  free(data->command);
	  free(next);
	  return (1);
	}
      else if (!bufferize)
	data->command = next;
      if (command_complete(data->command))
	{
	  bufferize = 0;
	  ret = process_command(data);
	  free(data->command);
	  if (ret || data->quit)
	    return (ret);
	}
      else
	bufferize = 1;
    }
  return (0);
}
