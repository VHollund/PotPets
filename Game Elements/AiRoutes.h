#ifndef KJELEDYR_AIROUTES_H
#define KJELEDYR_AIROUTES_H

namespace Kjeledyr {
    class AiRoutes {
    public:
        AiRoutes(int x,int y,int dir);
        void SetX(int x);
        void SetY(int y);
        void SetDir(int dir);
        int GetX();
        int GetY();
        int GetDir();

    private:
        int x;
        int y;
        int dir;
    };
}

#endif //KJELEDYR_AIROUTES_H
