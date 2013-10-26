# Makefile for Mancala Game
############################################
# James C. Porcelli, SB_ID 108900819, CSE230
# Spring 2013, Prof. Esmaili, HW3, gcc - 4.6
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