##
## EPITECH PROJECT, 2018
## Fairefichier
## File description:
## This is a fairefichier, made by HeyShafty
##

NAME	=	arcade
ROOT_PATH	=	./
SRC_NAME	=	src
TESTS_NAME	=	tests
INCL_NAME	=	include
SRC_PATH	=	$(ROOT_PATH)$(SRC_NAME)
INCL_PATH	=	$(ROOT_PATH)$(INCL_NAME)
TESTS_PATH	=	$(ROOT_PATH)$(TESTS_NAME)
COLOR_THEME	=	$(BLUE_C)
DEBUG_THEME	=	$(CYAN_C)
TESTS_THEME	=	$(RED_C)

SRC_DEFAULT	=	\
	src/Exceptions/ArcadeException.cpp	\
	src/Exceptions/BadFileException.cpp \
	src/Exceptions/BadInstanciationException.cpp \
	src/Exceptions/InvalidLibraryException.cpp	\
	src/Logger.cpp

SRC_GAMES	=	$(SRC_DEFAULT) \
	src/games/AGameModule.cpp

SRC_GRAPHICALS	=	$(SRC_DEFAULT) \
	src/libs/ADisplayModule.cpp

SRC_CORE	=	$(SRC_DEFAULT) \
	src/DLLoader.cpp \
	src/Core.cpp \
	src/main.cpp

SRC_LIBCACA	=	$(SRC_GRAPHICALS) \
	src/libs/Libcaca.cpp

SRC_SDL	=	$(SRC_GRAPHICALS) \
	src/libs/SDL.cpp

SRC_SFML	=	$(SRC_GRAPHICALS) \
	src/libs/SFML.cpp

SRC_CENTIPEDE	=	$(SRC_GAMES) \
	src/games/Centipede/Centipede.cpp

SRC_NIBBLER	=	$(SRC_GAMES) \
	src/games/Nibbler/Nibbler.cpp

SRC_PACMAN	=	$(SRC_GAMES) \
	src/games/Pacman/Pacman.cpp

SRC_QIX	=	$(SRC_GAMES) \
	src/games/Qix/Qix.cpp

SRC_SOLARFOX	=	$(SRC_GAMES) \
	src/games/Solarfox/Solarfox.cpp

OBJ_CENTIPEDE	=	$(SRC_CENTIPEDE:.cpp=.o)
OBJ_NIBBLER	=	$(SRC_NIBBLER:.cpp=.o)
OBJ_PACMAN	=	$(SRC_PACMAN:.cpp=.o)
OBJ_QIX	=	$(SRC_QIX:.cpp=.o)
OBJ_SOLARFOX	=	$(SRC_SOLARFOX:.cpp=.o)

OBJ_CORE	=	$(SRC_CORE:.cpp=.o)
OBJ_LIBCACA	=	$(SRC_LIBCACA:.cpp=.o)
OBJ_SDL		=	$(SRC_SDL:.cpp=.o)
OBJ_SFML	=	$(SRC_SFML:.cpp=.o)
OBJ_DEFAULT	=	$(SRC_DEFAULT:.cpp=.o)

CXX	= 	g++
CXXFLAGS	=	-Wall -Wextra -Werror -I $(INCL_PATH) -std=c++17 -O2
LDLIBS		=	-ldl -lstdc++fs
DEBUG_FLAGS	=	-g3 -gdwarf-4

all: message core graphicals games

message:
	@$(LINE_RETURN)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"Arcade"$(DEFAULT)

