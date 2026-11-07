#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>

#include "graphics.h"
#include "terrain.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define BUFFER_WIDTH 512

static unsigned int __attribute__((aligned(16)))
display_list[262144];

static TerrainChunk world_terrain;

static TerrainVertex terrain_vertices[TERRAIN_VERTEX_COUNT]
    __attribute__((aligned(16)));

static int terrain_vertex_count = 0;

void graphics_init(void)
{
    /* Gerar a primeira região */
    terrain_generate(&world_terrain, 0, 0);

    /* Converter alturas em geometria 3D */
    terrain_vertex_count = terrain_build_mesh(
        &world_terrain,
        terrain_vertices,
        TERRAIN_VERTEX_COUNT
    );

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
    ScePspFVector3 eye = {
        0.0f, 42.0f, 85.0f
    };

    ScePspFVector3 center = {
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
        55.0f,
        (float)SCREEN_WIDTH / SCREEN_HEIGHT,
        1.0f,
        250.0f
    );

    sceGumMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    sceGumLookAt(&eye, &center, &up);

    sceGumMatrixMode(GU_MODEL);
    sceGumLoadIdentity();

    if (terrain_vertex_count > 0)
    {
        sceGumDrawArray(
            GU_TRIANGLES,
            GU_COLOR_8888 |
            GU_VERTEX_32BITF |
            GU_TRANSFORM_3D,
            terrain_vertex_count,
            0,
            terrain_vertices
        );
    }

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
}
