#include <pspkernel.h>
#include <pspdebug.h>
#include <stdio.h>

PSP_MODULE_INFO("CCV LEGENDS", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(void)
{
    pspDebugScreenInit();

    printf("\n\n");
    printf("================================\n");
    printf("       CCV LEGENDS ENGINE\n");
    printf("================================\n\n");

    printf("Engine inicializado!\n");
    printf("Plataforma: PlayStation Portable\n");
    printf("Projeto: CCV LEGENDS\n");
    printf("Versao: 0.1.0\n\n");

    printf("Preparando os sistemas 3D...\n");

    sceKernelSleepThread();

    return 0;
}
