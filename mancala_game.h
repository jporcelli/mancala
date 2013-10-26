/* James C. Porcelli, SBU-ID 108900819, CSE230,
   Spring 2013, Prof. Esmaili, HW # 3, gcc - 4.6 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* APP LEVEL SETTINGS */
#define ERROR -1
#define TRUE 1
#define FALSE 0
#define DEBUG 0 /* DEBUG SWITCH, USE (1) FOR ON / (0) FOR OFF

/* GAME VALUES / SETTINGS / RULES / ETC */
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

/* PLAYER SUB - ROUTINES */
int prompt_player(int);

/* GAME SUB - ROUTINES */
void display_board(int, int[], int[]);
int isGameOver(int[], int);
void redistribute_A(int[], int, int, int[]);
void redistribute_B(int[], int, int, int[]);

/* CP SUB - ROUTINESS */
int cp_random(int, int);
