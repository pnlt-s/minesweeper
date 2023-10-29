#ifndef PNLT_MINESWEEPER
#define PNLT_MINESWEEPER

#define AREA_SIZE_EASY 10
#define AREA_SIZE_NORMAL 16
#define AREA_SIZE_HARD 24

enum Difficulty {
    Easy,
    Normal,
    Hard
};
typedef enum Difficulty Difficulty;

char* generateMap(Difficulty difficulty);
int checkIfBlockIsMine(char* map, int x, int y, int width, int height);
void genDirections();
#endif