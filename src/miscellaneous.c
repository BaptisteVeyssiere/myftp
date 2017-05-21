/*
** miscellaneous.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Thu May 18 15:16:48 2017 Baptiste Veyssiere
** Last update Fri May 19 19:35:28 2017 Baptiste Veyssiere
*/

#include "server.h"

static char     *get_filename(char *command)
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
        return (reply(data->control_channel, "550 The file is not available.\r\n"));
      else
        return (1);
    }
  return (reply(data->control_channel, "250 Requested file action okay, completed.\r\n"));
}

int     noop(t_data *data)
{
  return (reply(data->control_channel, "200 NOOP ok.\r\n"));
}

int     help(t_data *data)
{
  char	prologue[] = "214-The following commands are recognized.\r\n";
  char	list[] = "USER PASS CWD CDUP QUIT DELE PWD PASV PORT HELP NOOP RETR STOR LIST\r\n";
  char	epilogue[] = "214 Help OK.\r\n";

  if (reply(data->control_channel, prologue) == 1 ||
      reply(data->control_channel, list) == 1 ||
      reply(data->control_channel, epilogue) == 1)
    return (1);
  return (0);
}
