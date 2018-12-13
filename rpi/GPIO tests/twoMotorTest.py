import gpiozero

from time import sleep

leftMotor = gpiozero.PWMLED(23, frequency=50)
leftDir = gpiozero.LED(24)
leftDir.off()

rightMotor = gpiozero.PWMLED(17, frequency=50)
rightDir = gpiozero.LED(27)
rightDir.off()

mode = gpiozero.LED(22)
mode.on() #Sets pin high for Phase/Enable mode (direction control)


rightMotor.value = 1
leftMotor.value = 1

sleep(1)

rightMotor.value = 0
#leftMotor.value = 0

rightDir.on()


sleep(1)

rightDir.off()

rightMotor.value = 1

sleep(1)

rightMotor.value = 0
leftMotor.value = 0