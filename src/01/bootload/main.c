#include "defines.h"
#include "serial.h"
#include "lib.h"

int main(void)
{
    serial_init(SERIAL_DEFAULT_DEVICE);

    puts("Hello, World!\n");

    while (1)
    {
        // Main loop
    }

    return 0;
}