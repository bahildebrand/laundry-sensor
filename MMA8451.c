#include <i2c/i2c.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "MMA8451_registers.h"

#define I2C_BUS 0
#define SCL_PIN (5)
#define SDA_PIN (4)

#define DEV_ADDR 0x1D
#define MTN_INT_PIN 14

typedef struct
{
    uint8_t reg;
    uint8_t val;
} reg_struct;

const reg_struct motion_regs[] = {
    {CTRL_REG1, 0x18},
    {FF_MT_CFG, XEFE | YEFE | OAE | ELE},
    {FF_MT_THS, 0x02},
    {FF_MT_COUNT, 0x05},
    {CTRL_REG3, WAKE_FF_MT},
    {CTRL_REG4, INT_EN_FF_MT},
    {CTRL_REG5, INT_CFG_FF_MT},
    {XYZ_DATA_CFG, 0x02},
};

const reg_struct transient_regs[] = {
    {CTRL_REG1, 0x0},
    // {CTRL_REG1, 0x3},
    {TRANS_CFG, 0x16},
    {TRANS_THS, 0x08},
    {TRANS_CNT, 0x05},
    {CTRL_REG4, 0x20},
    {CTRL_REG5, 0x20},
};

/**
 * @brief I2C register write helper funciton
 *
 * @param reg_data
 * @param reg_addr
 * @return int
 */
static int i2c_reg_write(uint8_t reg_data, uint8_t reg_addr)
{
    return i2c_slave_write(I2C_BUS, DEV_ADDR, &reg_addr, &reg_data, 1);
}

/**
 * @brief Set the MMA8451Q reset bit and wait for status register to clear
 *
 */
static void reset_and_wait()
{
    uint8_t reset_wait;
    const uint8_t reg = CTRL_REG2;
    i2c_reg_write(reg, 0x40);
    do
    {
        i2c_slave_read(I2C_BUS, DEV_ADDR, &reg, &reset_wait, 1);
    }while(reset_wait);
}

/**
 * @brief Configure registers defined in an array of registers
 *
 * @param regs
 * @param cnt
 */
static void config_regs(const reg_struct * regs, size_t cnt)
{
    uint8_t i;
    for(i = 0; i < cnt; i++)
    {
        i2c_reg_write(regs[i].val, regs[i].reg);
    }
}

/**
 * @brief Interrupt handler for transient event
 *
 * @param gpio_num
 */
void transient_intr_handler(uint8_t gpio_num)
{
    uint8_t data;
    uint8_t reg = 0x1E;

    //clear interrupt
    i2c_slave_read(I2C_BUS, DEV_ADDR, &reg, &data, 1);
    printf("motion hit\n");
}

/**
 * @brief Set the up transient intterrupt
 *
 */
void setup_transient_int()
{
    config_regs(transient_regs, sizeof(transient_regs) / sizeof(reg_struct));
    gpio_enable(MTN_INT_PIN, GPIO_INPUT);
    gpio_set_interrupt(MTN_INT_PIN, GPIO_INTTYPE_EDGE_NEG, transient_intr_handler);
}

/**
 * @brief Read current accel data
 *
 * @return uint32_t Data is returned in the following format:
 *
 * MSB                          LSB
 * 00000000ZZZZZZZZYYYYYYYYXXXXXXXX
 */
uint32_t read_accel()
{
    uint8_t data;
    uint8_t reg;
    uint32_t combined_read;
    //clear interrupt

    reg = OUT_X_MSB;
    i2c_slave_read(I2C_BUS, DEV_ADDR, &reg, &data, 1);
    combined_read = (uint32_t)data;
    printf("X: %d\n", data);

    reg = OUT_Y_MSB;
    i2c_slave_read(I2C_BUS, DEV_ADDR, &reg, &data, 1);
    combined_read |= (uint32_t)data << 8;
    printf("Y: %d\n", data);

    reg = OUT_Z_MSB;
    i2c_slave_read(I2C_BUS, DEV_ADDR, &reg, &data, 1);
    combined_read |= (uint32_t)data << 16;
    printf("Z: %d\n", data);

    return combined_read;
}

/**
 * @brief Initialize I2C bus and reset chip
 *
 */
void accel_init()
{
    i2c_init(I2C_BUS, SCL_PIN, SDA_PIN, I2C_FREQ_100K);
    reset_and_wait();
    uint8_t data;
    uint8_t reg = CTRL_REG1;
    //Keep contents of reg, but set bit 0(active bit)
    i2c_slave_read(I2C_BUS, DEV_ADDR, &reg, &data, 1);
    i2c_reg_write(data | 1, CTRL_REG1);
}