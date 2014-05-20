/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hestela <hestela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 22:52:25 by hestela           #+#    #+#             */
/*   Updated: 2014/04/27 14:54:25 by hestela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <SDL/SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "champ.h"
#include <time.h>

extern char			**environ;

static SDL_Surface	*g_logo;
static SDL_Surface	*g_title;
static SDL_Surface	*g_subtitle;
static SDL_Surface	*g_logo_third;
static SDL_Surface	*g_load_bar;
static SDL_Surface	*g_text;
static SDL_Surface	*g_block;
static SDL_Surface	*g_bar;

static void		ft_sh(char *command, char **env)
{
	char		**av;
	pid_t		thread;

	av = ft_strsplit(command, '@');
	thread = fork();
	if (thread == 0)
		execve(av[0], av, env);
	else
		wait(&thread);
}

static void		ft_sh_redir(char *command, char *file, char **env)
{
	int			fd;
	pid_t		thread;
	char		*str;
	char		**av;

	av = ft_strsplit(command, '@');
	str = NULL;
	thread = -1;
	fd = open(file, O_CREAT | O_RDWR, 0644);
	while (ft_gnl(fd, &str) > 0)
		;
	thread = fork();
	if (thread == 0)
	{
		dup2(fd, 1);
		execve(av[0], av, env);
	}
	close(fd);
	wait(0);
}

static int		ft_random(int min, int max)
{
	int			rand_nbr;

	srand(time(NULL));
	rand_nbr = rand() % (max - min) + min;
	return (rand_nbr);
}

static void		ft_draw_bar(int	inc)
{
	static int	width = 0;

	if (width != 0)
		SDL_FreeSurface(g_bar);
	width += inc;
	g_bar = ft_new_surface(g_screen, width, 20, 52, 202, 7, 145, 252);
	SDL_Flip(g_screen);
}

static void		ft_draw_page()
{
	SDL_FillRect(g_screen, NULL, SDL_MapRGB(g_screen->format, 232, 232, 232));
	g_logo = ft_new_image(g_screen, 30, 30, "CHAMP.icns");
	g_title = ft_new_text(g_screen , "CHAMP", "semibold.ttf", 60, 170, 40, 150, 150, 150);
	g_subtitle = ft_new_text(g_screen , "Install and manage local servers", "semibold.ttf", 30, 170, 100, 150, 150, 150);
	g_logo_third = ft_new_image(g_screen, 34, HEIGHT - 80, "third_logo.png");
	g_load_bar = ft_new_image(g_screen, 50, 200, "load_bar.png");
	SDL_Flip(g_screen);
}

static void		ft_draw_end()
{
	SDL_FillRect(g_screen, NULL, SDL_MapRGB(g_screen->format, 232, 232, 232));
	g_logo = ft_new_image(g_screen, 30, 30, "CHAMP.icns");
	g_title = ft_new_text(g_screen , "CHAMP", "semibold.ttf", 60, 170, 40, 150, 150, 150);
	g_subtitle = ft_new_text(g_screen , "Install and manage local servers", "semibold.ttf", 30, 170, 100, 150, 150, 150);
	g_logo_third = ft_new_image(g_screen, 34, HEIGHT - 80, "third_logo.png");
	g_load_bar = ft_new_image(g_screen, 225, 145, "complete.png");
	SDL_Flip(g_screen);
}

static void		ft_copy_ressources(char **env, char *current_path, char *install_path)
{
	char		*command;

	command = ft_strjoin("/bin/mkdir@-p@", install_path);
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/mkdir@-p@", install_path, "/tmp/");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/httpd-2.4.9.tar.bz2@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/pcre-8.31.tar.bz2@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/apr-1.5.1.tar.gz@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/apr-util-1.5.3.tar.gz@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/openssl-1.0.1g.tar.gz@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/mod_ssl-2.8.30-1.3.39.tar.gz@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/libmcrypt-2.5.8.tar.gz@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/php-5.5.11.tar.bz2@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(4, "/usr/bin/curl@-o@", install_path, "/tmp/mysql-5.6.17-osx10.7-x86.tar.gz@-L@", "http://dev.mysql.com/get/Downloads/MySQL-5.6/mysql-5.6.17-osx10.7-x86.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/cp@-r@", current_path, "/../Ressources/phpMyAdmin-4.1.13-all-languages.zip@", install_path, "/tmp");
	ft_sh(command, env);
	free(command);
}

static void		ft_decompressing(char **env, char *path)
{
	char		*command;
	char		**av;
	char		*str;

	str = ft_str_multi_join(2, path, "/tmp/");
	chdir(str);
	free(str);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/httpd-2.4.9.tar.bz2");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/apr-1.5.1.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/pcre-8.31.tar.bz2");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/apr-util-1.5.3.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/openssl-1.0.1g.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/mod_ssl-2.8.30-1.3.39.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/libmcrypt-2.5.8.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/php-5.5.11.tar.bz2");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/mysql-5.6.17-osx10.7-x86.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/tar@-xvf@", path, "/tmp/phpMyAdmin-4.1.13-all-languages.zip");
	ft_sh(command, env);
	free(command);
}

static void			ft_cleaning(char **env, char *path)
{
	char			*command;

	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/httpd-2.4.9.tar.bz2");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/pcre-8.31.tar.bz2");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3,  "/bin/rm@-rf@", path, "/tmp/apr-1.5.1.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/apr-util-1.5.3.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/openssl-1.0.1g.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/mod_ssl-2.8.30-1.3.39.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/libmcrypt-2.5.8.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/php-5.5.11.tar.bz2");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/mysql-5.6.17-osx10.7-x86.tar.gz");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/phpMyAdmin-4.1.13-all-languages.zip");
	ft_sh(command, env);
	free(command);
}

static void		ft_clean_tmp(char **env, char *path)
{
	char		*command;

	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/httpd-2.4.9");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/pcre-8.31");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3,  "/bin/rm@-rf@", path, "/tmp/apr-1.5.1");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/apr-util-1.5.3");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/openssl-1.0.1g");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/mod_ssl-2.8.30-1.3.39");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/libmcrypt-2.5.8");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/php-5.5.11");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/mysql-5.6.17-osx10.7-x86");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(3, "/bin/rm@-rf@", path, "/tmp/phpMyAdmin-4.1.13-all-languages");
	ft_sh(command, env);
	free(command);
}

static void			ft_install_openssl(char **env, char *path)
{
	char			*command;
	char			*str;

	str = ft_str_multi_join(2, path, "/tmp/openssl-1.0.1g/");
	chdir(str);
	free(str);
	command = ft_str_multi_join(3, "/bin/mkdir@-p@", path, "/library");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/usr/bin/perl@", path, "/tmp/openssl-1.0.1g/configure@--prefix=", path, "/ssl/@darwin64-x86_64-cc");
	ft_sh(command, env);
	free(command);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make", env);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make@install", env);
	str = ft_str_multi_join(2, path, "/tmp/");
	chdir(str);
	free(str);
}

static void			ft_install_apr(char **env, char *path)
{
	char			*command;
	char			*str;

	str = ft_str_multi_join(2, path, "/tmp/apr-1.5.1");
	chdir(str);
	free(str);
	command = ft_str_multi_join(4, path, "/tmp/apr-1.5.1/configure@--prefix=", path, "/library/apr");
	ft_sh(command, env);
	free(command);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make", env);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make@install", env);
	str = ft_str_multi_join(2, path, "/tmp/");
	chdir(str);
	free(str);
}

static void		ft_install_apr_util(char **env, char *path)
{
	char		*command;
	char		*str;

	str = ft_str_multi_join(2, path, "/tmp/apr-util-1.5.3");
	chdir(str);
	free(str);
	command = ft_str_multi_join(6, path, "/tmp/apr-util-1.5.3/configure@--prefix=", path, "/library/apr-util@--with-apr=", path, "/library/apr/");
	ft_sh(command, env);
	free(command);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make", env);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make@install", env);
	str = ft_str_multi_join(2, path, "/tmp/");
	chdir(str);
	free(str);
}

static void		ft_install_apache(char **env, char *path, int port)
{
	char		*command;
	char		*str;
	char		**av;

	str = ft_str_multi_join(3, "export*SSL_BASE=", path, "/ssl");
	av = ft_strsplit(str, '*');
	free(str);
	env = ft_export(av, env);
	ft_array_str_free(av);
///////
	str = ft_str_multi_join(2, path, "/tmp/pcre-8.31");
	chdir(str);
	free(str);
	command = ft_str_multi_join(4, path, "/tmp/pcre-8.31/configure@--prefix=", path, "/library/pcre");
	ft_sh(command, env);
	free(command);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make", env);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make@install", env);
////////
	str = ft_str_multi_join(2, path, "/tmp/httpd-2.4.9");
	chdir(str);
	free(str);
	command = ft_str_multi_join(15, path, "/tmp/httpd-2.4.9/configure@--prefix=", path, "/apache2/@--with-apr=", path, "/library/apr/@--with-apr-util=", path, "/library/apr-util@--with-port=", ft_itoa(port), "@--with-ssl=", path, "/ssl/@--enable-ssl@--with-pcre=", path, "/library/pcre@--with-sslport=", ft_itoa(port - 1));
	ft_sh(command, env);
	free(command);
////////
	str = ft_str_multi_join(2, path, "/tmp/mod_ssl-2.8.30-1.3.39");
	chdir(str);
	free(str);
	command = ft_str_multi_join(8, path, "/tmp/mod_ssl-2.8.30-1.3.39/configure@--prefix=", path, "/modules/mod_ssl/@--with-apache=", path, "/tmp/httpd-2.4.9/@--with-ssl=", path, "/ssl");
	ft_sh(command, env);
	free(command);
////////
	str = ft_str_multi_join(2, path, "/tmp/httpd-2.4.9");
	chdir(str);
	free(str);
	command = ft_str_multi_join(2, path, "/tmp/httpd-2.4.9/config.status");
	ft_sh(command, env);
	free(command);
	ft_sh("/usr/bin/make", env);
	ft_sh("/usr/bin/make@install", env);	
	str = ft_str_multi_join(2, path, "/tmp/");
	chdir(str);
	free(str);
}

static void			ft_configure(char **env, char *path, int port)
{
	char			*command;
	char			*str;
	int				fd;

	str = ft_strjoin(path, "/apache2/htdocs/.htaccess");
	fd =  open(str, O_CREAT | O_RDWR, 0777);
	ft_putstr_fd("RewriteEngine on\n", fd);
	close(fd);
	free(str);
	
	command = ft_str_multi_join(3, "/usr/bin/sed@s/AllowOverride none/AllowOverride all/g@", path, "/apache2/conf/httpd.conf");
	str = ft_strjoin(path, "/apache2/conf/httpd2");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(3, "/usr/bin/sed@s/AllowOverride None/AllowOverride All/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);
	
	command = ft_str_multi_join(3, "/usr/bin/sed@s/#Include conf\\/extra\\/httpd-ssl.conf/Include conf\\/extra\\/httpd-ssl.conf/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);
	
	command = ft_str_multi_join(3, "/usr/bin/sed@s/#LoadModule ssl_module modules\\/mod_ssl.so/LoadModule ssl_module modules\\/mod_ssl.so/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(3, "/usr/bin/sed@s/#LoadModule socache_shmcb_module modules\\/mod_socache_shmcb.so/LoadModule socache_shmcb_module modules\\/mod_socache_shmcb.so/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);

	////////////////
	
	char	path_sed[1000];
	int		i = 0;
	int		j = 0;

	while (path[i])
	{
		if (path[i] == '/')
		{
			path_sed[j] = '\\';
			j++;
		}
		path_sed[j] = path[i];
		i++;
		j++;
	}
	path_sed[j] = '\0';
	
	command = ft_str_multi_join(5, "/usr/bin/sed@s/<Directory \\/>/<Directory ", path_sed ,">/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);
	
	/////
	
	command = ft_str_multi_join(3, "/usr/bin/sed@s/#Include conf\\/extra\\/httpd-vhosts.conf/Include conf\\/extra\\/httpd-vhosts.conf/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);
	
	command = ft_str_multi_join(3, "/usr/bin/sed@s/#LoadModule socache_dbm_module modules\\/mod_socache_dbm.so/LoadModule socache_dbm_module modules\\/mod_socache_dbm.so/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(3, "/usr/bin/sed@s/#LoadModule socache_memcache_module modules\\/mod_socache_memcache.so/LoadModule socache_memcache_module modules\\/mod_socache_memcache.so/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(3, "/usr/bin/sed@s/#ServerName www.example.com/ServerName www.example.com/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);
	
	command = ft_str_multi_join(3, "/usr/bin/sed@s/DirectoryIndex index.html/& index.php/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(3, "/usr/bin/sed@s/#LoadModule rewrite_module modules\\/mod_rewrite.so/LoadModule rewrite_module modules\\/mod_rewrite.so/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(3, "/usr/bin/sed@s/#LoadModule vhost_alias_module modules\\/mod_vhost_alias.so/LoadModule vhost_alias_module modules\\/mod_vhost_alias.so/g@", path, "/apache2/conf/httpd.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/apache2/conf/httpd.conf");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(3, "/bin/rm@-f@", path, "/apache2/conf/extra/httpd-vhosts.conf");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(3, "/usr/bin/touch@", path, "/apache2/conf/extra/httpd-vhosts.conf");
	ft_sh_redir(command, str, env);
	free(command);
	
	free(str);
	str = ft_strjoin(path, "/apache2/conf/httpd.conf");
	ft_sh_redir("/bin/echo@AddType application/x-httpd-php .php .phtml@", str, env);
	free(str);
	
	//CONFIG_SSL
	command = ft_str_multi_join(4, path, "/ssl/bin/openssl@genrsa@-out@", path, "/apache2/conf/server.key@1024");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(6, path, "/ssl/bin/openssl@req@-new@-x509@-days@365@-key@", path, "/apache2/conf/server.key@-out@", path, "/apache2/conf/server.crt@-subj@/C=FR/ST=France/L=Paris/O=42/OU=CHamp/CN=www.example.com/emailAddress=hestela?student.42.fr");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(4, path, "/ssl/bin/openssl@x509@-in@", path, "/apache2/conf/server.crt@-text@-noout");
	ft_sh(command, env);
	free(command);

	//CHAMP

	command = ft_str_multi_join(4, "/bin/cp@-r@", g_content_path, "/../Ressources/champ@", path);
	ft_sh(command, env);
	free(command);

	str = ft_strjoin(path, "/champ/index2.php");
	command = ft_str_multi_join(5, "/usr/bin/sed@s/__SERVER_PATH__/", path_sed,"/g@", path, "/champ/index.php");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/champ/index.php");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/usr/bin/sed@s/__APACHE_PORT__/", ft_itoa(port), "/g@", path, "/champ/index.php");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/champ/index.php");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/usr/bin/sed@s/__SSL_PORT__/", ft_itoa(port - 1), "/g@", path, "/champ/index.php");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/champ/index.php");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/usr/bin/sed@s/__MYSQL_PORT__/", ft_itoa(port + 1), "/g@", path, "/champ/index.php");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/champ/index.php");
	ft_sh(command, env);
	free(command);
	free(str);
	str = ft_strjoin(path, "/champ/cpanel2.php");
	command = ft_str_multi_join(5, "/usr/bin/sed@s/__SERVER_PATH__/", path_sed,"/g@", path, "/champ/cpanel.php");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/champ/cpanel.php");
	ft_sh(command, env);
	free(command);
	free(str);
	
}

static void		ft_libmcrypt(char **env, char *path)
{
	char		*command;
	char		*str;

	str = ft_str_multi_join(2, path, "/tmp/libmcrypt-2.5.8");
	chdir(str);
	free(str);

	command = ft_str_multi_join(4, path, "/tmp/libmcrypt-2.5.8/configure@--prefix=", path, "/library/libmcrypt@--disable-posix-threads@--enable-dynamic-loading");
	ft_sh(command, env);
	free(command);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make", env);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make@install", env);
	str = ft_str_multi_join(2, path, "/tmp/");
	chdir(str);
	free(str);
}

static void		ft_install_php(char **env, char *path)
{
	char		*command;
	char		*str;

	str = ft_str_multi_join(2, path, "/tmp/php-5.5.11");
	chdir(str);
	free(str);

	command = ft_str_multi_join(8, path, "/tmp/php-5.5.11/configure@--prefix=", path, "/PHP@--with-apxs2=", path, "/apache2/bin/apxs@--with-mysql@--with-mysqli@--with-pdo_mysql@--with-curl@--with-mcrypt=", path, "/library/libmcrypt@--enable-mbstring");
	ft_sh(command, env);
	free(command);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make", env);
	ft_draw_bar(20);
	ft_sh("/usr/bin/make@install", env);
	command = ft_str_multi_join(5, "/bin/cp@", path, "/tmp/php-5.5.11/php.ini-development@", path, "/PHP/lib/php.ini");
	ft_sh(command, env);
	free(command);
	str = ft_strjoin(path, "/PHP/lib/php.ini");
	ft_sh_redir("echo@date.timezone = \"Europe/Madrid\"\n", str, env);
	free(str);
	
	str = ft_str_multi_join(2, path, "/tmp/");
	chdir(str);
	free(str);
}

static void		ft_create_handlers(char **env, char *path, int port, char *password)
{
	char		*command;
	char		*str;

	command = ft_str_multi_join(3, "/bin/mkdir@-p@", path, "/.handlers");
	ft_sh(command, env);
	free(command);

	//START.SH
	command = ft_str_multi_join(7, "/bin/echo@#!/bin/sh\n", path, "/.handlers/start_apache.sh\n", path, "/.handlers/start_mysql.sh\nopen -a /Applications/Safari.app http://localhost:", ft_itoa(port), "/champ");
	str = ft_strjoin(path, "/.handlers/start.sh");
	ft_sh_redir(command, str, env);
	free(str);
	free(command);
	command = ft_str_multi_join(3, "/bin/chmod@+x@", path, "/.handlers/start.sh");
	ft_sh(command, env);
	free(command);

	//STOP.SH
	command = ft_str_multi_join(5, "/bin/echo@#!/bin/sh\n", path, "/.handlers/stop_apache.sh\n", path, "/.handlers/stop_mysql.sh");
	str = ft_strjoin(path, "/.handlers/stop.sh");
	ft_sh_redir(command, str, env);
	free(str);
	free(command);
	command = ft_str_multi_join(3, "/bin/chmod@+x@", path, "/.handlers/stop.sh");
	ft_sh(command, env);
	free(command);

	//RESTART.SH
	command = ft_str_multi_join(5, "/bin/echo@#!/bin/sh\n", path, "/.handlers/stop.sh\n", path, "/.handlers/start.sh");
	str = ft_strjoin(path, "/.handlers/restart.sh");
	ft_sh_redir(command, str, env);
	free(str);
	free(command);
	command = ft_str_multi_join(3, "/bin/chmod@+x@", path, "/.handlers/restart.sh");
	ft_sh(command, env);
	free(command);
	
	//START_APPACHE.SH
	command = ft_str_multi_join(3, "/bin/echo@#!/bin/sh\n", path, "/apache2/bin/apachectl start");
	str = ft_strjoin(path, "/.handlers/start_apache.sh");
	ft_sh_redir(command, str, env);
	free(str);
	free(command);
	command = ft_str_multi_join(3, "/bin/chmod@+x@", path, "/.handlers/start_apache.sh");
	ft_sh(command, env);
	free(command);

	//STOP_APPACHE.SH
	command = ft_str_multi_join(3, "/bin/echo@#!/bin/sh\n", path, "/apache2/bin/apachectl stop");
	str = ft_strjoin(path, "/.handlers/stop_apache.sh");
	ft_sh_redir(command, str, env);
	free(str);
	free(command);
	command = ft_str_multi_join(3, "/bin/chmod@+x@", path, "/.handlers/stop_apache.sh");
	ft_sh(command, env);
	free(command);

	//START_Mysql.sh
	command = ft_str_multi_join(9, "/bin/echo@#!/bin/sh\n", path, "/mysql/bin/mysqld --basedir=", path, "/mysql --port=", ft_itoa(port + 1), " --socket=", path, "/tmp/mysql.sock &");
	str = ft_strjoin(path, "/.handlers/start_mysql.sh");
	ft_sh_redir(command, str, env);
	free(str);
	free(command);
	command = ft_str_multi_join(3, "/bin/chmod@+x@", path, "/.handlers/start_mysql.sh");
	ft_sh(command, env);
	free(command);

	//STOP_Mysql.sh
	command = ft_str_multi_join(7, "/bin/echo@#!/bin/sh\n", path, "/mysql/bin/mysqladmin -uroot -p", password, " -S", path, "/tmp/mysql.sock shutdown");
	str = ft_strjoin(path, "/.handlers/stop_mysql.sh");
	ft_sh_redir(command, str, env);
	free(str);
	free(command);
	command = ft_str_multi_join(3, "/bin/chmod@+x@", path, "/.handlers/stop_mysql.sh");
	ft_sh(command, env);
	free(command);
}

static void		ft_install_mysql(char **env, char *path, int port, char *password)
{
	char		*command;
	char		*str;

	command = ft_str_multi_join(5, "/bin/mv@", path, "/tmp/mysql-5.6.17-osx10.7-x86@", path, "/mysql");
	ft_sh(command, env);
	free(command);
	str = ft_str_multi_join(2, path, "/mysql");
	chdir(str);
	free(str);

	command = ft_str_multi_join(12, path, "/mysql/scripts/mysql_install_db@--user=", getenv("USER"), "@--basedir=", path, "/mysql/@--datadir=", path, "/mysql/data/@--port=", ft_itoa(port + 1), "@--socket=", path, "/tmp/mysql.sock");
	ft_sh(command, env);
	free(command);
	ft_sh("/bin/sleep@5", env);
	ft_draw_bar(20);
	command = ft_str_multi_join(2, path, "/.handlers/start_apache.sh");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(2, path, "/.handlers/start_mysql.sh");
	ft_sh(command, env);
	free(command);
	ft_sh("/bin/sleep@10", env);
	command = ft_str_multi_join(5, path, "/mysql/bin/mysqladmin@-u@root@-S", path, "/tmp/mysql.sock@password@", password);
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(2, path, "/.handlers/stop_mysql.sh");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(2, path, "/.handlers/stop_apache.sh");
	ft_sh(command, env);
	free(command);
	ft_sh("/bin/sleep@5", env);
	
}

static void		ft_install_phpmyadmin(char **env, char *path, int port)
{
	char		*command;
	char		*str;
	char		cookie[1000];
	int			i;
	
	command = ft_str_multi_join(5, "/bin/mv@", path, "/tmp/phpMyAdmin-4.1.13-all-languages@", path, "/PhpMyAdmin");
	ft_sh(command, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", path, "/PhpMyAdmin/config.sample.inc.php@", path, "/PhpMyAdmin/config.inc.php");
	ft_sh(command, env);
	free(command);
	str = ft_str_multi_join(2, path, "/PhpMyAdmin/");
	chdir(str);
	free(str);

	str = ft_strjoin(path, "/PhpMyAdmin/config333");
	
	ft_bzero(cookie, 1000);
	while (i < 5)
	{
		ft_strcat(cookie, ft_itoa(ft_random(10000000, 99999999)));
		i++;
	}
	
	command = ft_str_multi_join(5, "/usr/bin/sed@s/a8b7c6d/", cookie, "/g@", path, "/PhpMyAdmin/config.inc.php");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/PhpMyAdmin/config.inc.php");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(5, "/usr/bin/sed@s/localhost/&:", ft_itoa(port + 1), "/g@", path, "/PhpMyAdmin/config.inc.php");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/PhpMyAdmin/config.inc.php");
	ft_sh(command, env);
	free(command);

	command = ft_str_multi_join(3, "/usr/bin/sed@s/?>/\\$cfg\\['PmaNoRelation_DisableWarning'\\] = true; ?>/g@", path, "/PhpMyAdmin/config.inc.php");
	ft_sh_redir(command, str, env);
	free(command);
	command = ft_str_multi_join(5, "/bin/mv@", str, "@", path, "/PhpMyAdmin/config.inc.php");
	ft_sh(command, env);
	free(command);

	free(str);
	str = ft_strjoin(path, "/apache2/conf/httpd.conf");
	command = ft_str_multi_join(9, "/bin/echo@<IfModule alias_module>\n\tAlias /phpMyAdmin \"", path ,"/phpMyAdmin/\"\n\t<Directory \"", path, "/phpMyAdmin\">\n\t\tOptions Indexes FollowSymLinks MultiViews\n\t\tRequire all granted\n\t\tAllowOverride All\n\t\tOrder allow,deny\n\t\tAllow from all\n\t</Directory>\n\tAlias /champ \"", path ,"/champ/\"\n\t<Directory \"", path, "/champ\">\n\t\tOptions Indexes FollowSymLinks MultiViews\n\t\tRequire all granted\n\t\tAllowOverride All\n\t\tOrder allow,deny\n\t\tAllow from all\n\t</Directory>\n </IfModule>");
	ft_sh_redir(command, str, env);
	

	free(str);

	

	chdir(path);
}

static char		*ft_get_path_install(char *mypath, char **env)
{
	char		path[1000];
	char		*user;
	int			i = 0;
	int			len;

	user = ft_getenv(env, "USER");
	len = ft_strlen(user);
	while (ft_strncmp(g_content_path + i, user, len))
	{
		path[i] = g_content_path[i];
		i++;
	}
	path[i] = '\0';
	return (ft_str_multi_join(5, path, "/", user, "/", mypath));
}

void	ft_install(char *path, int port, char *password)
{
	SDL_Event		event;
	int				mysuperbool;
	char			**env;
	char			**path_exec;

	env = ft_array_str_dup(environ);
	
	path = ft_get_path_install(path, env);
	ft_putendl(path);
	ft_putendl(g_content_path);
	path_exec = ft_strsplit("export*PATH=/bin:/usr/bin:/usr/local/bin", '*');
	env = ft_export(path_exec, env);
	mysuperbool = 1;
	ft_draw_page();

	//COPY
	ft_draw_bar(20);
	g_text = ft_new_text(g_screen , "Copying ressources...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_copy_ressources(env, g_content_path, path);

	ft_draw_bar(20);
	//Decompressing
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Decompressing...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_decompressing(env, path);
	
	ft_draw_bar(20);
	//Cleaning
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Cleaning...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_cleaning(env, path);
	
	ft_draw_bar(20);
	//Install OpenSSL
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Installing OpenSSL...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_install_openssl(env, path);
	
	ft_draw_bar(20);
	//Install APR
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Installing APR...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_install_apr(env, path);

	ft_draw_bar(20);
	//Install APR-UTIL
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Installing APR-Util...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_install_apr_util(env, path);
	
	ft_draw_bar(20);
	//Install APPACHE
	SDL_FreeSurface(g_text);

	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Installing Apache 2...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_install_apache(env, path, port);

	ft_draw_bar(20);
	//Configuring
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Configuring Apache 2 && ssl...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_configure(env, path, port);

	//libmcrypt
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Installing libmcrypt...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_libmcrypt(env, path);

	ft_draw_bar(20);
	//PHP
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Installing Php...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_install_php(env, path);

	ft_draw_bar(20);
	//Create Handlers
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Construct utilities...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_create_handlers(env, path, port, password);

	//Mysql
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Installing Mysql...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_install_mysql(env, path, port, password);

	ft_draw_bar(20);
	//PHPMyAdmin
	SDL_FreeSurface(g_text);
	g_block = ft_new_surface(g_screen, 500, 50, 50, 228, 232, 232, 232);
	g_text = ft_new_text(g_screen , "Installing PhpMyAdmin...", "semibold.ttf", 16, 60, 230, 50, 50, 50);
	SDL_Flip(g_screen);
	ft_install_phpmyadmin(env, path, port);

	ft_clean_tmp(env, path);	

	char	*command;
	
	command = ft_str_multi_join(4, "/bin/cp@-r@", g_content_path, "/../Ressources/CHAMP.app@", path);
	ft_sh(command, env);
	free(command);

	
	
	//END
	ft_draw_bar(20);
	SDL_FreeSurface(g_logo);
	SDL_FreeSurface(g_logo_third);
	SDL_FreeSurface(g_title);
	SDL_FreeSurface(g_subtitle);
	SDL_FreeSurface(g_load_bar);
	SDL_FreeSurface(g_text);
	SDL_FreeSurface(g_block);
	free(path);
	ft_draw_end();
	
	mysuperbool = 1111;
	while (mysuperbool)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			mysuperbool = 0;
			g_quit = 1;
		}
	}
}
