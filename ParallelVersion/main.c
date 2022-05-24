#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include <mpi.h>
#include <time.h>

Table *table;
MPI_File fh0;
MPI_File fh1;
MPI_File fh2;
MPI_File fh3;
int buf[1000], rank;
float time_diff(struct timeval *start, struct timeval *end)
{
  return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}
int main(int argc, char *argv[])
{
  table = (Table *)malloc(sizeof(Table));
  table->height = 15;
  table->weidth = 15;
  ListPlayers *listPlayers;

  MPI_Init(0, 0);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_File_open(MPI_COMM_WORLD, "0.txt",
                MPI_MODE_CREATE | MPI_MODE_WRONLY,
                MPI_INFO_NULL, &fh0);
  MPI_File_open(MPI_COMM_WORLD, "1.txt",
                MPI_MODE_CREATE | MPI_MODE_WRONLY,
                MPI_INFO_NULL, &fh1);
  MPI_File_open(MPI_COMM_WORLD, "2.txt",
                MPI_MODE_CREATE | MPI_MODE_WRONLY,
                MPI_INFO_NULL, &fh2);
  MPI_File_open(MPI_COMM_WORLD, "3.txt",
                MPI_MODE_CREATE | MPI_MODE_WRONLY,
                MPI_INFO_NULL, &fh3);
  char string0[80] = "PROCESSOR 0 \n";
  MPI_File_write(fh0, string0, strlen(string0), MPI_CHAR, MPI_STATUS_IGNORE);
  char string1[80] = "PROCESSOR 1 \n";
  MPI_File_write(fh1, string1, strlen(string1), MPI_CHAR, MPI_STATUS_IGNORE);
  char string2[80] = "PROCESSOR 2 \n";
  MPI_File_write(fh2, string2, strlen(string2), MPI_CHAR, MPI_STATUS_IGNORE);
  char string3[80] = "PROCESSOR 3 \n";
  MPI_File_write(fh3, string3, strlen(string3), MPI_CHAR, MPI_STATUS_IGNORE);
  struct timeval start, end;
  processes(argc, argv, rank);
  MPI_File_close(&fh0);
  MPI_File_close(&fh1);
  MPI_File_close(&fh2);
  MPI_File_close(&fh3);
  MPI_Finalize();
}

