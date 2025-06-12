#!/bin/bash

# 五子棋游戏演示脚本

echo "==================================="
echo "    五子棋游戏 (Gomoku) 演示"
echo "==================================="
echo ""

# 检查控制台版本是否存在
if [ -f "./gomoku_console" ]; then
    echo "✅ 控制台版本已编译"
else
    echo "📦 正在编译控制台版本..."
    make console
    if [ $? -eq 0 ]; then
        echo "✅ 控制台版本编译成功"
    else
        echo "❌ 控制台版本编译失败"
        exit 1
    fi
fi

echo ""
echo "🎮 控制台版本演示："
echo "   - 使用纯文本界面"
echo "   - 黑棋用 ● 表示，白棋用 ○ 表示"
echo "   - 输入格式：列号 行号（例如：8 8）"
echo ""

# 演示控制台版本
echo "正在启动控制台版本演示..."
echo "（将自动下几步棋进行演示）"
echo ""

# 创建演示输入
cat > demo_input.txt << EOF
8 8
9 8
7 8
10 8
6 8
n
EOF

echo "演示输入序列："
echo "8 8  - 黑棋下在中心"
echo "9 8  - 白棋下在右侧"
echo "7 8  - 黑棋继续"
echo "10 8 - 白棋继续"
echo "6 8  - 黑棋获胜（五子连珠）"
echo ""

# 运行演示
./gomoku_console < demo_input.txt

# 清理临时文件
rm -f demo_input.txt

echo ""
echo "==================================="
echo "演示完成！"
echo ""
echo "要手动游戏，请运行："
echo "  ./gomoku_console    # 控制台版本"
echo ""
echo "如果安装了SDL2，还可以运行："
echo "  make gui && ./gomoku  # GUI版本"
echo "==================================="
