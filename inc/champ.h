/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 00:19:35 by hestela           #+#    #+#             */
/*   Updated: 2014/04/24 07:16:25 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMP_H
# define CHAMP_H

# include <SDL/SDL.h>
# include "SDL_ttf.h"
# include "SDL_image.h"


typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

char		*g_content_path;
SDL_Surface	*g_screen;
int			g_quit;

# define HEIGHT 400
# define WIDTH 600

SDL_Surface		*ft_new_surface(SDL_Surface *screen, int width, int height, int x, int y, int r, int g, int b);
SDL_Surface		*ft_new_image(SDL_Surface *screen, int x, int y, char *img_file);
SDL_Surface		*ft_new_text(SDL_Surface *screen, char *text, char *ttf_file, int size, int x, int y, int r, int g, int b);
SDL_Surface		*ft_init_screen(char *title, int width, int height, int r, int g, int b);

void			ft_install(char *path, int port, char *password);
char			**ft_export(char **av, char **env);
char			*ft_check_exist(char *cmd, char **path);

#endif /* !CHAMP_H */
