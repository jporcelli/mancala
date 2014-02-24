# Makefile for Mancala Game
############################################
CC= gcc
CFLAGS= 
EFILE= play_mancala
OBJS= mancala.o game.o player.o cp.o
DEPS= mancala_game.h
$(EFILE): $(OBJS)
	@echo "linking ..."
	@$(CC) $(CFLAGS) -o $(EFILE) $(OBJS)
%.o: %.c $(DEPS) 
	$(CC) $(CFLAGS) -c $*.c
