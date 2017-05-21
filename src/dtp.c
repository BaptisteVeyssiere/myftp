/*
** dtp.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sun May 21 02:48:15 2017 Baptiste Veyssiere
** Last update Sun May 21 15:37:25 2017 Baptiste Veyssiere
*/

#include "server.h"

static char	*get_filepath(char *command)
{
  int           i;

  while (*(++command) && *command != ' ');
  if (*command == ' ')
    {
      i = 0;
      while (command[++i] && command[i] != ' ');
      if (command[i])
        command[i] = 0;
      return (command + 1);
    }
  return ("");
}

char	*get_full_path(char *command, t_data *data)
{
  char	*file;
  char	buffer[100];
  char	*ret;

  file = get_filepath(command);
  if (file[0] != '/')
    {
      if (file[0] == 0)
	{
	  if (!(ret = malloc(2)) || !memset(ret, 0, 2))
	    return (NULL);
	  ret[0] = '.';
	  return (ret);
	}
      if (!getcwd(buffer, 100) ||
	  !(ret = malloc(strlen(buffer) + strlen(file) + 2)) ||
	  !memset(ret, 0, strlen(buffer) + strlen(file) + 2))
	return (NULL);
      strcat(ret, buffer);
      strcat(ret, "/");
      strcat(ret, file);
    }
  else
    {
      if (!(ret = malloc(strlen(data->path) + strlen(file))) ||
	  !memset(ret, 0, strlen(data->path) + strlen(file)))
	return (NULL);
      strcat(ret, data->path);
      strcat(ret, file);
    }
  return (ret);
}

int		dtp_init(t_data *data)
{
  struct sockaddr_in	s_in;
  struct protoent	*pe;
  socklen_t		s_in_size;
  int			data_channel;

  if (data->mode == 2 &&
      (data_channel =
       accept(data->data_channel, (struct sockaddr *)&s_in, &s_in_size)) == -1)
    return (1);
  else if (data->mode == 1)
    {
      s_in.sin_family = AF_INET;
      s_in.sin_port = htons(data->client_port);
      s_in.sin_addr.s_addr = inet_addr(data->client_ip);
      if (!(pe = getprotobyname("TCP")) ||
	  (data_channel = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
	return (1);
      if (connect(data_channel, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
	{
	  close(data_channel);
	  return (reply(data->control_channel, "425 Failed to establish connection.\r\n"));
	}
    }
  return (data_channel);
}

int     stor(t_data *data)
{
  int	data_channel;
  int	ret;

  if (data->mode == 0)
    return (reply(data->control_channel, "425 Use PORT or PASV first.\r\n"));
  if ((data_channel = dtp_init(data)) == 1)
    {
      if (data->mode == 2)
	close(data->data_channel);
      data->mode = 0;
      return (1);
    }
  ret = reply(data_channel, "STOR\r\n");
  if (close(data_channel) == -1 ||
      (data->mode == 2 && close(data->data_channel)))
    {
      data->mode = 0;
      return (1);
    }
  data->mode = 0;
  return (ret);
}
