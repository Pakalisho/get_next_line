NAME	=	libget_next_line

SRCS	=	

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra

OUTN	=	$(NAME).a

CSRCS	=	$(SRCS:%=%.c)

OSRCS	=	$(SRCS:%=%.o)

$(NAME):
		$(CC) $(CFLAGS) -c $(CSRCS) -I./
		ar -rc $(OUTN) $(OSRCS)

all:	$(NAME)

clean:	rm -f $(OSRCS)

fclean:	clean
		rm -f $(NAME).a

re:		fclean all

.PHONY: all, clean, fclean, re
