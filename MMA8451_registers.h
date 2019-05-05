#define XYZ_DATA_CFG 0x0E

/* Freefall/Motion Detection */
#define FF_MT_CFG   0x15 /* Configuration       */
/* BIT 0 NOT USED */
/* BIT 1 NOT USED */
/* BIT 2 NOT USED */
#define XEFE        (1 << 3)
#define YEFE        (1 << 4)
#define ZEFE        (1 << 5)
#define OAE         (1 << 6)
#define ELE         (1 << 7)

#define FF_MT_SRC   0x16 /* Source              */ 
#define FF_MT_THS   0x17 /* Theshold            */
#define FF_MT_COUNT 0x18 /* Debounce counter    */   

#define TRANS_CFG   0x1D /* Transient config    */
#define TRANS_THS   0x1F /* Transient threshold */
#define TRANS_CNT   0x20 /* Transient counter   */

/* Control Registers */
#define CTRL_REG1   0x2A /* Sys control 1       */
#define ACTIVE      (1 << 0)
#define F_READ      (1 << 1)
#define LNOISE      (1 << 2)

#define CTRL_REG2   0X2b /* Sys control 2       */

/* Interrupt Sleep Control */
#define CTRL_REG3   0x2C 
#define PP_OD       (1 << 0)    /* 0:Push-Pull 1:Open-Drain     */
#define IPOL        (1 << 1)    /* Int polarity 0:low 1:high    */
/* BIT 2 NOT USED */
#define WAKE_FF_MT  (1 << 3)    /* Freefall/Motion 0:dis 1:en   */
#define WAKE_PULSE  (1 << 4)    /* Pulse 0:dis 1:en             */
#define WAKE_LNDPRT (1 << 5)    /* Portrait/Landscape 0:dis 1:en*/
#define WAKE_TRANS  (1 << 6)    /* Transient 0:dis 1:en         */
#define FIFO_GATE   (1 << 7)    /* Fifo gate 0:bypass 1:block   */

/* Interrupt Enable 
 * All interrupts enabled when set, disabled when cleared
 * */
#define CTRL_REG4   0x2D
#define INT_EN_DRDY   (1 << 0)  /* Data Ready           */
/* BIT 1 NOT USED */
#define INT_EN_FF_MT  (1 << 2)  /* Freefall/Motion      */
#define INT_EN_PULSE  (1 << 3)  /* Pulse                */
#define INT_EN_LNDPRT (1 << 4)  /* Landscape Portrait   */
#define INT_EN_TRANS  (1 << 5)  /* Transient            */
#define INT_EN_FIFO   (1 << 6)  /* FIFO                 */
#define INT_EN_ASLP   (1 << 7)  /* Auto-Sleep/Wake      */

/* 
 * Interrupt Pin routing - 0 for INT2, 1 for INT1
 * */
#define CTRL_REG5   0x2E
#define INT_CFG_DRDY   (1 << 0)  /* Data Ready           */
/* BIT 1 NOT USED */
#define INT_CFG_FF_MT  (1 << 2)  /* Freefall/Motion      */
#define INT_CFG_PULSE  (1 << 3)  /* Pulse                */
#define INT_CFG_LNDPRT (1 << 4)  /* Landscape Portrait   */
#define INT_CFG_TRANS  (1 << 5)  /* Transient            */
#define INT_CFG_FIFO   (1 << 6)  /* FIFO                 */
#define INT_CFG_ASLP   (1 << 7)  /* Auto-Sleep/Wake      */
