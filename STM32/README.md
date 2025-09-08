# STM32CubeIDE using Nucleo-64

## Chap 01: Install STM32 and Get Started

### 1. Install STM32CubeIDE
1. Download STM32CubeIDE from: [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).  
2. Install on your system (Windows, Linux, or macOS).  
3. Launch the IDE.

### 2. Setup a New Project
1. Open **STM32CubeIDE**.  
2. Go to **File > New > STM32 Project**.  
3. In the MCU/Board selector:  
   - Search for **STM32F446RET6**.  
4. Select the board and click **Next**.  
5. Name your project.  
6. Finish and let CubeIDE generate the project files.

   
---

## Chap 02: First Program – Blink the LED

### 1. Configure Pin in STM32CubeIDE
1. In the **.ioc file**, go to **Pinout & Configuration**.  
2. Select pin **PA5** and set it as **GPIO_Output**.  
  - On the NUCLEO-F446RE board, the **LD2 (user LED)** is connected to **PA5**.
  - Reference: [NUCLEO-F446RE Schematic Diagram](https://github.com/HuiLing226/Lim_Doc/blob/2a113a91e9d689b9ed65c5dcbf86898b3b2d77e3/NUCLEO_F446RE_SCHEMATICS.pdf)
3. CubeIDE will automatically add it under `GPIO`.  

### 2. Generate Code
- Select **Project > Generate Code** (or press **Ctrl+S**).  
- CubeIDE will generate `main.c` file along with the necessary HAL drivers.

### 3. Write Code in `main.c`in under while loop
Inside the **while loop**, add the following code:

```
while (1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);  // Toggle LED on PA5
    HAL_Delay(500);                         // Delay 500 ms
  }
}
```

### 4. Build and Flash the program
1. Go to **Project > Build Project** to compile the code.
2. Connect the NUCLEO-F446RE board via USB.
3. Select **Run > Run As > STM32 C/C++ Application**.
4. The LED (LD2) on pin **PA5** will start blinking at 1 Hz (on/off every 500 ms).

## Chap 03: Second program - UART LED Control with Tera Term

### 1.Hardware Setup
- **Board**: Nucleo-64 STM32F446RETx  
- **Built-in LED**: LD2 (connected to PA5)  
- **USB cable**: Connects board to PC (provides power + UART via ST-LINK Virtual COM Port)  
- No external USB-to-UART converter needed.

### 2. Software Setup
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)  
- [Tera Term](https://github.com/TeraTermProject/teraterm/releases/download/v5.4.1/teraterm-5.4.1.exe)

### 3. STM32CubeIDE Configuration
1. Create a new STM32 project for **STM32F446RETx**.  
2. Open the `.ioc` file and configure peripherals:  
   - **USART2 → Asynchronous mode**  
     - Baud rate: `115200`  
     - TX = PA2, RX = PA3 (default mapping)  
   - **PA5 → GPIO_Output** (controls LED)  
3. Generate initialization code by pressing **Ctrl+S**.  

### 4. Code (`main.c`)

```c
#include "main.h"
#include <string.h>

UART_HandleTypeDef huart2;

char rxBuffer[20];
uint8_t rxIndex = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        if (rxBuffer[rxIndex - 1] == '\r' || rxBuffer[rxIndex - 1] == '\n') {
            if (strstr(rxBuffer, "ON")) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
                char msg[] = "LED ON\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
            } 
            else if (strstr(rxBuffer, "OFF")) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
                char msg[] = "LED OFF\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
            }
            memset(rxBuffer, 0, sizeof(rxBuffer));
            rxIndex = 0;
        }
        HAL_UART_Receive_IT(&huart2, (uint8_t*)&rxBuffer[rxIndex++], 1);
    }
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    char msg[] = "UART LED Control Ready\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

    HAL_UART_Receive_IT(&huart2, (uint8_t*)&rxBuffer[rxIndex++], 1);

    while (1) {
        // UART is handled by interrupts
    }
}
```

### 5. Tera Term
1. Connect your board via USB.
2. Open **Tera Term**.
3. In the **New connection** window, setup as below.
   <img width="422" height="295" alt="image" src="https://github.com/user-attachments/assets/c5c26be6-cd81-428e-954d-38a2190e31b6" />
4. Configure Serial Port in Tera Term
   - Go to **Setup > Serial port** and set as below:
     <img width="616" height="701" alt="image" src="https://github.com/user-attachments/assets/da2cf11d-83ca-4351-97ac-d5436cbc982f" />
   - Go to **Setup > Terminal** and configure:
     <img width="616" height="701" alt="image" src="https://github.com/user-attachments/assets/440cc9c4-34dc-46f8-a4d4-001664bf0f6e" />
   - Clik **OK**.

### 6. Testing the project
1. Reset the STM32 board.
2. Type the commands:
   - `ON`  → LED turns ON, response:
     ```
     LED ON
     ```
   - `OFF`  → LED turns OFF, response:
     ```
     LED OFF
     ```
