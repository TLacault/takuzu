#include "takuzu.h"

bool test_move_create() {
    move m = move_create(0, 0, S_ONE, S_EMPTY);
    if (m == NULL)
        return false;
    if (m->row != 0 || m->col != 0 || m->s != S_ONE || m->p != S_EMPTY)
        return false;
    free(m);
    m = NULL;
    return true;
}

bool test_move_delete() {
    move m = move_create(0, 0, S_ONE, S_EMPTY);
    move_delete(m);
    m = NULL;
    if (m != NULL)
        return false;
    return true;
}

bool test_move_row() {
    move m1 = move_create(0, 0, S_ONE, S_EMPTY);
    if (move_row(m1) != 0)
        return false;
    move_delete(m1);
    m1 = NULL;
    move m2 = move_create(10, 10, S_ONE, S_EMPTY);
    if (move_row(m2) != 10)
        return false;
    move_delete(m2);
    m2 = NULL;
    return true;
}

bool test_move_col() {
    move m1 = move_create(0, 0, S_ONE, S_EMPTY);
    if (move_col(m1) != 0)
        return false;
    move_delete(m1);
    m1 = NULL;
    move m2 = move_create(10, 10, S_ONE, S_EMPTY);
    if (move_col(m2) != 10)
        return false;
    move_delete(m2);
    m2 = NULL;
    return true;
}

bool test_move_s() {
    move m1 = move_create(0, 0, S_ONE, S_EMPTY);
    if (move_s(m1) != (square)S_ONE)
        return false;
    move_delete(m1);
    m1 = NULL;
    move m2 = move_create(10, 10, S_ZERO, S_EMPTY);
    if (move_s(m2) != (square)S_ZERO)
        return false;
    move_delete(m2);
    m2 = NULL;
    return true;
}

bool test_move_p() {
    move m1 = move_create(0, 0, S_ONE, S_EMPTY);
    if (move_p(m1) != (square)S_EMPTY)
        return false;
    move_delete(m1);
    m1 = NULL;
    move m2 = move_create(10, 10, S_ZERO, S_IMMUTABLE_ONE);
    if (move_p(m2) != (square)S_IMMUTABLE_ONE)
        return false;
    move_delete(m2);
    m2 = NULL;
    return true;
}

bool test_move_print() {
    move m1 = move_create(0, 0, S_ONE, S_EMPTY);
    move_print(m1);
    move_delete(m1);
    m1 = NULL;
    move m2 = move_create(10, 10, S_ZERO, S_IMMUTABLE_ONE);
    move_print(m2);
    move_delete(m2);
    m2 = NULL;
    return true;
}

/*  USAGE  */
void usage(char *argv[]) {
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

/*  MAIN ROUTINE  */
int main(int argc, char *argv[]) {
    if (argc == 1)
        usage(argv);

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool pass = false;
    if (strcmp("move_create", argv[1]) == 0)
        pass = test_move_create();
    else if (strcmp("move_delete", argv[1]) == 0)
        pass = test_move_delete();
    else if (strcmp("move_row", argv[1]) == 0)
        pass = test_move_row();
    else if (strcmp("move_col", argv[1]) == 0)
        pass = test_move_col();
    else if (strcmp("move_s", argv[1]) == 0)
        pass = test_move_s();
    else if (strcmp("move_p", argv[1]) == 0)
        pass = test_move_p();
    else if (strcmp("move_print", argv[1]) == 0)
        pass = test_move_print();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (pass == true) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}