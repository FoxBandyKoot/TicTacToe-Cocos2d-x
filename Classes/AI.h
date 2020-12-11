#pragma once
#include <vector>
#include <array>
#include "cocos2d.h"


class AI
{
public:

    AI(int playerPiece);
    
    void PlacePiece(int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3], int* gameState);

private:

    void CheckSection(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck, int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3]);

    void CheckIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3]);

    int ai_piece;
    int player_piece;
    std::vector<std::array<int, 6>> checkMatchVector;
};