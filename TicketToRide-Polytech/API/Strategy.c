#include <stdlib.h>
#include <stdio.h>
#include "TicketToRideAPI.h"
#include "clientAPI.h"
#include "Data.h"

int calculescore(int length){
	
	if(length == 1){
		return 1;}
	if(length == 2){
		return 2;}
	if(length == 3){
		return 4;}
	if(length == 4){
		return 7;}
	if(length == 5){
		return 10;}
	if(length == 6){
		return 15;}
	return 0;
}

void recursiveStrat_increasing(int city1, int city2, t_dataTracks Tracks, int CurrentLength, int *minLength, t_objective listObjective[], t_objective comparelist[], int* bestscore, int currentscore, t_dataPlayer dataPlayer){
						
	if(Tracks.lengthTracks[city1][city2] > 0 && ((Tracks.takenTracks[city1][city2] == 0)|| (Tracks.takenTracks[city1][city2] == 1 ))){
			
		comparelist[CurrentLength].city1 = city1;
		comparelist[CurrentLength].city2 = city2;
		comparelist[CurrentLength].score = calculescore(Tracks.lengthTracks[city1][city2]);
		
		if(CurrentLength+1 < *minLength){		
				for(int j=0; j<CurrentLength+1; j++){
					listObjective[j].city1 = comparelist[j].city1;
					listObjective[j].city2 = comparelist[j].city2;
					listObjective[j].score = comparelist[j].score;
					*bestscore = currentscore + comparelist[CurrentLength].score;
				}
		}
		else{
			if(currentscore + comparelist[CurrentLength].score > *bestscore){
				for(int j=0; j<CurrentLength+1; j++){
						listObjective[j].city1 = comparelist[j].city1;
						listObjective[j].city2 = comparelist[j].city2;
						listObjective[j].score = comparelist[j].score;
						*bestscore = currentscore + comparelist[CurrentLength].score;
				}
			}
		}
		if(Tracks.takenTracks[city1][city2] == 0 ){
			*minLength = CurrentLength+1;
		}
	}	
	else{	
		for(int i=city1; i<city2+3 && i<35; i++){
			if( Tracks.lengthTracks[city1][i] > 0 && ((Tracks.takenTracks[city1][i] == 0)|| (Tracks.takenTracks[city1][i] == 1 ))){
				comparelist[CurrentLength].city1 = city1;
				comparelist[CurrentLength].city2 = i;
				comparelist[CurrentLength].score = calculescore(Tracks.lengthTracks[city1][i]);
				
				if(Tracks.takenTracks[city1][i] == 0){
					recursiveStrat_increasing(i, city2, Tracks, CurrentLength+1, minLength, listObjective, comparelist, bestscore, currentscore + comparelist[CurrentLength].score, dataPlayer);
				}
				else{
					recursiveStrat_increasing(i, city2, Tracks, CurrentLength, minLength, listObjective, comparelist, bestscore, currentscore + comparelist[CurrentLength].score, dataPlayer);
				}
			}
		}
	}
}

