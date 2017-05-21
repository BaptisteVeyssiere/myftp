/*
** retr.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sun May 21 15:34:07 2017 Baptiste Veyssiere
** Last update Sun May 21 22:38:17 2017 Baptiste Veyssiere
*/

#include "server.h"

static int	retr_file(t_data *data, int data_channel)
{
  char	*command;
  int	fd;
  int	ret;
  char	buffer[100];

  if (!(command = get_full_path(data->command, data)) ||
      !memset(buffer, 0, 100))
    return (1);
  fd = open(command, O_RDONLY);
  free(command);
  if (fd == -1)
    return (reply(data->control_channel, "550 Failed to open file.\r\n"));
  if (reply(data->control_channel, FILE_OK))
    return (1);
  while ((ret = read(fd, buffer, 100)) > 0)
    if (ret == -1 ||
	write(data_channel, buffer, strlen(buffer)) < (int)strlen(buffer) ||
	!memset(buffer, 0, 100))
      return (1);
  if (write(data_channel, "\r\n", 2) != 2 ||
      reply(data->control_channel, "226 Transfer complete.\r\n") ||
      close(fd) == -1)
    return (1);
  return (0);
}

int	retr(t_data *data)
{
  int   data_channel;

  if (data->mode == 0)
    return (reply(data->control_channel, "425 Use PORT or PASV first.\r\n"));
  if ((data_channel = dtp_init(data)) == 1)
    {
      if (data->mode == 2)
        close(data->data_channel);
      data->mode = 0;
      return (0);
    }
  if (retr_file(data, data_channel) || close(data_channel) == -1 ||
      (data->mode == 2 && close(data->data_channel)))
    {
      data->mode = 0;
      return (1);
    }
  data->mode = 0;
  return (0);
}
