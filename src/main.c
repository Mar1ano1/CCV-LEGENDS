#include <pspkernel.h>
#include "graphics/graphics.h"

PSP_MODULE_INFO("CCV LEGENDS", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(void)
{
    graphics_init();

    while (1)
    {
        graphics_frame();
    }

    return 0;
}
