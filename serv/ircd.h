/*
** xnet.h for raytracer in /home/snap/projects/raytracer/clustering
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Wed May 26 13:51:40 2010 botton vivien
** Last update Tue Jun  1 14:44:28 2010 botton vivien
*/

#ifndef		_IRCD_H_
# define	_IRCD_H_

#include <stdio.h>
#include "net.h"

#define RPL_MOTDSTART 375
#define RPL_MOTD 372
#define RPL_ENDOFMOTD 376

#define ERR_NONICKNAMEGIVEN 431
#define ERR_ERRONEUSNICKNAME 432
#define ERR_NICKNAMEINUSE 433
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTRED 462
#define ERR_NOMOTD 422
#define ERR_UNKNOWNCOMMAND 421
#define ERR_NOORIGIN 409
#define ERR_BADCHANMASK 476
#define ERR_NOSUCHCHANNEL 403
#define ERR_NOTONCHANNEL 442
#define ERR_NOTREGISTERED 451
#define ERR_CANNOTSENDTOCHAN 404
#define ERR_NORECIPIENT 411
#define ERR_NOTEXTTOSEND 412
#define ERR_NOSUCHNICK 401
#define RPL_WHOREPLY 352
#define RPL_ENDOFWHO 318
#define RPL_LISTSTART 321
#define RPL_LIST 322
#define RPL_LISTEND 323
#define RPL_NOTOPIC 331
#define RPL_TOPIC 332

# define TRUE 1
# define FALSE 0

# define IPV4_ONLY  AF_INET
# define IPV6_ONLY  AF_INET6
# define IP_MIXED AF_UNSPEC

# define PACKET_LEN 4096

typedef	struct	s_client t_client;
typedef struct	s_channel t_channel;
typedef struct	s_ircd t_ircd;

typedef struct	s_channel_list
{
  t_channel	*channel;
  struct s_channel_list *next;
} 		t_channel_list;

typedef struct	s_client_list
{
  t_client	*client;
  struct s_client_list *next;
} 		t_client_list;

typedef struct  s_packet
{
  char		data[1024];
  int		size;
  struct s_packet *next;
} 		t_packet;


struct	s_channel
{
  char		*name;
  char		*password;
  char		*topic;
  size_t	nb_users;
  size_t	right;
  size_t	limit;
  t_client_list	*clients;
  struct s_channel *next;
};

struct s_client
{
  char		*nickname;
  char		*username;
  char		*realname;
  char		*ip;
  int		authenticated;
  t_channel_list *channels;
  int		pos;
  char		buffer[1024];
  t_packet	*packets;
  SOCKET	socket;
  void		(*in)(t_ircd *, struct s_client*);
  void          (*out)(t_ircd *, struct s_client*);
  void		(*hangup)(t_ircd *, struct s_client*);
  int		(*recv)(struct s_client*, void*, size_t);
  int           (*send)(struct s_client*, void*, size_t);
  struct s_client *next;
};

struct s_ircd
{
  int		daemon;
  int		ssl;
  char		*domain;
  int		epoll_fd;
  int		stop;
  char		buffer[1024];
  t_client	*clients;
  t_channel	*channels;
};

typedef struct	s_cmd
{
  char          *cmd;
  int		authenticated;
  void          (*func)(t_ircd *, t_client*, char **, int size);
}		t_cmd;

typedef	struct	s_code
{
  int		code;
  char		*comment;
}		t_code;

void		send_data_client(t_ircd *ircd,
	       	t_client *client);

char		*my_strcat(char *,char *);

/* control_op.c */
int             send_ssl(t_client *client, void *buffer, size_t size);
int             send_normal(t_client *client, void *buffer, size_t size);
int             recv_ssl(t_client *client, void *buffer, size_t size);
int             recv_normal(t_client *client, void *buffer, size_t size);

/* init.c */
void		init(t_ircd *ircd);
int		listen_to_port(t_ircd *ircd, char *port);

/* utils.c */
int             connect_to(char *addr, char *port);
int             listen_to(char *port);

/* delete.c */
void		delete_channel(t_ircd *ircd, t_channel *channel);
void		close_client(t_ircd *ircd, t_client *);

/* client.c */
void		accept_client(t_ircd *ircd, t_client *);
void		add_packet(t_ircd *ircd, t_client *client, t_packet *packet, int size);

/* functions.c */
void		answer_error(t_ircd *ircd, t_client *client,
		int code, char *data);
void		answer(t_ircd *ircd, t_client *client, char *data);
void		answer_origin(t_ircd *ircd, t_client *origin, t_client *client, char *data);

t_channel	*get_channel_by_name(t_ircd *ircd, char *name);

void		send_to_channel(t_ircd *ircd, t_channel *channel, t_client *origin, char *data);
void		send_to_all_channel(t_ircd *ircd, t_client *client, char *data);

void		nick(t_ircd *ircd, t_client *client, char **arg, int size);
void		user(t_ircd *ircd, t_client *client, char **arg, int size);
void		ping(t_ircd *ircd, t_client *client, char **arg, int size);
void		quit(t_ircd *ircd, t_client *client, char **arg, int size);
void		join(t_ircd *ircd, t_client *client, char **arg, int size);
void		part(t_ircd *ircd, t_client *client, char **arg, int size);
void		privmsg(t_ircd *ircd, t_client *client, char **arg, int size);
void		who(t_ircd *ircd, t_client *client, char **arg, int size);
void		list(t_ircd *ircd, t_client *client, char **arg, int size);
void		topic(t_ircd *ircd, t_client *client, char **arg, int size);

/* xfunctions.c */
void		*xmalloc(size_t);

#endif		/* !_HTTPD_H */
