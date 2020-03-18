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

SRC_CORE	= \
	src/DLLoader.cpp \
	src/main.cpp

SRC_NCURSES	=	\
	src/libs/NCurses.cpp

SRC_SDL	=	\
	src/libs/SDL.cpp

SRC_SFML	=	\
	src/libs/SFML.cpp

SRC_EXCEPTIONS	=	\
	src/Exceptions/ArcadeException.cpp	\
	src/Exceptions/BadFileException.cpp	\

OBJ_CORE	:=	$(SRC_CORE:.cpp=.o)
OBJ_NCURSES	:=	$(SRC_NCURSES:.cpp=.o)
OBJ_SDL		:=	$(SRC_SDL:.cpp=.o)
OBJ_SFML	:=	$(SRC_SFML:.cpp=.o)
OBJ_EXCEPTIONS	:=	$(SRC_EXCEPTIONS:.cpp=.o)

CXX	= 	g++
CXXFLAGS	=	-Wall -Wextra -Werror -I $(INCL_PATH) -std=c++17
LDLIBS		=	-ldl
DEBUG_FLAGS	=	-g3 -gdwarf-4

all: message core games graphicals

message:
	@$(LINE_RETURN)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"NANO TEK SPICE"$(DEFAULT)

core: $(OBJ_CORE)
	@$(CXX) -o $(NAME) $(OBJ_CORE) $(LDLIBS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

games:

graphicals: CXXFLAGS += -fPIC
graphicals: ncurses sdl sfml

ncurses: NAME = lib/lib_arcade_ncurses.so
ncurses: OBJ = $(OBJ_NCURSES)
ncurses: OBJ += $(OBJ_EXCEPTIONS)
ncurses: $(OBJ_NCURSES) $(OBJ_EXCEPTIONS) build_ncurses

sdl: NAME = lib/lib_arcade_sdl.so
sdl: OBJ = $(OBJ_SDL)
sdl: OBJ += $(OBJ_EXCEPTIONS)
sdl: $(OBJ_SDL) $(OBJ_EXCEPTIONS) build_sdl

sfml: NAME = lib/lib_arcade_sfml.so
sfml: OBJ = $(OBJ_SFML)
sfml: OBJ += $(OBJ_EXCEPTIONS)
sfml: $(OBJ_SFML) $(OBJ_EXCEPTIONS) build_sfml

build_ncurses build_sdl build_sfml: $(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(LDLIBS) -shared && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

clean:
	@make fclean -C $(TESTS_PATH) -s SRC="$(SRC)" COLOR_THEME="$(RED_C)"
	@$(RM) $(OBJ_CORE) && \
		$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.* && \
		$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)"DELETED: "$(DEFAULT) $(LIGHT_RED)"Valgrind files"$(DEFAULT)
	@$(RM) $(OBJ_NCURSES) $(OBJ_SDL) $(OBJ_SFML) $(OBJ_EXCEPTIONS)

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

# tests_run:
# 	@make -C $(TESTS_PATH) -s \
# 		SRC="$(SRC)" \
# 		COLOR_THEME="$(TESTS_THEME)"
# 	@$(ECHO) $(TESTS_THEME)""
# 	@gcovr --exclude tests/ --sort-percentage --branches
# 	@$(ECHO) $(BOLD_T)""
# 	@gcovr --exclude tests/ --sort-percentage --print-summary
# 	@$(ECHO) $(DEFAULT)
# 	@gcovr --exclude tests/ --sort-percentage --html-details --html-title "Unit tests" --html-medium-threshold 40 --html-high-threshold 75 > results.html

%.o: %.cpp
	@$(CXX) -c $(CXXFLAGS) -o $@ $< && \
		$(ECHO) $(DIM_T) "$(CXX) $(CXXFLAGS) -c "$<$(COLOR_THEME)" -o "$@ $(DEFAULT) || \
		$(ECHO) "\n"$(MAGEN_C) $(UNDLN_T)$(BOLD_T)"$(CXX) $(CXXFLAGS) -c "$<" -o "$@$(DEFAULT)"\n"

.PHONY: all message clean fclean re debug tests_run

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
