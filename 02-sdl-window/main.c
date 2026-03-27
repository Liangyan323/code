#include <stdio.h>

#include "SDL.h"

int main(int argc, char *argv[])
{
    int run = 1;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rect; //长方形，原点在左上角
    rect.w = 50;
    rect.h = 50;

    SDL_Init(SDL_INIT_VIDEO); //初始化函数，可以确定希望激活的子系统

    window = SDL_CreateWindow("sdl2_window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0); //基于窗口创建渲染器
    if (!renderer) {
        return -1;
    }

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                640,
                                480); //创建纹理

    if (!texture) {
        return -1;
    }

    int show_count = 0;
    while (run) {
        rect.x = rand() % 600;
        rect.y = rand() % 400;

        SDL_SetRenderTarget(renderer, texture);         //设置渲染目标位纹理
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //纹理背景为黑色
        SDL_RenderClear(renderer);                      //清屏

        SDL_RenderDrawRect(renderer, &rect); //绘制长方形
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderTarget(renderer, NULL); //恢复默认，渲染目标为窗口
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer); //输出到目标窗口上
        SDL_Delay(300);
        if (show_count++ > 30) {
            run = 0;
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
    // printf("Hello World!\n");

    // SDL_Window *window = NULL;
    // SDL_Init(SDL_INIT_VIDEO);

    // window = SDL_CreateWindow("Basic Window",
    //                           SDL_WINDOWPOS_UNDEFINED,
    //                           SDL_WINDOWPOS_UNDEFINED,
    //                           640,
    //                           480,
    //                           SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    // if(!window){
    //   printf("Can`t create window, erroe:%s\n", SDL_GetError());
    //   return 1;
    // }

    // SDL_Delay(10000); //延迟5000毫秒
    // SDL_DestroyWindow(window);
    // SDL_Quit();
    // return 0;
}
