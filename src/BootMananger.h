//
// Created by luca on 7/12/21.
//

#ifndef POWERMCU_BOOTMANANGER_H
#define POWERMCU_BOOTMANANGER_H

enum BootResponse {
    BOOT_OK,
    BOOT_FAILED,
    BOOT_SECTION_OK,
    BOOT_SECTION_FAILED,
};

/**
 * Class which manages the booting sequence of the mcu
 */
class BootMananger {
public:
    BootMananger();

    /**
     * Starts boot sequence and maintains power
     */
    BootResponse coreBootInit();

    /**
     * Register basic and simple IO pins
     */
    BootResponse registerBasicIO();

    /**
     * Register any i2c interfaces required
     */
    BootResponse registerIIC();

    /**
     * Registers tasks and services
     * @return
     */
    BootResponse initTasksAndServices();

    /**
     * After succesful boot sequence we want to launch sysInit
     */
    void sysInit();

    /**
     * Starts entire boot sequence
     * @return
     */
    BootResponse startSequence();

};

#endif //POWERMCU_BOOTMANANGER_H