void recursiveStrat_decreasing(int city1, int city2, t_dataTracks Tracks, int CurrentLength, int *minLength, t_objective listObjective[], t_objective comparelist[], int* bestscore, int currentscore, t_dataPlayer dataPlayer){
						
	if(Tracks.lengthTracks[city1][city2] > 0 && ((Tracks.takenTracks[city1][city2] == 0)|| (Tracks.takenTracks[city1][city2] == 1 ))){
			
		comparelist[CurrentLength].city1 = city1;
		comparelist[CurrentLength].city2 = city2;
		comparelist[CurrentLength].score = calculescore(Tracks.lengthTracks[city1][city2]);
		
		if(CurrentLength+1 < *minLength){
				for(int j=0; j<CurrentLength+1; j++){
					listObjective[j].city1 = comparelist[j].city1;
					listObjective[j].city2 = comparelist[j].city2;
					listObjective[j].score = comparelist[j].score;
					*bestscore = currentscore + comparelist[CurrentLength].score;
				}
		}
		else{
			 if(currentscore + comparelist[CurrentLength].score > *bestscore){
				for(int j=0; j<CurrentLength+1; j++){
						listObjective[j].city1 = comparelist[j].city1;
						listObjective[j].city2 = comparelist[j].city2;
						listObjective[j].score = comparelist[j].score;
						*bestscore = currentscore + comparelist[CurrentLength].score;
				}
			}
		}
		if(Tracks.takenTracks[city1][city2] == 0 ){
			*minLength = CurrentLength+1;
		}
	}
	else{	
		for(int i=city2; i>city1-3 && i>0; i--){
			if( Tracks.lengthTracks[i][city2] > 0 && ((Tracks.takenTracks[i][city2] == 0)|| (Tracks.takenTracks[i][city2] == 1 ))){
				comparelist[CurrentLength].city1 = i;
				comparelist[CurrentLength].city2 = city2;
				comparelist[CurrentLength].score = calculescore(Tracks.lengthTracks[i][city2]);
				
				if(Tracks.takenTracks[i][city2] == 0){
					recursiveStrat_decreasing(city1, i, Tracks, CurrentLength+1, minLength, listObjective, comparelist, bestscore, currentscore + comparelist[CurrentLength].score, dataPlayer);
				}
				else{
					recursiveStrat_decreasing(city1, i, Tracks, CurrentLength, minLength, listObjective, comparelist, bestscore, currentscore + comparelist[CurrentLength].score, dataPlayer);
				}
			}
		}
	}
}	
/*
void LessWagon(int city1, int city2, t_dataTracks Tracks, int CurrentLength, int *minLength, t_objective listObjective[], t_objective comparelist[], int* bestscore, int currentscore, int *minWagon, int CurrentWagon, t_dataPlayer dataPlayer){
						
	if(Tracks.lengthTracks[city1][city2] > 0 && ((Tracks.takenTracks[city1][city2] == 0)|| (Tracks.takenTracks[city1][city2] == 1 ))){
			
		comparelist[CurrentLength].city1 = city1;
		comparelist[CurrentLength].city2 = city2;
		comparelist[CurrentLength].score = calculescore(Tracks.lengthTracks[city1][city2]);
		
		if(CurrentWagon + Tracks.lengthTracks[city1][city2] < *minWagon){		
				for(int j=0; j<CurrentLength+1; j++){
					listObjective[j].city1 = comparelist[j].city1;
					listObjective[j].city2 = comparelist[j].city2;
					listObjective[j].score = comparelist[j].score;
					*bestscore = currentscore + comparelist[CurrentLength].score;
					*minWagon = CurrentWagon+Tracks.lengthTracks[city1][city2];
				}
		}
		if(Tracks.takenTracks[city1][city2] == 0 ){
			*minLength = CurrentLength+1;
		}
	}	
	else{	
		for(int i=city1+1; i<city2+3 && i<36; i++){
			if(i != city1){
				if( Tracks.lengthTracks[city1][i] > 0 && ((Tracks.takenTracks[city1][i] == 0)|| (Tracks.takenTracks[city1][i] == 1 ))){
					comparelist[CurrentLength].city1 = city1;
					comparelist[CurrentLength].city2 = i;
					comparelist[CurrentLength].score = calculescore(Tracks.lengthTracks[city1][i]);
					
					if(Tracks.takenTracks[city1][i] == 0){
						LessWagon(i, city2, Tracks, CurrentLength+1, minLength, listObjective, comparelist, bestscore, currentscore + comparelist[CurrentLength].score, minWagon, currentscore + Tracks.lengthTracks[city1][i], dataPlayer);
					}
					else{
						LessWagon(i, city2, Tracks, CurrentLength, minLength, listObjective, comparelist, bestscore, currentscore + comparelist[CurrentLength].score, minWagon, currentscore, dataPlayer);
					}
				}
			}
		}
	}
}*/	
	
