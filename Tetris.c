// Tetris.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

// 0 = vuota, 1..7 = id/colore del blocco fissato
static int board[BOARD_ROWS][BOARD_COLS] = { 0 };

typedef struct {
    int id;
    int shape[4][4];
    int x, y;
} Piece;

Piece spawnPiece() {
    Piece p;

    int new_id = rand() % 7;
    p.id = new_id + 1;
    p.x = (BOARD_COLS - 4) / 2;
    p.y = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            p.shape[i][j] = TETROMINOES[new_id][i][j];
        }
    }

    return p;
}

// Funzione per interazione con i tetramini (solo spostamento nelle 3 direzioni, escluso l'alto)
void movePiece(Piece *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

// Restituisce true se lo spostamento (dx, dy) porta il pezzo fuori bordo
// o sopra blocchi già posizionati.
bool canMove(const Piece* p, int dx, int dy) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (p->shape[r][c] != 0) {
                int targetX = p->x + c + dx;
                int targetY = p->y + r + dy;

                // Controlla i 4 bordi della griglia
                if (targetX < 0 || targetX >= BOARD_COLS ||
                    targetY < 0 || targetY >= BOARD_ROWS) {
                    return false; // Movimento bloccato dal bordo
                }

                // (Opzionale se hai già una board con blocchi fissi)
                if (board[targetY][targetX] != 0) return false;
            }
        }
    }
    return true; // Spostamento valido
}

void rotatePiece(Piece* p) {
	int temp[4][4];
    // Rotazione della matrice 4x4 del pezzo di 90 gradi in senso orario
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            temp[c][3 - r] = p->shape[r][c];
			}
    }
    // Copia la matrice ruotata nella forma del pezzo
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            p->shape[r][c] = temp[r][c];
        }
    }
	// Controllo se la rotazione è valida
    if (!canMove(p, 0, 0)) {
        // Se la rotazione porta il pezzo fuori bordo, sposta il pezzo all'interno della griglia
		if (p->x < 0) p->x = 0;
        if (p->x > BOARD_COLS - 4) p->x = BOARD_COLS - 4;
        if (p->y < 0) p->y = 0;
		if (p->y > BOARD_ROWS - 4) p->y = BOARD_ROWS - 4;
    }
}

// Funzione per fissare il pezzo nella griglia di gioco. 
void lockPiece(Piece* p) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (p->shape[r][c] != 0) {
                int targetX = p->x + c;
                int targetY = p->y + r;
                if (targetX >= 0 && targetX < BOARD_COLS &&
                    targetY >= 0 && targetY < BOARD_ROWS) {
                    board[targetY][targetX] = p->id;
                }
            }
        }
    }
	*p = spawnPiece(); // Genera un nuovo pezzo
}

int main(void) {
    // 1. Inizializzazione del contesto grafico e della finestra
    srand((unsigned int)time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
    SetTargetFPS(60);

    Piece test_piece = spawnPiece();

	float fall_timer = 0.0f;
	float fall_speed = 1.0f; // Caduta ogni secondo


    while (!WindowShouldClose()) {

		float deltaTime = GetFrameTime();
		fall_timer += deltaTime;

        if (fall_timer >= fall_speed) {
			fall_timer = 0.0f;

            if (canMove(&test_piece, 0, 1)) {
                movePiece(&test_piece, 0, 1);
            }
            else {
				// Il pezzo non può più scendere, quindi lo "fissiamo" e generiamo un pezzo nuovo
                lockPiece(&test_piece); // Passa la board reale qui
            }
		}

        if(IsKeyPressed(KEY_SPACE)) {
            rotatePiece(&test_piece);
		}

        // Sinistra
		if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) ||
            IsKeyPressedRepeat(KEY_LEFT) || IsKeyPressedRepeat(KEY_A)) {
            if (canMove(&test_piece, -1, 0)) movePiece(&test_piece, -1, 0);
        }

        // Destra
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) ||
            IsKeyPressedRepeat(KEY_RIGHT) || IsKeyPressedRepeat(KEY_D)) {
            if (canMove(&test_piece, 1, 0)) movePiece(&test_piece, 1, 0);
        }

        // Su
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) ||
            IsKeyPressedRepeat(KEY_UP) || IsKeyPressedRepeat(KEY_W)) {
            if (canMove(&test_piece, 0, -1)) movePiece(&test_piece, 0, -1);
        }

        // Giù
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            if (canMove(&test_piece, 0, 1)) movePiece(&test_piece, 0, 1);
        }

        BeginDrawing();
        ClearBackground((Color) { 14, 14, 18, 255 });

        for (int r = 0; r < BOARD_ROWS; r++) {
            for (int c = 0; c < BOARD_COLS; c++) {
                int posX = BOARD_OFFSET_X + c * CELLS_SIZE;
                int posY = BOARD_OFFSET_Y + r * CELLS_SIZE;

                if (board[r][c] != 0) {
                    DrawRectangle(posX, posY, CELLS_SIZE, CELLS_SIZE, PALETTE[board[r][c]]);
				}

                DrawRectangleLines(posX, posY, CELLS_SIZE, CELLS_SIZE, DARKGRAY);
            }
        }

        // TODO: Pezzo che appare

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (test_piece.shape[r][c] != 0) {
                    int posX = BOARD_OFFSET_X + (test_piece.x+c) * CELLS_SIZE;
                    int posY = BOARD_OFFSET_Y + (test_piece.y+r) * CELLS_SIZE;

                    DrawRectangle(posX, posY, CELLS_SIZE, CELLS_SIZE, PALETTE[test_piece.id]);
                    DrawRectangleLines(posX, posY, CELLS_SIZE, CELLS_SIZE, PALETTE[test_piece.shape[r][c]]);
                }
            }
        }

        EndDrawing();

    }
    
    CloseWindow();
    return 0;
}