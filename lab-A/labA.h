#pragma once
#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define szE 12
#define SZ (szE * 8 / 10)

typedef struct elementS elementS;
typedef struct listS listS;
typedef struct IteratorS IteratorS;

typedef struct elementS {
  int bigdata[szE];
  int siz;
  struct elementS *next;
} elementS;

typedef struct listS {
  elementS *start;
  elementS *end;
  int siz;
} listS;

typedef struct IteratorS {
  listS *list;
  elementS *elem;
  int i;
} IteratorS;

elementS *createE();
listS *createL();
int L0(listS *List);

int add(listS *list, int num);
int deleteE(listS *list, int idelem);
int findL(listS *list, int key);
int findE(listS *list, int ind, int *el);
int countE(listS *list);

IteratorS createI(listS *list);
int iterated(IteratorS *iter, int *ind);

void printL(listS *list);
void freel(listS *list);

#ifdef __cplusplus
}
#endif

#endif