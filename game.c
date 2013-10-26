/* James C. Porcelli, SBU-ID 108900819, CSE230,
   Spring 2013, Prof. Esmaili, HW # 3, gcc - 4.6 */

#include "mancala_game.h"

/* 
   Check for end of game, which occurs when a 
   player has no marbles left in any of their non-scoring pits.
*/
int isGameOver(int *non_scoring_pits, int num_pits){
  
  int 
    /* TOTAL NUMBER OF MARBLES LEFT IN NON-SCORING PITS */
    totalMarbles = 0, 
    
    /* COUNTER */ 
    i;
  
  /* GET THE TOTAL NUMBER OF MARBLES LEFT IN NON-SCORING PITS 
     
     NOTE - WE USE POINTER ARITHMETIC TO ADD ONLY THE VALUES FROM
     THE CORRESPONDING NON SCORING PITS. SINCE THE SCORING PITS FOR 
     EACH PLAYER ARE ON DIFFERENT ENDS OF THE ARRAY WE JUST PASS A 
     POINTER TO THE CORRECT STARTING POSITION IN MEMORY AND WE CAN USE
     ONE SUB ROUTINE DEFINITION FOR BOTH PLAYERS*/
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
  int
    /* MARBLES REMAINING */ 
    marblesRemaining = EMPTY,
    
    /* COUNTER */
    i;
  
  /* IF ITS PLAYER A'S NON SCORING PITS */
  if(isGameOver(playerA_pits + 1, num_pits)){      
    /* THEN MOVE ALL PLAYER B'S REMAINING MARBLES TO PLAYER B'S
       SCORING PIT */
    
    for(i = STARTING_PIT; i < num_pits; i++){	
      /* GET THE MARBLE VALUE FROM EACH NON SCORING PIT */
      marblesRemaining += playerB_pits[i];
      
      /* AND EMPTY THE PITS OUT */
      playerB_pits[i] = EMPTY;
    }	
    /* AND ADD THE TOTAL VALUE OF MARBLES THAT WAS LEFT TO PLAYER B'S
       SCORING PIT */
    playerB_pits[i] += marblesRemaining;
    
  }else 
    /* MUST BE PLAYER B'S NON SCORING PITS */
    {
      /* THEN MOVE ALL PLAYER A'S REMAINING MARBLES TO PLAYER A'S
	 SCORING PIT */
      
      for(i = STARTING_PIT + 1; i < num_pits + 1; i++){	  
	/* GET THE MARBLE VALUE FROM EACH NON SCORING PIT */
	marblesRemaining += playerA_pits[i];
	
	/* AND EMPTY THE PITS OUT */
	playerA_pits[i] = EMPTY;
      }
      /* AND ADD THE TOTAL VALUE OF MARBLES THAT WAS LEFT TO PLAYER A'S
	 SCORING PIT */
      playerA_pits[SCORING_PIT_A_POSITION] += marblesRemaining;
      
    }
}
 

