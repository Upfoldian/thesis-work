TomLSM303C.py is an edited version of the LSM303 python code by adafruit (https://github.com/adafruit/Adafruit_Python_LSM303) to work with the LSM303c.

There are a number of differences, but the most significant ones are the differences in i2c addresses and the register addresses within the chip. It's not really important to know what the differences are, but it is imperative that you read the datasheet and fully understand the changes you're making when writing to the module, as writing to the incorrect address can cause damage. Page 30 and onwards is probably the best place to be looking  when trying to figure out addresses and what values affect what. The biggest problem I faced when making this edit was that some of the default values for the magnetometer need to be changed to get constant updates rather than a single reading from when the device is first turned on.


The LSM303C datasheet (https://www.st.com/resource/en/datasheet/dm00089896.pdf) includes all the relevant addresses and unit conversions for the module data.
