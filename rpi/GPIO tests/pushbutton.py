from gpiozero import LED
from gpiozero import Button
from time import sleep

led= LED(17)
button = Button(27)
print("start!")
while True:
	if (button.is_pressed):
		led.on()
		print("button on")
	else:
		led.off()