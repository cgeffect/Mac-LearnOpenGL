//
//  main.cpp
//  LearnOpenGL
//
//  Created by Jason on 2024/3/28.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。
// 参数：window - 被改变大小的窗口，width、height-窗口的新维度。
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 改变视口大小的函数
    glViewport(0, 0, width, height);
}

// 实现输入控制的函数
void processInput(GLFWwindow *window)
{
    // glfwGetKey两个参数：窗口，按键
    // 没有被按下返回 GLFW_PRESS
    std::cout << "是否点击ESC?" << std::endl;
    std::cout << glfwGetKey(window, GLFW_KEY_ESCAPE) << std::endl;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        // 被按下则将 WindowShouldClose 属性置为 true
        // 以便于关闭 渲染循环
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit(); // 初始化GLFW
    // glfwWindowHint函数的第一个参数代表选项的名称
    // 第二个参数接受一个整型，用来设置这个选项的值
    
    // 将主版本号(Major)和次版本号(Minor)都设为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用的是核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // 参数依次为：宽、高、窗口的名称,显示器用于全屏模式，设为NULL是为窗口
    // 窗口的上下文为共享资源，NULL为不共享资源
    GLFWwindow* window = glfwCreateWindow(800, 600, "FirstWindow", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        // 释放空间，防止内存溢出
        glfwTerminate();
        return -1;
    }
    
    // 创建完毕之后，需要让window的context成为当前线程的current context
    glfwMakeContextCurrent(window);
    
    // glfwGetProcAddress是glfw提供的用来加载 系统相关的OpenGL函数指针地址 的函数
    // 用gladLoadGLLoader函数根据使用者的系统定义了正确的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // 告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
    // 这样OpenGL才只能知道怎样根据窗口大小显示数据和坐标
    // 调用glViewport函数来设置窗口的维度(Dimension)
    // 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
    glViewport(0, 0, 800, 600);
    
    // 窗口大小改变时视口也要随之改变，这通过对窗口注册 framebuffer_size_callback 实现。
    // 它会在每次窗口大小被调整时调用
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    /* 渲染循环(Render Loop) */
    // glfwWindowShouldClose 检查一次GLFW是否被要求退出
    // 为true时渲染循环结束
    while(!glfwWindowShouldClose(window))
    {
        // 监测键盘输入
        processInput(window);
        
        /* 渲染 */
        // 状态设置函数，设置清空屏幕所用的颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 状态使用函数，使用设定好的颜色来清除旧的颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 上面两种函数起到的作用也可以用 glClearBufferfv 来现实
        /*GLfloat color[] = {0.2, 0.3, 0.3, 1.0};
        glClearBufferfv(GL_COLOR, 0, color);*/

        // glfwSwapBuffers 交换颜色缓冲，用来绘制并作为输出显示在屏幕
        glfwSwapBuffers(window);
        // glfwPollEvents 检查是否有触发事件
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}