void Strat(int city1, int city2, t_dataTracks Tracks, t_objective BestlistObjective[][35], t_dataPlayer dataPlayer, int number){

	int a = city1;
	int b = city2;
	int temp = city2;
	
	int minLength_increasing = 35;
	int minLength_decreasing = 35;	
	
	int Increasing_score = 0;
	int Decreasing_score = 0;
	
	int currentLength = 0;
	int currentscore = 0;
	
	/*
	int minLength_LessWagon = 35;
	int LessWagon_score = 0;
	int minWagon = 100;
	int CurrentWagon = 0;
	int Compare_wagon = 0;
	int Compare_score = 0;
	t_objective listObjective_LessWagon[35];
	*/
	
	t_objective listObjective_increasing[35];
	t_objective listObjective_decreasing[35];	
	t_objective comparelistObjective[35];
	
	if(a > b){
		b = city1;
		a = temp;
	}
	for(int i=0; i<35; i++){
		listObjective_increasing[i].city1 = 0;
		listObjective_increasing[i].city2 = 0;
		listObjective_increasing[i].score = 0;
		
		listObjective_decreasing[i].city1 = 0;
		listObjective_decreasing[i].city2 = 0;
		listObjective_decreasing[i].score = 0;
		
		comparelistObjective[i].city1 = 0;
		comparelistObjective[i].city2 = 0;
		comparelistObjective[i].score = 0;
	}
	
	recursiveStrat_increasing(a, b, Tracks, currentLength, &minLength_increasing , listObjective_increasing, comparelistObjective, &Increasing_score, currentscore, dataPlayer);
	recursiveStrat_decreasing(a, b, Tracks, currentLength, &minLength_decreasing , listObjective_decreasing, comparelistObjective, &Decreasing_score, currentscore, dataPlayer);
	//LessWagon(a, b, Tracks, currentLength, &minLength_LessWagon, listObjective_LessWagon, comparelistObjective, &LessWagon_score, currentscore, &minWagon, CurrentWagon, dataPlayer);
	
	if(minLength_increasing <= minLength_decreasing){
			for(int i=0; i<minLength_increasing; i++){
				BestlistObjective[number][i].city1 = listObjective_increasing[i].city1;
				BestlistObjective[number][i].city2 = listObjective_increasing[i].city2;
				BestlistObjective[number][i].score = listObjective_increasing[i].score;
			}
	}
	else{
		if(Increasing_score >= Decreasing_score){
			for(int i=0; i<minLength_increasing; i++){
				BestlistObjective[number][i].city1 = listObjective_increasing[i].city1;
				BestlistObjective[number][i].city2 = listObjective_increasing[i].city2;
				BestlistObjective[number][i].score = listObjective_increasing[i].score;
			}
		}
		else{
			for(int i=0; i<minLength_decreasing; i++){
				BestlistObjective[number][i].city1 = listObjective_decreasing[i].city1;
				BestlistObjective[number][i].city2 = listObjective_decreasing[i].city2;
				BestlistObjective[number][i].score = listObjective_decreasing[i].score;
			}
		}
	}
	/*
	for(int i=0; BestlistObjective[number][i].score != 0; i++){
		Compare_wagon = Compare_wagon + Tracks.lengthTracks[BestlistObjective[number][i].city1][BestlistObjective[number][i].city2];
		Compare_score = Compare_score + BestlistObjective[number][i].score;
	}
	if((Compare_score + dataPlayer.Player[dataPlayer.num_player].arrays_objective[number].score)*1.0/Compare_wagon > (LessWagon_score+ dataPlayer.Player[dataPlayer.num_player].arrays_objective[number].score)*1.0/minWagon){
		for(int i=0; i<minLength_LessWagon; i++){
			BestlistObjective[number][i].city1 = listObjective_LessWagon[i].city1;
			BestlistObjective[number][i].city2 = listObjective_LessWagon[i].city2;
			BestlistObjective[number][i].score = listObjective_LessWagon[i].score;
		}
		for(int i=minLength_LessWagon; i<35; i++){
			BestlistObjective[number][i].city1 = 0;
			BestlistObjective[number][i].city2 = 0;
			BestlistObjective[number][i].score = 0;
		}
	}
	*/
}			

