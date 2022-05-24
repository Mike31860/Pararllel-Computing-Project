#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

int main(int argc, char *argv[])
{
   
    for (int i = 0; i < 7; i++)
    {
     insertPlayer(i, 0, 0);

    }
    editarJugador( 3, 18, 1);
    editarJugador(5, 10, 1);

    printf("First\n"); 
    //printPlayers();

}