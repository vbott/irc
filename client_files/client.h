/*
** client.h for my_ftp in /home/audrade/work/graphic
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Thu Apr 21 19:52:50 2011 cailleux carole
** Last update Thu Apr 21 19:52:50 2011 cailleux carole
*/

#ifndef				__CLIENT_H__
# define			__CLIENT_H__

#include <gtk/gtk.h>
#include <glib.h>

typedef struct		s_packet
{
  char			data[1024];
  int			size;
  struct s_packet	*next;
}			t_packet;

typedef struct		s_server
{
  int			fd;
  char			buf[1024];
  int			index;
  struct s_server	*next;
}			t_server;

typedef struct		s_tabs
{
  GtkNotebook		*tab;
  GtkTextView		*text;
  GtkLabel		*name;
  char			*str;
  gint			index;
  struct s_tabs		*next;
}			t_tabs;

typedef struct		s_widgets
{
  GtkWidget		*window;
  GtkTextView		*topic;
  GtkTextView		*content;
  GtkTextView		*userlist;
  GtkTextView		*channels;
  GtkEntry		*msg;
  GtkButton		*send;
  GtkEntry		*nickname;
  GtkEntry		*ip;
  GtkEntry		*port;
  GtkButton		*connect;
  t_tabs		*tabs;
  t_server		*list;
  t_tabs		*currenttab;
  int			epfd;
  char			*nick;
}			t_widgets;

typedef struct		s_cmds
{
  char			*cmd;
  void			(*ptr)(t_widgets *, char **, char *);
  int			nb;
}			t_cmds;

typedef struct		s_cmdcli
{
  char			*cmd;
  void			(*ptr)(t_widgets *, char **);
  int			nb;
}			t_cmdcli;

/* channels.c */
void			join_channel(t_widgets *widgets, char **tab);
void			quit_channel(t_widgets *widgets, char **tab);

/* manage_widgets.c */
t_widgets		*get_widgets(GtkBuilder *p_builder);
void			set_signals(t_widgets *widgets, GtkWidget *p_win);

/* edit_text.c */
gchar			*get_text(GtkTextView *widget);
void			change_text(char *new, GtkTextView *widget);
const gchar		*get_entry(GtkEntry *widget);
void			send_msg(GtkWidget *widget, gpointer data);
void			append_text(char *new, GtkTextView *widget);

/* actions.c */
void			on_enter(t_widgets *widgets);
gboolean		handle_key(GtkWidget *widget, GdkEventKey *event,
				   gpointer func_data);
void			quit(void);
void			connect_server(GtkWidget *widget, gpointer data);

/* my_strtowordtab.c */
char			**my_strtowordtab(char *str);
int			len_tab(char **tab);

/* treat_packet.c */
void			treat_packet(t_packet *packet, t_widgets *widgets);

/* my_strlen.c */
int			my_strlen(char *str);

/* connect.c */
void			do_connect(t_widgets *widgets, char *ip, char *port);
void			send_packet(char *packet, int fd);

/* handle_packet.c */
gboolean		get_packet(gpointer data);
char			*my_strcat(char *str1, char *str2);
void			manage_packet(char **tab, t_widgets *widgets, char *prefix);

/* ../common/xfunctions.c */
void			*xmalloc(size_t size);

/* ../common/utils.c */
int			connect_to(char *addr, char *port);

/* list.c */
void			new_server_to_list(t_server **list);
void			free_list(t_server *list);

/* change_tab.c */
void			add_tab(t_widgets *widgets, const gchar *name);

/* send_msg.c */
void			send_msg(GtkWidget *widget, gpointer data);

/* cmd.c */
void			parse_cmd(char *cmd, t_widgets *widgets);

/* official_commands.c */
void			irc_quit(t_widgets *widgets, char **args, char *prefix);
void			irc_privmsg(t_widgets *widgets, char **args, char *prefix);
void			irc_notice(t_widgets *widgets, char **args, char *prefix);
void			irc_part(t_widgets *widgets, char **args, char *prefix);
void			irc_topic(t_widgets *widgets, char **args, char *prefix);

/* official_join.c */
t_tabs			*get_tab_by_channel(t_widgets *widgets, char *channel);
void			irc_join(t_widgets *widgets, char **args, char *prefix);

#endif
