/*
** list.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sun May 21 13:26:49 2017 Baptiste Veyssiere
** Last update Sun May 21 22:36:56 2017 Baptiste Veyssiere
*/

#include "server.h"

static int	send_list(int data_channel, t_data *data, char *command)
{
  DIR           *d;
  struct dirent *dir;
  int           i;

  d = opendir(command);
  if (d)
    {
      i = 0;
      while ((dir = readdir(d)) != NULL)
        if (dir->d_name[0] != '.')
          if ((++i > 1 && reply(data_channel, "\n")) ||
              reply(data_channel, dir->d_name))
            {
	      if (closedir(d) == -1)
                return (1);
              return (1);
            }
      if (closedir(d) == -1)
        return (1);
      if (reply(data_channel, "\r\n"))
        return (1);
    }
  else
    return (reply(data->control_channel, TFR_FAIL));
  return (reply(data->control_channel, "226 Directory send OK.\r\n"));
}

static int	data_close(t_data *data, int ret)
{
  if (data->mode == 2)
    close(data->data_channel);
  data->mode = 0;
  return (ret);
}

int	list(t_data *data)
{
  int   data_channel;
  int   ret;
  char	*command;

  if (data->mode == 0)
    return (reply(data->control_channel, "425 Use PORT or PASV first.\r\n"));
  if ((data_channel = dtp_init(data)) == 1)
    return (data_close(data, 0));
  if (!(ret = reply(data->control_channel, PRELIST)))
    {
      if (!(command = get_full_path(data->command, data)))
	return (data_close(data, 1));
      if (send_list(data_channel, data, command))
	return (1);
      free(command);
    }
  if (close(data_channel) == -1 ||
      (data->mode == 2 && close(data->data_channel)))
    {
      data->mode = 0;
      return (1);
    }
  data->mode = 0;
  return (ret);
}
