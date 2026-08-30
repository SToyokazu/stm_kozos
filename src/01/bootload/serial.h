#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

int serial_init(int index);            // デバイスの初期化
int serial_is_send_enable(int index);  // 送信可能かどうかを確認
int serial_send_byte(int index, unsigned char b);   // 1文字送信

#endif /* _SERIAL_H_INCLUDED_ */