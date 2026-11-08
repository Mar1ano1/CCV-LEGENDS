#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>
#include <pspkernel.h>

#include "renderer.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define BUFFER_WIDTH 512

static unsigned int __attribute__((aligned(16)))
display_list[262144];

void renderer_init(void)
{
    sceGuInit();

    sceGuStart(GU_DIRECT, display_list);

    sceGuDrawBuffer(
        GU_PSM_8888,
        (void *)0,
        BUFFER_WIDTH
    );

    sceGuDispBuffer(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        (void *)0x88000,
        BUFFER_WIDTH
    );

    sceGuDepthBuffer(
        (void *)0x110000,
        BUFFER_WIDTH
    );

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

    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);

    sceGuDepthRange(65535, 0);
    sceGuDepthFunc(GU_GEQUAL);
    sceGuEnable(GU_DEPTH_TEST);

    sceGuDisable(GU_CULL_FACE);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);
}

void renderer_begin(void)
{
    ScePspFVector3 eye = {
        0.0f, 65.0f, 110.0f
    };

    ScePspFVector3 target = {
        0.0f, 0.0f, 0.0f
    };

    ScePspFVector3 up = {
        0.0f, 1.0f, 0.0f
    };

    sceGuStart(GU_DIRECT, display_list);

    sceGuClearColor(0xFF87CEEB);
    sceGuClearDepth(0);

    sceGuClear(
        GU_COLOR_BUFFER_BIT |
        GU_DEPTH_BUFFER_BIT
    );

    sceGumMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();

    sceGumPerspective(
        60.0f,
        (float)SCREEN_WIDTH / SCREEN_HEIGHT,
        1.0f,
        1000.0f
    );

    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    sceGumLookAt(&eye, &target, &up);

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();
}

void renderer_draw_model(Model *model)
{
    if (!model || !model->vertices ||
        model->vertex_count == 0)
        return;

    sceKernelDcacheWritebackRange(
        model->vertices,
        sizeof(ModelVertex) * model->vertex_count
    );

    sceGumDrawArray(
        GU_TRIANGLES,
        GU_COLOR_8888 |
        GU_VERTEX_32BITF |
        GU_TRANSFORM_3D,
        model->vertex_count,
        NULL,
        model->vertices
    );
}

void renderer_end(void)
{
    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}
