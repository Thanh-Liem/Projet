typedef struct{

	char gameName[50];
	int nbCities;
	int nbTracks;
	int* tracks;
	t_color faceUp[5];
	t_color cards[4];
}t_dataMap;

typedef struct{

	int nb_wagon;
	int nb_color_cards[10];
	int nb_objectif;
	int completedobjective[20]; 	/* 1 for completed objective else 0 */
	t_objective arrays_objective[20];
}t_Player;
	
typedef struct{

	int num_player;		/* Our number */
	int PlayerWhoPlay;
	int nb_cards_deck;
	
	t_Player Player[2];				
	int replay;
	int nb_play;
}t_dataPlayer;

typedef struct{
	
	int lengthTracks[36][36];
	t_color colorTracks[36][36];
	int doubleTracks[36][36];
	int takenTracks[36][36];		/* 1 if the city is taken by us, -1 if the citty is taken by the opponent, else 0 */
}t_dataTracks;
	
