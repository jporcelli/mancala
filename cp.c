/* James C. Porcelli, SBU-ID 108900819, CSE230,
   Spring 2013, Prof. Esmaili, HW # 3, gcc - 4.6 */

#include "mancala_game.h"

/* Cp decision engine for random mode. */
int cp_random(int rand_num, int num_pits){
  /* RETURNS A RANDOMIZED PIT CHOICE BETWEEN [1, MAX_PITS] */
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
  
  /* WE ONLY USE THE RANDOM NUMBER NOW TO CHOOSE
     THE PIT WE WILL HOARD IN. THIS IS DONE SO PLAYER B
     DOESNT GET WISE TO OUR SCHEME AND COULD THEREFORE
     MORE EASILY FORMULATE A COUNTER ATTACK WHERE BY HE
     GAINS CONTROL OF OUR HOARDING PIT ! */
  int hoard_in = 1 + (int)( (num_pits * (rand_num / (RAND_MAX + 1.0))));
  
  /* RETURN OUR PIT CHOICE AS ANY PIT EXCEPT THE HOARDING PIT UNLESS
     WE MUST */
  
  /* CHECK IF WE WILL BE FORCED TO PICK OUR HOARDING PIT */
  int marblesLeft = EMPTY, 
    
    /* COUNTER */
    i,
    
    /* PIT CHOICE (BESIDES THE HOARDING PIT) */
    pit_choice;
  
  for(i = STARTING_PIT + 1;i < num_pits + 1;i++)
    /* ADD ALL MARBLES LEFT IN OUR OTHER PITS */
    if(i != hoard_in)
      marblesLeft += playerA_pits[i];
  
  /* WE HAVE NO CHOICE BUT TO PLAY OUR HOARDING PIT */
  if(marblesLeft == EMPTY)
    return hoard_in;
  else 
    /* RETURN A NON EMPTY PIT THATS NOT OUR HOARDING PIT */
    {
      for(i = STARTING_PIT + 1;i < num_pits + 1;i++)
	/* THE FIRST NON EMPTY NON SCORING PIT WILL DO */
	if(playerA_pits[i] != EMPTY && i!= hoard_in)
	  return i;
    }
}
