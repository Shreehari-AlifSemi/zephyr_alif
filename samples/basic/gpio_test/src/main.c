#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define GREEN_LED_NODE DT_ALIAS(led0)
//#define GPIO_INPUT_NODE DT_NODELABEL(input_pin)
#define TEST_LED_NODE DT_ALIAS(test_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios);
//static const struct gpio_dt_spec gpio_input = GPIO_DT_SPEC_GET(GPIO_INPUT_NODE, gpios);

#if !DT_NODE_HAS_STATUS(TEST_LED_NODE, okay)
#error "test-led alias is not defined or enabled"
#endif
static const struct gpio_dt_spec test_gpio = GPIO_DT_SPEC_GET(TEST_LED_NODE, gpios);

LOG_MODULE_REGISTER(app);

int main()
{
  int ret;

  if (!gpio_is_ready_dt(&led))
  {
    LOG_ERR("Led not ready\n");
    return 0;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0)
  {
    LOG_ERR("Led config failed\n");
    return 0;
  }

#if 0
  if (!gpio_is_ready_dt(&gpio_input))
  {
    LOG_ERR("GPIO input not ready\n");
    return 0;
  }

  ret = gpio_pin_configure_dt(&gpio_input, GPIO_INPUT);
  if (ret < 0)
  {
    LOG_ERR("GPIO input config failed\n");
    return 0;
  }
#else

  if (!gpio_is_ready_dt(&test_gpio))
  {
    LOG_ERR("GPIO input not ready\n");
    return 0;
  }

  ret = gpio_pin_configure_dt(&test_gpio, GPIO_OUTPUT);
  if (ret < 0)
  {
    LOG_ERR("GPIO input config failed\n");
    return 0;
  }
#endif
  while (true)
  {
#if 0
    int gpio_val = gpio_pin_get_dt(&gpio_input);
    LOG_INF("Blink from HE! GPIO13_7 value: %d", gpio_val);
#else
    int gpio_val = gpio_pin_get_dt(&test_gpio);
    LOG_INF("Blink from HE! GPIO13_7 value: %d", gpio_val);
#endif
    ret = gpio_pin_toggle_dt(&led);
    if (ret < 0)
    {
      LOG_ERR("Led toggle failed");
      return 0;
    }

    k_msleep(500);
  }
}
