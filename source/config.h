#ifndef _CONFIG_H
#define _CONFIG_H

//! Single linked list pair key/value
typedef struct pair_t {
	char name[32];       //!< Key (max 32 chars)
	char value[128];     //!< Value (max 128 chars)
	struct pair_t* next; //!< Next pair
} Pair;

//! Config file
typedef struct config_t {
	Pair* first; //!< First pair
} Config;

/*! \brief Load a config file
 *
 *  Load a config file into an unordered linked list (Config)
 *
 *  \param path Path to the config file
 *  \return Pointer to the loaded config struct, NULL otherwise
 */
Config* config_loadfile(const char* path);

/*! \brief Frees up the resources used by a Config instance
 *
 *  \param Config instance to free
 */
void config_free(Config* config);

#endif