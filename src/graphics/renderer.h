#ifndef CCV_RENDERER_H
#define CCV_RENDERER_H

#include "model.h"

void renderer_init(void);
void renderer_begin(void);
void renderer_draw_model(Model *model);
void renderer_end(void);

#endif