/* 
   Display the game board. 
*/
void display_board(int num_pits,int *playerA_pits,int *playerB_pits){
  /* COUNTER */
  int i;
  
  /* DISPLAY PLAYER A SCORING PIT HEADER*/
  printf("  Scoring Pit (A)  ||");
  
  /* DISPLAY PLAYER A NON SCORING PITS HEADERS */
  for(i = STARTING_PIT + 1; i < num_pits + 1; i++)
    printf("    Pit %d (A)    ||", i);
  
  /* DISPLAY PLAYER B SCORING PIT HEADER */
  printf(" Scoring Pit (B)"); 
  
  /* ADVANCE TO NEXT LINE */
  printf("\n                   ||");
  
  /* PRINT BUFFER LEVEL */
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("                 ||");

  /* ADVANCE TO NEXT LINE */
  printf("\n                   ||");
  
  /* NOW PLAYER A'S MARBLES VALUES */
  for(i = STARTING_PIT + 1; i < num_pits + 1; i++)
    printf("        %2d       ||", playerA_pits[i]);

  /* ADVANCE TO NEXT LINE */
  printf("\n                   ||");
    
  /* ANOTHER BUFFER LEVEL */
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("                 ||");

  /* ADVANCE TO NEXT LINE */
  printf("\n");

  /* NOW PLAYER A'S SCORE */
  printf("        %2d         ||", playerA_pits[SCORING_PIT_A_POSITION]);

  /* PRINT THE MIDDLE LEVEL OF THE BOARD */
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("-----------------");

  /* THE SIZE OF THE MIDDLE PARTITION IS A FUNCTION OF THE NUMBER OF PITS,
     SO WELL ADD THE EXTRA DASHES NEEDED FOR EACH SIZE BOARD SEPERATLY, 
     NOTICE HOW WE ADD 2 EXTRA DASHES FOR EACH INCREASING SIZE OF THE GAME
     BOARD */
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

  /* NOW PLAYER B'S SCORE */
  printf("||        %2d      ", playerB_pits[num_pits]);
  
  /* ADVANCE TO NEXT LINE */
  printf("\n                   ||");
  
  /* ANOTHER BUFFER LEVEL */
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("                 ||");
  
  /* ADVANCE TO NEXT LINE */
  printf("\n                   ||");
  
  /* NOW PLAYER B'S MARBLES VALUES */
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("        %2d       ||", playerB_pits[i]);
  
  /* ADVANCE TO NEXT LINE */
  printf("\n                   ||");
  
  /* ANOTHER BUFFER LEVEL */
  for(i = STARTING_PIT; i < num_pits; i++)
    printf("                 ||");

  /* ADVANCE TO NEXT LINE */
  printf("\n");
  
  /* DISPLAY PLAYER A SCORING PIT HEADER */
  printf("  Scoring Pit (A)  ||");
  
  /* DISPLAY PLAYER B NON SCORING PITS HEADERS */
  for(i = STARTING_PIT + 1; i < num_pits + 1; i++)
    printf("    Pit %d (B)    ||", i);

  /* DISPLAY PLAYER B SCORING PIT HEADER */
  printf(" Scoring Pit (B)\n\n");    
}    

