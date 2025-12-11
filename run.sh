#!/bin/bash

echo "🔧 Compilando o jogo..."

g++ -std=c++17 \
    src/main.cpp \
    src/Game.cpp \
    src/GameState.cpp \
    src/Entity/AimEntity.cpp \
    src/Entity/FruitEntity.cpp \
    src/Entity/BombEntity.cpp \
    src/Entity/SliceEntity.cpp \
    -Iinclude \
    -Iinclude/Entity \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -O2 \
    -o game

if [ $? -ne 0 ]; then
    echo "❌ Erro ao compilar!"
    exit 1
fi

echo "🎮 Rodando o jogo..."
./game
