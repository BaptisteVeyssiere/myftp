/*
** miscellaneous.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Thu May 18 15:16:48 2017 Baptiste Veyssiere
** Last update Sun May 21 18:11:34 2017 Baptiste Veyssiere
*/

#include "server.h"

static char	*get_filename(char *command)
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

int	dele(t_data *data)
{
  char	*filename;

  filename = get_filename(data->command);
  if (!filename || remove(filename) == -1)
    {
      if (ENOENT == errno)
        return (reply(data->control_channel, FILE_OFF));
      else
        return (1);
    }
  return (reply(data->control_channel, FILE_ON));
}

int	noop(t_data *data)
{
  return (reply(data->control_channel, "200 NOOP ok.\r\n"));
}

int	help(t_data *data)
{
  char	prologue[] = "214-The following commands are recognized.\r\n";
  char	list[] = HELP;
  char	epilogue[] = "214 Help OK.\r\n";

  if (reply(data->control_channel, prologue) == 1 ||
      reply(data->control_channel, list) == 1 ||
      reply(data->control_channel, epilogue) == 1)
    return (1);
  return (0);
}
