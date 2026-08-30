#include "defines.h"
#include "serial.h"

// 先頭アドレス
#define PERIPH_BASE     (0x40000000UL)                              // ペリフェラルレジスタの先頭アドレス
#define APB1PERIPH_BASE (PERIPH_BASE + 0x00000000UL)                // APB1ペリフェラルレジスタの先頭アドレス
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x00020000UL)                // AHB1ペリフェラルレジスタの先頭アドレス

// レジスタ
#define STM32F401_RCC ((RCC *)(AHB1PERIPH_BASE + 0x3800UL))         // リセットおよびクロック制御
#define STM32F401_GPIOA ((GPIO *)(AHB1PERIPH_BASE + 0x0000UL))      // 汎用 I/O ポート A
#define STM32F401_USART2 ((USART *)(APB1PERIPH_BASE + 0x4400UL))    // USART（Universal synchronous asynchronous receiver transmitter) モジュール2

// レジスタ定義
typedef struct RCC_REG {
    volatile uint32 CR;
    volatile uint32 PLLCFGR;
    volatile uint32 CFGR;
    volatile uint32 CIR;
    volatile uint32 AHB1RSTR;
    volatile uint32 AHB2RSTR;
    volatile uint32 RESERVED0[2];
    volatile uint32 APB1RSTR;
    volatile uint32 APB2RSTR;
    volatile uint32 RESERVED1[2];
    volatile uint32 AHB1ENR;
    volatile uint32 AHB2ENR;
    volatile uint32 RESERVED2[2];
    volatile uint32 APB1ENR;
    volatile uint32 APB2ENR;
    volatile uint32 RESERVED3[2];
    volatile uint32 AHB1LPENR;
    volatile uint32 AHB2LPENR;
    volatile uint32 RESERVED4[2];
    volatile uint32 APB1LPENR;
    volatile uint32 APB2LPENR;
    volatile uint32 RESERVED5[2];
    volatile uint32 BDCR;
    volatile uint32 CSR;
    volatile uint32 RESERVED6[2];
    volatile uint32 SSCGR;
    volatile uint32 PLLI2SCFGR;
    volatile uint32 RESERVED7;
    volatile uint32 DCKCFGR;
} RCC;

typedef struct GPIO_REG{
    volatile uint32 MODER;
    volatile uint32 OTYPER;
    volatile uint32 OSPEEDR;
    volatile uint32 PUPDR;
    volatile uint32 IDR;
    volatile uint32 ODR;
    volatile uint32 BSRR;
    volatile uint32 LCKR;
    volatile uint32 AFRL;
    volatile uint32 AFRH;
} GPIO;

typedef struct USART_REG {
    volatile uint32 SR;
    volatile uint32 DR;
    volatile uint32 BRR;
    volatile uint32 CR1;
    volatile uint32 CR2;
    volatile uint32 CR3;
    volatile uint32 GTPR;
} USART;

// ビット定義
#define RCC_AHB1ENR_GPIOA_EN     (1UL << 0)
#define RCC_APB1ENR_USART2_EN    (1UL << 17)

#define GPIO_MODER_AFMODE  (2UL)
#define GPIOA_MODER_PA2_AFMODE (GPIO_MODER_AFMODE << (2 * 2))
#define GPIOA_MODER_PA3_AFMODE (GPIO_MODER_AFMODE << (3 * 2))

#define GPIO_OSPEEDR_HIGH (3UL)
#define GPIOA_OSPEEDR_PA2_HIGH (GPIO_OSPEEDR_HIGH << (2 * 2))
#define GPIOA_OSPEEDR_PA3_HIGH (GPIO_OSPEEDR_HIGH << (3 * 2))

#define GPIOA_AFRL_AF7 (7UL)
#define GPIOA_AFRL_PA2_AF7 (GPIOA_AFRL_AF7 << (2 * 4))
#define GPIOA_AFRL_PA3_AF7 (GPIOA_AFRL_AF7 << (3 * 4))

#define USART_CR1_TE_EN  (1UL << 3)
#define USART_CR1_UE_EN  (1UL << 13)

#define USART_SR_TXE_EMPTY (1UL << 7)

int serial_init(int index)
{
    // 現状はで普通のデバイス番号しかサポートしていないので、違う番号が指定された場合はエラーとする
    if (index != SERIAL_DEFAULT_DEVICE) {
        return -1;
    }

    // ペリフェラルクロックの有効化
    STM32F401_RCC->AHB1ENR |= RCC_AHB1ENR_GPIOA_EN;
    STM32F401_RCC->APB1ENR |= RCC_APB1ENR_USART2_EN;

    // PA2: USART2_TX, alternate function 7
    STM32F401_GPIOA->MODER &= ~GPIOA_MODER_PA2_AFMODE;
    STM32F401_GPIOA->MODER |=  GPIOA_MODER_PA2_AFMODE;

    STM32F401_GPIOA->OSPEEDR &= ~GPIOA_OSPEEDR_PA2_HIGH;
    STM32F401_GPIOA->OSPEEDR |= GPIOA_OSPEEDR_PA2_HIGH;

    STM32F401_GPIOA->AFRL &= ~GPIOA_AFRL_PA2_AF7;
    STM32F401_GPIOA->AFRL |=  GPIOA_AFRL_PA2_AF7;

    // PA3: USART2_RX, alternate function 7
    STM32F401_GPIOA->MODER &= ~GPIOA_MODER_PA3_AFMODE;
    STM32F401_GPIOA->MODER |=  GPIOA_MODER_PA3_AFMODE;

    STM32F401_GPIOA->OSPEEDR &= ~GPIOA_OSPEEDR_PA3_HIGH;
    STM32F401_GPIOA->OSPEEDR |= GPIOA_OSPEEDR_PA3_HIGH;

    STM32F401_GPIOA->AFRL &= ~GPIOA_AFRL_PA3_AF7;
    STM32F401_GPIOA->AFRL |=  GPIOA_AFRL_PA3_AF7;

    // クロックは16MHzのHSIを使用する。APB1のプリスケーラのクロック設定前は1。
    // 16倍オーバーサンプリング方式を使用するため以下の計算でボーレートレジスタの値を求める。
    // USARTDIV = 16000000 / 115200 = 139, BRR = 0x08B
    STM32F401_USART2->CR1 = 0UL;      // USARTを一旦無効化
    STM32F401_USART2->BRR = 0x08B;  
    STM32F401_USART2->CR1 = USART_CR1_TE_EN | USART_CR1_UE_EN;  // 送信有効化、USART有効化

    return 0;
}

int serial_send_enable(int index)
{
    // 現状はで普通のデバイス番号しかサポートしていないので、違う番号が指定された場合はエラーとする
    if (index != SERIAL_DEFAULT_DEVICE) {
        return -1;
    }

    return ((STM32F401_USART2->SR & USART_SR_TXE_EMPTY) == USART_SR_TXE_EMPTY) ? 1 : 0;
}

int serial_send_byte(int index, unsigned char b)
{
    // 現状はで普通のデバイス番号しかサポートしていないので、違う番号が指定された場合はエラーとする
    if (index != SERIAL_DEFAULT_DEVICE) {
        return -1;
    }

    while (!serial_send_enable(index))
        ;

    STM32F401_USART2->DR = b;

    return 0;
}
