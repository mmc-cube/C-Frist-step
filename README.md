# 五子棋游戏 (Gomoku)

一个用C语言和SDL2库实现的五子棋游戏，具有图形界面，支持双人对战。

## 功能特点

- 🎮 图形化界面，支持鼠标操作
- ⚫⚪ 黑白双方轮流下棋
- 🏆 自动判断胜负（五子连珠）
- 🔄 支持重新开始游戏
- 🎯 15x15标准棋盘
- 💻 跨平台支持（Windows、Linux、macOS）

## 系统要求

- C编译器（GCC推荐）
- SDL2开发库
- Make工具

## 安装依赖

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev build-essential
```

### CentOS/RHEL/Fedora
```bash
sudo dnf install SDL2-devel gcc make
```

### macOS (使用Homebrew)
```bash
brew install sdl2
```

### Windows
1. 下载SDL2开发库：https://www.libsdl.org/download-2.0.php
2. 解压到项目目录或系统路径
3. 使用MinGW或Visual Studio编译

## 编译和运行

### 快速开始

### 方法一：使用自动安装脚本（推荐）
```bash
# 运行安装脚本（自动检测系统并安装依赖）
./install.sh
```

### 方法二：手动编译

#### GUI版本（需要SDL2）
```bash
# 编译GUI版本
make gui

# 运行GUI版本
make run
```

#### 控制台版本（无需SDL2）
```bash
# 编译控制台版本
make console

# 运行控制台版本
make run-console
```

### 方法三：完全手动编译
```bash
# GUI版本
gcc -Wall -Wextra -std=c99 -O2 main.c gomoku.c graphics.c -o gomoku -lSDL2 -lm
./gomoku

# 控制台版本
gcc -Wall -Wextra -std=c99 -O2 gomoku_console.c -o gomoku_console
./gomoku_console
```

## 游戏操作

- **鼠标左键**：在棋盘上下棋
- **R键**：重新开始游戏
- **ESC键**：退出游戏

## 游戏规则

1. 黑棋先行，双方轮流下棋
2. 在15x15的棋盘上，率先形成五子连珠（横、竖、斜任意方向）的一方获胜
3. 棋子一旦落下不能移动
4. 如果棋盘下满仍无人获胜则为平局

## 项目结构

```
├── main.c              # GUI版本主程序入口
├── gomoku.h            # 头文件，包含结构体和函数声明
├── gomoku.c            # 游戏逻辑实现
├── graphics.c          # 图形界面相关函数
├── gomoku_console.c    # 控制台版本（独立文件）
├── Makefile            # 编译配置
├── install.sh          # 自动安装脚本
└── README.md           # 项目说明
```

## 版本说明

### GUI版本（推荐）
- **文件**：`main.c`, `gomoku.c`, `graphics.c`, `gomoku.h`
- **依赖**：SDL2开发库
- **特点**：图形界面，鼠标操作，视觉效果好
- **适用**：有SDL2环境的系统

### 控制台版本
- **文件**：`gomoku_console.c`（单文件）
- **依赖**：无（仅需C编译器）
- **特点**：纯文本界面，键盘输入，兼容性强
- **适用**：任何支持C语言的系统

## 技术实现

- **游戏逻辑**：使用二维数组表示棋盘，实现胜负判断算法
- **图形界面**：使用SDL2库处理窗口创建、事件处理和图形绘制
- **事件处理**：支持鼠标点击和键盘输入
- **跨平台**：使用标准C语言和SDL2库，支持多平台编译

## 开发说明

### 编译调试版本
```bash
make debug
```

### 清理编译文件
```bash
make clean
```

### 查看帮助
```bash
make help
```

## 许可证

本项目采用MIT许可证，详见LICENSE文件。

## 贡献

欢迎提交Issue和Pull Request来改进这个项目！

## 作者

由AI助手创建，用于学习C语言图形编程。

---

**游戏截图和演示请查看项目文件！** 🎮
