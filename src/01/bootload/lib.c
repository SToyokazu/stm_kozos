#include "defines.h"
#include "serial.h"
#include "lib.h"

/*: 1文字送信 */
int putc(unsigned char c)
{
    if ( c== '\n' ) {
        serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
    }
    
    return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

/* 文字列送信 */
int puts(unsigned char *str)
{
    while(*str) {   //　文字列の終端が\0であることを前提として実装
        putc(*str++);
    }

    return 0;
}