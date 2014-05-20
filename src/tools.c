/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 23:02:58 by hestela           #+#    #+#             */
/*   Updated: 2014/04/23 23:07:52 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <SDL/SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "champ.h"

SDL_Surface			*ft_new_surface(SDL_Surface *screen, int width, int height, int x, int y, int r, int g, int b)
{
	SDL_Surface		*new;
	SDL_Rect		pos;

	new = NULL;
	pos.x = x;
	pos.y = y;
	new = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(new, NULL, SDL_MapRGB(new->format, r, g, b));
	SDL_BlitSurface(new, NULL, screen, &pos);
	return (new);
}

SDL_Surface			*ft_new_image(SDL_Surface *screen, int x, int y, char *img_file)
{
	SDL_Surface		*new;
	SDL_Rect		pos;
	char			*path;

	new = NULL;
	path = ft_str_multi_join(3, g_content_path, "/../Ressources/", img_file);
	pos.x = x;
	pos.y = y;
	new = IMG_Load(path);
	SDL_BlitSurface(new, NULL, screen, &pos);
	free(path);
	return (new);
}

SDL_Surface			*ft_new_text(SDL_Surface *screen, char *text, char *ttf_file, int size, int x, int y, int r, int g, int b)
{
	TTF_Font		*font;
	SDL_Color		color = {r, g, b};
	SDL_Surface		*new;
	SDL_Rect		pos;
	char			*path;

	font = NULL;
	new = NULL;
	pos.x = x;
	pos.y = y;
	path = ft_str_multi_join(3, g_content_path, "/../Ressources/", ttf_file);
	font = TTF_OpenFont(path, size);
	new = TTF_RenderText_Blended(font, text, color);
	SDL_BlitSurface(new, NULL, screen, &pos);
	TTF_CloseFont(font);
	free(path);
	return (new);
}

SDL_Surface			*ft_init_screen(char *title, int width, int height, int r, int g, int b)
{
	SDL_Surface		*new;

	new = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	new = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
	SDL_FillRect(new, NULL, SDL_MapRGB(new->format, r, g, b));
	SDL_WM_SetCaption(title , NULL);
	return (new);
}
