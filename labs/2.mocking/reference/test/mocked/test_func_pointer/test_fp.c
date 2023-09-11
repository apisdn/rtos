#include <stdio.h>
#include <unity.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/uart.h>
#include "uart_ptr.h"

char *test_data = "hello world!\n";
char *current;

int ptr_uart_in(const struct device* dev, unsigned char *c)
{
    *c = *current;
    if (*current == '\n')
        current = test_data;
    else
        current++;
    return 0;
}

char *expected = "HELLO WORLD!\n";
char *current_expected;
void ptr_uart_out(const struct device *dev, unsigned char c)
{
    TEST_ASSERT_EQUAL_CHAR(*current_expected++, c);
}

void setUp(void)
{
    current = test_data;
    current_expected = expected;
}

void tearDown(void) {}

void test_echo_upper(void)
{
    echo_uppercase_ptr((struct device *)0, ptr_uart_in, ptr_uart_out);
}

int main (void)
{
    UNITY_BEGIN();
    RUN_TEST(test_echo_upper);
    return UNITY_END();
}
