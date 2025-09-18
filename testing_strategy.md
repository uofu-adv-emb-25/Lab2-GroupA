Following Group B's Strategy, we will:

1. Document the expected functionality of the tests we perform
2. Connect to the target Pico over UART via the debugger Pico on the serial monitor
3. Test flashing test.c and hello_freertos.c executables work
4. Test blinking speed of led changes as vTaskDelay duration is changed
5. Test that sending lower/upper case chars over the serial monitor returns the opposite case (i.e. A --> a, B --> b)
6. Test that non-alphabetic characters are returned as they were entered in the terminal
7. Discuss and investigate tests that (may) fail