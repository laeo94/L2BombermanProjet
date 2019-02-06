#ifndef __game_h_LEBLANC_ONG__
#define __game_h_LEBLANC_ONG__

#include <sys/time.h>
#include <poll.h>

#include "load.h"

void explosion(niveau* n);
void pose_bombe(niveau* n, joueur* j);
bool collision(niveau* n, joueur* j, char c);
int game_players(niveau* n_to_change);

#endif
