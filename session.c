#include "main.h"

void restart_session_game_state(Session *session)
{
	restart_game_state(&session->current_game_state);
}
// just restarts the session by setting everything to defualt vals

void init_session(Session *session)
{
	session->best_score = 0;
	init_game_state(&session->current_game_state);
}
// starts a new session
