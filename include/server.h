/*
** server.h for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_myftp
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed May 17 22:10:30 2017 Baptiste Veyssiere
** Last update Sun May 21 21:52:12 2017 Baptiste Veyssiere
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
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# define READ_SIZE 256
# define USAGE "Usage : ./server port path\n"
# define QUEUE_SIZE 100

# define CWD_FAIL "550 Failed to change directory.\r\n"
# define CWD_SUCCESS "250 Directory successfully changed.\r\n"
# define CONNEXION_FAILED "425 Failed to establish connection.\r\n"
# define TFR_FAIL "226 Transfer done (but failed to open directory).\r\n"
# define PRELIST "150 Here comes the directory listing.\r\n"
# define USER_OK "331 User name okay, need password.\r\n"
# define LOGGED "230 User logged in, proceed.\r\n"
# define QUIT "221 Service closing control connection.\r\n"
# define FILE_OFF "550 The file is not available.\r\n"
# define FILE_ON "250 Requested file action okay, completed.\r\n"
# define HELP "USER PASS CWD CDUP QUIT DELE PWD PASV PORT \
HELP NOOP RETR STOR LIST\r\n"
# define PORT_OK "200 PORT command successful. Consider using PASV.\r\n"
# define FILE_OK "150 File status okay; about to open data connection.\r\n"
# define AUTH "530 Please login with USER and PASS.\r\n"

int	stop;

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
int	reply(int control_channel, const char *code);
int	init_data(t_data *data, int control_channel, const char *ip);

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
int	stor(t_data *data);

/*
** list.c
*/

int	list(t_data *data);

/*
** retr.c
*/

int	retr(t_data *data);

/*
** stor.c
*/

int	stor(t_data *data);

/*
** signal_handler.c
*/

void	sigint_handler(int sig);

/*
** tools.c
*/

int	pasv_init(t_data *data, int *fd, struct sockaddr_in *s_in);
int	free_and_ret(t_data *data);

#endif /* !SERVER_H_ */
