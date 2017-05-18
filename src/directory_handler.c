/*
** directory_handler.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Thu May 18 14:37:14 2017 Baptiste Veyssiere
** Last update Fri May 19 00:25:05 2017 Baptiste Veyssiere
*/

#include "server.h"

static char     *get_directory(char *command)
{
  int		i;

  while (*(++command) && *command != ' ');
  if (*command == ' ')
    {
      i = 0;
      while (command[++i] && command[i] != ' ' &&
	     command[i] != '\r' && command[i] != '\n');
      if (command[i])
	command[i] = 0;
      return (command + 1);
    }
  return ("");
}

int     cwd(t_data *data)
{
  char  *directory;

  directory = get_directory(data->command);
  if (!directory || chdir(directory) == -1)
    {
      if (ENOENT == errno)
        return (reply(data->control_channel, "550 Failed to change directory.\r\n"));
      else
        return (1);
    }
  return (reply(data->control_channel, "250 Directory successfully changed.\r\n"));
}

int     cdup(t_data *data)
{
  if (chdir("..") == -1)
    {
      if (ENOENT == errno)
        return (reply(data->control_channel, "550 Failed to change directory.\r\n"));
      else
        return (1);
    }
  return (reply(data->control_channel, "250 Directory successfully changed.\r\n"));
}

int     pwd(t_data *data)
{
  char  buffer[200];
  char  *current;

  if (memset(buffer, 0, 200) == NULL)
    return (1);
  if (getcwd(buffer, 200) == NULL)
    return (1);
  if (!(current = malloc(strlen(buffer) + 34)))
    return (1);
  if (memset(current, 0, strlen(buffer) + 34) == NULL)
    {
      free(current);
      return (1);
    }
  strcat(current, "257 \"");
  strcat(current, buffer);
  strcat(current, "\" is the current directory\r\n");
  if (reply(data->control_channel, current) == 1)
    {
      free(current);
      return (1);
    }
  free(current);
  return (0);
}
