#include "gomoku.h"

int main(int argc, char* argv[]) {
    // 初始化游戏和图形系统
    Game game;
    Graphics gfx;
    
    printf("正在启动五子棋游戏...\n");
    
    // 初始化图形系统
    if (!init_graphics(&gfx)) {
        printf("图形系统初始化失败！\n");
        return 1;
    }
    
    // 初始化游戏
    init_game(&game);
    
    printf("游戏启动成功！\n");
    printf("操作说明：\n");
    printf("- 鼠标左键：下棋\n");
    printf("- R键：重新开始\n");
    printf("- ESC键：退出游戏\n");
    
    // 主游戏循环
    while (gfx.running) {
        // 处理事件
        handle_events(&gfx, &game);
        
        // 渲染游戏
        render_game(&gfx, &game);
        
        // 控制帧率
        SDL_Delay(16); // 约60FPS
    }
    
    // 清理资源
    cleanup_graphics(&gfx);
    
    printf("游戏已退出。\n");
    return 0;
}
