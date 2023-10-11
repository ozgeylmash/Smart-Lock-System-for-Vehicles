# Smart Lock System for Vehicles
In my project developed taking into account the exemption for the locking system in cars, the aim is to prevent unauthorized access by foreign individuals. When the vehicle owner starts the engine, an alert sound, which serves as an indicator that the system is active, will remind the vehicle owner. If the user interferes with the touch sensor, the system will disable itself by switching to a secure mode.

If no interference is made to the sensor within 10 seconds, a warning notification will be sent to the vehicle owner's phone. If a negative response is received from the sent notification, or if there is no interference during the warning period, the system will switch to a danger mode, locking the car doors and stopping the engine.

In this project, I used the Nuvoton M032LD2AE card as the processor. I provided the notification messages sent to the phone using the HM-10 Bluetooth module via UART. The touchpad and buzzer handle the alert and control tasks. The green, yellow, and red LEDs I used represent the sensor status; if it's in a secure mode, the green LED is active, if it's in standby mode, the yellow LED is active, and if it switches to danger mode, the red LED is actively lit.
