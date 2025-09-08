# STM32CubeIDE with Nucleo-H755
## Chap 01: Install STM32 and Get Started

### 1. Install STM32CubeIDE
1. Download STM32CubeIDE from: [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).  
2. Install on your system (Windows, Linux, or macOS).  
3. Launch the IDE.

### 2. Setup a New Project
1. Open **STM32CubeIDE**.  
2. Go to **File > New > STM32 Project**.
    <img width="1204" height="676" alt="image" src="https://github.com/user-attachments/assets/9df3d9bc-9cea-4ec0-a813-3f06ef656afd" />
3. In the MCU/Board selector:  
   - Search for **STM32H755ZIT3**.  
4. Select the board and click **Next**.
    <img width="1372" height="1012" alt="image" src="https://github.com/user-attachments/assets/8a5b43ec-cfda-48e9-a5c9-ad9a4ef28ba0" />
5. Name your project.  
6. Finish and let CubeIDE generate the project files.

   <img width="297" height="331" alt="image" src="https://github.com/user-attachments/assets/28ec7b87-bcbd-499d-8099-c71d16f1ae8a" />

#### ##CubeIDE will generate two projects:
- `Project_CM7` → primary core -- it starts first after reset.
- `Project_CM4` → does not start by default -- only executes when explicitly activated by CM7.
        
---

## Chap 02: First Program – Turn on all 3 LEDs
##### !! NOTE: All example codes in this documentation are executed on the CM7 core. The CM4 core is not used at this stage.

### 1. Configure Pin in STM32CubeIDE
1. In the **.ioc file**, go to **Pinout & Configuration**.  
2. Select pin **PB0, PB14, PE1** and set them as **GPIO_Output**.  
  - On the NUCLEO-H755 board, the **LD1(Green)** is connected to **PB0**, **LD2(Yellow)** is connected to **PE1** and **LD3(Red)** is connected to **PB14**.
  - Reference: [Schematic_LEDs]
3. CubeIDE will automatically add it under `GPIO`.

<img width="330" height="327" alt="image" src="https://github.com/user-attachments/assets/4c28ea75-80f3-406c-a1b3-894150a54978" />


### 2. Generate Code
- Select **Project > Generate Code** (or press **Ctrl+S**).  
- CubeIDE will generate `main.c` file along with the necessary HAL drivers.

### 3. Write Code in `main.c`
Inside the **while loop**, add the following code:

```
/* Code runs under CM7 core */
while (1)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);   // Green LED ON
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);   // Yellow LED ON
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);  // Red LED ON
}
```

### 4. Build and Flash the program
1. Go to **Project > Build Project** to compile the code.
<img width="355" height="235" alt="image" src="https://github.com/user-attachments/assets/ec9fb4e0-a3f5-481d-bec3-f1ab281791dc" />

2. Connect the NUCLEO-H755 board via USB.
3. Select **Run > Run As > STM32 C/C++ Application**.
<img width="351" height="400" alt="image" src="https://github.com/user-attachments/assets/cf3181db-0ab9-40a3-aa2d-c1f88f00b0a9" />

4. All three LEDs should turn on as shown [here].









## First program --- Blink all the 3 LEDs
## Second program --- Toggle LED at 500ms
