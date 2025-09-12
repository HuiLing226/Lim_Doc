# Universal Synchronous/Asynchronous Receiver/Transmitter (USART)

## Chapter 1: Introduction and Setup
### What is USART?
- A hardware communication peripheral used for serial data exchange.  
- It supports both **synchronous** (with clock) and **asynchronous** (without clock) communication.  
- In most microcontroller-to-PC applications, we use **asynchronous mode**, commonly referred to as UART.  
- It is widely used for debugging and communication between microcontrollers and PCs.  

---

### Tools and Software  
- **Board**: Nucleo-H755ZI-Q   
- **USB cable** or **USB-to-UART dongle**: Connects board to PC.
- **STM32CubeIDE**: To program and configure the NUCLEO-H755 board.
- **[Tera Term](https://github.com/TeraTermProject/teraterm/releases/download/v5.4.1/teraterm-5.4.1.exe)**: Free serial monitor software to view UART messages on the PC.  

#### \## UART Pin Configuration on NUCLEO-H755ZI 
- The board has multiple USART/UART peripherals.  
- **Virtual COM Port (VCP)** via ST-LINK debugger:  
  - By default, **USART3** communication between the board and the STLINK is enabled, to support the Virtual COM port, which can be refer [here](https://github.com/HuiLing226/Lim_Doc/blob/9c81f873a7bc96f220db4fdab5ee1b550eed8dd6/Nucleo_H755/ref/Shc_UART.png).
  - Plug the board into your PC with a micro-USB cable, you can use it directly (no extra dongle).  
- **Other UARTs (like USART1, USART2, etc.)**:  
  - Can be used with an external **USB-UART dongle**.  
  - Example: PA2 (TX), PA3 (RX) → connect to dongle → PC.  

---

## Chap 2: Programming example: Control the LEDs and send the message
### Step 1: Pin configuration (set all the pins for CM7 project)
- **Red LED** → PB14  
- **Yellow LED** → PE1  
- **Green LED** → PB0
- **USART3** → PD8 (TX) and PD9 (RX) → set as *Asynchronous*

  ### Step 2: Example code
  (The full code at [here](https://github.com/HuiLing226/Lim_Doc/blob/0d6d86760e51e4b2463b8538d736f0c5d5e0019e/STM32/UART/main.c).)

  ```c
   #include "main.h"
   #include "string.h"
   #include "stdio.h"

   UART_HandleTypeDef huart3; // Using USART3 for VCP (PD8, PD9)

   void SystemClock_Config(void);
   static void MX_GPIO_Init(void);
   static void MX_USART3_UART_Init(void);

   int main(void)
   {
     HAL_Init();
     SystemClock_Config();
     MX_GPIO_Init();
     MX_USART3_UART_Init();

     char rxData[10];
     char txData[50];

     sprintf(txData, "UART LED Control Ready\r\n");
     HAL_UART_Transmit(&huart3, (uint8_t*)txData, strlen(txData), HAL_MAX_DELAY);

     while (1)
     {
       // Receive command from serial monitor
       HAL_UART_Receive(&huart3, (uint8_t*)rxData, sizeof(rxData)-1, HAL_MAX_DELAY);

       if (strstr(rxData, "RED"))
       {
         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
         sprintf(txData, "Red LED ON\r\n");
       }
       else if (strstr(rxData, "YELLOW"))
       {
         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
         sprintf(txData, "Green LED ON\r\n");
       }
       else if (strstr(rxData, "GREEN"))
       {
         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
         HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
         sprintf(txData, "Yellow LED ON\r\n");
       }
       else
       {
         sprintf(txData, "Error: Unknown Command\r\n");
       }

       HAL_UART_Transmit(&huart3, (uint8_t*)txData, strlen(txData), HAL_MAX_DELAY);

       memset(rxData, 0, sizeof(rxData)); // Clear buffer
     }
   }
  ```

### Step 4: Build the project and flash the program on the board

### Step 5: Serial monitor: Tera Term
1. Connect your board via USB.
2. Open **Tera Term**.
3. In the **New connection** window, set up as below.<img width="281" height="196" alt="image" src="https://github.com/user-attachments/assets/c5c26be6-cd81-428e-954d-38a2190e31b6" />
5. Configure Serial Port in Tera Term
   - Go to **Setup > Serial port** and set as below: <img width="410" height="467" alt="image" src="https://github.com/user-attachments/assets/da2cf11d-83ca-4351-97ac-d5436cbc982f" />
   - Go to **Setup > Terminal** and configure:<img width="410" height="467" alt="image" src="https://github.com/user-attachments/assets/440cc9c4-34dc-46f8-a4d4-001664bf0f6e" />
   - Clik **OK**.

#### The expected output is as follows and can be shown [here](https://drive.google.com/file/d/1HRVKbpC-2TpVPenaltfDKBtbzqenD9kI/view?usp=sharing):
- Type commands:
  - `RED` → Red LED turns ON and shows *Red LED ON* on.
  - `YELLOW` → Yellow LED turns ON and shows *Yellow LED ON* on.
  - `GREEN` → Green LED turns ON and shows *Green LED ON* on.
  - Anything else → `Error: Unknown Command`
