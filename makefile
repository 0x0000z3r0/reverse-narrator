NAME=reverse-narrator

all:
	# $(CC) main.c -o $(NAME) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor
	$(CC) main.c -o $(NAME) -lraylib -lGL -lm -pthread -ldl -lrt

.PHONY: all
