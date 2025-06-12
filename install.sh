#!/bin/bash

# 五子棋游戏安装脚本
# 自动检测系统并安装SDL2依赖

echo "==================================="
echo "    五子棋游戏 (Gomoku) 安装脚本"
echo "==================================="

# 检测操作系统
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Linux系统
    if command -v apt-get &> /dev/null; then
        # Ubuntu/Debian
        echo "检测到Ubuntu/Debian系统"
        echo "正在安装SDL2开发库..."
        sudo apt-get update
        sudo apt-get install -y libsdl2-dev build-essential
    elif command -v dnf &> /dev/null; then
        # Fedora
        echo "检测到Fedora系统"
        echo "正在安装SDL2开发库..."
        sudo dnf install -y SDL2-devel gcc make
    elif command -v yum &> /dev/null; then
        # CentOS/RHEL
        echo "检测到CentOS/RHEL系统"
        echo "正在安装SDL2开发库..."
        sudo yum install -y SDL2-devel gcc make
    elif command -v pacman &> /dev/null; then
        # Arch Linux
        echo "检测到Arch Linux系统"
        echo "正在安装SDL2开发库..."
        sudo pacman -S --noconfirm sdl2 gcc make
    else
        echo "未识别的Linux发行版，请手动安装SDL2开发库"
        exit 1
    fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    echo "检测到macOS系统"
    if command -v brew &> /dev/null; then
        echo "正在使用Homebrew安装SDL2..."
        brew install sdl2
    else
        echo "请先安装Homebrew: https://brew.sh/"
        echo "然后运行: brew install sdl2"
        exit 1
    fi
else
    echo "不支持的操作系统: $OSTYPE"
    echo "请手动安装SDL2开发库"
    exit 1
fi

echo ""
echo "依赖安装完成！"
echo ""

# 编译游戏
echo "正在编译五子棋游戏..."
if make; then
    echo ""
    echo "✅ 编译成功！"
    echo ""
    echo "运行游戏："
    echo "  ./gomoku"
    echo ""
    echo "或者使用："
    echo "  make run"
    echo ""
    echo "游戏操作："
    echo "  - 鼠标左键：下棋"
    echo "  - R键：重新开始"
    echo "  - ESC键：退出"
    echo ""
else
    echo ""
    echo "❌ 编译失败！"
    echo "请检查SDL2是否正确安装"
    exit 1
fi
