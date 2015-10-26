#include "game.h"
#include "config.h"
#include <stdlib.h>

GameError _errstatus = ERR_NONE;

const char* game_error() {
	switch (_errstatus) {
		case ERR_NONE:
			return "No error occurred";
		case ERR_OOM:
			return "Out of memory";
		case ERR_CONFIG:
			return "The game configuration file could not be found or is not valid";
		case ERR_MISCFG:
			return "The game configuration file is missing required fields";
		default:
			return "Unknown error";
	}
}

Game* game_create() {
	// Load config
	Config* cfg = config_loadfile("game.cfg");
	if (cfg == NULL) {
		_errstatus = ERR_CONFIG;
		return NULL;
	}

	Game* game = malloc(sizeof(Game));
	if (game == NULL) {
		_errstatus = ERR_OOM;
		return NULL;
	}

	return game;
}

void game_destroy(Game* game) {
	free(game);
}