# Door-lock-system-using-ATmega16
Developing a system to unlock a door using a password and generating an alarm if the password is entered wrongly 3 times.

- Drivers: GPIO, Keypad, LCD, Timer, UART, I2C, EEPROM, Buzzer, and DC-Motor.

- Microcontroller: ATmega16.

-	The code is built all into functions.
-	Both microcontrollers communicate with each other using UART Protocol.
-	MicroController 1 is a Human Machine Interface that sends input from the user to Uc2.
-	MicroController 2  is a Control that takes any decision for the system.
-	Interrupts are set to a minimum as I use different configurations (Compare value) for each case using the formula:
 
Compare Value = (Seconds * F_CPU)/Prescaler


You can find a video in the compressed file attached which test the following cases :
-	Entering the correct password.
-	Entering password that contains the 0 digits.
-	Entered the password wrong 3 times.
-	Entering 2 passwords with different lengths.
-	Changing password successfully.
-	Turning on the buzzer if the password is entered 3 times incorrectly.
