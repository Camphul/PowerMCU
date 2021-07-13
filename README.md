# PowerMCU
Embedded project based upon the ESP32-WROOM32 Devkit C(from AZDelivery to be exact).

This is the codebase used to manage my DIY powerbank BMS and provide smart features to it.
It will most likely be compatible if you have a smart bms from JBD/xiaoxiang with UART output.

The code aims to use the least amount of power to prolong battery life.
My powerbank will also integrate custom PCB(s) for soft latching it on/off safely.
These designs may end up in this repository later.

**DO NOT FORGET TO PUT A BIDIRECTIONAL LOGIC SHIFTER BETWEEN RX AND TX OF THE BMS.
THE BMS RUNS 5V LOGIC AND THE ESP32 3.3V**