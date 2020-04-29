/*
** main.c for irc in /home/audrade/work/graphic
** 
** Made by cailleux carole
** Login   <caille_c@epitech.net>
** 
** Started on  Wed Apr 20 15:18:28 2011 cailleux carole
** Last update Wed Apr 20 15:18:28 2011 cailleux carole
*/

#include <stdlib.h>
#include "client.h"

void			launchGraphic(int argc, char **argv)
{
  GtkBuilder		*p_builder;
  GError		*p_err;
  GtkWidget		*p_win;
  t_widgets		*widgets;

  p_builder = NULL;
  p_err = NULL;
  gtk_init(&argc, &argv);
  p_builder = gtk_builder_new();
  if (p_builder != NULL)
    {
      gtk_builder_add_from_file(p_builder, "interface.glade", & p_err);
      if (p_err == NULL)
        {
          p_win = (GtkWidget *)gtk_builder_get_object(p_builder, "window1");
	  widgets = get_widgets(p_builder);
	  g_timeout_add(20, get_packet, widgets);
	  set_signals(widgets, p_win);
	  widgets->window = p_win;
          gtk_widget_show_all(p_win);
          gtk_main();
        }
    }
}

int			main(int argc, char **argv)
{
  launchGraphic(argc, argv);
  return (0);
}
