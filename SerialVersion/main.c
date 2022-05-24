#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include <time.h>

float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

int main(int argc, char *argv[])
{

  int players = 61;

  Table *table = (Table *)malloc(sizeof(Table));
  table->height = 15;
  table->weidth = 15;

  char *obs = "3:31,8:36,13:41,16:32,17:48,20:49,21:37,22:53,25:54,26:42,27:58,30:59,78:106,83:111,88:116,91:107,92:123,96:112,97:128,101:117,102:133,153:181-4:34,9:39,14:44,18:47,23:52,28:57,46:62,50:64,51:67,55:69,56:72,60:74,79:109,84:114,89:119,93:122,98:127,103:132,121:137,125:139,126:142,130:144";
  int i;

  int c = 0;
  char **arr = NULL;
  c = split(obs, '-', &arr);
  printf("found %d tokens.\n", c);
  // for (i = 0; i < c; i++)
  //    printf("string #%d: %s\n", i, arr[i]);

  int c2 = 0;
  char **scalars = NULL;
  c2 = split(arr[0], ',', &scalars);

  int j;
  for (j = 0; j < c2; j++)
    printf("Scalars #%d: %s\n", j, scalars[j]);

  int c3 = 0;
  char **snakes = NULL;
  c3 = split(arr[1], ',', &snakes);
  int m;

  //  for (m = 0; m < c3; m++)
  // printf("Snakes #%d: %s\n", m, snakes[m]);

  // printf("Size scalars: %i\n", sizeof scalars);
  // printf("Size snakes: %i\n", sizeof snakes);
  for (int g = 0; g < 4; g++)
  {
    int l;
    int c4 = 0;
    char **xy = NULL;
    c4 = split(scalars[g], ':', &xy);
    // for (l = 0; l < c4; l++)
    //   printf("-------\n");
    insertObstacule(g, strtol(xy[0], NULL, 10), strtol(xy[1], NULL, 10), 'E');
  }
  // printf("Size %i\n", obst->length);
  for (int i = 0; i < 4; i++)
  {
    int h;
    int c4 = 0;
    char **xy = NULL;
    c4 = split(snakes[i], ':', &xy);
    // for (h = 0; h < c4; h++)
    // printf("--------\n");
    insertObstacule(i + 4, strtol(xy[0], NULL, 10), strtol(xy[1], NULL, 10), 'E');
  }
  // printf("Elements %i:\n", obst->length);
  table->obstacul = obst;
  char *filename = "input.txt";
  FILE *Input = fopen(filename, "r");
  if (Input == NULL)
  {
    perror("Unable to open the file");
    exit(1);
  }
  char line[100];
  while (fgets(line, sizeof(line), Input))
  {
    char *id = strtok(line, ",");
    char *position = strtok(NULL, ",");
    char *win = strtok(NULL, ",");
    int c = 0;
    char **arr = NULL;
    split(id, ' ', &arr);
    char **arr2 = NULL;
    c = split(position, ' ', &arr2);
    char **arr3 = NULL;
    split(win, ' ', &arr3);
    insertPlayer(strtol(arr[0], NULL, 10), strtol(arr2[0], NULL, 10), strtol(arr3[0], NULL, 10));
  }

  // Llenar el número de jugadores en el tablero

  table->listPlayers = listPlayers;

  // printf("Players in table %i:\n", table->listPlayers->length);
  FILE *fp;
  fp = fopen("Results.txt", "w");
  if (fp == NULL)
  {
    printf("Error!");
    exit(1);
  }
  fprintf(fp, "Serial Version of the Program \n");
  int count = 0;
  struct timeval start, end;
  gettimeofday(&start, NULL);
  while (count != table->listPlayers->length)
  {
    int l;

    for (l = 0; l < table->listPlayers->length; l++)
    {
      if (obtainPlayer(l)->player.win != 1)
      {
        // 3:11,10:12,9:18,6:17-4:14,8:19,20:22,16:24
        // 3:31,8:36,13:41,16:32,17:48,20:49,21:37,22:53,25:54,26:42,27:58,30:59,78:106,83:111,88:116,91:107,92:123,96:112,97:128,101:117,102:133,153:181,158:186,163:141,166:182,167:198,170:199,171:187,172:203,175:204,176:192,177:208,180:209-4:34,9:39,14:44,18:47,23:52,28:57,46:62,50:64,51:67,55:69,56:72,60:74,79:109,84:114,89:119,93:122,98:127,103:132,121:137,125:139,126:142,130:144,121:147,135:149,154:184,159:189,164:194,168:197,173:202,178:207,196:212,200:214,201:217,205:214,206:222,224:210
        int ju = l + 1;
        int random = (rand() % (6 - 1 + 1)) + 1;
        printf("Player %i throw the dice %i \n ", ju, random);
        int isInside = 0;
        int numObsta = table->obstacul->length;

        for (int i = 0; i < numObsta && isInside == 0; i++)
        {
          //&& isInside == 0
          Obstacule obstacu = obtainObstacule(i)->obstacule;
          int inferior = obstacu.button;
          int superior = obstacu.top;
          int result = (obtainPlayer(l)->player.position + random);
          if (inferior == result && obstacu.type == 'E')
          {
            editarJugador(l, superior, 0);
            isInside = 1;
            int positionnew = obtainPlayer(l)->player.position;
            printf("PLayer %i goes up for the scalar to square %i \n", ju, positionnew);
          }
          if (inferior == result && obstacu.type == 'S')
          {
            editarJugador(l, inferior, 0);
            isInside = 1;
            int positionnew = obtainPlayer(l)->player.position;
            printf("PLayer %i goes down for the snake to square %i  \n", ju, positionnew);
          }
        }

        if (isInside == 0)
        {
          editarJugador(l, obtainPlayer(l)->player.position + random, 0);
          printf("Player %i goes to square %i \n ", ju, obtainPlayer(l)->player.position);
        }

        if (obtainPlayer(l)->player.position > (table->height * table->weidth))
        {

          int newPosition = obtainPlayer(l)->player.position - (obtainPlayer(l)->player.position - (table->height * table->weidth));
          int backwards = obtainPlayer(l)->player.position - (table->height * table->weidth);
          editarJugador(l, newPosition, 1);
          printf("Player %i goes back %i blocks \n ", ju, backwards);
        }
        if (obtainPlayer(l)->player.position == (table->height * table->weidth))
        {
          editarJugador(l, obtainPlayer(l)->player.position, 1);
          printf("Player %i win \n ", ju);
          fprintf(fp, "Player %d has %d the game \n", ju, obtainPlayer(l)->player.win);

          count = count + 1;
        }
      }
    }
  }

  gettimeofday(&end, NULL);
  fprintf(fp,"Time in seconds %0.8f \n", time_diff(&start, &end));
  fclose(fp);
}
