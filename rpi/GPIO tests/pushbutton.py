import gpiozero

from time import sleep

leftMotor = gpiozero.PWMLED(17, frequency=50)

count = 0
up = True

while True:
	leftMotor = count/100.0
	
	if up:
		count+= 1
	else:
		count-=1

	if (count == 100):
		up = False
	elif (count == 0):
		up = True

	sleep(0.05)
	print(count)
