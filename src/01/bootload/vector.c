#include "defines.h"

extern void start(void);    /* スタート・アップ */

/*
 * 割り込みベクタの設定。
 * リンカスクリプトの定義により、Flash の先頭番地に配置される。
 */
void (*vectors[256])(void) = {
    (void (*)(void))0x20018000, /*   0: Initial stack pointer */
    start,                      /*   1: Reset */
    NULL,                       /*   2: NMI */
    NULL,                       /*   3: HardFault */
    NULL,                       /*   4: MemManage */
    NULL,                       /*   5: BusFault */
    NULL,                       /*   6: UsageFault */
    NULL,                       /*   7: Reserved */
    NULL,                       /*   8: Reserved */
    NULL,                       /*   9: Reserved */
    NULL,                       /*  10: Reserved */
    NULL,                       /*  11: SVC */
    NULL,                       /*  12: DebugMon */
    NULL,                       /*  13: Reserved */
    NULL,                       /*  14: PendSV */
    NULL,                       /*  15: SysTick */

    /* External interrupts: STM32F401 vector table */
    NULL,                       /*  16: WWDG */
    NULL,                       /*  17: PVD */
    NULL,                       /*  18: TAMP_STAMP */
    NULL,                       /*  19: RTC_WKUP */
    NULL,                       /*  20: FLASH */
    NULL,                       /*  21: RCC */
    NULL,                       /*  22: EXTI0 */
    NULL,                       /*  23: EXTI1 */
    NULL,                       /*  24: EXTI2 */
    NULL,                       /*  25: EXTI3 */
    NULL,                       /*  26: EXTI4 */
    NULL,                       /*  27: DMA1_Stream0 */
    NULL,                       /*  28: DMA1_Stream1 */
    NULL,                       /*  29: DMA1_Stream2 */
    NULL,                       /*  30: DMA1_Stream3 */
    NULL,                       /*  31: DMA1_Stream4 */
    NULL,                       /*  32: DMA1_Stream5 */
    NULL,                       /*  33: DMA1_Stream6 */
    NULL,                       /*  34: ADC */
    NULL,                       /*  35: Reserved */
    NULL,                       /*  36: Reserved */
    NULL,                       /*  37: Reserved */
    NULL,                       /*  38: Reserved */
    NULL,                       /*  39: EXTI9_5 */
    NULL,                       /*  40: TIM1_BRK_TIM9 */
    NULL,                       /*  41: TIM1_UP_TIM10 */
    NULL,                       /*  42: TIM1_TRG_COM_TIM11 */
    NULL,                       /*  43: TIM1_CC */
    NULL,                       /*  44: TIM2 */
    NULL,                       /*  45: TIM3 */
    NULL,                       /*  46: TIM4 */
    NULL,                       /*  47: I2C1_EV */
    NULL,                       /*  48: I2C1_ER */
    NULL,                       /*  49: I2C2_EV */
    NULL,                       /*  50: I2C2_ER */
    NULL,                       /*  51: SPI1 */
    NULL,                       /*  52: SPI2 */
    NULL,                       /*  53: USART1 */
    NULL,                       /*  54: USART2 */
    NULL,                       /*  55: Reserved */
    NULL,                       /*  56: EXTI15_10 */
    NULL,                       /*  57: RTC_Alarm */
    NULL,                       /*  58: OTG_FS_WKUP */
    NULL,                       /*  59: Reserved */
    NULL,                       /*  60: Reserved */
    NULL,                       /*  61: Reserved */
    NULL,                       /*  62: Reserved */
    NULL,                       /*  63: DMA1_Stream7 */
    NULL,                       /*  64: Reserved */
    NULL,                       /*  65: SDIO */
    NULL,                       /*  66: TIM5 */
    NULL,                       /*  67: SPI3 */
    NULL,                       /*  68: Reserved */
    NULL,                       /*  69: Reserved */
    NULL,                       /*  70: Reserved */
    NULL,                       /*  71: Reserved */
    NULL,                       /*  72: DMA2_Stream0 */
    NULL,                       /*  73: DMA2_Stream1 */
    NULL,                       /*  74: DMA2_Stream2 */
    NULL,                       /*  75: DMA2_Stream3 */
    NULL,                       /*  76: DMA2_Stream4 */
    NULL,                       /*  77: Reserved */
    NULL,                       /*  78: Reserved */
    NULL,                       /*  79: Reserved */
    NULL,                       /*  80: Reserved */
    NULL,                       /*  81: Reserved */
    NULL,                       /*  82: Reserved */
    NULL,                       /*  83: Reserved */
    NULL,                       /*  84: OTG_FS */
    NULL,                       /*  85: DMA2_Stream5 */
    NULL,                       /*  86: DMA2_Stream6 */
    NULL,                       /*  87: DMA2_Stream7 */
    NULL,                       /*  88: USART6 */
    NULL,                       /*  89: I2C3_EV */
    NULL,                       /*  90: I2C3_ER */
    NULL,                       /*  91: Reserved */
    NULL,                       /*  92: Reserved */
    NULL,                       /*  93: Reserved */
    NULL,                       /*  94: Reserved */
    NULL,                       /*  95: Reserved */
    NULL,                       /*  96: Reserved */
    NULL,                       /*  97: FPU */
    NULL,                       /*  98: Reserved */
    NULL,                       /*  99: Reserved */
    NULL,                       /* 100: SPI4 */

    /* Cortex-M external IRQ slots not implemented by STM32F401 */
    NULL,                       /* 101 */
    NULL,                       /* 102 */
    NULL,                       /* 103 */
    NULL,                       /* 104 */
    NULL,                       /* 105 */
    NULL,                       /* 106 */
    NULL,                       /* 107 */
    NULL,                       /* 108 */
    NULL,                       /* 109 */
    NULL,                       /* 110 */
    NULL,                       /* 111 */
    NULL,                       /* 112 */
    NULL,                       /* 113 */
    NULL,                       /* 114 */
    NULL,                       /* 115 */
    NULL,                       /* 116 */
    NULL,                       /* 117 */
    NULL,                       /* 118 */
    NULL,                       /* 119 */
    NULL,                       /* 120 */
    NULL,                       /* 121 */
    NULL,                       /* 122 */
    NULL,                       /* 123 */
    NULL,                       /* 124 */
    NULL,                       /* 125 */
    NULL,                       /* 126 */
    NULL,                       /* 127 */
    NULL,                       /* 128 */
    NULL,                       /* 129 */
    NULL,                       /* 130 */
    NULL,                       /* 131 */
    NULL,                       /* 132 */
    NULL,                       /* 133 */
    NULL,                       /* 134 */
    NULL,                       /* 135 */
    NULL,                       /* 136 */
    NULL,                       /* 137 */
    NULL,                       /* 138 */
    NULL,                       /* 139 */
    NULL,                       /* 140 */
    NULL,                       /* 141 */
    NULL,                       /* 142 */
    NULL,                       /* 143 */
    NULL,                       /* 144 */
    NULL,                       /* 145 */
    NULL,                       /* 146 */
    NULL,                       /* 147 */
    NULL,                       /* 148 */
    NULL,                       /* 149 */
    NULL,                       /* 150 */
    NULL,                       /* 151 */
    NULL,                       /* 152 */
    NULL,                       /* 153 */
    NULL,                       /* 154 */
    NULL,                       /* 155 */
    NULL,                       /* 156 */
    NULL,                       /* 157 */
    NULL,                       /* 158 */
    NULL,                       /* 159 */
    NULL,                       /* 160 */
    NULL,                       /* 161 */
    NULL,                       /* 162 */
    NULL,                       /* 163 */
    NULL,                       /* 164 */
    NULL,                       /* 165 */
    NULL,                       /* 166 */
    NULL,                       /* 167 */
    NULL,                       /* 168 */
    NULL,                       /* 169 */
    NULL,                       /* 170 */
    NULL,                       /* 171 */
    NULL,                       /* 172 */
    NULL,                       /* 173 */
    NULL,                       /* 174 */
    NULL,                       /* 175 */
    NULL,                       /* 176 */
    NULL,                       /* 177 */
    NULL,                       /* 178 */
    NULL,                       /* 179 */
    NULL,                       /* 180 */
    NULL,                       /* 181 */
    NULL,                       /* 182 */
    NULL,                       /* 183 */
    NULL,                       /* 184 */
    NULL,                       /* 185 */
    NULL,                       /* 186 */
    NULL,                       /* 187 */
    NULL,                       /* 188 */
    NULL,                       /* 189 */
    NULL,                       /* 190 */
    NULL,                       /* 191 */
    NULL,                       /* 192 */
    NULL,                       /* 193 */
    NULL,                       /* 194 */
    NULL,                       /* 195 */
    NULL,                       /* 196 */
    NULL,                       /* 197 */
    NULL,                       /* 198 */
    NULL,                       /* 199 */
    NULL,                       /* 200 */
    NULL,                       /* 201 */
    NULL,                       /* 202 */
    NULL,                       /* 203 */
    NULL,                       /* 204 */
    NULL,                       /* 205 */
    NULL,                       /* 206 */
    NULL,                       /* 207 */
    NULL,                       /* 208 */
    NULL,                       /* 209 */
    NULL,                       /* 210 */
    NULL,                       /* 211 */
    NULL,                       /* 212 */
    NULL,                       /* 213 */
    NULL,                       /* 214 */
    NULL,                       /* 215 */
    NULL,                       /* 216 */
    NULL,                       /* 217 */
    NULL,                       /* 218 */
    NULL,                       /* 219 */
    NULL,                       /* 220 */
    NULL,                       /* 221 */
    NULL,                       /* 222 */
    NULL,                       /* 223 */
    NULL,                       /* 224 */
    NULL,                       /* 225 */
    NULL,                       /* 226 */
    NULL,                       /* 227 */
    NULL,                       /* 228 */
    NULL,                       /* 229 */
    NULL,                       /* 230 */
    NULL,                       /* 231 */
    NULL,                       /* 232 */
    NULL,                       /* 233 */
    NULL,                       /* 234 */
    NULL,                       /* 235 */
    NULL,                       /* 236 */
    NULL,                       /* 237 */
    NULL,                       /* 238 */
    NULL,                       /* 239 */
    NULL,                       /* 240 */
    NULL,                       /* 241 */
    NULL,                       /* 242 */
    NULL,                       /* 243 */
    NULL,                       /* 244 */
    NULL,                       /* 245 */
    NULL,                       /* 246 */
    NULL,                       /* 247 */
    NULL,                       /* 248 */
    NULL,                       /* 249 */
    NULL,                       /* 250 */
    NULL,                       /* 251 */
    NULL,                       /* 252 */
    NULL,                       /* 253 */
    NULL,                       /* 254 */
    NULL,                       /* 255 */
};
