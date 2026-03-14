// =====================================================
// communication.h — UART Debug MCC
// =====================================================
#pragma once
#include <stdio.h>
#include <string.h>

#define UART_BUF_SIZE    64

class Communication {
public:
    char buf[UART_BUF_SIZE];
    uint32_t counter = 0;
    uint32_t print_every = 100;  // toutes les 100ms

    // Envoie donnees toutes les print_every ms
    // Format CSV : t,ia,wm,u,status
    void send(UART_HandleTypeDef* huart,
              float ia, float wm,
              float u,  uint8_t status) {
        counter++;
        if (counter % print_every != 0) return;
        int len = snprintf(buf, UART_BUF_SIZE,
            "%.2f,%.2f,%.2f,%d\r\n",
            ia, wm, u, status);
        HAL_UART_Transmit(huart,
            (uint8_t*)buf, len, 10);
    }

    // Lecture commande depuis UART
    // Format : "REF:190.0"
    float parse_reference(char* rx_buf) {
        if (strncmp(rx_buf, "REF:", 4) == 0)
            return atof(rx_buf + 4);
        return -1.0f;  // pas de commande
    }
};
