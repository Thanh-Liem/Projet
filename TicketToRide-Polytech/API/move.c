#include <stdlib.h>
#include <stdio.h>
#include "TicketToRideAPI.h"
#include "clientAPI.h"
#include "Data.h"
#include "move.h"

void Move(t_move* move){

	printf("Choose an action\n");
	printf("1. Claim a route\n");
	printf("2. Draw a blind card in the deck\n");
	printf("3. Draw a card from the 5 reveals cards\n");
	printf("4. Draw objectives \n");
	printf("5. Choose an objectives \n");
	
	scanf("%d", &move->type);
	
	if(move->type == CLAIM_ROUTE){
		printf("Give name of city1, city2, number of the color and number of locomotives separate by a space:\n");
		scanf("%d %d %d %d", &move->claimRoute.city1, &move->claimRoute.city2, &move->claimRoute.color, &move->claimRoute.nbLocomotives);		 
	}
	
	else if(move->type == DRAW_CARD){
		printf("Give the color of the card:\n");
		scanf("%d", &move->drawCard.card);	
	}
	
	else if(move->type == CHOOSE_OBJECTIVES){
		printf("For all your objective, put 1 to choose it or 0 to return it to the deck:\n");
		scanf("%d %d %d", &move->chooseObjectives.chosen[0], &move->chooseObjectives.chosen[1],
		&move->chooseObjectives.chosen[2]);
	}	
}

t_return_code OurMove(t_move* move){

	t_return_code temp;
	
	if(move->type == CLAIM_ROUTE){
		return claimRoute(move->claimRoute.city1, move->claimRoute.city2, 
		move->claimRoute.color, move->claimRoute.nbLocomotives);
	 }
	if(move->type == DRAW_BLIND_CARD){
		return drawBlindCard(&move->drawBlindCard.card);
	}
	if(move->type == DRAW_CARD){
		return drawCard(move->drawCard.card, move->drawCard.faceUp);
	}
	if(move->type == DRAW_OBJECTIVES){	
		temp = drawObjectives(move->drawObjectives.objectives);	
		for(int i=0; i<3; i++){
			printf("%d : city %d to city %d\n", i, move->drawObjectives.objectives[i].city1,
			move->drawObjectives.objectives[i].city2);
		}
		return temp;
	}
	if(move->type == CHOOSE_OBJECTIVES){
		return chooseObjectives(move->chooseObjectives.chosen);
	}
	
	return EXIT_FAILURE;
}
	
int DoReplay(t_move* move, int* nb_play){

	/* Check if the player have to replay or not */
	
	int replay = 0;

	if((move->type == DRAW_OBJECTIVES)&&(*nb_play == 1)){
		nb_play++;
		replay = 1;
	}
	else if((move->type == DRAW_BLIND_CARD)&&(*nb_play == 1)){
		nb_play++;
		replay = 1;
	}
	else if((move->type == DRAW_CARD && move->drawCard.card != MULTICOLOR)&&(*nb_play == 1)){
		nb_play++;
		replay = 1;
	}
	return replay;
}	
	
void EditMove(t_move* move, t_objective temp_objective[3], t_dataPlayer* dataPlayer, t_dataTracks* dataTracks, t_dataMap* dataMap){

	/* Edit our data after we play */

	if((move->type == DRAW_BLIND_CARD)||(move->type == DRAW_CARD)){
			
		if(move->type == DRAW_BLIND_CARD){
			dataPlayer->Player[dataPlayer->num_player].nb_color_cards[move->drawBlindCard.card]++;
			dataPlayer->nb_cards_deck--;
		}
		if(move->type == DRAW_CARD){
			dataPlayer->Player[dataPlayer->num_player].nb_color_cards[move->drawCard.card]++;
			dataPlayer->nb_cards_deck--;
			for(int i=0; i<5; i++){
				dataMap->faceUp[i] = move->drawCard.faceUp[i];
			}
		}
	}
			
	else if(move->type == CLAIM_ROUTE){
	
		dataTracks->takenTracks[move->claimRoute.city1][move->claimRoute.city2] = 1;
		dataTracks->takenTracks[move->claimRoute.city2][move->claimRoute.city1] = 1;
		
		dataPlayer->Player[dataPlayer->num_player].nb_wagon = dataPlayer->Player[dataPlayer->num_player].nb_wagon - dataTracks->lengthTracks[move->claimRoute.city1][move->claimRoute.city2];	
			
		dataPlayer->Player[dataPlayer->num_player].nb_color_cards[move->claimRoute.color] = dataPlayer->Player[dataPlayer->num_player].nb_color_cards[move->claimRoute.color] - dataTracks->lengthTracks[move->claimRoute.city1][move->claimRoute.city2] + move->claimRoute.nbLocomotives;
		dataPlayer->Player[dataPlayer->num_player].nb_color_cards[9] = dataPlayer->Player[dataPlayer->num_player].nb_color_cards[9] - move->claimRoute.nbLocomotives;
	}
					
	else if(move->type == DRAW_OBJECTIVES){
		temp_objective[0] = move->drawObjectives.objectives[0];
		temp_objective[1] = move->drawObjectives.objectives[1];
		temp_objective[2] = move->drawObjectives.objectives[2];
	}
			
	else if(move->type == CHOOSE_OBJECTIVES){
		
		for(int i; i<3; i++){	
			if(move->chooseObjectives.chosen[i] == 1){
				dataPlayer->Player[dataPlayer->num_player].nb_objectif++;
						
				dataPlayer->Player[dataPlayer->num_player].arrays_objective[dataPlayer->Player[dataPlayer->num_player].nb_objectif-1].city1 = temp_objective[i].city1;
				dataPlayer->Player[dataPlayer->num_player].arrays_objective[dataPlayer->Player[dataPlayer->num_player].nb_objectif-1].city2 = temp_objective[i].city2;
				dataPlayer->Player[dataPlayer->num_player].arrays_objective[dataPlayer->Player[dataPlayer->num_player].nb_objectif-1].score = temp_objective[i].score;
			}
		}
	}
	
}

void EditOpponnentMove(t_move* move, t_dataPlayer* dataPlayer, t_dataTracks* dataTracks, t_dataMap* dataMap){

	/* Edit our data after the opponent play */

	if((move->type == DRAW_BLIND_CARD)||(move->type == DRAW_CARD)){			
		dataPlayer->nb_cards_deck--;
		if(move->type == DRAW_CARD){
			for(int i=0; i<5; i++){
				dataMap->faceUp[i] = move->drawCard.faceUp[i];
			}	
		}
	}		
	if(move->type == CLAIM_ROUTE){
		dataTracks->takenTracks[move->claimRoute.city1][move->claimRoute.city2] = -1;
		dataTracks->takenTracks[move->claimRoute.city2][move->claimRoute.city1] = -1;		
	}
}

void CheckCompletedObjective(t_dataPlayer* dataPlayer, t_dataTracks dataTracks, t_objective Bestpath[][35]){
	
	/* Edit if we completed an objective */
	
	int Check;
	
	for(int i=0; i<dataPlayer->Player[dataPlayer->num_player].nb_objectif; i++){
		Check = 1;
		for(int j=0; Bestpath[i][j].score > 0; j++){
			if(dataTracks.takenTracks[Bestpath[i][j].city1][Bestpath[i][j].city2] != 1){
				Check = 0;
				dataPlayer->Player[dataPlayer->num_player].completedobjective[i] = 0;
			}
		}
		if(Check == 1){
			dataPlayer->Player[dataPlayer->num_player].completedobjective[i] = 1;
		}
	}
}





	
