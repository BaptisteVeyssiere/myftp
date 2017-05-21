/*
** directory_handler.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Thu May 18 14:37:14 2017 Baptiste Veyssiere
** Last update Sun May 21 02:26:13 2017 Baptiste Veyssiere
*/

#include "server.h"

static char     *get_directory(char *command)
{
  int		i;

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

int     cwd(t_data *data)
{
  char  *directory;
  char	str[100];

  directory = get_directory(data->command);
  if (directory[0] && !realpath(directory, str))
    {
      if (ENOENT == errno)
        return (reply(data->control_channel, "550 Failed to change directory.\r\n"));
      else
	return (1);
    }
  if (!directory[0] || (directory[0] == '/' && chdir(directory + 1) == -1) ||
      (!strncmp(str, data->path, strlen(data->path)) && chdir(directory) == -1))
    {
      if (!directory[0] || ENOENT == errno)
        return (reply(data->control_channel, "550 Failed to change directory.\r\n"));
      else
        return (1);
    }
  return (reply(data->control_channel, "250 Directory successfully changed.\r\n"));
}

int     cdup(t_data *data)
{
  char	buffer[100];

  if (!memset(buffer, 0, 100) || !getcwd(buffer, 100))
    return (1);
  if (strlen(buffer) > strlen(data->path) && chdir("..") == -1)
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

  if (memset(buffer, 0, 200) == NULL || getcwd(buffer, 200) == NULL ||
      !(current = malloc(strlen(buffer) - strlen(data->path) + 35)))
    return (1);
  if (memset(current, 0, strlen(buffer) - strlen(data->path) + 35) == NULL)
    {
      free(current);
      return (1);
    }
  strcat(current, "257 \"");
  if (strlen(buffer) <= strlen(data->path))
    strcat(current, "/");
  else
    strcat(current, buffer + strlen(data->path));
  strcat(current, "\" is the current directory\r\n");
  if (reply(data->control_channel, current) == 1)
    {
      free(current);
      return (1);
    }
  free(current);
  return (0);
}