core: exceptions $(OBJ_CORE)
	@$(CXX) -o $(NAME) $(OBJ_CORE) $(LDLIBS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

games: centipede nibbler pacman qix solarfox

centipede: NAME = games/lib_arcade_centipede.so
centipede: OBJ = $(OBJ_CENTIPEDE)
centipede: CXXFLAGS += -fPIC
centipede: $(OBJ_CENTIPEDE) build_centipede

nibbler: NAME = games/lib_arcade_nibbler.so
nibbler: OBJ = $(OBJ_NIBBLER)
nibbler: CXXFLAGS += -fPIC
nibbler: $(OBJ_NIBBLER) build_nibbler

pacman: NAME = games/lib_arcade_pacman.so
pacman: OBJ = $(OBJ_PACMAN)
pacman: CXXFLAGS += -fPIC
pacman: $(OBJ_PACMAN) build_pacman

qix: NAME = games/lib_arcade_qix.so
qix: OBJ = $(OBJ_QIX)
qix: CXXFLAGS += -fPIC
qix: $(OBJ_QIX) build_qix

solarfox: NAME = games/lib_arcade_solarfox.so
solarfox: OBJ = $(OBJ_SOLARFOX)
solarfox: CXXFLAGS += -fPIC
solarfox: $(OBJ_SOLARFOX) build_solarfox

graphicals: libcaca sdl sfml

libcaca: NAME = lib/lib_arcade_libcaca.so
libcaca: OBJ = $(OBJ_LIBCACA)
libcaca: CXXFLAGS += -fPIC
libcaca: $(OBJ_LIBCACA) build_libcaca

sdl: NAME = lib/lib_arcade_sdl.so
sdl: OBJ = $(OBJ_SDL)
sdl: CXXFLAGS += -fPIC
sdl: LDLIBS = -lSDL2 -lSDL2_ttf
sdl: $(OBJ_SDL) build_sdl

sfml: NAME = lib/lib_arcade_sfml.so
sfml: OBJ = $(OBJ_SFML)
sfml: CXXFLAGS += -fPIC
sfml: LDLIBS = -lsfml-graphics -lsfml-system -lsfml-window
sfml: $(OBJ_SFML) build_sfml

build_libcaca build_sdl build_sfml build_centipede build_nibbler build_pacman build_qix build_solarfox: exceptions $(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(LDLIBS) -shared && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

exceptions: CXXFLAGS += -fPIC
exceptions: $(OBJ_DEFAULT)

clean:
	@make fclean -C $(TESTS_PATH) -s SRC="$(SRC)" COLOR_THEME="$(RED_C)"
	@$(RM) $(OBJ_CORE) && \
		$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.* && \
		$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"Valgrind files"$(DEFAULT)
	@$(RM) $(OBJ_DEFAULT) $(OBJ_LIBCACA) $(OBJ_SDL) $(OBJ_SFML) $(OBJ_CENTIPEDE) $(OBJ_NIBBLER) $(OBJ_PACMAN) $(OBJ_QIX) $(OBJ_SOLARFOX)

fclean:	clean
	@$(RM) results.html && \
		$(ECHO) $(RED_C)$(DIM_T)"[fclean] "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"results.html"$(DEFAULT)
	@$(RM) $(NAME) && \
		$(ECHO) $(RED_C)$(DIM_T)"[fclean] "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"Binary $(NAME)"$(DEFAULT)
	@$(RM) games/*.so
	@$(RM) lib/*.so

re: fclean all

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: COLOR_THEME = $(DEBUG_THEME)
debug: all
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"⚠ DEBUG MODE ACTIVATED ⚠\n"$(DEFAULT)

doc:
	@doxygen doc/Doxyfile

doc_pdf:
	@make -C doc/latex
	@cp doc/latex/refman.pdf doc/ArcadeDoc.pdf

doc_clean:
	@$(RM) -r doc/html
	@$(RM) -r doc/latex
	@$(RM) -r doc/man

doc_re: doc_clean doc doc_pdf

%.o: %.cpp
	@$(CXX) -c $(CXXFLAGS) -o $@ $< && \
		$(ECHO) $(DIM_T) "$(CXX) $(CXXFLAGS) -c "$<$(COLOR_THEME)" -o "$@ $(DEFAULT) || \
		$(ECHO) "\n"$(MAGEN_C) $(UNDLN_T)$(BOLD_T)"$(CXX) $(CXXFLAGS) -c "$<" -o "$@$(DEFAULT)"\n"

.PHONY: all message core games graphicals \
		centipede nibbler pacman qix solarfox \
		libcaca sdl sfml \
		build_libcaca build_sdl build_sfml build_centipede build_nibbler build_pacman build_qix build_solarfox \
		exceptions \
		clean fclean re debug \
		doc doc_pdf doc_clean doc_re

ECHO	=	/bin/echo -e
DEFAULT	=	"\e[0m"
BOLD_T	=	"\e[1m"
DIM_T	=	"\e[2m"
UNDLN_T	=	"\e[4m"
BLACK_C	=	"\e[30m"
RED_C	=	"\e[31m"
GREEN_C	=	"\e[32m"
YELLO_C	=	"\e[33m"
BLUE_C	=	"\e[34m"
MAGEN_C	=	"\e[35m"
CYAN_C	=	"\e[36m"
WHITE_C	=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LIGHT_GREY	=	"\e[37m"
DARK_GREY	=	"\e[90m"
LIGHT_RED	=	"\e[91m"
LIGHT_GREEN	=	"\e[92m"
LIGHT_YELLO	=	"\e[93m"
LIGHT_BLUE	=	"\e[94m"
LIGHT_MAGEN	=	"\e[95m"
LIGHT_CYAN	=	"\e[96m"
LINE_RETURN	=	$(ECHO) ""