void processes(int argc, char *argv[], int rank)
{

  int Core1Done = 1;
  int Core2Done = 1;
  int Core3Done = 1;

  // char *obs = "3:11,10:12,9:18,6:17-4:14,8:19,20:22,16:24";
  char *obs = "3:31,8:36,13:41,16:32,17:48,20:49,21:37,22:53,25:54,26:42,27:58,30:59,78:106,83:111,88:116,91:107,92:123,96:112,97:128,101:117,102:133,153:181-4:34,9:39,14:44,18:47,23:52,28:57,46:62,50:64,51:67,55:69,56:72,60:74,79:109,84:114,89:119,93:122,98:127,103:132,121:137,125:139,126:142,130:144";
  int i;

  int c = 0;
  char **arr = NULL;
  c = split(obs, '-', &arr);
  printf("found %d tokens.\n", c);

  int c2 = 0;
  char **scalars = NULL;
  c2 = split(arr[0], ',', &scalars);
  int c3 = 0;
  char **snakes = NULL;
  c3 = split(arr[1], ',', &snakes);
  int m;
  for (int g = 0; g < 4; g++)
  {
    int l;
    int c4 = 0;
    char **xy = NULL;
    c4 = split(scalars[g], ':', &xy);

    insertObstacule(g, strtol(xy[1], NULL, 10), strtol(xy[0], NULL, 10), 'E');
  }

  for (int i = 0; i < 4; i++)
  {
    int h;
    int c4 = 0;
    char **xy = NULL;
    c4 = split(snakes[i], ':', &xy);

    insertObstacule(i + 4, strtol(xy[0], NULL, 10), strtol(xy[1], NULL, 10), 'S');
  }

  table->obstacul = obst;
  int number = 0;

  char line[100];
  int ciclye = 0;
  int total = 0;

  if (rank == 0)
  {
    char *filename = "input1.txt";
    FILE *Input = fopen(filename, "r");
    if (Input == NULL)
    {
      perror("Unable to open the file");
      exit(1);
    }
    struct timeval start, end;
    gettimeofday(&start, NULL);
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
      Player player;
      player.id = strtol(arr[0], NULL, 10);
      player.position = strtol(arr2[0], NULL, 10);
      player.win = strtol(arr3[0], NULL, 10);
      playGame(player, 0);
    }
    gettimeofday(&end, NULL);

    float time= time_diff(&start, &end);
    float time1;
    float time2;
    float time3;
     MPI_Recv(&time1, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
     MPI_Recv(&time2, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
     MPI_Recv(&time3, 1, MPI_FLOAT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    char answer[80];
    snprintf(answer, 80, "Time FINAL in seconds %0.8f \n", time);
    MPI_File_write(fh0, answer, strlen(answer), MPI_CHAR, MPI_STATUS_IGNORE);
  }
  if (rank == 1)
  {

    char *filename = "input2.txt";
    FILE *Input = fopen(filename, "r");
    if (Input == NULL)
    {
      perror("Unable to open the file");
      exit(1);
    }
    struct timeval start, end;
    gettimeofday(&start, NULL);
    while (fgets(line, sizeof(line), Input))
    {
      total++;
      printf("The number is %i\n", total);
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
      Player player;
      player.id = strtol(arr[0], NULL, 10);
      player.position = strtol(arr2[0], NULL, 10);
      player.win = strtol(arr3[0], NULL, 10);
      playGame(player, 1);
    }
    
    float time= time_diff(&start, &end);
    char answer[80];
    snprintf(answer, 80, "Time FINAL in seconds %0.8f \n", time_diff(&start, &end));
    MPI_File_write(fh1, answer, strlen(answer), MPI_CHAR, MPI_STATUS_IGNORE);
    MPI_Send(&time, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
  }
  else if (rank == 2)
  {
    char *filename = "input3.txt";
    FILE *Input = fopen(filename, "r");
    if (Input == NULL)
    {
      perror("Unable to open the file");
      exit(1);
    }
    struct timeval start, end;
    gettimeofday(&start, NULL);
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
      Player player;
      player.id = strtol(arr[0], NULL, 10);
      player.position = strtol(arr2[0], NULL, 10);
      player.win = strtol(arr3[0], NULL, 10);
      playGame(player, 2);
    }
   float time= time_diff(&start, &end);
    char answer[80];
    snprintf(answer, 80, "Time FINAL in seconds %0.8f \n", time_diff(&start, &end));
    MPI_File_write(fh2, answer, strlen(answer), MPI_CHAR, MPI_STATUS_IGNORE);
    MPI_Send(&time, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
  }
  else if (rank == 3)
  {
    char *filename = "input4.txt";
    FILE *Input = fopen(filename, "r");
    if (Input == NULL)
    {
      perror("Unable to open the file");
      exit(1);
    }
    struct timeval start, end;
    gettimeofday(&start, NULL);
    while (fgets(line, sizeof(line), Input))
    {
      total++;
      printf("The number is %i\n", total);
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
      Player player;
      player.id = strtol(arr[0], NULL, 10);
      player.position = strtol(arr2[0], NULL, 10);
      player.win = strtol(arr3[0], NULL, 10);
      playGame(player, 3);
    }
   float time= time_diff(&start, &end);
    MPI_Send(&time, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
     char answer[80];
    snprintf(answer, 80, "Time FINAL in seconds %0.8f \n", time_diff(&start, &end));
    MPI_File_write(fh3, answer, strlen(answer), MPI_CHAR, MPI_STATUS_IGNORE);
  }
}

void playGame(Player player, int processor)
{
  int count = 0;
  if (count == 0)
  {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    int diceThrow = 0;
    while (count == 0)
    {
      int l;

      for (l = 0; l < 1; l++)
      {
        if (player.win != 1)
        {
          // 3:11,10:12,9:18,6:17-4:14,8:19,20:22,16:24
          // 3:31,8:36,13:41,16:32,17:48,20:49,21:37,22:53,25:54,26:42,27:58,30:59,78:106,83:111,88:116,91:107,92:123,96:112,97:128,101:117,102:133,153:181,158:186,163:141,166:182,167:198,170:199,171:187,172:203,175:204,176:192,177:208,180:209-4:34,9:39,14:44,18:47,23:52,28:57,46:62,50:64,51:67,55:69,56:72,60:74,79:109,84:114,89:119,93:122,98:127,103:132,121:137,125:139,126:142,130:144,121:147,135:149,154:184,159:189,164:194,168:197,173:202,178:207,196:212,200:214,201:217,205:214,206:222,224:210
          // 3:31,8:36,13:41,16:32,17:48,20:49,21:37,22:53,25:54,26:42,27:58,30:59,78:106,83:111,88:116,91:107-4:34,9:39,14:44,18:47,23:52,28:57,46:62,50:64,51:67,55:69,56:72,60:74,79:109,84:114,89:119,93:122
          int ju = l + 1;
          int random = (rand() % (6 - 1 + 1)) + 1;
          printf("Player %i throw the dice %i \n ", player.id, random);
          diceThrow++;
          int isInside = 0;
          int numObsta = table->obstacul->length;
          for (int i = 0; i < numObsta && isInside == 0; i++)
          {
            Obstacule obstacu = obtainObstacule(i)->obstacule;
            int inferior = obstacu.button;
            int superior = obstacu.top;
            int result = (player.position + random);
            if (inferior == result && obstacu.type == 'E')
            {

              player.position = superior;
              isInside = 1;
              printf("PLayer %i goes up for the scalar to square %i \n", player.id, player.position);
            }
            if (inferior == result && obstacu.type == 'S')
            {
              player.position = inferior;
              isInside = 1;
              printf("PLayer %i goes down for the snake to square %i  \n", player.id, player.position);
            }
          }

          if (isInside == 0)
          {
            int newPosition = player.position + random;
            player.position = player.position + random;
            printf("Player %i goes to square %i \n ", player.id, player.position);
          }

          if (player.position > (table->height * table->weidth))
          {

            int newPosition = player.position - (player.position - (table->height * table->weidth));
            int backwards = player.position - (table->height * table->weidth);
            player.position = newPosition;
            printf("Player %i goes back %i blocks \n ", player.id, backwards);
          }

          if (player.position == (table->height * table->weidth))
          {

            player.win = 1;
            printf("Player %i win \n ", player.id);
            count = count + 1;
          }
        }
      }
    }
    gettimeofday(&end, NULL);
    size_t count;
    char str[] = "HELLO \n";
    if (processor == 0)
    {
      printf("HELLO FROM 0");
      char string[80];
      snprintf(string, 80, "Player %d took %f to win the game \n", player.id, time_diff(&start, &end));
      MPI_File_write(fh0, string, strlen(string), MPI_CHAR, MPI_STATUS_IGNORE);
    }
    else if (processor == 1)
    {
      printf("HELLO FROM 1");
      char string[80];
      snprintf(string, 80, "Player %d took %f to win the game \n", player.id, time_diff(&start, &end));
      MPI_File_write(fh1, string, strlen(string), MPI_CHAR, MPI_STATUS_IGNORE);
    }
    else if (processor == 2)
    {
      char string[80];
      printf("HELLO FROM 2");
      snprintf(string, 80, "Player %d took %f to win the game \n", player.id, time_diff(&start, &end));
      MPI_File_write(fh2, string, strlen(string), MPI_CHAR, MPI_STATUS_IGNORE);
    }
    else if (processor == 3)
    {
      char string[80];
      printf("HELLO FROM 3");
      snprintf(string, 80, "Player %d took %f to win the game \n", player.id, time_diff(&start, &end));
      MPI_File_write(fh3, string, strlen(string), MPI_CHAR, MPI_STATUS_IGNORE);
    }

    // fprintf((char)player.id, "Player %i throw the dice %i times and took %f to win", player.id, diceThrow, time_spent);
  }
}
