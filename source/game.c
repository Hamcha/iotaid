#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lualib.h>
#include <lauxlib.h>

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
		case ERR_LUA:
			return "The LUA interpreter encountered one or more errors";
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

	// Create instance
	Game* game = malloc(sizeof(Game));
	if (game == NULL) {
		_errstatus = ERR_OOM;
		return NULL;
	}

	game->config = cfg;

	// Create LUA state
	game->lua = luaL_newstate();
	if (game->lua == NULL) {
		_errstatus = ERR_OOM;
		game_destroy(game);
		return NULL;
	}

	luaL_openlibs(game->lua);

	// Get required fields from config
	Pair* name = config_get(cfg, "title");
	if (name == NULL) {
		_errstatus = ERR_MISCFG;
		game_destroy(game);
		return NULL;
	}
	strncpy(game->name, name->value, 128);

	Pair* gamefile = config_get(cfg, "main");
	if (gamefile == NULL) {
		_errstatus = ERR_MISCFG;
		game_destroy(game);
		return NULL;
	}

	// Load LUA engine
	if (luaL_dofile(game->lua, "engine/boot.lua") == 1) {
		printf("LUA Error encountered: %s\n", lua_tostring(game->lua, -1));
		_errstatus = ERR_LUA;
		game_destroy(game);
		return NULL;
	}

	// Execute game part (LUA game logic)
	char path[256] = "game/";
	strncat(path, gamefile->value, 128);
	if (luaL_dofile(game->lua, path) == 1) {
		printf("LUA Error encountered: %s\n", lua_tostring(game->lua, -1));
		_errstatus = ERR_LUA;
		game_destroy(game);
		return NULL;
	}

	return game;
}

void game_destroy(Game* game) {
	if (game->lua != NULL) {
		lua_close(game->lua);
	}
	if (game->config != NULL) {
		config_destroy(game->config);
	}
	free(game);
}