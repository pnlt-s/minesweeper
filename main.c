#include <stdio.h>
#include <Windows.h>
#include "sweeper.h"

void render(char* map, int width)
{
    printf("\x1b[1;1H\x1b[2J");
    int current = 0;
    while (*map != '\0')
    {
        char tile = *map;
        if (tile != '*' && tile != '?')
        {
            tile -= 1;
            if (tile > 0) {
                printf("%3d", tile);
            } else {
                printf("%3c", ' ');
            }

        } else {
            printf("%3c", tile);
        }
        ++current;
        ++map;

        if (current % width == 0)
        {
            printf("\n");
        }
    }
}

int isAlreadyRevealed(const char* renderMap, int x, int y, int width)
{
    return renderMap[width * y + x] != '?';
}

void revealTiles(char* map, char* renderMap, int x, int y, int width)
{
    if (x > width || y > width) return;
    if (x < 0 || y < 0) return;
    if (isAlreadyRevealed(renderMap, x, y, width)) return;

    printf("%d %d\n", x, y);

    printf("%d", map[width * y + x]);
    char tile = map[width * y + x];
    if ( tile == 1 )
    {
        renderMap[width * y + x] = tile;
        revealTiles(map, renderMap, x - 1, y - 1, width);
        revealTiles(map, renderMap, x, y - 1, width);
        revealTiles(map, renderMap, x + 1, y - 1, width);

        revealTiles(map, renderMap, x - 1, y, width);
        revealTiles(map, renderMap, x + 1, y, width);

        revealTiles(map, renderMap, x - 1, y + 1, width);
        revealTiles(map, renderMap, x, y + 1, width);
        revealTiles(map, renderMap, x + 1, y + 1, width);
    } else {
        renderMap[width * y + x] = tile;
    }
}

int play(Difficulty difficulty) {
    int width = 0;
    switch (difficulty)
    {
        case Hard:
            width = AREA_SIZE_HARD;
            break;
        case Normal:
            width = AREA_SIZE_NORMAL;
            break;
        case Easy:
        default:
            width = AREA_SIZE_EASY;
            break;
    }

    char * map = generateMap(difficulty);
    char * showMap = malloc(width * width + 1);
    for (int i = 0; i < width * width; ++i)
    {
        showMap[i] = '?';
    }
    showMap[width*width] = '\0';

    while (1) {
        render(showMap, width);
        printf("Waiting input: ");

        int x, y;
        scanf_s("%d%d", &x, &y);
        --x;
        --y;

        if (checkIfBlockIsMine(map, x, y, width, width))
        {
            render(map, width);
            printf("Game Over.");
            break;
        } else {
            revealTiles(map, showMap, x, y, width);
        }

    }
}

int main() {
    HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//    if (hHandle == INVALID_HANDLE_VALUE)
//    {
//        return 1;
//    }
//    DWORD dwOriginalMode = 0;
//    if (!GetConsoleMode(hHandle, &dwOriginalMode))
//    {
//        return 2;
//    }
//    if (!SetConsoleMode(hHandle, dwOriginalMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
//    {
//        return 3;
//    }


    Difficulty difficulty = Normal;

    play(difficulty);

    return 0;
}
