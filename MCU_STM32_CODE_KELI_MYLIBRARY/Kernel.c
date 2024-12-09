/***************************************************************************
 * @file    Kernel.c
 * @brief 	Dinh nghia cac hàm va cau tru lien quan toi kernel
 * @details File nay dinh nghia cac ham cho viec dieu khien kernel
 * @version 1.0
 * @date    2024-10-07
 * @author  NGUYEN VAN THANH
 * @website https://thanhlearningcode.github.io/Myprofile/
 ***************************************************************************/
#include "Kernel.h"
//khai bao so luong thread
tcbType tcbs[NUM_OF_THREAD];
//khai bao con tro toi thread hien tai dang chay
tcbType* currentPt;
//khoi tao vung nho stack
uint32_t TCB_STACK[NUM_OF_THREAD][STACK_SIZE];
//Set value for SysTick (to calculate quanta time)
uint32_t MILLIS_PRESCALER;
 /**************************************************************************
 * @brief   Khoi tao stack
 * @details Ham nay khoi tao stack cho tung thread
 * @param   i Thread thu i
 * @return  void
 **************************************************************************/
void osKernelStackInit ( int i ){
	//set stackPt to last data push in stack
	tcbs[i].stackPt = &TCB_STACK[i][STACK_SIZE-16];
	//chon che do Thump cho stm32
	TCB_STACK[i][STACK_SIZE-1] |= 1<<24;
	//Skip PC TCB_STACK[i][STACK_SIZE-2]
	TCB_STACK[i][STACK_SIZE-3] 	= 0xAAAAAAAA;/*R14 (LR)*/
	TCB_STACK[i][STACK_SIZE-4] 	= 0xAAAAAAAA;/*R12*/
	TCB_STACK[i][STACK_SIZE-5] 	= 0xAAAAAAAA;/*R3*/
	TCB_STACK[i][STACK_SIZE-6] 	= 0xAAAAAAAA;/*R2*/
	TCB_STACK[i][STACK_SIZE-7] 	= 0xAAAAAAAA;/*R1*/
	TCB_STACK[i][STACK_SIZE-8] 	= 0xAAAAAAAA;/*R0*/
	
	TCB_STACK[i][STACK_SIZE-9] 	= 0xAAAAAAAA; /*R11*/
	TCB_STACK[i][STACK_SIZE-10] = 0xAAAAAAAA;/*R10*/
	TCB_STACK[i][STACK_SIZE-11] = 0xAAAAAAAA;/*R9*/
	TCB_STACK[i][STACK_SIZE-12] = 0xAAAAAAAA;/*R8*/
	TCB_STACK[i][STACK_SIZE-13] = 0xAAAAAAAA;/*R7*/
	TCB_STACK[i][STACK_SIZE-14] = 0xAAAAAAAA;/*R6*/
	TCB_STACK[i][STACK_SIZE-15] = 0xAAAAAAAA;/*R5*/
	TCB_STACK[i][STACK_SIZE-16] = 0xAAAAAAAA;/*R4*/
}
 /*************************************************************************************
 * @brief   Add Thread vao OS de quan li
 * @details Ket noi cac thread thong qua nextPt, dieu huong con tro Pc
 * 					toi ham duoc goi, khoi tao Stack cho tung thread, chon thread
 * 					duoc khoi chay dau tien		
 * @param   void (*task0)(void) con tro toi task0 khong nhan tham so và co kieu tra ve là void.
 * @param   void (*task1)(void) con tro toi task1 khong nhan tham so và co kieu tra ve là void.
 * @param   void (*task2)(void) con tro toi task2 khong nhan tham so và co kieu tra ve là void.
 * @return  True
 **************************************************************************************/
uint8_t osKernelAddThread ( void (*task0)(void),void (*task1)(void),void (*task2)(void) ){
	__disable_irq();
	
	tcbs[0].nextPt = &tcbs[1]; // set nextPt cua tcb0 la tcb1
	tcbs[1].nextPt = &tcbs[2]; // set nextPt cua tcb1 la tcb2
	tcbs[2].nextPt = &tcbs[0]; // set nextPt cua tcb2 la tcb0
	
	osKernelStackInit(0); //khoi tao stack cho tcb0
	TCB_STACK[0][STACK_SIZE-2] = (uint32_t)task0; //dieu huong con tro pc cua tcb0 toi task0
	
	osKernelStackInit(1); //khoi tao stack cho tcb1
	TCB_STACK[1][STACK_SIZE-2] = (uint32_t)task1; //dieu huong con tro pc cua tcb1 toi task1
	
	osKernelStackInit(2); //khoi tao stack cho tcb2
	TCB_STACK[2][STACK_SIZE-2] = (uint32_t)task2; //dieu huong con tro pc cua tcb2 toi task2
	
	currentPt = &tcbs[0];
	__enable_irq();
	
	return 1;
}
 /*************************************************************************************
 * @brief   Thiet lap gia tri bo dem cho Systick
 * @details Xung clock noi cua stm la 72Mhz -> moi giay co 72000000 xung, 
 *	 				1ms thi se cap 72000000/1000 xung
 * @return  void
 **************************************************************************************/
void osKernelInit(void){
	//1ms
	MILLIS_PRESCALER = ( BUS_FREQ/1000 );
}
 /*****************************************************************************************
 * @brief   Khoi chay osKernel
 * @details Reset gia tri systick, set gia tri dem hien tai ve 0, thiet lap gia tri bo dem
 * 					cai dat muc do uu tien cua sys,Enable Systick va chon Internal clock la nguon cap xung
 * @param   quanta thoi gian chay moi chu ki cua 1 thread
 * @return  void
 ******************************************************************************************/
void osKernelLaunch ( uint32_t quanta ){
	/*Reset the SysTick*/
	SysTick->CTRL = SYSTICK_RST;
	/*Clear Systick current value register*/
	SysTick->VAL = 0;
	/*Load the quanta*/
	SysTick->LOAD = ( quanta*MILLIS_PRESCALER-1 );
	/*Set Systick interupt to lowest priority*/
	NVIC_SetPriority ( SysTick_IRQn, 15 );
	/*Enable Systick, select Internal clock*/
	SysTick->CTRL |= CTRL_CLCKSRC|CTRL_ENABLE;
	/*Enable Systick interupt*/
	SysTick->CTRL |= CTRL_TICKINT;
	//os launch scheduler
	osSchedulerLaunch();
}
