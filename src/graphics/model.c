#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "model.h"

#define CCVM_MAGIC 0x4D564343
#define CCVM_VERSION 1
#define MAX_MODEL_VERTICES 30000

typedef struct {
    unsigned int magic;
    unsigned int version;
    unsigned int vertex_count;
} CCVMHeader;

int model_load(Model *model, const char *path)
{
    FILE *file;
    CCVMHeader header;

    if (!model || !path)
        return 0;

    model->vertices = NULL;
    model->vertex_count = 0;

    file = fopen(path, "rb");

    if (!file)
        return 0;

    if (fread(&header, sizeof(header), 1, file) != 1)
        goto error;

    if (header.magic != CCVM_MAGIC ||
        header.version != CCVM_VERSION ||
        header.vertex_count == 0 ||
        header.vertex_count > MAX_MODEL_VERTICES ||
        header.vertex_count % 3 != 0)
        goto error;

    model->vertices = memalign(
        16,
        sizeof(ModelVertex) * header.vertex_count
    );

    if (!model->vertices)
        goto error;

    if (fread(
        model->vertices,
        sizeof(ModelVertex),
        header.vertex_count,
        file
    ) != header.vertex_count)
        goto error;

    fclose(file);

    model->vertex_count = header.vertex_count;
    return 1;

error:
    free(model->vertices);
    model->vertices = NULL;
    model->vertex_count = 0;

    fclose(file);
    return 0;
}

void model_free(Model *model)
{
    if (!model)
        return;

    free(model->vertices);

    model->vertices = NULL;
    model->vertex_count = 0;
}
