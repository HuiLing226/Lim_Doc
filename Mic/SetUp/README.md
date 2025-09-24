
# Microphone Setup: SPH0645 with Nucleo H755

## 1. Hardware Connections

Refer to the Nucleo H755 schematics:  
- [CN8 Pinout](https://github.com/HuiLing226/Lim_Doc/blob/main/Nucleo_H755/ref/Sch_CN8.png)  
- [CN7 Pinout](https://github.com/HuiLing226/Lim_Doc/blob/main/Nucleo_H755/ref/Sch_CN7.png)  

| SPH0645 Pin | Nucleo H755 Pin | Function |
|-------------|-----------------|----------|
| VDD         | CN8 Pin 7 (+3V3) | Power Supply |
| GND         | CN8 Pin 13 (GND) | Ground |
| BCLK        | CN7 Pin 10 (D13 / PA5) | Bit Clock |
| DOUT        | CN7 Pin 12 (D12 / PA6) | Data Output |
| LRCL        | CN7 Pin 17 (D24 / PA4) | Left/Right Clock (WS) |
| SEL         | CN7 Pin 8 (GND) | Select channel (left) |

**Notes**:  
- Tie `SEL` to **GND** for **left channel**, or **VDD** for right.  
- Ensure 3.3V logic compatibility.  

---

## 2. Software Configuration (STM32CubeIDE)

1. **I²S1 Configuration**
   - Mode: **Half Duplex Master Receive**
   - Communication standard: **I²S Philips**
   - Data/Frame format: **16-bit data, 32-bit frame**

2. **DMA Settings**
   - Enable DMA for I²S1 RX  
   - Configure circular buffer for continuous audio capture
     
---

## 3. Code
```c
/* USER CODE BEGIN PV */
int32_t data_i2s[100];          
volatile int32_t sample_i2s = 0; 
/* USER CODE END PV */

/* USER CODE BEGIN 2 */
HAL_I2S_Receive_DMA(&hi2s1, (uint16_t*)data_i2s, sizeof(data_i2s)/2);
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
// DMA callback - complete
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s) {
    sample_i2s = data_i2s[0];  // pick first sample of second half
}
/* USER CODE END 4 */
```

--- 
## 4. Test the functionality of the mic
1. Debug using **SWV ITM Data Console** -- watch the waveform.
   - Enable the `debug` mode, and it will automatically set the pins <img width="663" height="705" alt="image" src="https://github.com/user-attachments/assets/4cc7073c-afae-47c1-8fd3-773ce9e3d523" />
   - Under debug configuration - debugger - enable the SWV <img width="1147" height="694" alt="image" src="https://github.com/user-attachments/assets/bf06629a-948d-4799-8314-2996ab30fab0" />
   - Debug
   - Open SWV Data Trace Timeline Graph <img width="1920" height="1020" alt="image" src="https://github.com/user-attachments/assets/d19d5ede-29ec-4bdb-94e7-e6aeab6322d5" />
   - Start Trace and press `resume`<img width="1034" height="1020" alt="image" src="https://github.com/user-attachments/assets/829ad93e-f3d9-4fc5-a5fd-16dc5cd3474d" />


2. Results:
![with and without bird](https://github.com/user-attachments/assets/43896961-40f4-4b7d-b19c-7a6731d7d4af)
** Bird sound in between 18.25s - 23.75s.