void NewObjective(t_move* move, t_dataPlayer dataPlayer, t_dataTracks Tracks, int tabObjective[3]){
	
	t_objective temp[3]; 
	t_objective pathObjective[3][35];
	int TotalScore[] = {0, 0, 0};
	int TotalWagon[] = {0, 0, 0};
	float ScorePerWagon[] = {0, 0, 0};
	
	for(int i=0; i<3; i++){
		temp[i].city1 = move->drawObjectives.objectives[i].city1;
		temp[i].city2 = move->drawObjectives.objectives[i].city2;
		temp[i].score = move->drawObjectives.objectives[i].score;
		
		Strat(temp[i].city1, temp[i].city2, Tracks, pathObjective, dataPlayer, i);
		
		for(int j=0; pathObjective[i][j].score != 0; j++){
			TotalScore[i] = TotalScore[i] + temp[i].score;
			if(Tracks.takenTracks[pathObjective[i][j].city1][pathObjective[i][j].city2] != 1){
				TotalScore[i] = TotalScore[i] + pathObjective[i][j].score;
				TotalWagon[i] = TotalWagon[i] + Tracks.lengthTracks[pathObjective[i][j].city1][pathObjective[i][j].city2];
			}
		}
		
		if(TotalWagon[i] > dataPlayer.Player[dataPlayer.num_player].nb_wagon-1){
			tabObjective[i] = 0;	/* If we don't have the amount of wagon, we don't take the objective */
		}
		else{
			tabObjective[i] = 1;	/* If we have the amount of wagon, we take the objective */
		}
	}
	
	for(int i=0; i<3; i++){
		ScorePerWagon[i] = TotalScore[i]*1.0 / TotalWagon[i];
	}
	
	if(tabObjective[0] + tabObjective[1] + tabObjective[2] == 1){
		/* If we can only take one objective, we take it */
		
		return;
	}
	if(tabObjective[0] == 0 && tabObjective[1] == 0 && tabObjective[2] == 0){
		if(TotalWagon[0] < TotalWagon[1] && TotalWagon[0] < TotalWagon[2]){
			tabObjective[0] = 1;
			return;
		}
		else if(TotalWagon[1] < TotalWagon[0] && TotalWagon[1] < TotalWagon[2]){
			tabObjective[1] = 1;
			return;
		}
		else{
			tabObjective[2] = 1;
			return;
		}
	}
	
	if(tabObjective[0] == 1 && tabObjective[1] == 1 && tabObjective[2] == 1){
		if(ScorePerWagon[0] < ScorePerWagon[1] && ScorePerWagon[0] < ScorePerWagon[2]){
			tabObjective[0] = 0;
			return;
		}
		else if(ScorePerWagon[1] < ScorePerWagon[0] && ScorePerWagon[1] < ScorePerWagon[2]){
			tabObjective[1] = 0;
			return;
		}
		else{
			tabObjective[2] = 0;
			return;
		}
	}
	
	for(int i=0; i<3; i++){
		if(tabObjective[i] == 1){
			for(int j=i+1; j<3; j++){
				if(tabObjective[j] == 1){
					if(TotalWagon[i] + TotalWagon[j] > dataPlayer.Player[dataPlayer.num_player].nb_wagon){
						if( ScorePerWagon[i] > ScorePerWagon[j]){
							tabObjective[i] = 1;
							tabObjective[j] = 0;
							return;
						}
						else{
							tabObjective[i] = 0;
							tabObjective[j] = 1;
							return;
						}
					}
					else{
						tabObjective[i] = 1;
						tabObjective[j] = 1;
						return;
					}
				}
			}
		}
	}
}
				
