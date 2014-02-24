/* 
   @author - James C. Porcelli 
   @file - player.c
   @app - Mancala, cmd line
*/

#include "mancala_game.h"

/* Prompt the player to select desired pit */
int prompt_player(int num_pits){
  int pit;

  printf("> Player B, please select pit >> ");
  
  /* Players choice */
  scanf("%d",&pit);
  printf("\n");
  
  /* Error checking */
  if(pit < 1 || pit > num_pits){
    return ERROR; 
  }else{
      return (pit - 1); 
    }
}

