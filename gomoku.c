#include "gomoku.h"

// 初始化游戏
void init_game(Game* game) {
    // 清空棋盘
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = EMPTY;
        }
    }
    
    game->current_player = BLACK;
    game->state = GAME_PLAYING;
    game->move_count = 0;
}

// 下棋
bool place_stone(Game* game, int x, int y) {
    // 检查位置是否有效
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return false;
    }
    
    // 检查位置是否为空
    if (game->board[y][x] != EMPTY) {
        return false;
    }
    
    // 检查游戏是否结束
    if (game->state != GAME_PLAYING) {
        return false;
    }
    
    // 放置棋子
    game->board[y][x] = game->current_player;
    game->move_count++;
    
    // 检查是否获胜
    if (check_win(game, x, y)) {
        game->state = (game->current_player == BLACK) ? GAME_BLACK_WIN : GAME_WHITE_WIN;
    } else if (game->move_count >= BOARD_SIZE * BOARD_SIZE) {
        game->state = GAME_DRAW;
    } else {
        switch_player(game);
    }
    
    return true;
}

// 检查获胜条件
bool check_win(Game* game, int x, int y) {
    // 检查四个方向：水平、垂直、对角线
    return check_direction(game, x, y, 1, 0) ||  // 水平
           check_direction(game, x, y, 0, 1) ||  // 垂直
           check_direction(game, x, y, 1, 1) ||  // 对角线 \
           check_direction(game, x, y, 1, -1);   // 对角线 /
}

// 检查指定方向是否有五子连珠
bool check_direction(Game* game, int x, int y, int dx, int dy) {
    StoneType stone = game->board[y][x];
    int count = 1;
    
    // 向正方向检查
    int nx = x + dx, ny = y + dy;
    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && 
           game->board[ny][nx] == stone) {
        count++;
        nx += dx;
        ny += dy;
    }
    
    // 向负方向检查
    nx = x - dx;
    ny = y - dy;
    while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && 
           game->board[ny][nx] == stone) {
        count++;
        nx -= dx;
        ny -= dy;
    }
    
    return count >= 5;
}

// 切换玩家
void switch_player(Game* game) {
    game->current_player = (game->current_player == BLACK) ? WHITE : BLACK;
}

// 重置游戏
void reset_game(Game* game) {
    init_game(game);
}
