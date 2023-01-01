#include "game_ext.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_struct.h"
#include "move_stack.h"

static void throw_error(char *msg) {
    fprintf(stderr, "[error] %s\n", msg);
    exit(EXIT_FAILURE);
}
static void test_pointer(void *p, char *msg) {
    if (p == NULL)
        throw_error(msg);
}
static void cgame_test(cgame g, char *msg) {
    if (g == NULL)
        throw_error(msg);
}

game game_new_ext(uint nb_rows, uint nb_cols, square *squares, bool wrapping, bool unique) {
    game g = malloc(sizeof(struct game_s));
    test_pointer(g, "game_nex_ext: game_ext malloc failed");
    test_pointer(squares, "game_nex_ext: squares is NULL");
    g->game = malloc(sizeof(square) * (nb_rows * nb_cols));
    test_pointer(g->game, "game_nex_ext: game malloc failed");
    memcpy(g->game, squares, sizeof(square) * (nb_rows * nb_cols));
    g->nb_rows = nb_rows;
    g->nb_cols = nb_cols;
    g->wrapping = wrapping;
    g->unique = unique;
    g->history = ms_create(1);
    g->backup = ms_create(1);
    return g;
}

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping, bool unique) {
    game g = malloc(sizeof(struct game_s));
    test_pointer(g, "game_nex_ext: game_ext malloc failed");
    g->game = malloc(sizeof(square) * (nb_rows * nb_cols));
    test_pointer(g->game, "game_nex_ext: game malloc failed");
    memset(g->game, 0, sizeof(square) * (nb_rows * nb_cols));
    g->nb_rows = nb_rows;
    g->nb_cols = nb_cols;
    g->wrapping = wrapping;
    g->unique = unique;
    g->history = ms_create(1);
    g->backup = ms_create(1);
    return g;
}

uint game_nb_rows(cgame g) {
    cgame_test(g, "g is NULL");
    return g->nb_rows;
}

uint game_nb_cols(cgame g) {
    cgame_test(g, "g is NULL");
    return g->nb_cols;
}

bool game_is_wrapping(cgame g) {
    cgame_test(g, "g is NULL");
    return g->wrapping;
}

bool game_is_unique(cgame g) {
    cgame_test(g, "g is NULL");
    return g->unique;
}

void game_undo(game g) {
    cgame_test(g, "g is NULL");
    if (ms_is_empty(g->history)) {
        printf("game_undo: history is empty\n");
        return;
    }
    game_set_square(g, ms_top_row(g->history), ms_top_col(g->history), ms_top_p(g->history));
    ms_push(g->backup, ms_top(g->history));
    ms_pop(g->history);

}

void game_redo(game g) {
    cgame_test(g, "g is NULL");
    if (ms_is_empty(g->backup)) {
        printf("game_redo: backup is empty\n");
        return;
    }
    game_set_square(g, ms_top_row(g->backup), ms_top_col(g->backup), ms_top_s(g->backup));
    ms_push(g->history, ms_top(g->backup));
    ms_pop(g->backup);
}