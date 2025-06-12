#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 游戏常量
#define BOARD_SIZE 15

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

// 函数声明
void init_game(Game* game);
void print_board(Game* game);
bool place_stone(Game* game, int x, int y);
bool check_win(Game* game, int x, int y);
bool check_direction(Game* game, int x, int y, int dx, int dy);
void switch_player(Game* game);
void get_player_move(Game* game);
const char* get_player_name(StoneType player);

// 初始化游戏
void init_game(Game* game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = EMPTY;
        }
    }
    game->current_player = BLACK;
    game->state = GAME_PLAYING;
    game->move_count = 0;
}

// 打印棋盘
void print_board(Game* game) {
    printf("\n   ");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%2d ", i + 1);
    }
    printf("\n");
    
    for (int y = 0; y < BOARD_SIZE; y++) {
        printf("%2d ", y + 1);
        for (int x = 0; x < BOARD_SIZE; x++) {
            switch (game->board[y][x]) {
                case EMPTY:
                    printf(" . ");
                    break;
                case BLACK:
                    printf(" ● ");
                    break;
                case WHITE:
                    printf(" ○ ");
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

// 下棋
bool place_stone(Game* game, int x, int y) {
    // 转换为0基索引
    x--;
    y--;
    
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return false;
    }
    
    if (game->board[y][x] != EMPTY) {
        return false;
    }
    
    if (game->state != GAME_PLAYING) {
        return false;
    }
    
    game->board[y][x] = game->current_player;
    game->move_count++;
    
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
    return check_direction(game, x, y, 1, 0) ||  // 水平
           check_direction(game, x, y, 0, 1) ||  // 垂直
           check_direction(game, x, y, 1, 1) ||  // 对角线
           check_direction(game, x, y, 1, -1);   // 对角线
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

// 获取玩家输入
void get_player_move(Game* game) {
    int x, y;
    printf("%s的回合，请输入坐标 (列 行): ", get_player_name(game->current_player));
    
    if (scanf("%d %d", &x, &y) != 2) {
        printf("输入格式错误！请输入两个数字。\n");
        // 清理输入缓冲区
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    
    if (!place_stone(game, x, y)) {
        printf("无效的移动！请重试。\n");
    }
}

// 获取玩家名称
const char* get_player_name(StoneType player) {
    return (player == BLACK) ? "黑棋(●)" : "白棋(○)";
}

// 主函数
int main() {
    Game game;
    char choice;
    
    printf("=================================\n");
    printf("        五子棋游戏 (控制台版)\n");
    printf("=================================\n");
    printf("游戏规则：在15x15棋盘上率先连成五子的玩家获胜\n");
    printf("输入格式：列号 行号 (例如: 8 8 表示中心位置)\n");
    printf("=================================\n");
    
    do {
        init_game(&game);
        
        while (game.state == GAME_PLAYING) {
            print_board(&game);
            get_player_move(&game);
        }
        
        print_board(&game);
        
        // 显示游戏结果
        switch (game.state) {
            case GAME_BLACK_WIN:
                printf("🎉 黑棋(●)获胜！\n");
                break;
            case GAME_WHITE_WIN:
                printf("🎉 白棋(○)获胜！\n");
                break;
            case GAME_DRAW:
                printf("平局！\n");
                break;
            default:
                break;
        }
        
        printf("\n是否再来一局？(y/n): ");
        if (scanf(" %c", &choice) != 1) {
            choice = 'n';
        }
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("感谢游戏！\n");
    return 0;
}
