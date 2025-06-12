# 五子棋游戏 Makefile

# 编译器和编译选项
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LIBS = -lSDL2 -lm

# 目标文件
TARGET_GUI = gomoku
TARGET_CONSOLE = gomoku_console
SOURCES_GUI = main.c gomoku.c graphics.c
SOURCES_CONSOLE = gomoku_console.c
OBJECTS_GUI = $(SOURCES_GUI:.c=.o)

# 默认目标 - 尝试编译GUI版本，失败则编译控制台版本
all: gui

# 编译GUI版本
gui: $(TARGET_GUI)

# 编译控制台版本
console: $(TARGET_CONSOLE)

# 编译GUI可执行文件
$(TARGET_GUI): $(OBJECTS_GUI)
	$(CC) $(OBJECTS_GUI) -o $(TARGET_GUI) $(LIBS)

# 编译控制台可执行文件
$(TARGET_CONSOLE): $(SOURCES_CONSOLE)
	$(CC) $(CFLAGS) $(SOURCES_CONSOLE) -o $(TARGET_CONSOLE)

# 编译目标文件
%.o: %.c gomoku.h
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译文件
clean:
	rm -f $(OBJECTS_GUI) $(TARGET_GUI) $(TARGET_CONSOLE)

# 安装SDL2依赖（Ubuntu/Debian）
install-deps-ubuntu:
	sudo apt-get update
	sudo apt-get install libsdl2-dev

# 安装SDL2依赖（CentOS/RHEL/Fedora）
install-deps-fedora:
	sudo dnf install SDL2-devel

# 安装SDL2依赖（macOS with Homebrew）
install-deps-macos:
	brew install sdl2

# 运行GUI版本
run: $(TARGET_GUI)
	./$(TARGET_GUI)

# 运行控制台版本
run-console: $(TARGET_CONSOLE)
	./$(TARGET_CONSOLE)

# 调试版本
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET_GUI)

# 控制台调试版本
debug-console: CFLAGS += -g -DDEBUG
debug-console: $(TARGET_CONSOLE)

# 帮助信息
help:
	@echo "可用的make目标："
	@echo "  all              - 编译GUI版本（默认）"
	@echo "  gui              - 编译GUI版本（需要SDL2）"
	@echo "  console          - 编译控制台版本"
	@echo "  clean            - 清理编译文件"
	@echo "  run              - 编译并运行GUI版本"
	@echo "  run-console      - 编译并运行控制台版本"
	@echo "  debug            - 编译GUI调试版本"
	@echo "  debug-console    - 编译控制台调试版本"
	@echo "  help             - 显示此帮助信息"
	@echo ""
	@echo "安装依赖："
	@echo "  install-deps-ubuntu  - 在Ubuntu/Debian上安装SDL2"
	@echo "  install-deps-fedora  - 在Fedora/CentOS上安装SDL2"
	@echo "  install-deps-macos   - 在macOS上安装SDL2"

.PHONY: all gui console clean run run-console debug debug-console help install-deps-ubuntu install-deps-fedora install-deps-macos
