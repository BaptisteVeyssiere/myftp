/*
** login.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 23:02:09 2017 Baptiste Veyssiere
** Last update Thu May 18 10:44:02 2017 Baptiste Veyssiere
*/

#include "server.h"

static char	*get_login(char *command)
{
  while (*(++command) && *command != ' ');
  if (*command == ' ')
    return (command + 1);
  return ("\r\n");
}

int     user(t_data *data)
{
  char	*login;

  login = get_login(data->command);
  if (!login || strcmp(login, "Anonymous\r\n"))
    return (reply(data->control_channel, "430 Invalid username.\r\n"));
  else
    {
      data->username = 1;
      return (reply(data->control_channel, "331 User name okay, need password.\r\n"));
    }
  return (0);
}

int     pass(t_data *data)
{
  char	*password;

  if (data->username == 0)
    return (reply(data->control_channel, "503 Login with USER first.\r\n"));
  password = get_login(data->command);
  if (!password || strcmp(password, "\r\n"))
    {
      data->username = 0;
      return (reply(data->control_channel, "430 Invalid password.\r\n"));
    }
  else
    {
      data->password = 1;
      return (reply(data->control_channel, "230 User logged in, proceed.\r\n"));;
    }
  return (0);
}

int     quit(t_data *data)
{
  data->quit = 1;
  if (reply(data->control_channel, "221 Service closing control connection.\r\n") == 1)
    return (1);
  return (0);
}
