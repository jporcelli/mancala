/* 
   @author - James C. Porcelli
   @file - mancala_game.h
   @app - Mancala, cmd line
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* App level settings */
#define ERROR -1
#define TRUE 1
#define FALSE 0
#define DEBUG 0 /* Debug mode switch */

/* Game values, settings, rules, etc */
#define ONE_NON_SCORING 1
#define TWO_NON_SCORING 2
#define THREE_NON_SCORING 3
#define FOUR_NON_SCORING 4
#define FIVE_NON_SCORING 5
#define SIX_NON_SCORING 6
#define INIT_MARBLES 4
#define INIT_SCORE 0
#define MIN_NON_SCORING_PITS 1
#define MAX_NON_SCORING_PITS 6
#define GAME_OVER 0
#define SUCCESS 0
#define EMPTY 0
#define SCORING_PIT_A_POSITION 0
#define STARTING_PIT 0

/* Player functions */
int prompt_player(int);

/* Mancala sub routines */
void display_board(int, int[], int[]);
int isGameOver(int[], int);
void redistribute_A(int[], int, int, int[]);
void redistribute_B(int[], int, int, int[]);

/* CP sub routines */
int cp_random(int, int);
