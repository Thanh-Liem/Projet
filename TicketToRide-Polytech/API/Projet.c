#include <stdlib.h>
#include <stdio.h>
#include "TicketToRideAPI.h"
#include "clientAPI.h"
#include "Data.h"
#include "Init.h"
#include "move.h"
#include "Strategy.h"

int main(){

	t_dataMap dataMap;
	t_dataPlayer dataPlayer;
	t_dataTracks dataTracks;
	
	t_move move;
	t_move OurLastMove;
	t_return_code return_code;
	
	t_objective temp_objective[3];
	t_objective Bestpath[20][36];
	
	//InitGame(&dataMap, &dataPlayer, &dataTracks);
	
	Connect();
	
	do{
	
		InitMap(&dataMap, &dataPlayer, &dataTracks);
		InitTracks(&dataMap, &dataTracks, Bestpath);
		InitPlayer(&dataPlayer, &dataMap);

		do{
			printMap();
			
			if(dataPlayer.num_player == dataPlayer.PlayerWhoPlay){
			
				dataPlayer.nb_play++;
				
				//Move(&move); 	
				Fake_IA(&move, &OurLastMove, dataPlayer, dataMap, dataTracks, Bestpath);
				
				dataPlayer.replay = DoReplay(&move, &dataPlayer.nb_play);
				return_code = OurMove(&move);
				EditMove(&move, temp_objective, &dataPlayer, &dataTracks, &dataMap);
			
			}
			/* Opponent move */
			else{
				return_code = getMove(&move, &dataPlayer.replay);		
				EditOpponnentMove(&move, &dataPlayer, &dataTracks, &dataMap);
			}
			
			if( (return_code == NORMAL_MOVE)&&(dataPlayer.replay == 0) ){
				dataPlayer.nb_play = 0;
				dataPlayer.PlayerWhoPlay = !dataPlayer.PlayerWhoPlay;
			}
			
			for(int i=0; i<dataPlayer.Player[dataPlayer.num_player].nb_objectif; i++){
				Strat(dataPlayer.Player[dataPlayer.num_player].arrays_objective[i].city1, dataPlayer.Player[dataPlayer.num_player].arrays_objective[i].city2, dataTracks, Bestpath, dataPlayer, i);
			}
			CheckCompletedObjective(&dataPlayer, dataTracks, Bestpath);		

		}while(return_code == NORMAL_MOVE);
			
		
	if( (return_code == WINNING_MOVE && dataPlayer.PlayerWhoPlay == dataPlayer.num_player) || (return_code == LOOSING_MOVE && dataPlayer.PlayerWhoPlay != dataPlayer.num_player)){
		printf(" We win !\n");
	}
	else{
		printf(" We lose !\n");
	}
	}while(1);		
	
	/* Disconnect from server */
	closeConnection();
	printf("Close Success\n");
	
	return EXIT_SUCCESS;
}
