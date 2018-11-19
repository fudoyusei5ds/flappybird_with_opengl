#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "pipe.h"
#include "bird.h"


// 這個函數用來改變視口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float testcoll(const float x1,const float y1,const float x2,const float y2);

int main()
{
    // 初始化
    glfwInit();
    // 設置glfw所使用的OpenGL的版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 設置glfw使用OpenGL的一個子集以及啓用OpenGL的核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 在Macos中使用
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 創建窗體
    GLFWwindow* window = glfwCreateWindow(400, 600, "LearnOpenGL", NULL, NULL);
    // 如果創建失敗, 輸出錯誤信息並釋放資源
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 設置窗體上下文爲線程主上下文
    glfwMakeContextCurrent(window);

    // 初始化glad, 用於返回OpenGL函數的地址
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 設置窗體維度
    glViewport(0, 0, 400, 600);
    // 注冊窗體調整函數
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    /***************************************************************/

    // 繪制水管1,2
    Pipe pipe1(-0.25f);
    Pipe pipe2(1.75f);

    // 繪制小鳥
    Bird bird;

    /***************************************************************/

    // 一個渲染循環, 在窗體退出前一直渲染
    // 首先檢查窗體是否被要求退出

    // 這幾個變量用來控制幀數
    clock_t lastFrame,newFrame;
    lastFrame=clock();

    bool isfly=false;
    // 這個變量用來記分用
    int count=0;
    bool ispassing=false;
    
    while(!glfwWindowShouldClose(window))
    {
        // 接收輸入
        processInput(window);  
        // 設置顏色
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // 清除顏色緩衝區, 並使用上面設置的顏色進行填充 
        glClear(GL_COLOR_BUFFER_BIT);
        
        if(count==2){
            pipe1.show();
        }
        else if(count==3){
            pipe2.show();
        }

        pipe1.move();
        pipe2.move();
        pipe1.draw();
        pipe2.draw();

        bird.drop();
        bird.draw();

        if((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)&&isfly==false)
        {
            isfly=true;
            bird.fly();
        }
        if((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)&&isfly==true)
            isfly=false;

        float allowh=testcoll(pipe1.getX(),pipe1.getY(),pipe2.getX(),pipe2.getY());
        if(allowh>-1.00f)
        {
            ispassing=true;
            if(count>=2)
            {
                if(!(bird.getY()<=allowh+0.01f && bird.getY()>=allowh-0.35f))
                {
                    printf("你撞牆了...\n");
                    break;
                }
            }
        }
        else
        {
            if(ispassing==true)
            {
                ispassing=false;
                count++;
            }
        }
        if(bird.getY()>1.0f||bird.getY()<-1.0f)
        {
            break;
        }

        // 交換緩衝, 繪制屏幕
        glfwSwapBuffers(window);
        // 檢查觸發事件, 調整窗體狀態
        glfwPollEvents(); 

        newFrame=clock();
        if(newFrame-lastFrame<=10000)
        {
            usleep(10000-newFrame+lastFrame);
        }
        lastFrame=newFrame;
    }

    pipe1.clear();
    pipe2.clear();
    bird.clear();

    // 最後釋放資源
    glfwTerminate();
    if(count<=2){
        count=0;
    }
    else{
        count-=2;
    }
    printf("你的得分是:%d\n",count);

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 當窗體大小改變時, 調用這個函數重新設置視口大小
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // 按下esc, 發出窗體退出信號
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float testcoll(const float x1,const float y1,const float x2,const float y2)
{
    if(x1>=-0.620f&&x1<=0.120f)
    {
        return y1;
    }
    else if(x2>=-0.620f&&x2<=0.120f)
    {
        return y2;
    }
    else
    {
        return -100.00f;
    }
}
