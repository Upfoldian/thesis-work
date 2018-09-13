File List:


- at_hc05
	- Very useful code which puts HC-05 modules in command mode where you can send commands to it via serial (e.g. AT-NAME?)
- master_hc05
	- Master code that sends data over the bluetooth module to the slave unit. Generally used to send a single character as a proof of concept
- slave_hc05
	- Slave code that accepts data over the bluetooth module. Turns an LED on or off depending on if a '1' or '0' is sent