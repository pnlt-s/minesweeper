#include "sweeper.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int** dirs = NULL;

void genDirections()
{
    if (dirs != NULL)
        return;
    dirs = malloc(sizeof(int*) * 8);
    for (int i = 0; i < 8; ++i)
    {
        dirs[i] = malloc(sizeof(int) * 2);
    }
    dirs[0][0] = -1;
    dirs[0][1] = -1;

    dirs[1][0] = 0;
    dirs[1][1] = -1;

    dirs[2][0] = 1;
    dirs[2][1] = -1;

    dirs[3][0] = -1;
    dirs[3][1] = 0;

    dirs[4][0] = 1;
    dirs[4][1] = 0;

    dirs[5][0] = -1;
    dirs[5][1] = 1;

    dirs[6][0] = 0;
    dirs[6][1] = 1;

    dirs[7][0] = 1;
    dirs[7][1] = 1;

    return dirs;
}

int checkIfBlockIsMine(char* map, int x, int y, int width, int height)
{
    if (x < 0 || y < 0) return 0;
    if (x > width || y > height) return 0;
    if (width * y + x > width * height) return 0;
    return map[width * y + x] == '*';
}

char* generateMap(Difficulty difficulty)
{
    genDirections();
    srand(time(NULL));

    int height = 0;
    int width = 0;

    switch (difficulty) {
        case Hard: {
            height = AREA_SIZE_HARD;
            width = AREA_SIZE_HARD;
            break;
        }
        case Normal: {
            height = AREA_SIZE_NORMAL;
            width = AREA_SIZE_NORMAL;
            break;
        }
        case Easy:
        default: {
            width = AREA_SIZE_EASY;
            height = AREA_SIZE_EASY;
            break;
        }
    }

    int mines = (height * width) / 4;

    char* map = malloc(width * height + 1);
    for (int mine = 0; mine < mines; ++mine)
    {
        int x = rand() % width;
        int y = rand() % height;

        if (checkIfBlockIsMine(map, x, y, width, height))
        {
            --mine;
            continue;
        }

        map[y * width + x] = '*';
    }
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (checkIfBlockIsMine(map, x, y, width, height)){
                continue;
            }
            int minesAround = 0;
            for (int dirId = 0; dirId < 8; ++dirId)
            {
                int* dir = dirs[dirId];
                if (checkIfBlockIsMine(map, x + dir[0], y + dir[1], width, height)) {
                    ++minesAround;
                }
            }
            map[width * y + x] = (char)minesAround + 1;
        }
    }
    map[width*height] = '\0';
    return map;
}