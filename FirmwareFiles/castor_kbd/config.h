#pragma once

// Handedness by Pin - PA15
#define SPLIT_HAND_PIN A15
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// Split USART Full-duplex 설정
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN A2
#define SERIAL_USART_RX_PIN A3
#define SERIAL_USART_DRIVER SD2  // PA2/PA3는 USART2
#define SERIAL_USART_TX_PAL_MODE 1
#define SERIAL_USART_RX_PAL_MODE 1

// Split watchdog for slave timeout issues
#define SPLIT_WATCHDOG_ENABLE
