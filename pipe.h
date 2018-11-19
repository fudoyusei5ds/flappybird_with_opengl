#ifndef PIPE_H
#define PIPE_H

#include "rectangle.h"
#include <stdlib.h>

class Pipe
{
private:
    // 水管
    Rectangle pipe;
    // 通道 
    Rectangle turn;

    float posx;
    float tposy;
public:
    Pipe(float x):
        pipe(0.5f,2.0f),
        turn(0.5f,0.5f),
        posx(x),
        tposy(0.0f)
    {
        pipe.setcolor(0.0f,0.0f,0.0f);
        turn.setcolor(0.0f,0.0f,0.0f);
    }
    void show()
    {
        pipe.setcolor(0.0f,1.0f,0.0f);
    }
    void draw()
    {
        pipe.setposition(posx,1.0f);
        pipe.draw();

        turn.setposition(posx,tposy);
        turn.draw();
    }
    void move()
    {
        posx-=0.01f;
        if(posx<-1.50f)
        {
            posx=2.50f;
            tposy=rand()%6*0.1;
        }
    }
    void clear()
    {
        pipe.clear();
        turn.clear();
    }

    float getX()
    {
        return posx;
    }
    float getY()
    {
        return tposy;
    }
};

#endif