#ifndef CCV_MODEL_H
#define CCV_MODEL_H

typedef struct {
    unsigned int color;
    float position[3];
} ModelVertex;

typedef struct {
    unsigned int vertex_count;
    ModelVertex *vertices;
} Model;

int model_load(Model *model, const char *path);
void model_free(Model *model);

#endif
