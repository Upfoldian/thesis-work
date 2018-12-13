import gpiozero

from time import sleep

leftMotor = gpiozero.PWMLED(23, frequency=50)
leftDir = gpiozero.LED(24)


while True:
	count = 1
	up = True
	dir = True
	leftDir.off()
	print("Start")
	while dir == True:
		leftMotor.value = count/100.0
		print(leftMotor.value)
		if up:
			count+= 1
		else:
			count-=1
		if (count == 100):
			up = False
		elif (count == 0):
			dir = False
			count = 1
		sleep(0.03)
	sleep(2)
	leftDir.on()
	up = False
	count = 99
	print("Switch")
	while dir == False:
		leftMotor.value = count/100.0
		print(leftMotor.value)
		if up:
			count+= 1
		else:
			count-=1
		if (count == 100):
			up = False
			dir = True
		elif (count == 0):
			up = True
		sleep(0.03)
	sleep(2)
	
