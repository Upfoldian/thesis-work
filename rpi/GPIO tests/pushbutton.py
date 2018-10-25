import gpiozero
from time import sleep

led= LED(17)
button = Button(27)

while True:
	if (button.is_pressed):
		sleep(0.1)
		led.on()
	else:
		led.off()