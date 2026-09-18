// Tetris.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_COLS 10
#define BOARD_ROWS 20
#define CELLS_SIZE 30

#define SCREEN_WIDTH  560
#define SCREEN_HEIGHT 660

#define BOARD_OFFSET_X 30
#define BOARD_OFFSET_Y 30

// Palette colori ufficiale: 0 = vuoto, 1..7 = Tetramini
static const Color PALETTE[8] = {
    { 20, 20, 26, 255 },    // 0: Sfondo cella vuota
    { 0, 240, 240, 255 },   // 1: I (Ciano)
    { 240, 240, 0, 255 },   // 2: O (Giallo)
    { 160, 0, 240, 255 },   // 3: T (Viola)
    { 0, 240, 0, 255 },     // 4: S (Verde)
    { 240, 0, 0, 255 },     // 5: Z (Rosso)
    { 0, 0, 240, 255 },     // 6: J (Blu)
    { 240, 160, 0, 255 }    // 7: L (Arancione)
};

// Matrici dei 7 tetramini in griglia 4x4
static const int TETROMINOES[7][4][4] = {
    // 0: I
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // 1: O
    {
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // 2: T
    {
        {0, 3, 0, 0},
        {3, 3, 3, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // 3: S
    {
        {0, 4, 4, 0},
        {4, 4, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // 4: Z
    {
        {5, 5, 0, 0},
        {0, 5, 5, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // 5: J
    {
        {6, 0, 0, 0},
        {6, 6, 6, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // 6: L
    {
        {0, 0, 7, 0},
        {7, 7, 7, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

typedef struct {
    int id;
    int shape[4][4];
    int x, y;
} Piece;

Piece spawnPiece(int id_piece) {
    Piece p;
    p.id = id_piece;
    p.x = (BOARD_COLS - 4) / 2;
    p.y = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            p.shape[i][j] = TETROMINOES[id_piece][i][j];
        }
    }

    return p;
}

int main(void) {


    return 0;
}