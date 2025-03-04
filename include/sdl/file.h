#ifndef FILE_H
#define FILE_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE(file, line) (get_pos((file), (line)) - get_pos((file), (line - 1)))

FILE *open_file(const char *path);
void close_file(FILE *file);

char *get_line(char *path, int line);
char *get_setting(char *path, char *setting);

bool set_value(char *path, int line, int value);
bool set_setting(char *path, char *setting, char *value);
bool set_line(char *path, int line, char *nline);
void copy_file(char *path, char *new_file);

#endif /* FILE_H */