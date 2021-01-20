#include <stdlib.h>
#include <stdio.h>
#include "TicketToRideAPI.h"
#include "clientAPI.h"
#include "Data.h"
#include "Init.h"

void InitPlayer(t_dataPlayer* dataPlayer, t_dataMap* dataMap){

	/* Init the struct dataPlayer at the beginning */
	
	dataPlayer->PlayerWhoPlay = 0;
	dataPlayer->replay = 0;
	dataPlayer->nb_play = 0;
	dataPlayer->nb_cards_deck = 110-5-4-4;
	
	dataPlayer->Player[0].nb_wagon = 45;
	dataPlayer->Player[0].nb_objectif = 0;
	
	dataPlayer->Player[1].nb_wagon = 45;
	dataPlayer->Player[1].nb_objectif = 0;
	
	for(int i=0; i<20; i++){
		dataPlayer->Player[dataPlayer->num_player].completedobjective[i] = 0;
	}
	
	for(int i=0; i<10; i++){
		dataPlayer->Player[0].nb_color_cards[i] = 0;
		dataPlayer->Player[1].nb_color_cards[i] = 0;
	}
	for(int i=0; i<4; i++){
		dataPlayer->Player[dataPlayer->num_player].nb_color_cards[dataMap->cards[i]]++;
	}
}

void InitGame(t_dataMap* dataMap, t_dataPlayer* dataPlayer, t_dataTracks* dataTracks){
	
	/* Connect to server */
	connectToServer("li1417-56.members.linode.com", 1234, "T_bot");
	printf("You are in the server\n");
	
	/* Collect data and wait for a game */
	waitForT2RGame( "TRAINING NICE_BOT map=USA timeout=10000", dataMap->gameName, &dataMap->nbCities, &dataMap->nbTracks);	
	printf("Game name = %s\n", dataMap->gameName);	
	printf("nbCities = %d, nbTracks = %d\n\n", dataMap->nbCities, dataMap->nbTracks);
	
	dataMap->tracks = malloc(5*dataMap->nbTracks*sizeof(int));
	
	dataPlayer->num_player = getMap( dataMap->tracks, dataMap->faceUp, dataMap->cards);
	printf("You are the player %d\n", dataPlayer->num_player);
	
}

void Connect(){
	/* just for connect to server */

	connectToServer("li1417-56.members.linode.com", 1234, "T_bot");
	printf("You are in the server\n");
}

void InitMap(t_dataMap* dataMap, t_dataPlayer* dataPlayer, t_dataTracks* dataTracks){
	/* Init the map and bot*/
	
	waitForT2RGame( "TOURNAMENT EISE3 map=USA timeout=10000", dataMap->gameName, &dataMap->nbCities, &dataMap->nbTracks);	
	printf("Game name = %s\n", dataMap->gameName);	
	printf("nbCities = %d, nbTracks = %d\n\n", dataMap->nbCities, dataMap->nbTracks);
	
	dataMap->tracks = malloc(5*dataMap->nbTracks*sizeof(int));
	
	dataPlayer->num_player = getMap( dataMap->tracks, dataMap->faceUp, dataMap->cards);
	printf("You are the player %d\n", dataPlayer->num_player);
	
}

void InitTracks(t_dataMap* dataMap, t_dataTracks* dataTracks, t_objective Bestpath[][35]){

	/* Init the struct dataTracks at the beginning */

	for(int i=0; i< dataMap->nbCities;i++){
		for(int j=0; j< dataMap->nbCities; j++){
		
			dataTracks->lengthTracks[i][j] = 0;
			dataTracks->colorTracks[i][j] = 0;
			dataTracks->doubleTracks[i][j] = 0;
			dataTracks->takenTracks[i][j] = 0;
		}	
	}
	for(int i=0; i<20; i++){
		for(int j=0; j<35; j++){
			Bestpath[i][j].city1 = 0;
			Bestpath[i][j].city2 = 0;
			Bestpath[i][j].score = 0;
		}
	}
	for(int i=0; i < 5*dataMap->nbTracks ; i=i+5){
	
		dataTracks->lengthTracks[dataMap->tracks[i]][dataMap->tracks[i+1]] = dataMap->tracks[i+2];
		dataTracks->colorTracks[dataMap->tracks[i]][dataMap->tracks[i+1]] = dataMap->tracks[i+3];
		dataTracks->doubleTracks[dataMap->tracks[i]][dataMap->tracks[i+1]] = dataMap->tracks[i+4];
		dataTracks->takenTracks[dataMap->tracks[i]][dataMap->tracks[i+1]] = 0;
		
		dataTracks->lengthTracks[dataMap->tracks[i+1]][dataMap->tracks[i]] = dataMap->tracks[i+2];
		dataTracks->colorTracks[dataMap->tracks[i+1]][dataMap->tracks[i]] = dataMap->tracks[i+3];
		dataTracks->doubleTracks[dataMap->tracks[i+1]][dataMap->tracks[i]] = dataMap->tracks[i+4];
		dataTracks->takenTracks[dataMap->tracks[i+1]][dataMap->tracks[i]] = 0;
	}
}
	
	
	
	
	
	
	
	
	
	
