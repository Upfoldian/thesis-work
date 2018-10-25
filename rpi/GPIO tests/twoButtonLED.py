from gpiozero import LED
from time import sleep

ledR = LED(17)
#ledL = LED(27)
while True:
    ledL.on()
    #ledR.off()
    sleep(1)
    ledL.off()
    #ledR.on()
    sleep(1)