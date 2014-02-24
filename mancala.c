/* 
@author - James C. Porcelli
@file - manacala.c
@app - Mancala, cmd line
*/

#include "mancala_game.h"

/* Game Engine for Mancala 
   
   Mancala is an ancient family of board
   games, and there are numerous varients.
   This applicaton is a version of the basic
   game, known as two-rank Mancala and also
   known as Kalah. 
*/
int main(int argc, char *argv[]){
  
  srand(time(NULL));  
 
  int num_pits, *playerA_pits, pit_choiceA, *playerB_pits, pit_choiceB, i, game_overA, game_overB;
  
  printf("\n> How many non-scoring pits would you like\n"
	 "> to configure the game of Mancala for >> ");
  
  scanf("%d",&num_pits);

  while(num_pits < MIN_NON_SCORING_PITS || num_pits > MAX_NON_SCORING_PITS){
    printf("> Invalid number of non-scoring pits.\n"
	   "> Please enter an integer from 1 - 6 \n"
	   "\n> How many non-scoring pits would you like\n"
	   "> to configure the game of Mancala for >> ");
    
    scanf("%d",&num_pits);
  }
  

  playerA_pits = calloc(num_pits + 1, sizeof(int));

  playerB_pits = calloc(num_pits + 1, sizeof(int));
  
  playerA_pits[SCORING_PIT_A_POSITION] = INIT_SCORE;

  for(i = STARTING_PIT + 1; i < num_pits + 1; i++)
    playerA_pits[i] = INIT_MARBLES;
  
  for(i = STARTING_PIT; i < num_pits ; i++)
    playerB_pits[i] = INIT_MARBLES;

  playerB_pits[i] = INIT_SCORE;
  
  /* THIS GIVES A REPRESENTATION AS SUCH, SO WE CAN EASILY MANIPULATE THE
     ARRAYS AS A CYCLE OF PITS
     
     ** Pit 1 (A) Pit 2 (A) ..... Pit N (A) **
     Scoring Pit (A) ---------------Scoring Pit (B)
     ** Pit 1 (B) Pit 2 (B) ..... Pit N (B) ***/  
  
  printf("\n> Please make sure to adequately size the\n"
	 "> terminal window before playing mancala.\n"
	 "> Failure to provide an adequately sized\n"
	 "> terminal window can cause the game board\n"
	 "> to be misconfigured and effect game play.\n\n"
	 "> Press any key to begin Mancala ... \n");
  
  /* Press any key to begin */
  scanf("%*c%*c"); 
  
  game_overA = game_overB = FALSE;
  
  while(!game_overA && !game_overB){
    
    display_board(num_pits, playerA_pits, playerB_pits);
    
    while(playerA_pits[(pit_choiceA = cp_random(rand(), num_pits))] == EMPTY);
    
    printf("> Player A selects pit >> %d\n\n", pit_choiceA);
    
    redistribute_A(playerB_pits, num_pits, pit_choiceA, playerA_pits);    
    
    if(!(game_overA = isGameOver(playerA_pits + 1, num_pits)) &&
       !(game_overB = isGameOver(playerB_pits, num_pits))){
    
    	display_board(num_pits, playerA_pits, playerB_pits);
    
    	while( ((pit_choiceB = prompt_player(num_pits)) == ERROR)
	   	|| playerB_pits[pit_choiceB] == EMPTY)
      		printf("> Invalid pit selection, try again\n\n");
    
    	redistribute_B(playerA_pits, num_pits, pit_choiceB, playerB_pits);
    
	game_overA = isGameOver(playerB_pits, num_pits);
	game_overB = isGameOver(playerA_pits + 1, num_pits);
    
    }else{
      /*Game over */
      break;
    }
  }
  
  remove_remaining_marbles(num_pits, playerA_pits, playerB_pits);
  display_board(num_pits, playerA_pits, playerB_pits);
  
  if(playerA_pits[SCORING_PIT_A_POSITION] > playerB_pits[num_pits]){
    /* Player A wins */
    printf("\nGame Over, Player A Wins!\n\n");
  }else{ 
    /* Player B wins */
    printf("\nGame Over, Player B You Win !\n\n");
  }
  
  return SUCCESS;  
}
