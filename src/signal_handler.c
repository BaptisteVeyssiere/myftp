/*
** signal_handler.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sun May 21 21:10:54 2017 Baptiste Veyssiere
** Last update Sun May 21 21:56:09 2017 Baptiste Veyssiere
*/

#include "server.h"

void	sigint_handler(int sig)
{
  struct sigaction	act;

  if (sig == SIGINT)
    {
      stop = 1;
      memset(&act, 0, sizeof(act));
      act.sa_handler = &sigint_handler;
      sigaction(SIGINT, &act, NULL);
    }
}
