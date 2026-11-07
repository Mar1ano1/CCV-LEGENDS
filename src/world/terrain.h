#ifndef CCV_TERRAIN_H
#define CCV_TERRAIN_H

#define TERRAIN_RESOLUTION 17
#define TERRAIN_CHUNK_SIZE 64.0f

typedef struct {
    float heights[TERRAIN_RESOLUTION][TERRAIN_RESOLUTION];
    int chunk_x;
    int chunk_z;
} TerrainChunk;

void terrain_generate(TerrainChunk *chunk, int chunk_x, int chunk_z);
float terrain_get_height(const TerrainChunk *chunk, int x, int z);

#endif
