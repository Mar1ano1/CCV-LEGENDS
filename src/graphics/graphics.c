#include <pspkernel.h>
#include <pspgu.h>
#include <pspgum.h>

#include "graphics.h"
#include "renderer.h"
#include "terrain.h"
#include "model.h"

static TerrainChunk world_terrain;

static TerrainVertex terrain_vertices[TERRAIN_VERTEX_COUNT]
    __attribute__((aligned(16)));

static Model terrain_model;
static int terrain_vertex_count = 0;

void graphics_init(void)
{
    terrain_generate(&world_terrain, 0, 0);

    terrain_vertex_count = terrain_build_mesh(
        &world_terrain,
        terrain_vertices,
        TERRAIN_VERTEX_COUNT
    );
    sceKernelDcacheWritebackInvalidateAll();

    terrain_model.vertex_count = terrain_vertex_count;
    terrain_model.vertices = (ModelVertex *)terrain_vertices;

    renderer_init();
}

void graphics_frame(void)
{
    renderer_begin();

    renderer_draw_model(&terrain_model);

    renderer_end();
}