/* 
   Updates the appropriate non-scoring and scoring pits to
   reflect the number of marbles redistibuted during Player
   A's turn.
*/
void redistribute_A(/* PLAYER B PITS*/
		    int *playerB_pits, 
		    
		    /* NUMBER OF NON-SCORING PITS FOR THIS GAME */
		    int num_pits, 
		    
		    /* PLAYER A PIT CHOICE */
		    int pit_choice, 
		    
		    /* PLAYER A PITS */ 
		    int *playerA_pits){
  int
    /* COUNTERS */
    i, j,    
    
    /* MARBLES TO REDISTRIBUTE */ 
    marblesToMove,
    
    /* FLAG */
    redistribute = TRUE;
  
  /* PLAYER A PIT CHOICE - 1 SINCE WE START REDISTRIBUTION FROM THE NEXT
     PIT */
  i = pit_choice - 1;  
  
  /* AND CONTINUE THROUGH PLAYER B'S NON SCORING PITS */
  j = STARTING_PIT;
  
  /* REMOVE ALL MARBLES IN SELECTED PIT */
  marblesToMove = playerA_pits[pit_choice];
  playerA_pits[pit_choice] = EMPTY;  
  
  /* REDISTRIBUTE ACCORING TO RULES OF MANCALA */
  while(redistribute){
    
    /* REDISTRIBUTION STARTS FROM PLAYER-A PIT CHOICE 
       
       NOTE - ALL PITS TRAVERSED HERE ARE ON PLAYER A'S SIDE */ 
    while(i >= SCORING_PIT_A_POSITION && marblesToMove-- > EMPTY){
      
#if DEBUG
      printf("i = %d , marbles = %d ",i, marblesToMove);
#endif
      
      /* AS LONG AS THE LAST PIT RECIEVING A MARBLE WAS NOT EMPTY BEFORE
	 GETTING THE LAST MARBLE AND AS LONG AS IT WAS NOT THE PLAYERS 
	 SCORING PIT, ALL MARBLES ARE TAKEN FROM THE PIT THAT LAST 
	 RECIEVED THE MARBLE AND THE REDISTRIBUTION PROCESS IS REPEATED FROM
	 THIS LAST PIT */
      
      if(marblesToMove == EMPTY /* LAST MARBLE */ 
	 && playerA_pits[i] != EMPTY  /* LAST PIT RECIEVING 
					 MARBLE NOT EMPTY */
	 && i != SCORING_PIT_A_POSITION /* NOT PLAYER A'S SCORING PIT */ ){
	
	(playerA_pits[i])++; /* ADD LAST MARBLE TO PIT */
	
	/* REMOVE ALL MARBLES FROM PIT */
	marblesToMove = playerA_pits[i];
	playerA_pits[i] = EMPTY; 
	
	/* REDISTRIBUTION STARTS AT NEXT PIT */
	i--;
	
      }else if /* IF THE LAST MARBLE WAS DROPPED IN AN EMPTY NON-SCORING
		  PIT ON THE PLAYERS SIDE, THAT MARBLE AND ANY MARBLES IN
		  THE OPPOSITE NON-SCORING PIT ARE MOVED TO THE PLAYERS
		  SCORING PIT AND IT IS NOW THE OTHER PLAYERS TURN */
	  
	  (marblesToMove == EMPTY /* LAST MARBLE */
	   && playerA_pits[i] == EMPTY  /* LAST PIT RECIEVING MARBLE
					   IS EMPTY */
	   && i != SCORING_PIT_A_POSITION /* NOT PLAYER A'S SCORING PIT */ ){
	
	/* PIT IS EMPTY SO INSTEAD OF INCREMENTING THEN DECREMENTING 
	   JUST LEAVE EMPTY AND ADD AN EXTRA MARBLE TO THE #MARBLESTOMOVE
	   REPRESENTING THE LAST MARBLE TO ADD TO THE EMPTY PIT */
	
	marblesToMove = 1; /* THE LAST MARBLE PLUS THE MARBLES IN THE 
			      OPPOSITE NON-SCORING PIT ARE ADDED TO PLAYER A'S
			      SCORING PIT */
	marblesToMove += 
	  playerB_pits[i - 1]; /* OPPOSITE 
				  NON-SCORING PIT */
	
	playerB_pits[i - 1] = EMPTY ; /* OPPOSITE NON-SCORING PIT
					 IS NOW EMPTY */
	
	playerA_pits[SCORING_PIT_A_POSITION] += marblesToMove; /* 
								  PLAYER A'S 
								  SCORING PIT 
							       */
	
	/* NOW ITS THE OTHER PLAYERS TURN */
	marblesToMove = EMPTY; 
	redistribute = FALSE;
	break;
	
      }else /* NOTE THE ONLY OTHER CASE WHERE THE LAST MARBLE IS DROPPED
	       IN THE PLAYERS SCORING PIT, AND THEN IT IS THE OTHER PLAYERS
	       TURN IS HANDLED NATURALLY BY THE LOGIC ALREADY IN PLACE, 
	       NAMELY THAT CASE WOULD BE HANDLED RIGHT HERE */
	{
	  (playerA_pits[i--])++; 	  
	}
    }
    
    /* REDISTRIBUTION CONTINUES THROUGH PLAYER-B'S NON-SCORING PITS IF VALID 
       
       NOTE - ALL PITS TRAVERSED HERE ARE PLAYER B'S NON SCORING PITS */
    while(j < num_pits && marblesToMove-- > EMPTY){
      
#if DEBUG
      printf("j = %d , marbles = %d ",j, marblesToMove);
#endif
      
      /* AS LONG AS THE LAST PIT RECIEVING A MARBLE WAS NOT EMPTY BEFORE
	 GETTING THE LAST MARBLE AND AS LONG AS IT WAS NOT THE PLAYERS 
	 SCORING PIT, ALL MARBLES ARE TAKEN FROM THE PIT THAT LAST 
	 RECIEVED THE MARBLE AND THE REDISTRIBUTION PROCESS IS REPEATED FROM
	 THIS LAST PIT */
      
      if(marblesToMove == EMPTY /* LAST MARBLE */ 
	 && playerB_pits[j] != EMPTY){  /* LAST PIT RECIEVING 
					   MARBLE NOT EMPTY */ 
	/* NOT PLAYER A'S SCORING PIT BECAUSE ONLY PLAYER B'S
	   NON SCORING PITS ARE TRAVERSED HERE */ 
	
	(playerB_pits[j])++; /* ADD LAST MARBLE TO PIT */
	
	/* REMOVE ALL MARBLES FROM PIT */
	marblesToMove = playerB_pits[j];
	playerB_pits[j] = EMPTY; 
	
	/* REDISTRIBUTION STARTS AT NEXT PIT */
	j++;
	
      }else{	
	/* NORMAL REDISTRIBUTION PROCESS 
	   NOTE - ALL PITS TRAVERSED HERE ARE PLAYER B'S NON SCORING PITS */
	(playerB_pits[j++])++;
	
      }
    }    
    
    /* IF WE STILL HAVE MARBLES TO REDISTRIBUTE START FROM THE LARGEST VALUE
       PIT IN PLAYER-A'S PITS */
    if(marblesToMove > EMPTY){
      i = num_pits;
      j = STARTING_PIT;
    }else{ 
      /* IF NOT WE ARE DONT REDISTRIBUTING */
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
void redistribute_B(/* PLAYER A NON-SCORING PITS*/
		    int *playerA_pits, 
		    
		    /* NUMBER OF NON-SCORING PITS FOR THIS GAME */
		    int num_pits, 
		    
		    /* PLAYERS B PIT CHOICE */
		    int pit_choice, 
		    
		    /* PLAYER B PITS */ 
		    int *playerB_pits){
  
  int     
    /* COUNTERS */
    i, j,
    
    /* MARBLES TO REDISTRIBUTE */ 
    marblesToMove,
    
    /* FLAG */
    redistribute = TRUE;
  
  /* PLAYER-B PIT CHOICE + 1 SINCE WE START REDISTRIBUTION FROM THE NEXT PIT */
  i = pit_choice + 1;
  
  /* AND CONTINUE THROUGH PLAYER A'S PITS*/
  j = num_pits ;
  
  /* REMOVE ALL MARBLES IN SELECTED PIT */
  marblesToMove = playerB_pits[pit_choice];
  playerB_pits[pit_choice] = EMPTY;
  
  /* REDISTRIBUTE ACCORING TO RULES OF MANCALA */
  while(redistribute){
    
    /* REDISTRIBUTION STARTS FROM PLAYER-B PIT CHOICE 

     NOTE - ALL PITS TRAVERSED HERE ARE ON PLAYER B'S SIDE */
    while(i <= num_pits && marblesToMove-- > EMPTY){
      
      /* AS LONG AS THE LAST PIT RECIEVING A MARBLE WAS NOT EMPTY BEFORE
	 GETTING THE LAST MARBLE AND AS LONG AS IT WAS NOT THE PLAYERS 
	 SCORING PIT, ALL MARBLES ARE TAKEN FROM THE PIT THAT LAST 
	 RECIEVED THE MARBLE AND THE REDISTRIBUTION PROCESS IS REPEATED FROM
	 THIS LAST PIT */
      
      if(marblesToMove == EMPTY /* LAST MARBLE */ 
	 && playerB_pits[i] != EMPTY  /* LAST PIT RECIEVING 
					 MARBLE NOT EMPTY */
	 && (i != num_pits) /* NOT PLAYER B'S SCORING PIT */ ){
	
	(playerB_pits[i])++; /* ADD LAST MARBLE TO PIT */
	
	/* REMOVE ALL MARBLES FROM PIT */
	marblesToMove = playerB_pits[i];
	playerB_pits[i] = EMPTY; 
	
	/* REDISTRIBUTION STARTS AT NEXT PIT */
	i++;
	
      }else if /* IF THE LAST MARBLE WAS DROPPED IN AN EMPTY NON-SCORING
		  PIT ON THE PLAYERS SIDE, THAT MARBLE AND ANY MARBLES IN
		  THE OPPOSITE NON-SCORING PIT ARE MOVED TO THE PLAYERS
		  SCORING PIT AND IT IS NOW THE OTHER PLAYERS TURN */
	  
	  (marblesToMove == EMPTY /* LAST MARBLE */
	    && playerB_pits[i] == EMPTY  /* LAST PIT RECIEVING MARBLE
					    IS EMPTY */
	   && i != num_pits /* NOT PLAYER B'S SCORING PIT */ ){
	
	/* PIT IS EMPTY SO INSTEAD OF INCREMENTING THEN DECREMENTING 
	   JUST LEAVE EMPTY AND ADD AN EXTRA MARBLE TO THE #MARBLESTOMOVE
	   REPRESENTING THE LAST MARBLE TO ADD TO THE EMPTY PIT */
	
	marblesToMove = 1; /* THE LAST MARBLE PLUS THE MARBLES IN THE 
			      OPPOSITE NON-SCORING PIT ARE ADDED TO PLAYER B'S
			      SCORING PIT */
	marblesToMove += 
	  playerA_pits[i + 1]; /* OPPOSITE 
				  NON- SCORING PIT */
	
	playerA_pits[i + 1] = EMPTY; /* OPPOSITE
					NON-SCORING
					PIT IS NOW
					EMPTY */
	
	playerB_pits[num_pits] += marblesToMove; /* PLAYER B'S 
						    SCORING PIT */
	
	/* NOW ITS THE OTHER PLAYERS TURN */
	marblesToMove = EMPTY; 
	redistribute = FALSE;
	break;
	
      }else /* NOTE THE ONLY OTHER CASE WHERE THE LAST MARBLE IS DROPPED
	       IN THE PLAYERS SCORING PIT, AND THEN IT IS THE OTHER PLAYERS
	       TURN IS HANDLED NATURALLY BY THE LOGIC ALREADY IN PLACE */
	{	
	  /* NORMAL REDISTRIBUTION PROCESS */
	  (playerB_pits[i++])++; 
	}      
    }
    
    /* REDISTRIBUTION CONTINUES THROUGH PLAYER A'S NON-SCORING PITS IF VALID */
    while(j > SCORING_PIT_A_POSITION && marblesToMove-- > EMPTY){
      
      /* AS LONG AS THE LAST PIT RECIEVING A MARBLE WAS NOT EMPTY BEFORE
	 GETTING THE LAST MARBLE AND AS LONG AS IT WAS NOT THE PLAYERS 
	 SCORING PIT, ALL MARBLES ARE TAKEN FROM THE PIT THAT LAST 
	 RECIEVED THE MARBLE AND THE REDISTRIBUTION PROCESS IS REPEATED FROM
	 THIS LAST PIT */
      
      if(marblesToMove == EMPTY /* LAST MARBLE */ 
	 && playerA_pits[j] != EMPTY  /* LAST PIT RECIEVING 
					 MARBLE NOT EMPTY */ ){
	/* NOT PLAYER B'S SCORING PIT BECAUSE ONLY PLAYER A'S
	   NON SCORING PITS ARE TRAVERSED HERE */ 
	
	(playerA_pits[j])++; /* ADD LAST MARBLE TO PIT */
	
	/* REMOVE ALL MARBLES FROM PIT */
	marblesToMove = playerA_pits[j];
	playerA_pits[j] = EMPTY; 
	
	/* REDISTRIBUTION STARTS AT NEXT PIT */
	j--;
	
      }else{
	/* NORMAL REDISTRIBUTION PROCESS 
	   NOTE - ALL PITS TRAVERSED HERE ARE PLAYER A'S NON SCORING PITS */
	(playerA_pits[j--])++;
      }
    }
    
    /* IF WE STILL HAVE MARBLES TO REDISTRIBUTE START FROM THE SMALLEST VALUE
       PIT IN PLAYER-B'S PITS */
    if(marblesToMove > EMPTY){
      i = STARTING_PIT;
      j = num_pits;
    }else{
      /* IF NOT WE ARE DONE REDISTRIBUTING */
      redistribute = FALSE;
    }
  }
}



