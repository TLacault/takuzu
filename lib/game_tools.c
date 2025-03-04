#include "takuzu.h"

/* ************************************************************************** */
/*                                GAME TOOLS                                  */
/* ************************************************************************** */

game game_load(char *filename) {
    // Open the file
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "[error] cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Read the header
    uint nb_rows, nb_cols, wrapping, unique;
    if (fscanf(f, "%u %u %u %u\n", &nb_rows, &nb_cols, &wrapping, &unique) != 4) {
        fprintf(stderr, "[error] cannot read file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Create a new game
    game g = game_new_empty_ext(nb_rows, nb_cols, wrapping, unique);
    assert(g);

    // Read the grid
    for (uint i = 0; i < g->nb_rows; i++) {
        for (uint j = 0; j < g->nb_cols; j++) {
            char s;
            if (fscanf(f, "%c", &s) != 1) {
                fprintf(stderr, "[error] cannot read file %s\n", filename);
                exit(EXIT_FAILURE);
            }
            if (s == 'e')
                s = S_EMPTY;
            else if (s == 'w')
                s = S_ZERO;
            else if (s == 'W')
                s = S_IMMUTABLE_ZERO;
            else if (s == 'b')
                s = S_ONE;
            else if (s == 'B')
                s = S_IMMUTABLE_ONE;
            else {
                fprintf(stderr, "[error] cannot read file %s\n", filename);
                exit(EXIT_FAILURE);
            }
            SQUARE(g, i, j) = s;
        }
        if (fscanf(f, "\n") != 0)
            fprintf(stderr, "[error] cannot read file %s\n", filename);
    }

    update_counters(g);

    fclose(f);
    return g;
}

/* ************************************************************************** */

void game_save(cgame g, char *filename) {
    char *final_filepath = (char *)malloc(sizeof(char) * (strlen(filename) + strlen("./") + 1));
    strcpy(final_filepath, "./");
    strcat(final_filepath, filename);

    FILE *f = fopen(final_filepath, "w");
    if (f == NULL) {
        free(final_filepath);
        fprintf(stderr, "[error] cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fprintf(f, "%u %u %u %u\n", g->nb_rows, g->nb_cols, g->wrapping, g->unique);
    for (uint i = 0; i < g->nb_rows; i++) {
        for (uint j = 0; j < g->nb_cols; j++) {
            char s;
            if (SQUARE(g, i, j) == S_EMPTY)
                s = 'e';
            else if (SQUARE(g, i, j) == S_ZERO)
                s = 'w';
            else if (SQUARE(g, i, j) == S_IMMUTABLE_ZERO)
                s = 'W';
            else if (SQUARE(g, i, j) == S_ONE)
                s = 'b';
            else if (SQUARE(g, i, j) == S_IMMUTABLE_ONE)
                s = 'B';
            else {
                fprintf(stderr, "[error] cannot write file %s\n", filename);
                exit(EXIT_FAILURE);
            }
            fprintf(f, "%c", s);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    free(final_filepath);
}

/* ************************************************************************** */

bool game_solve(game g) {
    solver s = solver_new(g, true);
    find_solutions(g, s, 0);
    bool solved = false;
    if (s->nb_solutions == 1) {
        solved = true;
        copy_solution(g, s);
    }
    solver_delete(s);
    return solved;
}

/* ************************************************************************** */

uint game_nb_solutions(cgame g) {
    game other = game_copy(g);
    update_counters(other);
    solver s = solver_new(other, false);
    find_solutions(other, s, 0);
    uint nb_solutions = s->nb_solutions;
    solver_delete(s);
    game_delete(other);
    return nb_solutions;
}
