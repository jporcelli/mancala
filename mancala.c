/* James C. Porcelli, SBU-ID 108900819, CSE230,
   Spring 2013, Prof. Esmaili, HW # 3, gcc - 4.6 */

#include "mancala_game.h"

/* Game Engine for Mancala 
   
   Mancala is an ancient family of board
   games, and there are numerous varients.
   This applicaton is a version of the basic
   game, known as two-rank Mancala and also
   known as Kalah. I hope you enjoy playing
   Mancala, and good luck agaist the cp, he's
   very cunning!
*/
int main(int argc, char *argv[]){
  
  /* SEED THE RANDOM NUMBER GENERATOR */
  srand(time(NULL));  
 
  int     
    /* NUMBER OF NON - SCORING PITS FOR THIS GAME */
    num_pits,   
    
    /* PLAYER A PITS */
    *playerA_pits,  
    
    /* PLAYER A PIT CHOICE */
    pit_choiceA,
    
    /* PLAYER B PITS */
    *playerB_pits,
    
    /* PLAYER B PIT CHOICE */
    pit_choiceB,
    
    /* COUNTER */
    i,
    
    /* FLAGS */
    game_overA, game_overB;
  
  /* PROMPT THE USER TO ENTER THE NUMBER OF
     NON - SCORING PITS FOR EACH PLAYER */
  printf("\n> How many non-scoring pits would you like\n"
	 "> to configure the game of Mancala for >> ");
  
  /* READ IN THE USERS CHOICE FOR THE NUMBER OF NON-SCORING PITS */
  scanf("%d",&num_pits);

  /* MAKE SURE THE USER ENTERS VALID INPUT FOR THE NUMBER OF NON SCORING
     PITS DESIRED. THE MAXIMUM IS 6 AND THE MINIMUM IS OBVIOUSLY 1 */
  while(num_pits < MIN_NON_SCORING_PITS || num_pits > MAX_NON_SCORING_PITS){
    /* DISPLAY AN ERROR MESSAGE */
    printf("> Invalid number of non-scoring pits.\n"
	   "> Please enter an integer from 1 - 6 \n");
    
    /* PROMPT THE USER TO ENTER THE NUMBER OF
       NON - SCORING PITS FOR EACH PLAYER */
    printf("\n> How many non-scoring pits would you like\n"
	   "> to configure the game of Mancala for >> ");
    
    /* READ IN THE USERS CHOICE FOR THE NUMBER OF NON-SCORING PITS */
    scanf("%d",&num_pits);
  }
  
  /* ALLOCATE MEMORY FOR PLAYER A PITS */
  playerA_pits = calloc(num_pits + 1 /* ADD EXTRA SPACE FOR SCORING PIT */
			, sizeof(int));
  
  /* ALLOCATE MEMORY FOR PLAYER B PITS */
  playerB_pits = calloc(num_pits + 1 /* ADD EXTRA SPACE FOR SCORING PIT */
			, sizeof(int));
  
  /* INITIALIZE PLAYER A PITS ADDING PLAYER A'S SCORING PIT FIRST */
  playerA_pits[SCORING_PIT_A_POSITION] = INIT_SCORE;

  /* NOW THE NON - SCORING PITS */
  for(i = STARTING_PIT + 1; i < num_pits + 1; i++)
    playerA_pits[i] = INIT_MARBLES;
  
  /* INITIALIZE PLAYER B PITS */
  for(i = STARTING_PIT; i < num_pits ; i++)
    playerB_pits[i] = INIT_MARBLES;
  
  /* ADDING PLAYER B'S SCORING PIT LAST */
  playerB_pits[i] = INIT_SCORE;
  
  /* THIS GIVES A REPRESENTATION AS SUCH, SO WE CAN EASILY MANIPULATE THE
     ARRAYS AS A CYCLE OF PITS
     
     ** Pit 1 (A) Pit 2 (A) ..... Pit N (A) **
     Scoring Pit (A) ---------------Scoring Pit (B)
     ** Pit 1 (B) Pit 2 (B) ..... Pit N (B) ***/  
  
  /* DISPLAY WARNING ABOUT PROVIDING AN
     ADEQUATELY SIZED TERMINAL WINDOW WHEN
     PLAYING MANCALA */
  printf("\n> Please make sure to adequately size the\n"
	 "> terminal window before playing mancala.\n"
	 "> Failure to provide an adequately sized\n"
	 "> terminal window can cause the game board\n"
	 "> to be misconfigured and effect game play.\n\n"
	 "> Press any key to begin Mancala ... \n");
  
  /* "PRESS ANY KEY TO BEGIN MANCALA" */
  scanf("%*c%*c"); /* READS IN AND DISCARDS THE KEY SIGNALING USERS
		      DESIRE TO BEGIN THE GAME */
  
  /* INIT GAME FLAGS */
  game_overA = game_overB = FALSE;
  
  /* REPEAT WHILE EACH PLAYER HAS AT LEAST 1 MARBLE IN 
     A NON-SCORING PIT */
  while(!game_overA && !game_overB){
    
    /* DISPLAY THE BOARD BEFORE EACH PLAYER MOVES */
    display_board(num_pits, playerA_pits, playerB_pits);
    
    /* CP (PLAYER A) ALWAYS GOES FIRST 
       CP (PLAYER A) RANDOM MODE 
       
       NOTE - COMPUTER WILL PICK AGAIN IF IT SELECTED AN EMPTY PIT
       UNTIL A NON EMPTY PIT IS SELECTED. THERE IS NO NEED TO DISPLAY
       A MESSAGE IF THE COMPUTER PICKED AN EMPTY PIT, JUST PICK AGAIN
       QUIETLY
       
       NOTE - IF WE ARE AT THIS POINT THEN THERE EXISTS AT LEAST ONE
       NON EMPTY PIT FOR PLAYER A 
       
       NOTE - cp_random ALWAYS RETURNS AN INTEGER BOUNDED BY THE SIZE OF
       THE NUMBER OF PITS, NO NEED TO CHECK */    
    while(playerA_pits[(pit_choiceA = cp_random(rand(), num_pits))] == EMPTY);
    
    /* ANNOUNCE PLAYER A PIT CHOICE */
    printf("> Player A selects pit >> %d\n\n", pit_choiceA);
    
    /* CP (PLAYER A) EXPERT MODE 
       CP (PLAYER A) PIT CHOICE FOR EXPERT MODE */
    /***** UNDER CONSTRUCTION *****/ 
    
    /* UPDATE PIT VALUES AFTER PLAYER A'S TURN*/
    redistribute_A(playerB_pits, num_pits, pit_choiceA, playerA_pits);    
    
    /* NOTE - GAME OVER CONDITION IS CHECKED AFTER EACH
       UPDATE TO THE MARBLES IN THE NON-SCORING PITS I.E
       AFTER EACH PLAYERS TURN */
    if(!(game_overA = isGameOver(playerA_pits + 1, num_pits)) &&
       !(game_overB = isGameOver(playerB_pits, num_pits))){
    
    /* DISPLAY THE BOARD BEFORE EACH PLAYER MOVES */
    display_board(num_pits, playerA_pits, playerB_pits);
    
    /* PROMPT PLAYER B FOR PIT CHOICE */
    while( ((pit_choiceB = prompt_player(num_pits)) == ERROR)
	   /* THE ERROR CHECK ABOVE PREVENTS THE NEXT EXPRESSION
	      FROM BEING EVALUATED WITH AN OUT OF BOUNDS ARRAY INDEX */
	   || playerB_pits[pit_choiceB] == EMPTY)
      /* IF PLAYER B PROVIDES INVALID CHOICE, TRY AGAIN */ 
      printf("> Invalid pit selection, try again\n\n");
    
    /* UPDATE PIT VALUES AFTER PLAYER-B'S TURN */
    redistribute_B(playerA_pits, num_pits, pit_choiceB, playerB_pits);
    
    /* NOTE - GAME OVER CONDITION IS CHECKED AFTER EACH
       UPDATE TO THE MARBLES IN THE NON-SCORING PITS I.E
       AFTER EACH PLAYERS TURN */
    game_overA = isGameOver(playerB_pits, num_pits);
    game_overB = isGameOver(playerA_pits + 1, num_pits);
    
    }else{
      /* GAME OVER,         
	 TERMINATE THE GAME LOOP */
      break;
    }
  }
  
  /* GAME OVER, 
     
     ADD ALL THE REMAINING MARBLES TO THE PLAYERS SCORING PIT 
     WHOSE SIDE THE NON EMPTY PITS BELONG */
  remove_remaining_marbles(num_pits, playerA_pits, playerB_pits);
  
  /* SHOW THE FINAL GAME BOARD */
  display_board(num_pits, playerA_pits, playerB_pits);
  
  if(playerA_pits[SCORING_PIT_A_POSITION] > playerB_pits[num_pits]){
    /* PLAYER A WINS */
    printf("\nGame Over, Player A Wins!\n\n");
  }else{ 
    /* PLAYER B (USER) WINS */
    printf("\nGame Over, Player B You Win !\n\n");
  }
  
  /* RETURN WITH SUCCESSFUL COMPLETITION STATUS */
  return SUCCESS;  
  
}
