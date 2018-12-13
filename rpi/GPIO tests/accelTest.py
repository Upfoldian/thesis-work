# Simple demo of of the LSM303 accelerometer & magnetometer library.
# Will print the accelerometer & magnetometer X, Y, Z axis values every half
# second.
# Author: Tony DiCola
# License: Public Domain
import time

# Import the LSM303 module.
import TomLSM303


# Create a LSM303 instance.
lsm303 = TomLSM303.LSM303() #check it with sudo i2cdetect -y 1 (should be 1D, 1E)

print('Printing accelerometer & magnetometer X, Y, Z axis values, press Ctrl-C to quit...')
while True:
    # Read the X, Y, Z axis acceleration values and print them.
    accel, mag = lsm303.read()
    # Grab the X, Y, Z components from the reading and print them out.
    accel_x, accel_y, accel_z = accel
    mag_x, mag_y, mag_z = mag
    #print('Accel X={0}, Accel Y={1}, Accel Z={2}, Mag X={3}, Mag Y={4}, Mag Z={5}'.format(accel_x, accel_y, accel_z, mag_x, mag_y, mag_z))
    print('AX=%04d, AY=%04d, AZ=%04d\tMX=%04d, MY=%04d, MZ=%04d' % (accel_x, accel_y, accel_z, mag_x, mag_y, mag_z) )
    # Wait half a second and repeat.
    time.sleep(0.5)