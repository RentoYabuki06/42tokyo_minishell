# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/05 15:00:00 by yabukirento       #+#    #+#              #
#    Updated: 2025/03/07 14:52:42 by yabukirento      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# プログラム名
NAME = minishell

# コンパイラとフラグ
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include -I./utils/libft

# ライブラリ
LIBFT = utils/libft/libft.a
LIBFT_DIR = utils/libft

# ソースファイル
SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/shell/shell.c \
       $(SRCS_DIR)/shell/signal.c \
       $(SRCS_DIR)/shell/env/env.c \
       $(SRCS_DIR)/builtin/cd.c \
       $(SRCS_DIR)/builtin/echo.c \
       $(SRCS_DIR)/builtin/env.c \
       $(SRCS_DIR)/builtin/exit.c \
       $(SRCS_DIR)/builtin/export.c \
       $(SRCS_DIR)/builtin/unset.c \
       $(SRCS_DIR)/parsing/main_parsing.c \
       $(SRCS_DIR)/parsing/make_parsing.c \
       $(SRCS_DIR)/parsing/double_quote.c \
       $(SRCS_DIR)/parsing/single_quote.c \
       $(SRCS_DIR)/parsing/quote_error.c \
       $(SRCS_DIR)/parsing/free_parsing.c \
       $(UTILS_DIR)/additive/ft_strchr_index.c \
       $(UTILS_DIR)/additive/ft_strjoin_minishell.c \
       $(UTILS_DIR)/get_next_line/get_next_line.c \
       $(UTILS_DIR)/get_next_line/get_next_line_utils.c

# オブジェクトファイル
OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# 必要なディレクトリ
DIRS = $(OBJS_DIR) \
       $(OBJS_DIR)/shell \
       $(OBJS_DIR)/shell/env \
       $(OBJS_DIR)/builtin \
       $(OBJS_DIR)/parsing \
       $(OBJS_DIR)/utils/additive \
       $(OBJS_DIR)/utils/get_next_line

# readline ライブラリ
READLINE_DIR = $(shell brew --prefix readline)
READLINE_LIB = -L$(READLINE_DIR)/lib -lreadline
READLINE_INC = -I$(READLINE_DIR)/include

# ターゲット
all: $(NAME)

# メインターゲット
$(NAME): $(DIRS) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) -o $(NAME)

# オブジェクトファイルの生成
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -c $< -o $@

# libft の作成
$(LIBFT):
	@make -C $(LIBFT_DIR)

# 必要なディレクトリの作成
$(DIRS):
	@mkdir -p $@

# クリーンアップ
clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re help
