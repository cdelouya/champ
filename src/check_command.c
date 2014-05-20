/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 00:00:54 by hestela           #+#    #+#             */
/*   Updated: 2014/04/24 06:55:02 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "champ.h"

static char		*ft_split_path(char *path, int *i)
{
	int			j;
	char		*str;

	j = 0;
	if (path[*i] == '\0')
		return (NULL);
	(*i)++;
	while (path[*i - 1] != '/' && path[*i])
		(*i)++;
	str = (char*)malloc(sizeof(*str) * (*i) + 1);
	str[*i] = '\0';
	while (j < *i)
	{
		str[j] = path[j];
		j++;
	}
	return (str);
}

static int		ft_check_dir(char *path, char *file)
{
	t_stat		file_stat;

	stat(path, &file_stat);
	if (ft_strlen(path) == ft_strlen(file))
	{
		if (S_ISDIR(file_stat.st_mode) || !(file_stat.st_mode & S_IXUSR)
			|| access(file, F_OK))
		{
			if (access(file, F_OK))
				return (2);
			ft_printf_fd(2, "not found"); 
			return (0);
		}
	}
	else if (S_ISDIR(file_stat.st_mode))
	{
		if (!(file_stat.st_mode & S_IXUSR))
		{
			ft_printf_fd(2, " permission denied:");
			return (0);
		}
	}
	return (1);
}

static int		ft_check_complete_path(char *file)
{
	t_stat		file_stat;
	char		*path;
	int			i;
	int			ret;

	i = 0;
	stat(file, &file_stat);
	path = ft_split_path(file, &i);
	while (path)
	{
		ret = ft_check_dir(path, file);
		if (ret == 0 || ret == 2)
			free(path);
		if (ret == 0)
			return (0);
		if (ret == 2)
			return (2);
		free(path);
		path = ft_split_path(file, &i);
	}
	return (1);
}

static int		ft_check_in_path(char *cmd, char **away, char **path)
{
	int			i;
	char		*way;

	i = 0;
	while (path[i])
	{
		way = ft_strjoin(path[i], cmd);
		if (access(way, F_OK) == 0)
		{
			if (ft_check_complete_path(way))
			{
				*away = way;
				return (1);
			}
			else
				return (0);
		}
		free(way);
		way = NULL;
		i++;
	}
	return (1);
}

char			*ft_check_exist(char *cmd, char **path)
{
	char		*way;
	int			ret;

	way = NULL;
	if (!ft_check_in_path(cmd, &way, path))
		return (NULL);
	if (way)
		return (way);
	way = ft_strdup(cmd + 1);
	ret = ft_check_complete_path(way);
	if (ret == 1)
		return (way);
	else if (ret == 0)
	{
		free(way);
		return (NULL);
	}
	ft_printf_fd(2, "command not found:");
	free(way);
	return (NULL);
}
