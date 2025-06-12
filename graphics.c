#include "gomoku.h"
#include <math.h>

// 初始化图形系统
bool init_graphics(Graphics* gfx) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL初始化失败: %s\n", SDL_GetError());
        return false;
    }
    
    gfx->window = SDL_CreateWindow("五子棋 - Gomoku",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   WINDOW_WIDTH,
                                   WINDOW_HEIGHT,
                                   SDL_WINDOW_SHOWN);
    
    if (!gfx->window) {
        printf("窗口创建失败: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    gfx->renderer = SDL_CreateRenderer(gfx->window, -1, SDL_RENDERER_ACCELERATED);
    if (!gfx->renderer) {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        SDL_DestroyWindow(gfx->window);
        SDL_Quit();
        return false;
    }
    
    gfx->running = true;
    return true;
}

// 清理图形系统
void cleanup_graphics(Graphics* gfx) {
    if (gfx->renderer) {
        SDL_DestroyRenderer(gfx->renderer);
    }
    if (gfx->window) {
        SDL_DestroyWindow(gfx->window);
    }
    SDL_Quit();
}

// 处理事件
void handle_events(Graphics* gfx, Game* game) {
    while (SDL_PollEvent(&gfx->event)) {
        switch (gfx->event.type) {
            case SDL_QUIT:
                gfx->running = false;
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                if (gfx->event.button.button == SDL_BUTTON_LEFT) {
                    int board_x, board_y;
                    get_board_position(gfx->event.button.x, gfx->event.button.y, 
                                     &board_x, &board_y);
                    place_stone(game, board_x, board_y);
                }
                break;
                
            case SDL_KEYDOWN:
                if (gfx->event.key.keysym.sym == SDLK_r) {
                    reset_game(game);
                } else if (gfx->event.key.keysym.sym == SDLK_ESCAPE) {
                    gfx->running = false;
                }
                break;
        }
    }
}

// 渲染游戏
void render_game(Graphics* gfx, Game* game) {
    // 设置背景色
    SDL_Color bg = COLOR_BACKGROUND;
    SDL_SetRenderDrawColor(gfx->renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(gfx->renderer);
    
    // 渲染棋盘
    render_board(gfx);
    
    // 渲染棋子
    render_stones(gfx, game);
    
    // 渲染UI
    render_ui(gfx, game);
    
    // 显示渲染结果
    SDL_RenderPresent(gfx->renderer);
}

// 渲染棋盘
void render_board(Graphics* gfx) {
    SDL_Color line_color = COLOR_BOARD_LINE;
    SDL_SetRenderDrawColor(gfx->renderer, line_color.r, line_color.g, line_color.b, line_color.a);
    
    // 绘制垂直线
    for (int i = 0; i < BOARD_SIZE; i++) {
        int x = BOARD_MARGIN + i * CELL_SIZE;
        SDL_RenderDrawLine(gfx->renderer, x, BOARD_MARGIN, 
                          x, BOARD_MARGIN + (BOARD_SIZE - 1) * CELL_SIZE);
    }
    
    // 绘制水平线
    for (int i = 0; i < BOARD_SIZE; i++) {
        int y = BOARD_MARGIN + i * CELL_SIZE;
        SDL_RenderDrawLine(gfx->renderer, BOARD_MARGIN, y,
                          BOARD_MARGIN + (BOARD_SIZE - 1) * CELL_SIZE, y);
    }
    
    // 绘制天元点（中心点）
    int center = BOARD_SIZE / 2;
    int center_x = BOARD_MARGIN + center * CELL_SIZE;
    int center_y = BOARD_MARGIN + center * CELL_SIZE;

    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            SDL_RenderDrawPoint(gfx->renderer, center_x + dx, center_y + dy);
        }
    }
}

