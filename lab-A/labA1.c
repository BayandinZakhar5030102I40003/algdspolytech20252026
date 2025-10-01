#pragma warning(disable : 4996)

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define szE 12
#define SZ (szE * 8 / 10)

typedef struct
{
    int bigdata[szE];
    int siz;
    struct element* next;
} element;

typedef struct
{
    element* start;
    element* end;
    int siz;
} list;

typedef struct
{
    list* list;
    element* elem;
    int i;
} Iterator;

element* createE()
{

    element* ELEM = malloc(sizeof(element));

    if (!ELEM)
    {
        return 0;
    }

    ELEM->siz = 0;
    ELEM->next = NULL;

    return ELEM;
}

int L0(list* List)
{

    List->start = 0;
    List->end = 0;
    List->siz = 0;

    return 0;
}

list* createL()
{
    list* LIST = malloc(sizeof(list));
    if (LIST != 0)
    {
        L0(LIST);
    }
    return LIST;
}

int add(list* list, int num)
{

    if (!list)
    {
        return 0;
    }

    if (!list->start)
    {
        list->start = createE();
        if (!list->start)
        {
            return 0;
        }
        list->end = list->start;
    }

    if (list->end->siz == szE)
    {
        element* Elem = createE();
        if (!Elem)
        {
            return 0;
        }

        int m = szE - SZ;

        for (int i = 0; i <= (m); i++)
        {
            Elem->bigdata[i] = list->end->bigdata[SZ + i];
        }

        list->end->siz = (SZ);
        Elem->siz = m;
        Elem->next = NULL;

        list->end->next = Elem;
        list->end = Elem;

        list->end->bigdata[list->end->siz] = num;
        list->end->siz++;
        list->siz++;
    }
    else
    {
        list->end->bigdata[list->end->siz] = num;
        list->end->siz++;
        list->siz++;
    }

    return 1;
}

void printL(list* list)
{

    element* beg = list->start;
    int numm = 0;

    do
    {
        printf("Ёлемент %d {%d, %d}: [ ", ++numm, beg->siz, szE);
        for (int i = 0; i < beg->siz; i++)
        {
            printf("%d ", beg->bigdata[i]);
        }
        printf("]\n");
        beg = beg->next;

    } while (beg);
}

int findL(list* list, int key)
{

    element* beg = list->start;
    int ind = 0;

    do
    {
        for (int i = 0; i < beg->siz; i++)
        {
            if (beg->bigdata[i] == key)
            {
                return ind;
            }
            ind++;
        }
        beg = beg->next;

    } while (beg);

    return 0;
}

int findE(list* list, int ind, int* el)
{
    element* beg = list->start;
    int el0 = 0;

    do
    {
        if (ind < (el0 + beg->siz))
        {
            *el = beg->bigdata[ind - el0];
            return 1;
        }

        el0 += beg->siz;
        beg = beg->next;

    } while (beg);

    return 0;
}

int deleteE(list* list, int idelem)
{

    element* beg = list->start;
    int count = 1;
    element* rep = 0;

    do
    {
        if (idelem < count + beg->siz)
        {
            int ind = idelem - count;

            for (int i = ind; i < beg->siz - 1; i++)
            {
                beg->bigdata[i] = beg->bigdata[i + 1];
            }
            beg->siz = beg->siz - 1;
            list->siz = list->siz - 1;

            if ((beg->siz < szE) && (beg->next != 0))
            {
                element* new = beg->next;
                int newsz = SZ - beg->siz;
                int tt;
                if (new->siz < newsz)
                {
                    tt = new->siz;
                }
                else
                {
                    tt = newsz;
                }

                for (int i = 0; i < tt; i++)
                {
                    beg->bigdata[beg->siz + i] = new->bigdata[i];
                }

                beg->siz += tt;

                if (tt < new->siz)
                {
                    for (int i = 0; i < new->siz - tt; i++)
                    {
                        new->bigdata[i] = new->bigdata[tt + i];
                    }
                    new->siz -= tt;
                }
                else
                {
                    beg->next = new->next;
                    if (list->end == new)
                    {
                        list->end = beg;
                    }
                    free(new);
                }
            }
            if ((beg->siz == 0) && (list->start != list->end))
            {
                if (rep)
                {
                    rep->next = beg->next;
                }
                else
                {
                    list->start = beg->next;
                }
                if (list->end == beg)
                {
                    list->end = rep;
                }
                free(beg);
            }

            return 1;
        }
        count += beg->siz;
        rep = beg;
        beg = beg->next;
    } while (beg);

    return 0;
}

int countE(list* list)
{
    return list->siz;
}

Iterator createI(list* list)
{
    Iterator iter;
    iter.list = list;
    if (list != NULL)
    {
        iter.elem = list->start;
    }
    else
    {
        iter.elem = 0;
    }
    iter.i = 0;
    return iter;
}

int iterated(Iterator* iter, int* ind)
{

    if (iter->i >= iter->elem->siz)
    {
        iter->elem = iter->elem->next;
        iter->i = 0;

        if (!iter->elem != 0)
        {
            return 0;
        }
    }
    *ind = iter->elem->bigdata[iter->i++];
    return 1;
}

void freel(list* list)
{
    if (!list)
    {
        return 0;
    }

    element* beg = list->start;

    do
    {
        element* next = beg->next;
        free(beg);
        beg = next;
    } while (beg);

    free(list);
}

int main(void)
{
    setlocale(LC_CTYPE, "Russian");
    list* Unlist = createL();

    for (int i = 1; i <= 100; i++)
    {
        add(Unlist, i);
    }

    deleteE(Unlist, 65);
    printL(Unlist);
    // ddd

    return 0;
}

