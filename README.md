# motion_controller
A motion_controller based on DSP.
This project uses a tms320f28335,with CAN bus and SPI bus.
Use a differential line driver chip--am26ls31 to enhance the stability in transform.
I use Can-interrupt and Timer0-interrupt to handle the data.
In the Timer0,use pid to control two motor-drivers.
