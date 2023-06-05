/** @file 
 *
 *  Brief description. 
 *  Detailed description starts here. 
 *
 *  @author		won.hur
 *  @version	1.0 
 *  @date		2023-06-05
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/delay.h>
#include <linux/kthread.h>


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
static const char __FUNC__[] = "function-name";

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static void __UVM_ESCAL_MONITOR_KTHREAD(void);
static void __UVM_ESCAL_MONITOR_Set_InitDevhandler(volatile UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *pDevHandler, bool isResume);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
gUvmEscalThread = {NULL, 0, 0, UVM_ESCAL_THREAD_INITIAL_SLEEP_MS, 0};


/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/
static volatile UVM_ESCAL_MONITOR_DEVICE_HANDLER_T __sUvmEscalDevHandler;


/*========================================================================================
	Implementation Group
========================================================================================*/
int UVM_ESCAL_Init(void)
{
	int __ret = RET_ERROR;

	do {
		/* Step 1 : Maybe need to avoid multiple inits... */

		/* Step 2 : Need to initiate device handler */
		__UVM_ESCAL_MONITOR_Set_InitDevhandler(&__sUvmEscalDevHandler, 0);

		/* Last */
		__ret = RET_OK;
	} while(0);	

	return __ret;
}


int UVM_ESCAL_InitThread(void)
{
	int __ret = RET_ERROR;

	do {
		/* Restore HDMI Thread */
		if(gUvmEscalThread.isAlive <= 0){
			gUvmEscalThread.isAlive = 1;
			gUvmEscalThread.pThread= kthread_create( (void *)__UVM_ESCAL_MONITOR_KTHREAD, 0, "uvm_escal_daemon");
			if(gUvmEscalThread.pThread){
				UVM_ESCAL_PRINT("[ESCAL][%s:%d] : Initialing monitor kdaemon\n", __FUNC__, __LINE__);
				wake_up_process(gUvmEscalThread.pThread);
			}else {
				UVM_ESCAL_PRINT("[ESCAL][%s:%d] : Cannot create kdaemon\n", __FUNC__, __LINE__);
				break;
			}
		}
		else{
			UVM_ESCAL_PRINT("[ESCAL][%s:%d] : Error! ESCAL kdaemon already activated\n", __FUNC__, __LINE__);
			break;
		}

		__ret = RET_OK;
	} while(0);	

	return __ret;
}



/*========================================================================================
 Static Function Implementation 
======================================================================================== */

static void __UVM_ESCAL_MONITOR_KTHREAD(void)
{



}

static void __UVM_ESCAL_MONITOR_Set_InitDevhandler(volatile UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *pDevHandler, bool isResume)
{
	volatile UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *_p = pDevHandler;

	do {
		UVM_ESCAL_PRINT("[ESCAL] : Initialize UVM ESCAL device handler\n");

		/* Check Pointer */
		if(_p == NULL) {
			UVM_ESCAL_PRINT("[ESCAL][%s:%d] : Null Pointer\n", __FUNC__, __LINE__);
			break;
		}

		/* Mem set */
		memset((UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *)_p, 0, sizeof(UVM_ESCAL_MONITOR_DEVICE_HANDLER_T);

	} while(0);

	return;
}
