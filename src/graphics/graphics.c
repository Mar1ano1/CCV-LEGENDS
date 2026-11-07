#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>
#include "graphics.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define BUFFER_WIDTH 512

typedef struct {
    unsigned int color;
    ScePspFVector3 position;
} Vertex;

static unsigned int __attribute__((aligned(16))) display_list[262144];

static Vertex vertices[] __attribute__((aligned(16))) = {
    {0xFFFF0000, {-1.0f, -1.0f,  0.0f}},
    {0xFFFF0000, { 1.0f, -1.0f,  0.0f}},
    {0xFFFF0000, { 0.0f,  1.0f,  0.0f}},

    {0xFF00FF00, {-1.0f, -1.0f,  0.0f}},
    {0xFF00FF00, { 0.0f, -1.0f, -1.5f}},
    {0xFF00FF00, { 0.0f,  1.0f,  0.0f}},

    {0xFF0000FF, { 1.0f, -1.0f,  0.0f}},
    {0xFF0000FF, { 0.0f, -1.0f, -1.5f}},
    {0xFF0000FF, { 0.0f,  1.0f,  0.0f}},

    {0xFFFFFF00, {-1.0f, -1.0f,  0.0f}},
    {0xFFFFFF00, { 1.0f, -1.0f,  0.0f}},
    {0xFFFFFF00, { 0.0f, -1.0f, -1.5f}}
};

void graphics_init(void)
{
    sceGuInit();

    sceGuStart(GU_DIRECT, display_list);

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

    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuDepthRange(65535, 0);

    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);

    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);

    sceGuDisable(GU_CULL_FACE);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);
}

void graphics_frame(void)
{
    ScePspFVector3 eye = {0.0f, 0.0f, 4.0f};
    ScePspFVector3 center = {0.0f, 0.0f, 0.0f};
    ScePspFVector3 up = {0.0f, 1.0f, 0.0f};

    sceGuStart(GU_DIRECT, display_list);

    sceGuClearColor(0xFF101020);
    sceGuClearDepth(0);

    sceGuClear(
        GU_COLOR_BUFFER_BIT |
        GU_DEPTH_BUFFER_BIT
    );

    sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();
    sceGumPerspective(
        45.0f,
        (float)SCREEN_WIDTH / SCREEN_HEIGHT,
        0.5f,
        100.0f
    );

    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();
    sceGumLookAt(&eye, &center, &up);

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    sceGumDrawArray(
        GU_TRIANGLES,
        GU_COLOR_8888 |
        GU_VERTEX_32BITF |
        GU_TRANSFORM_3D,
        12,
        0,
        vertices
    );

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}
