#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pair* parseline(char* line) {
	if (line == NULL) {
		return NULL;
	}

	char* token;
	Pair* pair = malloc(sizeof(Pair));
	if (pair == NULL) {
		//TODO give an error here
		return NULL;
	}

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
	if (conf == NULL) {
		//TODO will currently give a ERR_CONFIG error, should give ERR_OOM
		fclose(fp);
		return NULL;
	}

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

Pair* config_get(Config* conf, const char* name) {
	Pair* current = conf->first;
	while (current != NULL) {
		if (strncmp(current->name, name, 32) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void config_destroy(Config* conf) {
	Pair* current = conf->first;
	while (current != NULL) {
		Pair* temp = current;
		current = current->next;
		free(temp);
	}
	free(conf);
}