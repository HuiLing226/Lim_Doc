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
