# STM32CubeIDE

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
  - Reference: [NUCLEO-F446RE Schematic Diagram](https://github.com/HuiLing226/Lim_Doc/blob/2d1de2e8a5fcc01b14a30b48e440fd6f5c466c0c/NUCLEO_F446RE_SCHEMATICS.pdf)
3. CubeIDE will automatically add it under `GPIO`.  

### 2. Generate Code
- Select **Project > Generate Code** (or press **Alt+K**).  
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


