
#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include <pico/cyw43_arch.h>
#include "unity_config.h"
#include "test_func.h"

void setUp(void) {}

void tearDown(void) {}

char switch_case(char c) {
    if (c >= 'a' && c <= 'z') {
        return (char)(c - 'a' + 'A'); // lowercase → uppercase
    } else if (c >= 'A' && c <= 'Z') {
        return (char)(c - 'A' + 'a'); // uppercase → lowercase
    } else {
        return c; // non-alphabetic → unchanged
    }
}

//A basic test to check if the changeCase function is working with an error message if there is an incorrect return
void test_changeCase(){
    TEST_ASSERT_TRUE_MESSAGE(switch_case('a')=='A', "FLAG: Test failed - wrong character was returned (test a -> A)");
    TEST_ASSERT_TRUE_MESSAGE(switch_case('B')=='b', "FLAG: Test failed - wrong character was returned (test B -> b)");
    TEST_ASSERT_TRUE_MESSAGE(switch_case('!')=='!', "FLAG: Test failed - wrong character was returned (test ! -> !)");  
}

bool do_blink(bool on, int *count)
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
    *count += 1;
    return *count % 11 ? !on : on;
}

void test_blinking(void)
{
    int count = 0;
    bool on = 0;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    for (int i = 0; i < 500; i += 1) {
        int curr_count = count;
        bool next_on = do_blink(on, &count);
        int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        TEST_ASSERT_EQUAL_MESSAGE(gpio, on, "GPIO should be set to the state of 'on' variable.");
        TEST_ASSERT_EQUAL_MESSAGE(count, curr_count +1, "Always increment the count");
        if ((i+1) % 11) {
            TEST_ASSERT_NOT_EQUAL_MESSAGE(on, next_on, "Should toggle when count is not a multiple of 11.");
        } else {
            TEST_ASSERT_EQUAL_MESSAGE(on, next_on, "Should not toggle otherwise.");
        }
        on = next_on;
    }
}


int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    while(1) {
	sleep_ms(5000); // Give time for TTY to attach.
	printf("Start tests\n");
	UNITY_BEGIN();
	RUN_TEST(test_changeCase);
	RUN_TEST(test_blinking);
	UNITY_END();
    }
}
