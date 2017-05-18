/*
** miscellaneous.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Thu May 18 15:16:48 2017 Baptiste Veyssiere
** Last update Thu May 18 15:18:46 2017 Baptiste Veyssiere
*/

#include "server.h"

int     noop(t_data *data)
{
  return (reply(data->control_channel, "200 NOOP ok.\r\n"));
}

int     help(t_data *data)
{
  (void)data;
  printf("help\n");
  return (0);
}
