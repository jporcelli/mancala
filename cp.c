/* 
@author - James C. Porcelli 
@file - cp.c
@app - Mancala, cmd line
*/

#include "mancala_game.h"

/* Cp decision engine for random mode. */
int cp_random(int rand_num, int num_pits){
  return (1 + (int)( (num_pits * (rand_num / (RAND_MAX + 1.0)))));
}

/* This is the strategy known as hoarding where as the player
   attempts to accumlate marbles in a given pit refusing to play
   that pit. If the player refuses to play that pit until the end 
   of the game then all of the marbles well be swept into the
   scoring pit. Of course there are risk to this strategy or else
   it wouldnt be a strategy and instead would be accepted practice!
*/
int cp_hoarding(int rand_num, int num_pits, int playerA_pits[]){
  
  int hoard_in = 1 + (int)( (num_pits * (rand_num / (RAND_MAX + 1.0))));
  
  int marblesLeft = EMPTY, i, pit_choice;
  
  for(i = STARTING_PIT + 1;i < num_pits + 1;i++)
    if(i != hoard_in)
      marblesLeft += playerA_pits[i];
  
  if(marblesLeft == EMPTY)
    return hoard_in;
  else{
      for(i = STARTING_PIT + 1;i < num_pits + 1;i++)
	if(playerA_pits[i] != EMPTY && i!= hoard_in)
	  return i;
    }
}
