#include "sys.h"

void WFI_SET(void)
{
	__ASM volatile("wfi");
}

//  Close all interupts
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}

// Open all interupts
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");
}

// Set stack-top pointer
// addr: Stack-top pointer
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0
    BX r14
}

void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
