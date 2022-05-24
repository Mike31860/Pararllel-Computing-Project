#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct player
{
    int id;
    int position;
    int win;
    double timeConsumed;
} Player;

typedef struct obstacule
{
    int id;
    int top;
    int button;
    char type;

} Obstacule;

typedef struct listPlayers
{
    Player *head;
    int length;
} ListPlayers;

typedef struct list
{
    Obstacule *head;
    int length;
} List;

typedef struct Table
{
    ListPlayers *listPlayers;
    List *obstacul;
    int height;
    int weidth;

} Table;

typedef struct nodo
{
    Obstacule obstacule;
    struct nodo *next;
} Nodo;

typedef struct nodo2
{
    Player player;
    struct nodo2 *next;
} Nodo2;

List *obst;
ListPlayers *listPlayers;
ListPlayers *listPlayers2;

Nodo *CreateObstacule(int id, int top, int button, char type)
{
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->obstacule.id = id,
    nodo->obstacule.top = top;
    nodo->obstacule.button = button;
    nodo->obstacule.type = type;
    nodo->next = NULL;
    return nodo;
}

Nodo2 *CreatePlayer(int id, int position, int win, double timeConsumed)
{
    Nodo2 *nodo = (Nodo2 *)malloc(sizeof(Nodo2));
    nodo->player.id = id;
    nodo->player.position = position;
    nodo->player.win = win;
    nodo->player.timeConsumed = timeConsumed;
    nodo->next = NULL;
    return nodo;
}

void deleteNodo(Nodo *nodo)
{
    free(nodo);
}

void insertObstacule(int id, int top, int button, char type)
{
    Nodo *nodo = CreateObstacule(id, top, button, type);
    if (obst == NULL)
    {
        obst = (List *)malloc(sizeof(List));
        obst->length = 0;
        obst->head = NULL;
    }
    if (obst->head == NULL)
    {
        obst->head = nodo;
        obst->length++;
    }
    else
    {
        Nodo *point = obst->head;
        while (point->next)
        {
            point = point->next;
        }
        point->next = nodo;
        obst->length++;
        //  printf("Size %i\n", obst->length);
    }
}

Nodo *obtainObstacule(int id)
{

    if (obst->head == NULL)
    {
        return NULL;
    }
    else
    {
        Nodo *point = obst->head;
        while (point)
        {
            if (point->obstacule.id == id)
            {
                return point;
            }
            else
            {

                point = point->next;
            }
        }

        return point;
    }
}
int split(const char *str, char c, char ***arr)
{
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char **)malloc(sizeof(char *) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char *)malloc(sizeof(char) * token_len);
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char *)malloc(sizeof(char) * token_len);
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;

            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}
void editarJugador(int id, int position, int win)
{

    printf("WELL \n");
    printf("Player to be edited %i has position %i, and has won: %i \n", id, position, win);
    Nodo2 *nodo = CreatePlayer(id, position, win,0);
    // printf("Player %i EDIT  %i  \n ",id,  position);
    printf("HEY %d \n",&listPlayers->length);

    if (&listPlayers->head == NULL)
    {   
        printf("WELL223 \n");
        listPlayers->head = nodo;
    }
    else
    {
        printf("WELL22 \n");
        Nodo2 *puntero = &listPlayers->head;
         printf("AA Player %i has position %i, and has won: %i \n", puntero->player.id, puntero->player.position, puntero->player.win);
        if (id == 0)
        {
            Nodo2 *puntero2 = puntero->next;
            nodo->next = puntero2;
            listPlayers->head = nodo;
            printPlayers2();
        }
        else
        {
            while (puntero->player.id != id)
            {
                puntero = puntero->next;
            }
            Nodo2 *next = puntero->next;
            Nodo2 *before = puntero->next;
            nodo->next = next;
            // printf("-----Player %i postion  %i win: %i \n ",nodo->player.id, nodo->player.position, nodo->player.win);
            // printPlayers();
            Nodo2 *p2 = listPlayers->head;
            while (p2->player.id != id)
            {
                insertPlayer2(p2->player.id, p2->player.position, p2->player.win);
                p2 = p2->next;
            }
            Nodo2 *p3 = listPlayers2->head;
            while (p3->next)
            {
                p3 = p3->next;
            }
            p3->next = nodo;
            //  printf("-Player %i postion  %i win: %i \n ",nodo->player.id, nodo->player.position, nodo->player.win);
            listPlayers = listPlayers2;
            listPlayers2 = NULL;
            // printPlayers();
        }
        ///
    }
}

int contarObstacules()
{
    return obst->length;
}

void printPlayers(ListPlayers *listPlayersTemporal)
{
    if (listPlayersTemporal->head != NULL)
    {

        Nodo2 *point = listPlayersTemporal->head;
        while (point->next)
        {

            printf("Player %i has position %i, and has won: %i \n", point->player.id, point->player.position, point->player.win);
            point = point->next;
        }
    }
    else
    {
        printf("NO Player \n");
    }
}
void printPlayers2()
{
    if (listPlayers->head != NULL)
    {

        Nodo2 *point = listPlayers->head;
        while (point->next)
        {

            printf("Player %i has position %i, and has won: %i , time %f \n", point->player.id, point->player.position, point->player.win, point->player.timeConsumed);
            point = point->next;
        }
    }
    else
    {
        printf("NO Player \n");
    }
}

void insertPlayer(int id, int position, int win, double timeConsumed)
{
    printf("The values are %i,%i,%i\n", id, position, win);
    Nodo2 *nodo = CreatePlayer(id, position, win, timeConsumed);

    if (listPlayers == NULL)
    {
        listPlayers = (ListPlayers *)malloc(sizeof(ListPlayers));
        listPlayers->length = 0;
        listPlayers->head = NULL;
        printf("NO Player \n");
    }
    if (listPlayers->head == NULL)
    {
        listPlayers->head = nodo;
        listPlayers->length++;
        printf("in %d \n",  listPlayers->length);
    }
    else
    {
        Nodo2 *point = listPlayers->head;
        while (point->next)
        {
            point = point->next;
        }
        point->next = nodo;
        listPlayers->length++;
    }
}

void insertPlayer2(int id, int position, int win)
{
    Nodo2 *nodo = CreatePlayer(id, position, win, 0);

    if (listPlayers2 == NULL)
    {
        listPlayers2 = (ListPlayers *)malloc(sizeof(ListPlayers));
        listPlayers2->length = 0;
        listPlayers2->head = NULL;
        // printf("NO Player \n");
    }
    if (listPlayers2->head == NULL)
    {
        listPlayers2->head = nodo;
        listPlayers2->length++;
    }
    else
    {
        Nodo2 *point = listPlayers2->head;
        while (point->next)
        {
            point = point->next;
        }
        point->next = nodo;
        listPlayers2->length++;
    }
}

Nodo2 *obtainPlayer(int id)
{

    if (listPlayers->head == NULL)
    {
        return NULL;
    }
    else
    {
        Nodo2 *point = listPlayers->head;
        while (point)
        {
            if (point->player.id == id)
            {
                return point;
            }
            else
            {

                point = point->next;
            }
        }

        return point;
    }
}

