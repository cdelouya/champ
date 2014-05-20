/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 23:45:57 by hestela           #+#    #+#             */
/*   Updated: 2014/04/27 15:17:51 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <SDL/SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "champ.h"

static void				ft_get_location(char *executable);
static void				ft_pre_click(int x, int y);
static void				ft_edit_path();
static void				ft_edit_port();
static void				ft_edit_password();
static void				ft_click(int x, int y);
static int				ft_wait_quit(void);

static int				g_prev_click;
static char				*g_path_install;
static char				*g_port;
static char				*g_password;
static SDL_Surface		*g_validate;
static SDL_Surface		*g_field_1;
static SDL_Surface		*g_field_2;
static SDL_Surface		*g_field_3;
static SDL_Surface		*g_field_text_1;
static SDL_Surface		*g_field_text_2;
static SDL_Surface		*g_field_text_3;
static char				*g_hide_pass;

static void		ft_get_location(char *executable)
{
	char		*path;
	char		*binary;
	int			len;

	binary = executable;
	len = ft_strlen(binary);
	while (binary[len - 1] != '/')
		len--;
	path = (char*)malloc(sizeof(*path) * len + 5);
	ft_bzero(path, len + 4);
	ft_strncpy(path, binary, len);
	g_content_path = path;
}

static void			ft_edit_path()
{
	int				bool;
	SDL_Event		event;
	size_t			pos;
	int				unicode;
	char			dst[100];

	ft_bzero((char*)dst, 100);
	if (g_path_install)
		ft_strcpy(dst, g_path_install);
	pos = ft_strlen(dst);
	bool = 1;
	SDL_EnableUNICODE(1);
	while (bool)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			unicode = event.key.keysym.unicode;
			if (unicode >= 32 && unicode <= 127)
			{
				if (unicode == 127 && pos > 0)
				{
					dst[pos - 1] = '\0';
					pos--;
				}
				else if (unicode >= 32 && unicode < 127 && pos < 37)
				{
					dst[pos] = (char)unicode;
					pos++;
				}
				SDL_FreeSurface(g_field_1);
				g_field_1 = ft_new_image(g_screen, 245, 176, "field_active.png");
				g_field_text_1 =  ft_new_text(g_screen , dst, "semibold.ttf", 16, 253, 181, 150, 150, 150);
				SDL_Flip(g_screen);
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.x < 247 || event.button.x > 537 || event.button.y < 178 || event.button.y > 200)
			{
				SDL_FreeSurface(g_field_1);
				g_field_1 = ft_new_image(g_screen, 245, 176, "field.png");
				if ((int)ft_strlen(dst) > 0)
				{
					if (g_path_install)
						free(g_path_install);
					g_path_install = ft_strdup(dst);
				}
				else
				{
					if (g_path_install)
					{
						free(g_path_install);
						g_path_install = NULL;
					}
				}
				SDL_Flip(g_screen);
				ft_pre_click(event.button.x, event.button.y);
				bool = 0;
			}
		}
		if (event.type == SDL_QUIT)
		{
			bool = 0;
			g_quit = 1;
		}
	}
	SDL_EnableUNICODE(0);
}

static void			ft_edit_port()
{
	int				bool;
	SDL_Event		event;
	size_t			pos;
	int				unicode;
	char			dst[100];

	ft_bzero((char*)dst, 100);
	if (g_port)
		ft_strcpy(dst, g_port);
	pos = ft_strlen(dst);
	bool = 1;
	SDL_EnableUNICODE(1);
	while (bool)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			unicode = event.key.keysym.unicode;
			if ((unicode >= 48 && unicode <= 57) || unicode == 127)
			{
				if (unicode == 127 && pos > 0)
				{
					dst[pos - 1] = '\0';
					pos--;
				}
				else if (unicode >= 48 && unicode <= 57 && pos < 4)
				{
					dst[pos] = (char)unicode;
					pos++;
				}
				SDL_FreeSurface(g_field_2);
				g_field_2 = ft_new_image(g_screen, 245, 216, "field_active.png");
				g_field_text_2 =  ft_new_text(g_screen , dst, "semibold.ttf", 16, 253, 221, 150, 150, 150);
				SDL_Flip(g_screen);
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.x < 247 || event.button.x > 537 || event.button.y < 218 || event.button.y > 200)
			{
				SDL_FreeSurface(g_field_2);
				g_field_2 = ft_new_image(g_screen, 245, 216, "field.png");
				if ((int)ft_strlen(dst) > 0)
				{
					if (g_port)
						free(g_port);
					g_port = ft_strdup(dst);
				}
				else
				{
					if (g_port)
					{
						free(g_port);
						g_port = NULL;
					}
				}
				SDL_Flip(g_screen);
				ft_pre_click(event.button.x, event.button.y);
				bool = 0;
			}
		}
		if (event.type == SDL_QUIT)
		{
			bool = 0;
			g_quit = 1;
		}
	}
	SDL_EnableUNICODE(0);
}

static void			ft_edit_password()
{
	int				bool;
	SDL_Event		event;
	size_t			pos;
	int				unicode;
	char			dst[100];
	char			dst2[100];
	int				i;

	i = 0;
	ft_bzero((char*)dst, 100);
	ft_bzero((char*)dst2, 100);
	if (g_port)
		ft_strcpy(dst, g_password);
	pos = ft_strlen(dst);
	bool = 1;
	SDL_EnableUNICODE(1);
	while (bool)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			unicode = event.key.keysym.unicode;
			if (unicode >= 32 && unicode <= 127)
			{
				if (unicode == 127 && pos > 0)
				{
					dst[pos - 1] = '\0';
					dst2[pos - 1] = '\0';
					pos--;
				}
				else if (unicode >= 32 && unicode < 127 && pos < 37)
				{
					dst[pos] = (char)unicode;
					dst2[pos] = '*';
					pos++;
				}
				SDL_FreeSurface(g_field_3);
				g_field_3 = ft_new_image(g_screen, 245, 256, "field_active.png");
				g_field_text_3 = ft_new_text(g_screen , dst2, "semibold.ttf", 16, 253, 264, 150, 150, 150);
				SDL_Flip(g_screen);
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.x < 247 || event.button.x > 537 || event.button.y < 258 || event.button.y > 200)
			{
				SDL_FreeSurface(g_field_3);
				g_field_3 = ft_new_image(g_screen, 245, 256, "field.png");
				if ((int)ft_strlen(dst) > 0)
				{
					if (g_password)
					{
						free(g_password);
						free(g_hide_pass);
					}
					g_password = ft_strdup(dst);
					g_hide_pass = ft_strdup(dst2);
					while (g_hide_pass[i])
					{
						g_hide_pass[i] = '*';
						i++;
					}
				}
				else
				{
					if (g_password)
					{
						free(g_password);
						g_password = NULL;
					}
				}
				SDL_Flip(g_screen);
				ft_pre_click(event.button.x, event.button.y);
				bool = 0;
			}
		}
		if (event.type == SDL_QUIT)
		{
			bool = 0;
			g_quit = 1;
		}
	}
	SDL_EnableUNICODE(0);
}

static void			ft_pre_click(int x, int y)
{
	if (x > 425 && x < 515 && y > 325 && y < 355)
	{
		SDL_FreeSurface(g_validate);
		g_validate = ft_new_image(g_screen, WIDTH - 175, HEIGHT - 65, "validate_active.png");
		if (g_path_install)
			g_field_text_1 =  ft_new_text(g_screen , g_path_install, "semibold.ttf", 16, 253, 181, 150, 150, 150);
		if (g_port)
			g_field_text_2 =  ft_new_text(g_screen , g_port, "semibold.ttf", 16, 253, 221, 150, 150, 150);
		if (g_password)
			g_field_text_3 = ft_new_text(g_screen , g_hide_pass, "semibold.ttf", 16, 253, 264, 150, 150, 150);
		SDL_Flip(g_screen);
		g_prev_click = 4;
	}

	else if (x > 247 && x < 537 && y > 178 && y < 200)
	{
		SDL_FreeSurface(g_field_1);
		g_field_1 = ft_new_image(g_screen, 245, 176, "field_active.png");
		SDL_FreeSurface(g_field_2);
		g_field_2 = ft_new_image(g_screen, 245, 216, "field.png");
		SDL_FreeSurface(g_field_3);
		g_field_3 = ft_new_image(g_screen, 245, 256, "field.png");
		if (g_path_install)
			g_field_text_1 = ft_new_text(g_screen , g_path_install, "semibold.ttf", 16, 253, 181, 150, 150, 150);
		if (g_port)
			g_field_text_2 =  ft_new_text(g_screen , g_port, "semibold.ttf", 16, 253, 221, 150, 150, 150);
		if (g_password)
			g_field_text_3 = ft_new_text(g_screen , g_hide_pass, "semibold.ttf", 16, 253, 264, 150, 150, 150);
		SDL_Flip(g_screen);
		ft_edit_path();
	}
	else if (x > 247 && x < 537 && y > 218 && y < 240)
	{
		SDL_FreeSurface(g_field_2);
		g_field_2 = ft_new_image(g_screen, 245, 216, "field_active.png");
		SDL_FreeSurface(g_field_1);
		g_field_1 = ft_new_image(g_screen, 245, 176, "field.png");
		SDL_FreeSurface(g_field_3);
		g_field_3 = ft_new_image(g_screen, 245, 256, "field.png");
		if (g_path_install)
			g_field_text_1 =  ft_new_text(g_screen , g_path_install, "semibold.ttf", 16, 253, 181, 150, 150, 150);
		if (g_port)
			g_field_text_2 =  ft_new_text(g_screen , g_port, "semibold.ttf", 16, 253, 221, 150, 150, 150);
		if (g_password)
			g_field_text_3 = ft_new_text(g_screen , g_hide_pass, "semibold.ttf", 16, 253, 264, 150, 150, 150);
		SDL_Flip(g_screen);
		ft_edit_port();
	}
	else if (x > 247 && x < 537 && y > 258 && y < 290)
	{
		SDL_FreeSurface(g_field_3);
		g_field_3 = ft_new_image(g_screen, 245, 256, "field_active.png");
		SDL_FreeSurface(g_field_1);
		g_field_1 = ft_new_image(g_screen, 245, 176, "field.png");
		SDL_FreeSurface(g_field_2);
		g_field_2 = ft_new_image(g_screen, 245, 216, "field.png");
		if (g_path_install)
			g_field_text_1 =  ft_new_text(g_screen , g_path_install, "semibold.ttf", 16, 253, 181, 150, 150, 150);
		if (g_port)
			g_field_text_2 =  ft_new_text(g_screen , g_port, "semibold.ttf", 16, 253, 221, 150, 150, 150);
		if (g_password)
			g_field_text_3 = ft_new_text(g_screen , g_hide_pass, "semibold.ttf", 16, 253, 264, 150, 150, 150);
		SDL_Flip(g_screen);
		ft_edit_password();
	}
	else
	{
		SDL_FreeSurface(g_field_1);
		g_field_1 = ft_new_image(g_screen, 245, 176, "field.png");
		SDL_Flip(g_screen);
		SDL_FreeSurface(g_field_2);
		g_field_2 = ft_new_image(g_screen, 245, 216, "field.png");
		SDL_Flip(g_screen);
		SDL_FreeSurface(g_field_3);
		g_field_3 = ft_new_image(g_screen, 245, 256, "field.png");
		if (g_path_install)
			g_field_text_1 =  ft_new_text(g_screen , g_path_install, "semibold.ttf", 16, 253, 181, 150, 150, 150);
		if (g_port)
			g_field_text_2 =  ft_new_text(g_screen , g_port, "semibold.ttf", 16, 253, 221, 150, 150, 150);
		if (g_password)
			g_field_text_3 = ft_new_text(g_screen , g_hide_pass, "semibold.ttf", 16, 253, 264, 150, 150, 150);
		SDL_Flip(g_screen);
		g_prev_click = 0;
	}
}

static void			ft_click(int x, int y)
{
	if (g_prev_click == 4)
	{
		SDL_FreeSurface(g_validate);
		g_validate = ft_new_image(g_screen, WIDTH - 175, HEIGHT - 65, "validate.png");
		if (g_path_install)
			g_field_text_1 =  ft_new_text(g_screen , g_path_install, "semibold.ttf", 16, 253, 181, 150, 150, 150);
		if (g_port)
			g_field_text_2 =  ft_new_text(g_screen , g_port, "semibold.ttf", 16, 253, 221, 150, 150, 150);
		if (g_password)
			g_field_text_3 = ft_new_text(g_screen , g_hide_pass, "semibold.ttf", 16, 253, 264, 150, 150, 150);
		SDL_Flip(g_screen);
		g_prev_click = 0;
		if (g_path_install && g_password && g_port)
		{
			ft_install(g_path_install, ft_atoi(g_port), g_password); 
		}
	}
}

static int			ft_wait_quit(void)
{
	SDL_Event		event;
	int				bool;

	bool = 1;
	while (bool)
	{
		if (g_quit == 1)
			bool = 0;
		else
		{
			SDL_WaitEvent(&event);
			if (event.type == SDL_QUIT)
				bool = 0;
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
					ft_click(event.button.x, event.button.y);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
					ft_pre_click(event.button.x, event.button.y);
			}
		}
	}
	return (event.type);
}

int					main(int ac, char **av)
{
	int				event_type;
	ac = (int)ac;

	//INIT
	ft_get_location(av[0]);
	SDL_Surface *screen = ft_init_screen("CHAMP", WIDTH, HEIGHT, 232, 232, 232);
	g_screen = screen;
	g_prev_click = 0;;
	g_path_install = NULL;;
	g_port = NULL;
	g_password = NULL;
	g_validate = NULL;
	g_field_1 = NULL;
	g_field_2 = NULL;
	g_field_3 = NULL;
	g_field_text_1 = NULL;
	g_field_text_2 = NULL;
	g_field_text_3 = NULL;
	g_hide_pass = NULL;

	//Common
	SDL_Surface *logo = ft_new_image(screen, 30, 30, "CHAMP.icns");
	SDL_Surface *title = ft_new_text(screen , "CHAMP", "semibold.ttf", 60, 170, 40, 150, 150, 150);
	SDL_Surface *subtitle = ft_new_text(screen , "Install and manage local servers", "semibold.ttf", 30, 170, 100, 150, 150, 150);
	SDL_Surface *logo_third = ft_new_image(screen, 34, HEIGHT - 80, "third_logo.png");

	//Field 1
	char		*str;
	str = ft_str_multi_join(3, "Location:/Users/", getenv("USER"), "/");
	SDL_Surface *location_txt = ft_new_text(screen , str, "semibold.ttf", 16, 60, 180, 50, 50, 50);
	free(str);
	g_field_1 = ft_new_image(screen, 245, 176, "field.png");

	//Field 2
	SDL_Surface *port_txt = ft_new_text(screen , "port", "semibold.ttf", 16, 60, 220, 50, 50, 50);
	g_field_2 = ft_new_image(screen, 245, 216, "field.png");

	//Field 3
	SDL_Surface *pwd_txt = ft_new_text(screen , "mysql root password", "semibold.ttf", 16, 60, 260, 50, 50, 50);
	g_field_3 = ft_new_image(screen, 245, 256, "field.png");

	//Validate
	g_validate = ft_new_image(screen, WIDTH - 175, HEIGHT - 65, "validate.png");
	
	SDL_Flip(screen);




	
	event_type = ft_wait_quit();
	
	SDL_FreeSurface(logo);
	SDL_FreeSurface(title);
	SDL_FreeSurface(subtitle);
	SDL_FreeSurface(logo_third);
	SDL_FreeSurface(g_field_3);
	SDL_FreeSurface(g_field_2);
	SDL_FreeSurface(g_field_1);
	SDL_FreeSurface(g_validate);

	TTF_Quit();
	SDL_Quit(); // Arrêt de la SDL
	return (0);
}
