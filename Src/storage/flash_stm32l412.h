#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>
#include <string.h>
#include <stm32l4xx.h>

#define PAGE_START_ADDRESS 0x08000000

enum {
	FLASH_PAGE_SIZE   = 2048,
	FLASH_SECTOR_SIZE = 2048,
	FLASH_BLOCK_SIZE  = 64 * FLASH_SECTOR_SIZE,
	FLASH_MEM_SIZE    = 64 * FLASH_SECTOR_SIZE, // 64 * 2048 (128kB)
};


/**
  * @brief  FLASH Cache structure definition
  */
typedef enum
{
  FLASH_CACHE_DISABLED = 0,
  FLASH_CACHE_ICACHE_ENABLED,
  FLASH_CACHE_DCACHE_ENABLED,
  FLASH_CACHE_ICACHE_DCACHE_ENABLED
} FLASH_CacheTypeDef;

/**
  * @brief  FLASH handle Structure definition
  */
typedef struct
{
  __IO uint32_t               ErrorCode;         /* FLASH error code */
  __IO uint32_t               Address;           /* Internal variable to save address selected for program in IT context */
  __IO uint32_t               Bank;              /* Internal variable to save current bank selected during erase in IT context */
  __IO uint32_t               Page;              /* Internal variable to define the current page which is erasing in IT context */
  __IO uint32_t               NbPagesToErase;    /* Internal variable to save the remaining pages to erase in IT context */
  __IO FLASH_CacheTypeDef     CacheToReactivate; /* Internal variable to indicate which caches should be reactivated */
}FLASH_ProcessTypeDef;



/* FLASH_Keys FLASH Keys*/
#define FLASH_KEY1                0x45670123U                          /*!< Flash key1 */
#define FLASH_KEY2                0xCDEF89ABU                          /*!< Flash key2: used with FLASH_KEY1
                                                                            to unlock the FLASH registers access */

#define FLASH_PDKEY1              0x04152637U                          /*!< Flash power down key1 */
#define FLASH_PDKEY2              0xFAFBFCFDU                          /*!< Flash power down key2: used with FLASH_PDKEY1
                                                                            to unlock the RUN_PD bit in FLASH_ACR */

#define FLASH_OPTKEY1             0x08192A3BU                          /*!< Flash option byte key1 */
#define FLASH_OPTKEY2             0x4C5D6E7FU                          /*!< Flash option byte key2: used with FLASH_OPTKEY1
                                                                            to allow option bytes operations */
		
																				
#define FLASH_FLAG_EOP            FLASH_SR_EOP                         /*!< FLASH End of operation flag */
#define FLASH_FLAG_OPERR          FLASH_SR_OPERR                       /*!< FLASH Operation error flag */
#define FLASH_FLAG_PROGERR        FLASH_SR_PROGERR                     /*!< FLASH Programming error flag */
#define FLASH_FLAG_WRPERR         FLASH_SR_WRPERR                      /*!< FLASH Write protection error flag */
#define FLASH_FLAG_PGAERR         FLASH_SR_PGAERR                      /*!< FLASH Programming alignment error flag */
#define FLASH_FLAG_SIZERR         FLASH_SR_SIZERR                      /*!< FLASH Size error flag  */
#define FLASH_FLAG_PGSERR         FLASH_SR_PGSERR                      /*!< FLASH Programming sequence error flag */
#define FLASH_FLAG_MISERR         FLASH_SR_MISERR                      /*!< FLASH Fast programming data miss error flag */
#define FLASH_FLAG_FASTERR        FLASH_SR_FASTERR                     /*!< FLASH Fast programming error flag */
#define FLASH_FLAG_RDERR          FLASH_SR_RDERR                       /*!< FLASH PCROP read error flag */
#define FLASH_FLAG_OPTVERR        FLASH_SR_OPTVERR                     /*!< FLASH Option validity error flag  */
#define FLASH_FLAG_BSY            FLASH_SR_BSY                         /*!< FLASH Busy flag */

#define FLASH_FLAG_ECCR_ERRORS    (FLASH_FLAG_ECCD | FLASH_FLAG_ECCC)
#define FLASH_FLAG_ECCC           FLASH_ECCR_ECCC                      /*!< FLASH ECC correction */
#define FLASH_FLAG_ECCD           FLASH_ECCR_ECCD                      /*!< FLASH ECC detection */

#define FLASH_FLAG_SR_ERRORS      (FLASH_FLAG_OPERR   | FLASH_FLAG_PROGERR | FLASH_FLAG_WRPERR | \
                                   FLASH_FLAG_PGAERR  | FLASH_FLAG_SIZERR  | FLASH_FLAG_PGSERR | \
                                   FLASH_FLAG_MISERR  | FLASH_FLAG_FASTERR | FLASH_FLAG_RDERR  | \
                                   FLASH_FLAG_OPTVERR)

#define __HAL_FLASH_DATA_CACHE_DISABLE()        CLEAR_BIT(FLASH->ACR, FLASH_ACR_DCEN)
																				
#define __HAL_FLASH_INSTRUCTION_CACHE_RESET()   do { SET_BIT(FLASH->ACR, FLASH_ACR_ICRST);   \
                                                     CLEAR_BIT(FLASH->ACR, FLASH_ACR_ICRST); \
                                                   } while (0)
													   
#define __HAL_FLASH_INSTRUCTION_CACHE_ENABLE()  SET_BIT(FLASH->ACR, FLASH_ACR_ICEN)
													   
#define __HAL_FLASH_DATA_CACHE_RESET()          do { SET_BIT(FLASH->ACR, FLASH_ACR_DCRST);   \
                                                     CLEAR_BIT(FLASH->ACR, FLASH_ACR_DCRST); \
                                                   } while (0)
													  
#define __HAL_FLASH_DATA_CACHE_ENABLE()         SET_BIT(FLASH->ACR, FLASH_ACR_DCEN)
													   
#define __HAL_FLASH_GET_FLAG(__FLAG__)          ((((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U)     ? \
                                                 (READ_BIT(FLASH->ECCR, (__FLAG__)) == (__FLAG__)) : \
                                                 (READ_BIT(FLASH->SR,   (__FLAG__)) == (__FLAG__)))

#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)        do { if(((__FLAG__) & FLASH_FLAG_ECCR_ERRORS) != 0U) { SET_BIT(FLASH->ECCR, ((__FLAG__) & FLASH_FLAG_ECCR_ERRORS)); }\
                                                     if(((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS)) != 0U) { WRITE_REG(FLASH->SR, ((__FLAG__) & ~(FLASH_FLAG_ECCR_ERRORS))); }\
                                                   } while(0)
													   

void flash_init(void);

int flash_write(uint32_t addr, const uint8_t *buf, uint8_t size);

int flash_sector_erase(uint32_t addr);

static inline void flash_set_write_protection(uint32_t mask)
{
//	*((volatile uint32_t *)&FTFA->FPROT3) = mask;
}

static inline void flash_read_buf(uint32_t addr, uint8_t *buf, uint16_t size)
{
	memcpy(buf, (uint32_t *)(addr), size);
}


#endif /* FLASH_H_ */
