#include "main.h"

void restart_session_game_state(Session *session)
{
	init_game_state(&session->current_game_state);
}
// to restart session, just call init_game_state to reset everything

void init_session(Session *session)
{
	session->best_score = 0;
	restart_session_game_state(session);
}
// to create a new session, it just sets best_score to 0 and restarts_session
