TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c

win32 {

# 1. FFmpeg 配置 (你原本写好的，保留)
# ==========================================
INCLUDEPATH += D:/software/FFmpeg/ffmpeg-7.1.1-full_build-shared/include
LIBS += -LD:/software/FFmpeg/ffmpeg-7.1.1-full_build-shared/lib
LIBS += -lavcodec -lavformat -lavutil -lswscale -lswresample -lavdevice -lavfilter

# ==========================================
# 2. SDL2 配置 (新增的部分！！！)
# ==========================================
# 告诉编译器 SDL.h 在哪里
INCLUDEPATH += D:/software/SDL2/SDL2-devel-2.32.8-VC/SDL2-2.32.8/include

# 告诉链接器 SDL2.lib 在哪里
# 注意：因为你选的是 MSVC 64位，所以要连 lib/x64 目录
LIBS += -LD:/software/SDL2/SDL2-devel-2.32.8-VC/SDL2-2.32.8/lib/x64

# 链接库文件
LIBS += -lSDL2 -lSDL2main

# 【新增】链接 Windows 系统库 (解决 CommandLineToArgvW 报错)
LIBS += -lShell32

}
