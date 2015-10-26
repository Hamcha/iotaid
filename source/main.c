#include <stdio.h>
#include "term.h"
#include "game.h"

int running;

void loop() {
}

int main() {
	printf("IOTAID - Bootstrap\n");

	Game* game = game_create();
	if (game == NULL) {
		fprintf(stderr, game_error());
		return 1;
	}

	printf(" - Game loaded: %s", game->name);

	running = 1;
	term_blink(0);
	term_clear();
	while(running) {
		loop();
	}

	game_destroy(game);
	return 0;
}