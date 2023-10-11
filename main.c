#include <stdio.h>
#include "NuMicro.h"
#include <string.h>
#include <stdlib.h>


int sayac=0;
int button_value=0;

void GPABGH_IRQHandler(void)
{
	
	int	say = rand();
	
	if (GPIO_GET_INT_FLAG(PB, BIT1))
	{
		GPIO_CLR_INT_FLAG(PB, BIT1);
		
		button_value++;
		
		TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1);
		TIMER_EnableInt(TIMER0);
		NVIC_EnableIRQ(TMR0_IRQn);
		TIMER_Start(TIMER0);

		if(button_value==2) {
		
		printf("engine start\n");
		
		printf("security password: %d\n" , say);
		
	}
		else if(button_value>=4) {
			
			TIMER_Close(TIMER0);
		
			PB0 = 0;
			PB6 = 0;
			PB4 = 1;
			printf("okay captain, drive safe\n");
			
		}
	}
}

void TMR0_IRQHandler(void) {

    if (TIMER_GetIntFlag(TIMER0))
    {
        TIMER_ClearIntFlag(TIMER0);
			
					sayac++;
		
					printf("tick tock: %d\n" , sayac);

					if(sayac>=10 && sayac<=14){
				
					PB6 = !PB6;
					PB0 = 0;
					printf("please check the system! \n");
						
				}
					else if (sayac<=10){
						
					PB0 = !PB0;
				
					}
					else if(sayac>14){
				
					PB5 = 1;
					PB6 = 1;
					TIMER_Close(TIMER0);
					printf("system failed, warning!\n");
							
				}
    }
		
}
void UART02_IRQHandler(void)
{
    static char buffer[100]; 
    static int bufferIndex = 0; 
    uint8_t led;
		uint16_t kod;
	
    if (UART_GET_INT_FLAG(UART0, UART_INTSTS_RDAINT_Msk))
    {
        UART_ClearIntFlag(UART0, UART_INTSTS_RDAINT_Msk);
        while (UART_IS_RX_READY(UART0))
        {				
            led = UART_READ(UART0);
					
						buffer[bufferIndex] = led;
						bufferIndex = (bufferIndex + 1);
            printf("%c", led);
					
						if(led == 0x0A){
								
								if (buffer[0] == 0x4F && buffer[1] == 0x4E)
								{
									TIMER_Close(TIMER0);	
										
									PB5 = 1;
									PB6 = 1;
									PB0 = 0;
					
									printf("\n warning! system locked \n");
									memset(buffer,0,sizeof(buffer));
									bufferIndex=0;
								}
						
								else if (buffer[0] == 0x4F && buffer[1] == 0x46 && buffer[2] == 0x46 )
								{
									TIMER_Close(TIMER0);	
									PB4 = 1;
									PB0 = 0;
									printf("\n chill, it's me \n");
									memset(buffer,0,sizeof(buffer));
									bufferIndex=0;
								}
						}
					
				}
    }
		 
				 if(UART_GET_INT_FLAG(UART0, UART_INTSTS_THREINT_Msk))
				{

						while(UART_IS_TX_FULL(UART0)) 
							
						{
								UART_WRITE(UART0, kod);
							
								buffer[bufferIndex] = kod;
								bufferIndex = (bufferIndex + 1);
								printf("%c", kod);
					
							if(kod == 0x0A){
								
								if (buffer[0] == 0x31 && buffer[1] == 0x37 && buffer[2] == 0x37 && buffer[3] == 0x37 && buffer[4] == 0x32
									&& buffer[5] == 0x30 && buffer[6] == 0x38 && buffer[7] == 0x31 && buffer[8] == 0x32 && buffer[9] == 0x37)
								{
									TIMER_Close(TIMER0);	
									
									PB0 = 0;
									PB6 = 0;
									PB4 = 1;
									printf("okay captain, drive safe\n");
								
									memset(buffer,0,sizeof(buffer));
									bufferIndex=0;
								}
						}
				}
		} 
}

void SYS_Init(void)
{

    SYS_UnlockReg();
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
	
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));
	
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));
		CLK_EnableModuleClock(TMR0_MODULE);
		CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HIRC, 0);
	
    SystemCoreClockUpdate();
	
		SYS->GPA_MFPL = SYS_GPA_MFPL_PA5MFP_UART0_TXD|SYS_GPA_MFPL_PA6MFP_UART0_RXD;
  
		
		SYS_LockReg();
}

int main()
{			
	SYS_Init();
	
	UART_Open(UART0, 9600);

	UART_EnableInt(UART0, (UART_INTEN_RDAIEN_Msk));
	UART_ClearIntFlag(UART0, UART_INTSTS_RDAINT_Msk);
	NVIC_EnableIRQ(UART02_IRQn);

	
	GPIO_SetMode(PB, BIT0, GPIO_MODE_OUTPUT);
	GPIO_SetMode(PB, BIT4, GPIO_MODE_OUTPUT);
	GPIO_SetMode(PB, BIT5, GPIO_MODE_OUTPUT);
	GPIO_SetMode(PB, BIT6, GPIO_MODE_OUTPUT);

	GPIO_SetMode(PB, BIT1, GPIO_MODE_INPUT);
	GPIO_EnableInt(PB, 1, GPIO_INT_BOTH_EDGE); 
	NVIC_EnableIRQ(GPIO_PAPB_IRQn);

	PB6 = 0;
	PB0 = 0;
	PB4 = 0;
	PB5 = 0;


	
	while (1){
		}
	
	}