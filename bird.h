#ifndef BIRD_H
#define BIRD_H

#include "rectangle.h"

class Bird 
{
private:
    Rectangle bird;
    float posy;
    float speed;
    int acc;
public:
    Bird():
        bird(0.24f,0.16f),
        posy(0.08f),
        speed(0.0f),
        acc(10)
    {
        bird.setcolor(0.9f,0.0f,0.0f);
    }

    void draw()
    {
        bird.setposition(-0.12f,posy);
        bird.draw();
    }

    void clear()
    {
        bird.clear();
    }

    void drop()
    {
        if(posy<=-2.0f || posy>=2.0f)
        {
            return;
        }
        if(acc<=10)
        {
            acc++;
        }
        posy-=speed;
        speed+=(0.0001f*acc);
    }

    void fly()
    {
        speed=0.0f;
        acc=-15;
    }
    float getY()
    {
        return posy;
    }

};

#endif