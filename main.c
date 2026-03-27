#include "SDL.h"
#include <stdio.h>

// 定义用户自定义事件 ID
// SDL_USEREVENT 是系统预留给用户的起始 ID
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)

// 注意：在 MSVC 环境下，必须带 argc 和 argv 参数
int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // 1. 初始化视频子系统
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // 2. 创建窗口
    window = SDL_CreateWindow("SDL Event Test",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // 3. 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // 4. 设置红色背景并清屏 (对应视频截图1中的操作)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 红色
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // 5. 事件循环
    SDL_Event event;
    int b_exit = 0;

    while (!b_exit) // 使用 while 循环，当 b_exit 为 1 时退出
    {
        // 阻塞等待事件
        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_KEYDOWN: // 键盘按下事件
            switch (event.key.keysym.sym) {
            case SDLK_a:
                printf("key down a\n");
                break;
            case SDLK_s:
                printf("key down s\n");
                break;
            case SDLK_d:
                printf("key down d\n");
                break;
            case SDLK_q:
                printf("key down q and push quit event\n");
                // 核心演示：手动创建一个事件并推送到队列中
                SDL_Event event_q;
                event_q.type = FF_QUIT_EVENT;
                SDL_PushEvent(&event_q);
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN: // 鼠标按下事件
            if (event.button.button == SDL_BUTTON_LEFT) {
                printf("mouse down left\n");
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                printf("mouse down right\n");
            }
            printf("mouse down: %d\n", event.button.button);
            break;

        case SDL_MOUSEMOTION: // 鼠标移动事件
            // 注意：视频里可能用了 event.button.x，但标准写法建议用 event.motion.x
            printf("mouse move (%d, %d)\n", event.motion.x, event.motion.y);
            break;

        case FF_QUIT_EVENT: // 处理我们在 SDLK_q 里发送的自定义事件
            printf("receive quit event\n");
            b_exit = 1; // 设置退出标志
            break;

        case SDL_QUIT: // 处理点击窗口右上角叉号的事件 (视频里没写，但建议加上)
            b_exit = 1;
            break;
        }
    }

    // 6. 释放资源
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

// #include <stdio.h>

// #include "SDL.h"

// int main(int argc, char *argv[])
// {
//     int run = 1;
//     SDL_Window *window = NULL;
//     SDL_Renderer *renderer = NULL;
//     SDL_Texture *texture = NULL;
//     SDL_Rect rect; //长方形，原点在左上角
//     rect.w = 50;
//     rect.h = 50;

//     SDL_Init(SDL_INIT_VIDEO); //初始化函数，可以确定希望激活的子系统

//     window = SDL_CreateWindow("sdl2_window",
//                               SDL_WINDOWPOS_UNDEFINED,
//                               SDL_WINDOWPOS_UNDEFINED,
//                               640,
//                               480,
//                               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

//     if (!window) {
//         return -1;
//     }
//     renderer = SDL_CreateRenderer(window, -1, 0); //基于窗口创建渲染器
//     if (!renderer) {
//         return -1;
//     }

//     texture = SDL_CreateTexture(renderer,
//                                 SDL_PIXELFORMAT_RGBA8888,
//                                 SDL_TEXTUREACCESS_TARGET,
//                                 640,
//                                 480); //创建纹理

//     if (!texture) {
//         return -1;
//     }

//     int show_count = 0;
//     while (run) {
//         rect.x = rand() % 600;
//         rect.y = rand() % 400;

//         SDL_SetRenderTarget(renderer, texture);         //设置渲染目标位纹理
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //纹理背景为黑色
//         SDL_RenderClear(renderer);                      //清屏

//         SDL_RenderDrawRect(renderer, &rect); //绘制长方形
//         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//         SDL_RenderFillRect(renderer, &rect);

//         SDL_SetRenderTarget(renderer, NULL); //恢复默认，渲染目标为窗口
//         SDL_RenderCopy(renderer, texture, NULL, NULL);

//         SDL_RenderPresent(renderer); //输出到目标窗口上
//         SDL_Delay(300);
//         if (show_count++ > 30) {
//             run = 0;
//         }
//     }
//     SDL_DestroyWindow(window);
//     SDL_DestroyRenderer(renderer);
//     SDL_Quit();
//     return 0;
//     // printf("Hello World!\n");

//     // SDL_Window *window = NULL;
//     // SDL_Init(SDL_INIT_VIDEO);

//     // window = SDL_CreateWindow("Basic Window",
//     //                           SDL_WINDOWPOS_UNDEFINED,
//     //                           SDL_WINDOWPOS_UNDEFINED,
//     //                           640,
//     //                           480,
//     //                           SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
//     // if(!window){
//     //   printf("Can`t create window, erroe:%s\n", SDL_GetError());
//     //   return 1;
//     // }

//     // SDL_Delay(10000); //延迟5000毫秒
//     // SDL_DestroyWindow(window);
//     // SDL_Quit();
//     // return 0;
// }
