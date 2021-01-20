int calculescore(int length);
/* Calcule the score of the tracks between two city */

void recursiveStrat_increasing(int city1, int city2, t_dataTracks Tracks, int CurrentLength, int *minLength, t_objective listObjective[], t_objective comparelist[], int* bestscore, int currentscore, t_dataPlayer dataPlayer);
/* Collect the best path while we check for city1 to city2 */

void recursiveStrat_decreasing(int city1, int city2, t_dataTracks Tracks, int CurrentLength, int *minLength, t_objective listObjective[], t_objective comparelist[], int* bestscore, int currentscore, t_dataPlayer dataPlayer);
/* Collect the best path while we check for city2 to city1 */

void LessWagon(int city1, int city2, t_dataTracks Tracks, int CurrentLength, int *minLength, t_objective listObjective[], t_objective comparelist[], int* bestscore, int currentscore, int *minWagon, int CurrentWagon, t_dataPlayer dataPlayer);

void Strat(int city1, int city2, t_dataTracks Tracks, t_objective BestlistObjective[][35], t_dataPlayer dataPlayer, int number);
/* Compared the result of recursiveStrat_increasing and recursiveStrat_decreasing and store the best one in BestlistObjective */

void NewObjective(t_move* move, t_dataPlayer dataPlayer, t_dataTracks Tracks, int tabObjective[3]);
/* Fill tabObjective and choose if we take the objective or not */

void Fake_IA(t_move* move, t_move* OurLastMove, t_dataPlayer dataPlayer, t_dataMap dataMap, t_dataTracks Tracks, t_objective Bestpath[][35]);
/* Take the choice for the move */
