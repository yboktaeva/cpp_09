# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 09:54:12 by yuboktae          #+#    #+#              #
#    Updated: 2024/01/09 14:35:28 by yuboktae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/

SRC_FILES = main.cpp BitcoinExchange.cpp

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRC))

RM = rm -f
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CPPFLAGS = -I/usr/local/includes -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
		
fclean: clean
	$(RM) $(NAME)
		
re: fclean all

.PHONY: all clean fclean re