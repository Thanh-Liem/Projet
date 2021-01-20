void Move(t_move* move);

t_return_code OurMove(t_move* move);

int DoReplay(t_move* move, int* nb_play);
/* Check if we need a replay or not */

void EditMove(t_move* move, t_objective temp_objective[3], t_dataPlayer* dataPlayer, t_dataTracks* dataTracks, t_dataMap* dataMap);
/* Edit our data after we play */

void EditOpponnentMove(t_move* move, t_dataPlayer* dataPlayer, t_dataTracks* dataTracks, t_dataMap* dataMap);
/* Edit our data after the opponnent play */

void CheckCompletedObjective(t_dataPlayer* dataPlayer, t_dataTracks dataTracks, t_objective Bestpath[][36]);
/* Edit our data if we completed an objective */
