/*
** server_pi.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 00:24:41 2017 Baptiste Veyssiere
** Last update Sun May 21 01:25:08 2017 Baptiste Veyssiere
*/

#include "server.h"

int	retr(t_data *data)
{
  if (data->mode == 0)
    return (reply(data->control_channel, "425 Use PORT or PASV first.\r\n"));
  data->mode = 0;
  printf("retr\n");
  return (0);
}

int	stor(t_data *data)
{
  if (data->mode == 0)
    return (reply(data->control_channel, "425 Use PORT or PASV first.\r\n"));
  data->mode = 0;
  printf("stor\n");
  return (0);
}

int	list(t_data *data)
{
  if (data->mode == 0)
    return (reply(data->control_channel, "425 Use PORT or PASV first.\r\n"));
  data->mode = 0;
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
    {"USER", "PASS", "CWD ", "CDUP", "QUIT", "DELE ", "PWD",
     "PASV", "PORT ", "HELP", "NOOP", "RETR ", "STOR ", "LIST"};
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
  if (!data->username || !data->password)
    return (reply(data->control_channel, "530 Please login with USER and PASS.\r\n"));
  return (reply(data->control_channel, "500 Unknown command.\r\n"));
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

int	server_pi(int control_channel, const char *ip)
{
  char		*next;
  int		bufferize;
  int		ret;
  t_data	*data;
  char		buffer[100];

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
  if (!(data->path = getcwd(buffer, 100)))
    {
      free(data);
      return (1);
    }
  data->mode = 0;
  data->client_port = 0;
  data->client_ip = NULL;
  data->ip = (char*)ip;
  data->data_channel = -1;
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
	  if ((data->command = epur_str(data->command)))
	    {
	      ret = process_command(data);
	      free(data->command);
	    }
	  else
	    ret = 1;
	  if (ret || data->quit)
	    return (ret);
	}
      else
	bufferize = 1;
    }
  return (0);
}
