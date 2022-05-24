#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Player{
    int id;
    int position;
    int win;
} Player;

struct Obstacule{
    int id;
    int top;
    int button;
    char type;

};

typedef struct listPlayers{
    Player* head;
    int length;
} ListPlayers;

typedef struct list{
    Obstacule* head;
    int length;
} List;


typedef struct Table{
    ListPlayers listPlayers;
    List obstacul;
    int height;
    int weidth;
    
} Table;

typedef struct nodo {
    Obstacule obstacule;
    struct nodo* next;
} Nodo;

typedef struct nodo2 {
    Player player;
    struct nodo2* next;
} Nodo2;







