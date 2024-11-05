NAME = philo
CC = @clang
THREAD_FLAG = -g -fsanitize=thread
ADDRESS_FLAG = -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
RM = @rm -rf


FILES = ft_atol \
		ft_fork \
		ft_initialize \
		ft_process \
		ft_utils \
		philo \

SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

thread:	$(SRCS_DIR)philo.h $(OBJS)
	$(CC) $(CFLAGS) $(THREAD_FLAG) -o $(NAME) $(OBJS)
	@echo "philo compiled with -fsanitize=thread flag"

address: $(SRCS_DIR)philo.h $(OBJS)
	$(CC) $(CFLAGS) $(ADDRESS_FLAG) -o $(NAME) $(OBJS)
	@echo "philo compiled with -fsanitize=address flag"

$(NAME): $(SRCS_DIR)philo.h $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "philo compiled"

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(OBJS) $(NAME) $(OBJS_DIR)

re: fclean $(NAME)

.PHONY: all clean fclean re fre