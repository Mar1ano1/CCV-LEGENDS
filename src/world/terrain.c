#include <math.h>
#include "terrain.h"

/* Ruído determinístico */
static unsigned int terrain_hash(int x, int z)
{
    unsigned int h = (unsigned int)x * 374761393u;
    h += (unsigned int)z * 668265263u;
    h = (h ^ (h >> 13)) * 1274126177u;

    return h ^ (h >> 16);
}

/* Conversão para valores entre 0 e 1 */
static float random_value(int x, int z)
{
    return (terrain_hash(x, z) & 65535u) / 65535.0f;
}

/* Interpolação suave */
static float smooth(float t)
{
    return t * t * (3.0f - 2.0f * t);
}

/* Parte inteira inferior */
static int floor_int(float value)
{
    int result = (int)value;

    if (value < (float)result)
        result--;

    return result;
}

/* Ruído suave em duas dimensões */
static float value_noise(float x, float z)
{
    int x0 = floor_int(x);
    int z0 = floor_int(z);

    int x1 = x0 + 1;
    int z1 = z0 + 1;

    float fx = smooth(x - x0);
    float fz = smooth(z - z0);

    float a = random_value(x0, z0);
    float b = random_value(x1, z0);
    float c = random_value(x0, z1);
    float d = random_value(x1, z1);

    float top = a + (b - a) * fx;
    float bottom = c + (d - c) * fx;

    return top + (bottom - top) * fz;
}

/* Geração do terreno */
void terrain_generate(TerrainChunk *chunk, int chunk_x, int chunk_z)
{
    int x, z;

    chunk->chunk_x = chunk_x;
    chunk->chunk_z = chunk_z;

    for (z = 0; z < TERRAIN_RESOLUTION; z++)
    {
        for (x = 0; x < TERRAIN_RESOLUTION; x++)
        {
            float world_x = (float)(chunk_x * 16 + x);
            float world_z = (float)(chunk_z * 16 + z);

            float mountains = value_noise(
                world_x / 20.0f,
                world_z / 20.0f
            );

            float hills = value_noise(
                world_x / 7.0f,
                world_z / 7.0f
            );

            float detail = value_noise(
                world_x / 2.5f,
                world_z / 2.5f
            );

            chunk->heights[z][x] =
                (mountains - 0.5f) * 35.0f +
                (hills - 0.5f) * 9.0f +
                (detail - 0.5f) * 1.5f;
        }
    }
}

/* Consulta da altura */
float terrain_get_height(const TerrainChunk *chunk, int x, int z)
{
    if (x < 0 || x >= TERRAIN_RESOLUTION ||
        z < 0 || z >= TERRAIN_RESOLUTION)
        return 0.0f;

    return chunk->heights[z][x];
}
