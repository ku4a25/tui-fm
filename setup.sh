#!/bin/bash

set -e

echo "🔍 Checking for required tools..."

if ! command -v g++ &> /dev/null; then
    echo "g++ not found, installing..."
    if [ -f /etc/debian_version ]; then
        sudo apt update && sudo apt install -y g++
    elif [ -f /etc/arch-release ]; then
        sudo pacman -Sy --noconfirm gcc
    elif [ -f /etc/redhat-release ]; then
        sudo dnf install -y gcc-c++
    else
        echo "Unsupported Linux distro. Install g++ manually."
        exit 1
    fi
fi

if ! ldconfig -p | grep -q ncurses; then
    echo "libncurses not found, installing..."
    if [ -f /etc/debian_version ]; then
        sudo apt install -y libncurses-dev
    elif [ -f /etc/arch-release ]; then
        sudo pacman -Sy --noconfirm ncurses
    elif [ -f /etc/redhat-release ]; then
        sudo dnf install -y ncurses-devel
    else
        echo "Unsupported Linux distro. Install ncurses manually."
        exit 1
    fi
fi

echo "🔨 Compiling all source files in src/..."

mkdir -p build
g++ src/*.cpp -o build/tui-fm -lncurses -std=c++17

echo "✅ Build complete: build/tui-fm"

read -p "📛 Enter the desired command name (e.g. myfm): " binname
if [[ -z "$binname" ]]; then
    echo "❌ You must enter a valid command name."
    exit 1
fi

sudo cp build/tui-fm "/usr/bin/$binname"
sudo chmod +x "/usr/bin/$binname"

echo "🚀 Installed successfully! You can now run: $binname"
