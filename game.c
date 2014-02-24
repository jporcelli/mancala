/* 
@author - James C. Porcelli
@file - game.c
@app - Mancala, cmd line
*/

#include "mancala_game.h"

/* 
   Check for end of game, which occurs when a 
   player has no marbles left in any of their non-scoring pits.
*/
int isGameOver(int *non_scoring_pits, int num_pits){
  
  int totalMarbles = 0, i;
  
  for(i = STARTING_PIT; i < num_pits; i++)
    totalMarbles += *non_scoring_pits++;
  
  return (totalMarbles == GAME_OVER);
}

/*
  Takes all the marbles from the player that still has marbles
  left in non scoring pits and adds them to that players 
  scoring pit. 
*/
void remove_remaining_marbles(int num_pits, 
			      int *playerA_pits, int *playerB_pits){
  int marblesRemaining = EMPTY, i;
  
  if(isGameOver(playerA_pits + 1, num_pits)){      
    
    for(i = STARTING_PIT; i < num_pits; i++){	
      marblesRemaining += playerB_pits[i];
      playerB_pits[i] = EMPTY;
    }	

    playerB_pits[i] += marblesRemaining;
    
  }else {
      
      for(i = STARTING_PIT + 1; i < num_pits + 1; i++){	  
	marblesRemaining += playerA_pits[i];
	playerA_pits[i] = EMPTY;
      }

      playerA_pits[SCORING_PIT_A_POSITION] += marblesRemaining;
      
    }
}
 

/* 
   Display the game board. 
*/
void display_board(int num_pits,int *playerA_pits,int *playerB_pits){
  int i;
  
  printf("  Scoring Pit (A)  ||");

  for(i = STARTING_PIT + 1; i < num_pits + 1; i++)
    printf("    Pit %d (A)    ||", i);
  
  printf(" Scoring Pit (B)"); 
  printf("\n                   ||");
  
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("                 ||");


  printf("\n                   ||");
  

  for(i = STARTING_PIT + 1; i < num_pits + 1; i++)
    printf("        %2d       ||", playerA_pits[i]);

  printf("\n                   ||");
    
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("                 ||");

  printf("\n");
  printf("        %2d         ||", playerA_pits[SCORING_PIT_A_POSITION]);

  for(i = STARTING_PIT; i < num_pits; i++)
    printf("-----------------");

  if(num_pits == TWO_NON_SCORING)
    printf("--");
  else if(num_pits == THREE_NON_SCORING)
    printf("----");
  else if(num_pits == FOUR_NON_SCORING)
    printf("------");
  else if(num_pits == FIVE_NON_SCORING)
    printf("--------");
  else if(num_pits == SIX_NON_SCORING)
    printf("----------");

  printf("||        %2d      ", playerB_pits[num_pits]);
  printf("\n                   ||");
  
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("                 ||");
  
  printf("\n                   ||");
  
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("        %2d       ||", playerB_pits[i]);
  
  printf("\n                   ||");
  
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("                 ||");

  printf("\n");

  printf("  Scoring Pit (A)  ||");
  
  for(i = STARTING_PIT + 1; i < num_pits + 1; i++)
    printf("    Pit %d (B)    ||", i);

  printf(" Scoring Pit (B)\n\n");    
}    

/* 
   Updates the appropriate non-scoring and scoring pits to
   reflect the number of marbles redistibuted during Player
   A's turn.
*/
void redistribute_A(int *playerB_pits, int num_pits, int pit_choice, int *playerA_pits){
  int i, j, marblesToMove, redistribute = TRUE;
  
  i = pit_choice - 1;  
  j = STARTING_PIT;
  
  marblesToMove = playerA_pits[pit_choice];
  playerA_pits[pit_choice] = EMPTY;  
  
  while(redistribute){
    while(i >= SCORING_PIT_A_POSITION && marblesToMove-- > EMPTY){
      
#if DEBUG
      printf("i = %d , marbles = %d ",i, marblesToMove);
#endif
   
      if(marblesToMove == EMPTY && playerA_pits[i] != EMPTY 
	 && i != SCORING_PIT_A_POSITION){
	
	(playerA_pits[i])++; 
	
	marblesToMove = playerA_pits[i];
	playerA_pits[i] = EMPTY; 
	
	i--;
	
      }else if(marblesToMove == EMPTY 
	   && playerA_pits[i] == EMPTY && i != SCORING_PIT_A_POSITION){
	
	marblesToMove = 1; 
	marblesToMove += playerB_pits[i - 1]; 
	
	playerB_pits[i - 1] = EMPTY ; 
	
	playerA_pits[SCORING_PIT_A_POSITION] += marblesToMove; /
	
	marblesToMove = EMPTY; 
	redistribute = FALSE;
	break;
	
      }else{
	  (playerA_pits[i--])++; 	  
	}
    }
    
    while(j < num_pits && marblesToMove-- > EMPTY){
      
#if DEBUG
      printf("j = %d , marbles = %d ",j, marblesToMove);
#endif
      
      if(marblesToMove == EMPTY && playerB_pits[j] != EMPTY){  

	(playerB_pits[j])++; 
	
	marblesToMove = playerB_pits[j];
	playerB_pits[j] = EMPTY; 
	
	j++;
	
      }else{	
	(playerB_pits[j++])++;
      }
    }    
    
    if(marblesToMove > EMPTY){
      i = num_pits;
      j = STARTING_PIT;
    }else{ 
      redistribute = FALSE;
    }
  }
  
#if DEBUG
  printf("i = %d , j = %d ",i, j);
#endif
  
}

/* 
   Updates the appropriate non-scoring and scoring pits to
   reflect the number of marbles redistibuted during Player
   B's turn.   
*/
void redistribute_B(int *playerA_pits, int num_pits, int pit_choice, int *playerB_pits){
  
  int i, j,marblesToMove, redistribute = TRUE;
  
  i = pit_choice + 1;
  
  j = num_pits ;
  
  marblesToMove = playerB_pits[pit_choice];
  playerB_pits[pit_choice] = EMPTY;
  
  while(redistribute){
    while(i <= num_pits && marblesToMove-- > EMPTY){
      
      if(marblesToMove == EMPTY && playerB_pits[i] != EMPTY 
	 && (i != num_pits)){
	
	(playerB_pits[i])++; 
	
	marblesToMove = playerB_pits[i];
	playerB_pits[i] = EMPTY; 
	
	i++;
	
      }else if(marblesToMove == EMPTY && playerB_pits[i] == EMPTY  
	   && i != num_pits){
	
	marblesToMove = 1; 
	marblesToMove += playerA_pits[i + 1]; 
	
	playerA_pits[i + 1] = EMPTY; 
	
	playerB_pits[num_pits] += marblesToMove; 
	
	marblesToMove = EMPTY; 
	redistribute = FALSE;
	break;
	
      }else{	
	  (playerB_pits[i++])++; 
	}      
    }
    
    while(j > SCORING_PIT_A_POSITION && marblesToMove-- > EMPTY){
      
      if(marblesToMove == EMPTY && playerA_pits[j] != EMPTY){
	
	(playerA_pits[j])++;
	
	marblesToMove = playerA_pits[j];
	playerA_pits[j] = EMPTY; 
	
	j--;
	
      }else{
	(playerA_pits[j--])++;
      }
    }
    
    if(marblesToMove > EMPTY){
      i = STARTING_PIT;
      j = num_pits;
    }else{
      redistribute = FALSE;
    }
  }
}



