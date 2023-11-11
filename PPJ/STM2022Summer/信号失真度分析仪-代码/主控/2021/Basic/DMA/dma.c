#include "dma.h"
#include "main.h"
#include "u_dma.h"
#include "adc.h"
#include "string.h"

#define TEST_LENGTH_SAMPLES 1024
#define SAMPLE_LENGTH 1024

extern volatile uint8_t dma_flag;


/* DMA Control Table  这一段是必须要有的*/
#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_ALIGN(controlTable, 1024)
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=1024
#elif defined(__GNUC__)
__attribute__ ((aligned (1024)))
#elif defined(__CC_ARM)
__align(1024)
#endif
uint8_t controlTable[1024];


extern void delay(uint16_t z);

void DMA_confing(void)
{
    MAP_DMA_enableModule();
    MAP_DMA_setControlBase(controlTable);


    MAP_DMA_disableChannelAttribute(DMA_CH7_ADC14 ,
        UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
        UDMA_ATTR_HIGH_PRIORITY |
        UDMA_ATTR_REQMASK);
    MAP_DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC14 ,
        UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
    MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14 ,
        UDMA_MODE_BASIC, (void*) &ADC14->MEM[0],
        data_array1, SAMPLE_LENGTH);
    /* Assigning/Enabling Interrupts */
    MAP_DMA_assignInterrupt(DMA_INT1, 7);
    MAP_Interrupt_enableInterrupt(INT_DMA_INT1);
    MAP_DMA_assignChannel(DMA_CH7_ADC14);
    MAP_DMA_clearInterruptFlag(7);
    MAP_Interrupt_enableMaster();
		//MAP_MAP_DMA_enableChannel(7);
		//MAP_DMA_requestSoftwareTransfer(0);
		//MAP_ADC14_enableConversion();

}

void DMA_INT1_IRQHandler(void)
{
    MAP_DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC14 ,
        UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
    MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14 ,
        UDMA_MODE_BASIC, (void*) &ADC14->MEM[0],
        data_array1, SAMPLE_LENGTH);
		Interrupt_enableInterrupt(INT_DMA_INT1);
    DMA_clearInterruptFlag(7);
    Interrupt_enableMaster();
		dma_flag=1;
		//MAP_MAP_DMA_enableChannel(7);
		//MAP_DMA_requestSoftwareTransfer(0);
		//MAP_ADC14_enableConversion();
}


