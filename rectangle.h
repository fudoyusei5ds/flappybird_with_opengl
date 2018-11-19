#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shader.h"
#include <glad/glad.h>

#define createBuffers(A, B, E,VERT,INDI) \
do{\
    glGenVertexArrays(1, &A);\
    glGenBuffers(1, &B);\
    glGenBuffers(1, &E);\
\
    glBindVertexArray(A);\
\
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, E);\
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDI), INDI, GL_STREAM_DRAW);\
\
    glBindBuffer(GL_ARRAY_BUFFER, B);\
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERT), VERT, GL_STREAM_DRAW);\
\
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);\
    glEnableVertexAttribArray(0);\
\
    glBindBuffer(GL_ARRAY_BUFFER, 0);\
    glBindVertexArray(0);\
}while(0)

class Rectangle
{
private:
    float width;
    float height;
    float posx,posy;
    Shader shader;
    float color[3];
    unsigned int VAO,VBO,EBO;
public:
    Rectangle(float w,float h):
        width(w),
        height(h),
        shader("./shader.vs", "./shader.fs"),
        color{0.0f,0.0f,0.0f}
    {
        float vert[]=
        {
            w,  0,    0.0f,  // 右上角
            w,  -h,   0.0f,  // 右下角
            0, -h,   0.0f,  // 左下角
            0, 0,    0.0f  // 左上角
        };
        unsigned int indi[]=
        {
            0, 1, 3, 
            1, 2, 3
        };
        // 創建矩形的各種值
        createBuffers(VAO,VBO,EBO,vert,indi);
    }

    void draw()
    {
        shader.use();
        shader.setFloat("colorR",color[0]);
        shader.setFloat("colorG",color[1]);
        shader.setFloat("colorB",color[2]);
        shader.setFloat("ourX",posx);
        shader.setFloat("ourY",posy);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void setposition(float x,float y)
    {
        posx=x;
        posy=y;
    }

    void setcolor(float r,float g,float b)
    {
        color[0]=r;
        color[1]=g;
        color[2]=b;
    }

    void clear()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

#endif