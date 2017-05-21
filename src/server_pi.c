/*
** server_pi.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 00:24:41 2017 Baptiste Veyssiere
** Last update Sun May 21 22:25:52 2017 Baptiste Veyssiere
*/

#include "server.h"

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
	  return (fptr[i](data));
      }
  if (!data->username || !data->password)
    return (reply(data->control_channel, AUTH));
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

static int	pi_check(t_data *data, int *bufferize)
{
  int		ret;

  if (command_complete(data->command))
    {
      *bufferize = 0;
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
    *bufferize = 1;
  return (2);
}

int	server_pi(int control_channel, const char *ip)
{
  char		*next;
  int		buffer;
  t_data	*data;

  buffer = 0;
  if (reply(control_channel, "220 Service ready for new user.\r\n") ||
      !(data = malloc(sizeof(t_data))) ||
      init_data(data, control_channel, ip))
    return (1);
  while (!stop)
    {
      if (!(next = get_client_command(control_channel)))
	return (free_and_ret(data));
      if (buffer && !(data->command = concatenate_string(data->command, next)))
	{
	  free(data->command);
	  free(next);
	  return (free_and_ret(data));
	}
      else if (!buffer)
	data->command = next;
      if (pi_check(data, &buffer) < 2)
	return (free_and_ret(data));
    }
  return (0);
}
