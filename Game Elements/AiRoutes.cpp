#include "AiRoutes.h"

Kjeledyr::AiRoutes::AiRoutes(int x,int y,int dir) {
    this->x=x;
    this->y=y;
    this->dir=dir;
}

void Kjeledyr::AiRoutes::SetX(int x) {x=x;}

void Kjeledyr::AiRoutes::SetY(int y) {y=y;}

void Kjeledyr::AiRoutes::SetDir(int ydir) {dir=ydir;}

int Kjeledyr::AiRoutes::GetX() { return x;}

int Kjeledyr::AiRoutes::GetY() { return y; }

int Kjeledyr::AiRoutes::GetDir() { return dir; }

