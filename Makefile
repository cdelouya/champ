#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hestela <hestela@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/21 23:38:46 by hestela           #+#    #+#              #
#    Updated: 2014/04/26 14:59:03 by hestela          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

###################### TO CUSTOMIZE #########################
NAME	=	CHAMP_Installer
ICON	=	./ressources/CHAMP.icns
SOURCES	= 	src/main.c \
			src/tools.c \
			src/install.c \
			src/export.c
HEADERS	=	-I./inc
RESSOURCES=	$(ICON) \
			./ressources/semibold.ttf \
			./ressources/third_logo.png \
			./ressources/field.png \
			./ressources/validate.png \
			./ressources/load_bar.png \
			./ressources/validate_active.png \
			./ressources/field_active.png \
			./ressources/httpd-2.4.9.tar.bz2 \
			./ressources/apr-1.5.1.tar.gz \
			./ressources/apr-util-1.5.3.tar.gz \
			./ressources/libmcrypt-2.5.8.tar.gz \
			./ressources/mod_ssl-2.8.30-1.3.39.tar.gz \
			./ressources/openssl-1.0.1g.tar.gz \
			./ressources/php-5.5.11.tar.bz2 \
			./ressources/phpMyAdmin-4.1.13-all-languages.zip \
			./ressources/pcre-8.31.tar.bz2 \
			./ressources/complete.png \
			./ressources/CHAMP.app \
			./ressources/champ
LIBRARY = 	-L./lib/ -lft
LIBFT	=	lib/libft.a
FRAMEWORKS=
#############################################################

CC		=	clang -isysroot sdk/MacOSX10.9.sdk
WFLAGS	=	-Wall -Werror -Wextra
APP		=	$(NAME).app
BINARY	= 	build/$(APP)/Contents/Applications/$(NAME)
OBJECTS =	$(subst src,obj,$(subst .c,.o,$(SOURCES)))
APPSRC	=	$(subst ressources,build/$(APP)/Contents/Ressources,$(RESSOURCES))
SDLFMK	=	Frameworks/SDL.framework \
			Frameworks/SDL_image.framework \
			Frameworks/SDL_ttf.framework
SDLSRC	= 	$(subst Frameworks,build/$(APP)/Contents/Frameworks,$(SDLFMK))
SDL		=	-F./Frameworks \
			-framework SDL \
			-framework Cocoa \
			-framework SDL_image \
			-framework SDL_ttf
INSTALLER=	build/$(APP)/Contents/MacOS/$(NAME)
FOLDERS = 	build/$(APP) \
			build/$(APP)/Contents \
			build/$(APP)/Contents/MacOS \
			build/$(APP)/Contents/Ressources \
			build/$(APP)/Contents/Frameworks \
			build/$(APP)/Contents/Applications

#############################################################

.SILENT:

all: $(FOLDERS) $(APPSRC) $(SDLSRC) $(INSTALLER) $(BINARY)

$(FOLDERS):
	mkdir -p $(FOLDERS)
	printf "making directories\n"

build/$(APP)/Contents/Ressources/%: ressources/%
	cp -r $^ $@
	printf "copy $^ to $@\n"

build/$(APP)/Contents/Frameworks/%: Frameworks/%
	cp -r $^ $@
	printf "copy $^ to $@\n"

$(INSTALLER):
	cp ./ressources/Framework_installer build/$(APP)/Contents/MacOS/$(NAME)
	printf "build launcher"

$(BINARY): $(LIBFT) $(OBJECTS)
	$(CC) $(HEADERS)  -F$(PWD)/Frameworks -c src/SDLMain.m -o obj/SDLMain.o # BUILDING SDL MAIN
	printf "\033[1;32m[✔]\033[1;36m SDLMain\n"
	printf "\033[1;33m----------------------------------\n"
	$(CC) $(HEADERS) $(FRAMEWORKS) $(SDL) $(LIBRARY) $(OBJECTS) obj/SDLMain.o -o $(BINARY) # LINK OBJECTS
	printf "\033[1;32m[✔]\033[1;36m $@\n"
	printf "\033[1;33m----------------------------------\n"

obj/%.o: src/%.c
	$(CC) $(LIBRARY) $(HEADERS) $(SDL) $(FRAMEWORK) -c $^ -o $@ # BUILDING OBJECTS
	printf "\033[1;32m[✔]\033[1;36m $@ \n"

################################################################

$(LIBFT):
	make -C ./srclib/libft
	mv ./srclib/libft/libft.a ./lib/
	cp ./srclib/libft/libft.h ./inc/
	printf "\033[1;33m----------------------------------\n"
	printf "build libft\n"
	printf "\033[1;33m----------------------------------\n"

clean:
	make -C ./srclib/libft clean
	rm -f $(OBJECTS)
	rm -f obj/SDLMain.o
	printf "\033[1;33m----------------------------------\n"
	printf "project cleaned\n"
	printf "\033[1;33m----------------------------------\n"

fclean: clean
	make -C ./srclib/libft clean
	rm -f ./lib/libft.a
	rm -rf build/$(APP)
	printf "\033[1;33m----------------------------------\n"
	printf "binaries erased\n"
	printf "\033[1;33m----------------------------------\n"

re: fclean all
