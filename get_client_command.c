/*
** get_client_command.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 00:23:14 2017 Baptiste Veyssiere
** Last update Wed May 17 00:23:15 2017 Baptiste Veyssiere
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define READ_SIZE 256

char	*concatenate_string(const char *s1, const char *s2)
{
  char	*result;
  int	length;
  int	i;
  int	j;

  length = strlen(s1) + strlen(s2) + 1;
  result = malloc(length);
  if (result == NULL || memset(result, 0, length) == NULL)
    return (NULL);
  i = -1;
  while (s1[++i])
    result[i] = s1[i];
  --i;
  j = -1;
  while (++i < length)
    result[i] = s2[++j];
  return (result);
}

static char	*fill_command(char *command, char *buffer, int i)
{
  int		j;

  j = -1;
  while (++j < i)
    {
      command[j] = buffer[j];
      buffer[j] = 0;
    }
  if (j < READ_SIZE && buffer[j])
    {
      --j;
      while (++j < READ_SIZE && buffer[j])
	{
	  buffer[j - i] = buffer[j];
	  buffer[j] = 0;
	}
    }
  return (command);
}

char	*get_client_command(int fd)
{
  char		*command;
  static char	buffer[READ_SIZE] = {0};
  int		i;

  if (buffer[0] == 0 && read(fd, buffer, READ_SIZE) < 1)
    return (NULL);
  i = -1;
  while (++i < READ_SIZE && buffer[i] &&
	 (i == 0 || buffer[i] != '\n' || buffer[i - 1] != '\r'));
  if (i < READ_SIZE && buffer[i])
    ++i;
  if (i < 0 || !(command = malloc(i + 1)) || memset(command, 0, i + 1) == NULL)
    return (NULL);
  command = fill_command(command, buffer, i);
  return (command);
}
