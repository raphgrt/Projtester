##
## EPITECH PROJECT, 2024
## my_rpg
## File description:
## Makefile
##

TARGET			=	projTester
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
BUILD_DIR 		=	build
OBJS			=	${addprefix ${BUILD_DIR}/, ${SRCS:.c=.o}}

SRCS			=	src/main.c									\
					src/my_str_to_word_array.c					\
					src/my_puterr.c								\
					src/test_file/args.c							\
					src/test_file/btf.c							\
					src/test_file/exec_test.c					\
					src/test_file/get_argv.c						\
					src/test_file/output.c						\
					src/test_file/print_test.c					\
					src/tree/tree.c								\
					src/tree/tree_print.c						\
					src/tree/tree_sort.c						\

all:	${BUILD_DIR} ${TARGET}

${BUILD_DIR}:
	mkdir -p $@

${BUILD_DIR}/%.o: %.c
	mkdir -p ${dir $@}
	${CC} -c $< -o $@ ${LDFLAGS} ${CPPFLAGS}

${TARGET}:	${OBJS}
	${CC} ${CFLAGS} -o ${TARGET} ${OBJS}

re:	fclean all

clean:
	rm -rf ${BUILD_DIR}

fclean:	clean
	rm -f ${TARGET}

.PHONY: all re clean fclean
