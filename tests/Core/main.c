//TESTrunning MAIN.C
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"


/* Private includes ----------------------------------------------------------*/

#include "ledDriver.h"
#include "unity.h"

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LPUART1_UART_Init();

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

    // Optional: small banner so your PC script knows tests started
    UNITY_OUTPUT_CHAR('\n'); UNITY_OUTPUT_CHAR('\r');

    UNITY_BEGIN();
    RUN_TEST(test_crc_initial_value);
    RUN_TEST(test_can_encode_classic_frame);
    // ...add more RUN_TEST()s or generate this list
    int failures = UNITY_END();

    // Optionally blink or breakpoint on failures
    for(;;) { /* stay here; or NVIC_SystemReset(); */ }
}
