/*
** tools.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sun May 21 21:50:30 2017 Baptiste Veyssiere
** Last update Sun May 21 21:51:22 2017 Baptiste Veyssiere
*/

#include "server.h"

int	free_and_ret(t_data *data)
{
  free(data);
  return (1);
}

int	pasv_init(t_data *data, int *fd, struct sockaddr_in *s_in)
{
  struct protoent       *pe;

  if (data->mode == 2 && close(data->data_channel) == -1)
    return (1);
  data->mode = 0;
  data->data_channel = -1;
  if (!(pe = getprotobyname("TCP")) ||
      (*fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (1);
  s_in->sin_family = AF_INET;
  s_in->sin_port = htons(0);
  s_in->sin_addr.s_addr = inet_addr(data->ip);
  return (0);
}
