#ifndef GOMOKU_H
#define GOMOKU_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 游戏常量
#define BOARD_SIZE 15
#define CELL_SIZE 40
#define BOARD_MARGIN 50
#define WINDOW_WIDTH (BOARD_SIZE * CELL_SIZE + 2 * BOARD_MARGIN)
#define WINDOW_HEIGHT (BOARD_SIZE * CELL_SIZE + 2 * BOARD_MARGIN + 100)
#define STONE_RADIUS 15

// 棋子类型
typedef enum {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
} StoneType;

// 游戏状态
typedef enum {
    GAME_PLAYING,
    GAME_BLACK_WIN,
    GAME_WHITE_WIN,
    GAME_DRAW
} GameState;

// 游戏结构体
typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    StoneType current_player;
    GameState state;
    int move_count;
} Game;

// 图形相关结构体
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool running;
} Graphics;

// 游戏逻辑函数
void init_game(Game* game);
bool place_stone(Game* game, int x, int y);
bool check_win(Game* game, int x, int y);
bool check_direction(Game* game, int x, int y, int dx, int dy);
void switch_player(Game* game);
void reset_game(Game* game);

// 图形界面函数
bool init_graphics(Graphics* gfx);
void cleanup_graphics(Graphics* gfx);
void handle_events(Graphics* gfx, Game* game);
void render_game(Graphics* gfx, Game* game);
void render_board(Graphics* gfx);
void render_stones(Graphics* gfx, Game* game);
void render_ui(Graphics* gfx, Game* game);
void get_board_position(int mouse_x, int mouse_y, int* board_x, int* board_y);

// 颜色定义
#define COLOR_BACKGROUND {240, 217, 181, 255}
#define COLOR_BOARD_LINE {0, 0, 0, 255}
#define COLOR_BLACK_STONE {0, 0, 0, 255}
#define COLOR_WHITE_STONE {255, 255, 255, 255}
#define COLOR_TEXT {0, 0, 0, 255}

#endif // GOMOKU_H
