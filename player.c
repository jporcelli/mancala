/* James C. Porcelli, SBU-ID 108900819, CSE230,
   Spring 2013, Prof. Esmaili, HW # 3, gcc - 4.6 */

#include "mancala_game.h"

/* Prompt the player to select desired pit */
int prompt_player(int num_pits){
  /* PLAYERS PIT CHOICE */
  int pit;

  /* DISPLAY PROMPT */
  printf("> Player B, please select pit >> ");
  /* STORE PLAYERS CHOICE */
  scanf("%d",&pit);

  /* GO TO NEXT LINE */
  printf("\n");
  
  /* ERROR CHECKING */
  if(pit < 1 || pit > num_pits){
    return ERROR; /* SELECTED PIT INVALID */
  }else
    /* NOTE - SINCE PLAYER B'S SCORING PIT IS AT THE END OF
       THE ARRAY WE RETURN ONE LESS THEN THE PIT CHOICE SO AS TO
       RETURN THE CORRECT CORRESPONDING ARRAY INDEX FOR PLAYER B'S
       NON SCORING PITS */
    {
      return (pit - 1); /* VALID PIT SELECTED */
    }
}

