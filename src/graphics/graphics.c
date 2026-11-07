#include <pspgu.h>
#include <pspdisplay.h>
#include "graphics.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define BUFFER_WIDTH 512
static unsigned int __attribute__((aligned(16))) display_list[262144];

void graphics_init(void)
{
    sceGuInit();

    sceGuStart(GU_DIRECT, display_list);

    sceGuDrawBuffer(GU_PSM_8888, (void *)0, BUFFER_WIDTH);sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT,
                (void *)0x88000, BUFFER_WIDTH);list);

    sceGuDrawBuffer(GU_PSM_8888, (void *)0, BUFFER_WIDTH);

    sceGuDispBuffer(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        (void *)0x88000,
        BUFFER_WIDTH
    );

    sceGuDepthBuffer((void *)0x110000, BUFFER_WIDTH);

    sceGuOffset(
        2048 - SCREEN_WIDTH / 2,
        2048 - SCREEN_HEIGHT / 2
    );

    sceGuViewport(
        2048,
        2048,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    sceGuDepthRange(65535, 0);

    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);

    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);

    sceGuFrontFace(GU_CW);
    sceGuShadeModel(GU_SMOOTH);

    sceGuEnable(GU_CULL_FACE);
    sceGuEnable(GU_CLIP_PLANES);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);
}

void graphics_frame(void)
{
    sceGuStart(GU_DIRECT, display_list);

    sceGuClearColor(0xFF101020);
    sceGuClearDepth(0);

    sceGuClear(
        GU_COLOR_BUFFER_BIT |
        GU_DEPTH_BUFFER_BIT
    );

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}
EOF    sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT,
                    (void *)0x88000);

    sceGuDepthBuffer((void *)0x110000, BUFFER_WIDTH);

    sceGuOffset(2048 - SCREEN_WIDTH / 2,
                2048 - SCREEN_HEIGHT / 2);

    sceGuViewport(2048, 2048,
                  SCREEN_WIDTH, SCREEN_HEIGHT);

    sceGuDepthRange(65535, 0);

    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);

    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);

    sceGuFrontFace(GU_CW);
    sceGuShadeModel(GU_SMOOTH);

    sceGuEnable(GU_CULL_FACE);
    sceGuEnable(GU_CLIP_PLANES);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);
}

void graphics_frame(void)
{
    sceGuStart(GU_DIRECT, display_list);

    sceGuClearColor(0xFF101020);
    sceGuClearDepth(0);
    sceGuClear(GU_COLOR_BUFFER_BIT |
               GU_DEPTH_BUFFER_BIT);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}
