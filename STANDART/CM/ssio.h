#ifndef ssio
#define ssio

    void        sio_start(void);

    word read_ssio(LPC_SSP_TypeDef *SSPx);
    void write_ssio(LPC_SSP_TypeDef *SSPx, word in);
    word read_write_ssio(LPC_SSP_TypeDef *SSPx, word in);



/* --------------------- BIT DEFINITIONS -------------------------------------- */
/*********************************************************************//**
 * Macro defines for CR0 register
 **********************************************************************/
/** SSP data size select, must be 4 bits to 16 bits */
#define SSP_CR0_DSS(n)   		((uint32_t)((n-1)&0xF))
/** SSP control 0 Motorola SPI mode */
#define SSP_CR0_FRF_SPI  		((uint32_t)(0<<4))
/** SSP control 0 TI synchronous serial mode */
#define SSP_CR0_FRF_TI   		((uint32_t)(1<<4))
/** SSP control 0 National Micro-wire mode */
#define SSP_CR0_FRF_MICROWIRE  	((uint32_t)(2<<4))
/** SPI clock polarity bit (used in SPI mode only), (1) = maintains the
   bus clock high between frames, (0) = low */
#define SSP_CR0_CPOL_HI		((uint32_t)(1<<6))
/** SPI clock out phase bit (used in SPI mode only), (1) = captures data
   on the second clock transition of the frame, (0) = first */
#define SSP_CR0_CPHA_SECOND	((uint32_t)(1<<7))
/** SSP serial clock rate value load macro, divider rate is
   PERIPH_CLK / (cpsr * (SCR + 1)) */
#define SSP_CR0_SCR(n)   	((uint32_t)((n&0xFF)<<8))
/** SSP CR0 bit mask */
#define SSP_CR0_BITMASK		((uint32_t)(0xFFFF))

/*********************************************************************//**
 * Macro defines for CR1 register
 **********************************************************************/
/** SSP control 1 loopback mode enable bit */
#define SSP_CR1_LBM_EN		((uint32_t)(1<<0))
/** SSP control 1 enable bit */
#define SSP_CR1_SSP_EN		((uint32_t)(1<<1))
/** SSP control 1 slave enable */
#define SSP_CR1_SLAVE_EN	((uint32_t)(1<<2))
/** SSP control 1 slave out disable bit, disables transmit line in slave
   mode */
#define SSP_CR1_SO_DISABLE	((uint32_t)(1<<3))
/** SSP CR1 bit mask */
#define SSP_CR1_BITMASK		((uint32_t)(0x0F))

/*********************************************************************//**
 * Macro defines for DR register
 **********************************************************************/
/** SSP data bit mask */
#define SSP_DR_BITMASK(n)   ((n)&0xFFFF)

/*********************************************************************//**
 * Macro defines for SR register
 **********************************************************************/
/** SSP status TX FIFO Empty bit */
#define SSP_SR_TFE      ((uint32_t)(1<<0))
/** SSP status TX FIFO not full bit */
#define SSP_SR_TNF      ((uint32_t)(1<<1))
/** SSP status RX FIFO not empty bit */
#define SSP_SR_RNE      ((uint32_t)(1<<2))
/** SSP status RX FIFO full bit */
#define SSP_SR_RFF      ((uint32_t)(1<<3))
/** SSP status SSP Busy bit */
#define SSP_SR_BSY      ((uint32_t)(1<<4))
/** SSP SR bit mask */
#define SSP_SR_BITMASK	((uint32_t)(0x1F))

/*********************************************************************//**
 * Macro defines for CPSR register
 **********************************************************************/
/** SSP clock prescaler */
#define SSP_CPSR_CPDVSR(n) 	((uint32_t)(n&0xFF))
/** SSP CPSR bit mask */
#define SSP_CPSR_BITMASK	((uint32_t)(0xFF))

#define  sio_out(out)  write_ssio(_SPP_S500, (w)out);

#define  sio_in(inp)   inp = read_ssio(_SPP_S500);

#endif