// 渲染棋子
void render_stones(Graphics* gfx, Game* game) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (game->board[y][x] != EMPTY) {
                int center_x = BOARD_MARGIN + x * CELL_SIZE;
                int center_y = BOARD_MARGIN + y * CELL_SIZE;

                // 设置棋子颜色
                if (game->board[y][x] == BLACK) {
                    SDL_Color black = COLOR_BLACK_STONE;
                    SDL_SetRenderDrawColor(gfx->renderer, black.r, black.g, black.b, black.a);
                } else {
                    SDL_Color white = COLOR_WHITE_STONE;
                    SDL_SetRenderDrawColor(gfx->renderer, white.r, white.g, white.b, white.a);
                }

                // 绘制圆形棋子（用多个圆圈近似）
                for (int r = 0; r <= STONE_RADIUS; r++) {
                    int x_offset = (int)(sqrt(STONE_RADIUS * STONE_RADIUS - r * r));
                    SDL_RenderDrawLine(gfx->renderer,
                                     center_x - x_offset, center_y + r,
                                     center_x + x_offset, center_y + r);
                    if (r != 0) {
                        SDL_RenderDrawLine(gfx->renderer,
                                         center_x - x_offset, center_y - r,
                                         center_x + x_offset, center_y - r);
                    }
                }

                // 如果是白棋，绘制黑色边框
                if (game->board[y][x] == WHITE) {
                    SDL_Color black = COLOR_BLACK_STONE;
                    SDL_SetRenderDrawColor(gfx->renderer, black.r, black.g, black.b, black.a);

                    // 绘制圆形边框
                    for (int angle = 0; angle < 360; angle += 5) {
                        int px = center_x + (int)(STONE_RADIUS * cos(angle * M_PI / 180));
                        int py = center_y + (int)(STONE_RADIUS * sin(angle * M_PI / 180));
                        SDL_RenderDrawPoint(gfx->renderer, px, py);
                    }
                }
            }
        }
    }
}

// 渲染UI信息
void render_ui(Graphics* gfx, Game* game) {
    // 这里可以添加文字渲染，但SDL2需要额外的字体库
    // 为了简化，我们用简单的图形来表示游戏状态

    int ui_y = BOARD_MARGIN + BOARD_SIZE * CELL_SIZE + 20;

    // 显示当前玩家
    if (game->state == GAME_PLAYING) {
        int indicator_x = BOARD_MARGIN;
        int indicator_y = ui_y;

        if (game->current_player == BLACK) {
            SDL_Color black = COLOR_BLACK_STONE;
            SDL_SetRenderDrawColor(gfx->renderer, black.r, black.g, black.b, black.a);
        } else {
            SDL_Color white = COLOR_WHITE_STONE;
            SDL_SetRenderDrawColor(gfx->renderer, white.r, white.g, white.b, white.a);
        }

        // 绘制当前玩家指示器
        SDL_Rect indicator = {indicator_x, indicator_y, 30, 30};
        SDL_RenderFillRect(gfx->renderer, &indicator);

        if (game->current_player == WHITE) {
            SDL_Color black = COLOR_BLACK_STONE;
            SDL_SetRenderDrawColor(gfx->renderer, black.r, black.g, black.b, black.a);
            SDL_RenderDrawRect(gfx->renderer, &indicator);
        }
    }

    // 显示游戏结果
    if (game->state != GAME_PLAYING) {
        int result_x = BOARD_MARGIN + 100;
        int result_y = ui_y;

        SDL_Color result_color;
        if (game->state == GAME_BLACK_WIN) {
            result_color = COLOR_BLACK_STONE;
        } else if (game->state == GAME_WHITE_WIN) {
            result_color = COLOR_WHITE_STONE;
        } else {
            result_color = COLOR_TEXT;
        }

        SDL_SetRenderDrawColor(gfx->renderer, result_color.r, result_color.g, result_color.b, result_color.a);

        // 绘制胜利标志（简单的矩形）
        SDL_Rect result_rect = {result_x, result_y, 100, 30};
        SDL_RenderFillRect(gfx->renderer, &result_rect);
    }
}

// 将鼠标坐标转换为棋盘坐标
void get_board_position(int mouse_x, int mouse_y, int* board_x, int* board_y) {
    *board_x = (mouse_x - BOARD_MARGIN + CELL_SIZE / 2) / CELL_SIZE;
    *board_y = (mouse_y - BOARD_MARGIN + CELL_SIZE / 2) / CELL_SIZE;
}
