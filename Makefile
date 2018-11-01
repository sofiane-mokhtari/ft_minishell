# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/23 14:14:32 by smokhtar          #+#    #+#              #
#    Updated: 2018/08/23 14:14:34 by smokhtar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = minishell

flag = -Wall -Werror -Wextra -fsanitize=address

file = minishell\
		input\
		builtins\
		fork\
		buildin_cd\
		buildin_cd_2\
		ft_splitwhitespace\
		env\
		pars\
		autre

Src = $(addprefix src/, $(file))

src = $(addsuffix .c, $(Src))

obj = $(addsuffix .o, $(file))

lib =  libft/libft.a

inc = -Iinclude -Ilibft

object = $(addsuffix .o, $(Src))

all: $(name)

$(name) :
	make -C libft/
	gcc -o $(name) $(lib) $(src) $(inc) $(flag)

e : 
	touch ft_ls
	rm ft_ls
	gcc -o $(name) $(lib) $(src) $(inc) $(flag) 

f : 
	touch ft_ls
	rm ft_ls
	gcc -o $(name) $(lib) $(src) $(inc) $(flag) $(fz)

clean :
	make -C libft/ clean
	rm -rf $(obj)

fclean : clean
	make -C libft/ fclean
	touch $(name)
	rm $(name)

re : fclean all
