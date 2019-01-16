#pragma once
#include <assert.h>

typedef char *string;
typedef char boolean;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);

struct U_boolList_ {boolean head; struct U_boolList_* tail;};
typedef struct U_boolList_ *U_boolList;
U_boolList U_BoolList(boolean head, U_boolList tail);