void Fake_IA(t_move* move, t_move* OurLastMove, t_dataPlayer dataPlayer, t_dataMap dataMap, t_dataTracks Tracks, t_objective Bestpath[][35]){

	int CheckAllObjective = 1;	/* 1 if we completed all our objective, else 0 */
	int tabObjective[3];
	int NumberLocomotive = dataPlayer.Player[dataPlayer.num_player].nb_color_cards[9];
	int temp1 = 0; 
	int temp2 = 0;
	int temp3 = 0;
	int temp4 = 0;
	int Index, NotInIndex;
	
	for(int i=0; i<dataPlayer.Player[dataPlayer.num_player].nb_objectif; i++){			/* Check if we have completed all our objective or not */
		if(dataPlayer.Player[dataPlayer.num_player].completedobjective[i] != 1){
			CheckAllObjective = 0;													/* Collect the first index of the objective that we don't completed */
			Index = i;
			break;
		} 
	}
		
	if( ((OurLastMove->type == DRAW_CARD) || (OurLastMove->type == DRAW_BLIND_CARD)) && dataPlayer.replay == 1){
	
		move->type = DRAW_BLIND_CARD;
		OurLastMove->type = DRAW_BLIND_CARD;
		return;
	}
	
	else if(OurLastMove->type == DRAW_OBJECTIVES){										/* If we have DRAW_OBJECTIVE on our last move, we choose the objective to keep */
		
		move->type = CHOOSE_OBJECTIVES;
		OurLastMove->type = CHOOSE_OBJECTIVES;
		
		if(dataPlayer.Player[dataPlayer.num_player].nb_objectif == 0){
			move->chooseObjectives.chosen[0] = 1;
			move->chooseObjectives.chosen[1] = 1;
			move->chooseObjectives.chosen[2] = 1;
		}
		else{		
			NewObjective(move, dataPlayer, Tracks, tabObjective);
			for(int i=0; i<3; i++){
				move->chooseObjectives.chosen[i] = tabObjective[i];
			}
		}
		return;
	}
	
	else if( ((dataPlayer.Player[dataPlayer.num_player].nb_objectif == 0) || (CheckAllObjective == 1))&&(dataPlayer.Player[dataPlayer.num_player].nb_wagon > 6)){				
	/* If we don't have objective or we complete all our objective, we pick objective*/
		
		move->type = DRAW_OBJECTIVES;
		OurLastMove->type = DRAW_OBJECTIVES;
		return;
	}
		
	else{
		// ####################
		for(int i=0; Bestpath[Index][i].score != 0 && i<35; i++){
			if(Tracks.takenTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] != 1){
				if(Tracks.colorTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] == MULTICOLOR){
					for(int j=1; j<9; j++){
						if(dataPlayer.Player[dataPlayer.num_player].nb_color_cards[j] >= Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]){
							if(temp2 < dataPlayer.Player[dataPlayer.num_player].nb_color_cards[j]){
								temp1 = j;
								temp2 = dataPlayer.Player[dataPlayer.num_player].nb_color_cards[j];
							}
						}
									
						if(dataPlayer.Player[dataPlayer.num_player].nb_color_cards[j] + NumberLocomotive >= Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]){
							if(temp4 < dataPlayer.Player[dataPlayer.num_player].nb_color_cards[j]){
								temp3 = j;
								temp4 = dataPlayer.Player[dataPlayer.num_player].nb_color_cards[j];
							}
						}												
					}
					
					if(dataPlayer.Player[dataPlayer.num_player].nb_color_cards[temp1] >= Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] && Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_wagon){
									
							move->type = CLAIM_ROUTE;
							OurLastMove->type = CLAIM_ROUTE;
							move->claimRoute.city1 = Bestpath[Index][i].city1;
							move->claimRoute.city2 = Bestpath[Index][i].city2;
							move->claimRoute.color = temp1;
							move->claimRoute.nbLocomotives = 0;
							return;
					}
					if(dataPlayer.Player[dataPlayer.num_player].nb_color_cards[temp3] + NumberLocomotive >= Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] && Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_wagon){
									
							move->type = CLAIM_ROUTE;
							OurLastMove->type = CLAIM_ROUTE;
							move->claimRoute.city1 = Bestpath[Index][i].city1;
							move->claimRoute.city2 = Bestpath[Index][i].city2;
							move->claimRoute.color = temp3;
							move->claimRoute.nbLocomotives = Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] - dataPlayer.Player[dataPlayer.num_player].nb_color_cards[temp3];
					}
				}				
				else{
								
					if(Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_color_cards[Tracks.colorTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]] && Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_wagon){
											
						/* If we have enough wagon of the first color we use it */
											
						move->type = CLAIM_ROUTE;
						OurLastMove->type = CLAIM_ROUTE;
						move->claimRoute.city1 = Bestpath[Index][i].city1;
						move->claimRoute.city2 = Bestpath[Index][i].city2;
						move->claimRoute.color = Tracks.colorTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2];
						move->claimRoute.nbLocomotives = 0;
						return;
					}
										
					else if(Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_color_cards[Tracks.doubleTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]] && Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_wagon){
											
						/* else If we have enough wagon of the second color we use it */
											
						move->type = CLAIM_ROUTE;
						OurLastMove->type = CLAIM_ROUTE;
						move->claimRoute.city1 = Bestpath[Index][i].city1;
						move->claimRoute.city2 = Bestpath[Index][i].city2;
						move->claimRoute.color = Tracks.doubleTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2];
						move->claimRoute.nbLocomotives = 0;	
						return;				
					}	
										
					else if(Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_color_cards[Tracks.colorTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]] + NumberLocomotive && Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_wagon){
										
						/* else If we have enough wagon of the first color + locomotive we use it */
											
						move->type = CLAIM_ROUTE;
						OurLastMove->type = CLAIM_ROUTE;
						move->claimRoute.city1 = Bestpath[Index][i].city1;
						move->claimRoute.city2 = Bestpath[Index][i].city2;
						move->claimRoute.color = Tracks.colorTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2];
						move->claimRoute.nbLocomotives = Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] - dataPlayer.Player[dataPlayer.num_player].nb_color_cards[Tracks.colorTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]];
						return;
					}
										
					else if(Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_color_cards[Tracks.doubleTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]] + NumberLocomotive && Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_wagon){
										
						/* else If we have enough wagon of the second color + locomotive we use it */
											
						move->type = CLAIM_ROUTE;
						OurLastMove->type = CLAIM_ROUTE;
						move->claimRoute.city1 = Bestpath[Index][i].city1;
						move->claimRoute.city2 = Bestpath[Index][i].city2;
						move->claimRoute.color = Tracks.doubleTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2];
						move->claimRoute.nbLocomotives = Tracks.lengthTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] - dataPlayer.Player[dataPlayer.num_player].nb_color_cards[Tracks.doubleTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]];
						return;
					}
				}
			}
		}				
		
		for(int i=0; Bestpath[Index][i].score != 0 && i<35; i++){
			if( Tracks.takenTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2] != 1){					
				for(int j=0; j<5; j++){
					if(dataMap.faceUp[j] != 9){
						if(dataMap.faceUp[j] == Tracks.colorTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]){
									
						move->type = DRAW_CARD;
						OurLastMove->type = DRAW_CARD;
						move->drawCard.card = dataMap.faceUp[j];
						return;
						}									
						else if(dataMap.faceUp[j] == Tracks.doubleTracks[Bestpath[Index][i].city1][Bestpath[Index][i].city2]){
										
						move->type = DRAW_CARD;
						OurLastMove->type = DRAW_CARD;
						move->drawCard.card = dataMap.faceUp[j];
						return;
						}
					}
				}
			}
		}
		
		// ####################
	
		for(int k=Index+1; k<dataPlayer.Player[dataPlayer.num_player].nb_objectif; k++){
			if(dataPlayer.Player[dataPlayer.num_player].completedobjective[k] == 0){
				for(int i=0; Bestpath[k][i].score != 0 && i<35; i++){
					if(Tracks.takenTracks[Bestpath[k][i].city1][Bestpath[k][i].city2] != 1){
					
						NotInIndex = 0;
						for(int j=0; Bestpath[Index][j].score != 0 && j<35; j++){
							if(Tracks.takenTracks[Bestpath[Index][j].city1][Bestpath[Index][j].city2] != 1 && Tracks.colorTracks[Bestpath[Index][j].city1][Bestpath[Index][j].city2] == Tracks.colorTracks[Bestpath[k][i].city1][Bestpath[k][i].city2]){
								NotInIndex = 1;
							}
						}
						
						if(NotInIndex == 0){
							if(Tracks.lengthTracks[Bestpath[k][i].city1][Bestpath[k][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_color_cards[Tracks.colorTracks[Bestpath[k][i].city1][Bestpath[k][i].city2]] && Tracks.lengthTracks[Bestpath[k][i].city1][Bestpath[k][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_wagon){
											
								/* If we have enough wagon of the first color we use it */
											
								move->type = CLAIM_ROUTE;
								OurLastMove->type = CLAIM_ROUTE;
								move->claimRoute.city1 = Bestpath[k][i].city1;
								move->claimRoute.city2 = Bestpath[k][i].city2;
								move->claimRoute.color = Tracks.colorTracks[Bestpath[k][i].city1][Bestpath[k][i].city2];
								move->claimRoute.nbLocomotives = 0;
								return;
							}
										
							else if(Tracks.lengthTracks[Bestpath[k][i].city1][Bestpath[k][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_color_cards[Tracks.doubleTracks[Bestpath[k][i].city1][Bestpath[k][i].city2]] && Tracks.lengthTracks[Bestpath[k][i].city1][Bestpath[k][i].city2] <= dataPlayer.Player[dataPlayer.num_player].nb_wagon){
											
								/* else If we have enough wagon of the second color we use it */
											
								move->type = CLAIM_ROUTE;
								OurLastMove->type = CLAIM_ROUTE;
								move->claimRoute.city1 = Bestpath[k][i].city1;
								move->claimRoute.city2 = Bestpath[k][i].city2;
								move->claimRoute.color = Tracks.doubleTracks[Bestpath[k][i].city1][Bestpath[k][i].city2];
								move->claimRoute.nbLocomotives = 0;	
								return;				
							}									
						}
					}
				}
			}
		}
	}
	
	for(int k=Index; k<dataPlayer.Player[dataPlayer.num_player].nb_objectif; k++){
		if(dataPlayer.Player[dataPlayer.num_player].completedobjective[k] == 0){
			for(int i=0; Bestpath[k][i].score != 0 && i<35; i++){
				if( Tracks.takenTracks[Bestpath[k][i].city1][Bestpath[k][i].city2] != 1){					
					for(int j=0; j<5; j++){
						if(dataMap.faceUp[j] != 9){
							if(dataMap.faceUp[j] == Tracks.colorTracks[Bestpath[k][i].city1][Bestpath[k][i].city2]){
										
								move->type = DRAW_CARD;
								OurLastMove->type = DRAW_CARD;
								move->drawCard.card = dataMap.faceUp[j];
								return;
							}
										
							else if(dataMap.faceUp[j] == Tracks.doubleTracks[Bestpath[k][i].city1][Bestpath[k][i].city2]){
										
								move->type = DRAW_CARD;
								OurLastMove->type = DRAW_CARD;
								move->drawCard.card = dataMap.faceUp[j];
								return;
							}
						}
					}
				}
			}
		}
	}
	move->type = DRAW_BLIND_CARD;
	OurLastMove->type = DRAW_BLIND_CARD;
	return;
}
			
			
