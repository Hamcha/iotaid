#ifndef _GAME_H
#define _GAME_H

//! Fatal error types
typedef enum gameerror_t {
	ERR_NONE,
	ERR_OOM,
	ERR_CONFIG,
	ERR_MISCFG
} GameError;

//! Game instance
typedef struct game_t {
	const char* name;
} Game;

/*! \brief Get fatal error
 *
 *  Get the last (and only) fatal error as a humanly readable string
 *
 *  \return Fatal error as a string
 */
const char* game_error();

/*! \brief Create new game instance
 *
 *  Search for the game config file and create a new game instance.
 *  This function will return NULL if a fatal error occurs
 *
 *  \return Game instance if it is successful, NULL otherwise
 */
Game* game_create();

/*! \brief Frees up the resources used by a Game instance
 *
 *  \param Game instance to free
 */
void game_destroy(Game* game);

#endif