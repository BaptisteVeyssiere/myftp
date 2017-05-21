/*
** server.h for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 22:10:30 2017 Baptiste Veyssiere
** Last update Sun May 21 14:34:33 2017 Baptiste Veyssiere
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <netdb.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <ctype.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>

# define READ_SIZE 256
# define USAGE "Usage : ./server port path\n"
# define QUEUE_SIZE 100

typedef struct	s_data
{
  char		*command;
  int		username;
  int		password;
  int		control_channel;
  int		quit;
  int		mode;
  char		*path;
  char		*client_ip;
  int		client_port;
  char		*ip;
  int		data_channel;
}		t_data;

/*
** server_pi.c
*/

int	server_pi(int control_channel, const char *ip);
int	reply(int control_channel, const char *code);

/*
** server_main.c
*/

int	server_main(int fd);

/*
** get_client_command.c
*/

char	*concatenate_string(char *s1, char *s2);
char	*get_client_command(int fd);

/*
** login.c
*/

int	user(t_data *data);
int	pass(t_data *data);
int	quit(t_data *data);

/*
** directory_handler.c
*/

int	cwd(t_data *data);
int	pwd(t_data *data);
int	cdup(t_data *data);

/*
** miscellaneous.c
*/

int	noop(t_data *data);
int	help(t_data *data);
int	dele(t_data *data);

/*
** basic_functions.c
*/

int	my_getnbr(const char *str);
char	*epur_str(const char *str);

/*
** port.c
*/

int	port(t_data *data);

/*
** pasv.c
*/

int	pasv(t_data *data);

/*
** dtp.c
*/

char	*get_full_path(char *command, t_data *data);
int	dtp_init(t_data *data);
int	retr(t_data *data);
int	stor(t_data *data);

/*
** list.c
*/

int	list(t_data *data);

#endif /* !SERVER_H_ */
