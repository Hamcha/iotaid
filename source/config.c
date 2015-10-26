#include "config.h"
#include <stdio.h>

Pair* parseline(const char* line) {
	if (line == NULL) {
		return NULL;
	}

	char* token;
	Pair* pair = malloc(sizeof(Pair));

	// Get key
	token = strtok(line, "=");
	if (token == NULL) {
		free(pair);
		return NULL;
	}
	strncpy(pair->name, token, 32);

	// Get value
	token = strtok(NULL, "\0");
	if (token == NULL) {
		free(pair);
		return NULL;
	}
	strncpy(pair->value, token, 128);

	return pair;
}

Config* config_loadfile(const char* path) {
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		return NULL;
	}

	Config* conf = malloc(sizeof(Config));

	char line[256];
	Pair* current = NULL;
	while (fgets(line, sizeof(line), fp) != NULL) {
		Pair* p = parseline(line);
		if (p != NULL) {
			if (current == NULL) {
				current = p;
				conf->first = current;
			} else {
				current->next = p;
			}
		}
	}

	fclose(fp);

	return conf;
}

void config_free(Config* conf) {
	Pair* current = conf->first;
	while (current != NULL) {
		Pair* temp = current;
		current = conf->next;
		free(temp);
	}
	free(conf);
}