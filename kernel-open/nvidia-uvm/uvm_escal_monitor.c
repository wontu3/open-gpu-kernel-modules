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
	UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *_p = __sUvmEscalDevHandler;

	do {
		/* Pointer Check */
		if(__p == NULL) break;

		/* Restore HDMI Thread */
		if(gUvmEscalThread.isAlive <= 0){
			gUvmEscalThread.isAlive = 1;
			gUvmEscalThread.pThread= kthread_create( (void *)__UVM_ESCAL_MONITOR_KTHREAD, _p, "uvm_escal_daemon");
			if(gUvmEscalThread.pThread){
				UVM_ESCAL_PRINT("initialing monitor kdaemon\n");
				wake_up_process(gUvmEscalThread.pThread);
			}else {
				UVM_ESCAL_PRINT("cannot create kdaemon\n");
				break;
			}
		}
		else{
			UVM_ESCAL_PRINT("error! kdaemon already activated\n");
			break;
		}

		__ret = RET_OK;
	} while(0);	

	return __ret;
}

void UVM_ESCAL_MONITOR_PROC_PrintStatus(struct seq_file *s)
{

}


/*========================================================================================
 Static Function Implementation 
======================================================================================== */

static void __UVM_ESCAL_MONITOR_KTHREAD(volatile UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *pDevHandler)
{
	volatile UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *_p = pDevHandler;

	UVM_ESCAL_PRINT("kdaemon activated\n");
	
	/* Step 0. Set stamp to zero */
	gUvmEscalThread.stamp = 0;

	while(1)
	{
		/* Step 1. Check Force kill */
		if(gUvmEscalThread.isAlive <= 0) {
			UVM_ESCAL_PRINT("killed\n");
			break;
		}
		
		/* Describe main activity */



		/* Step last : Stamps & Iterate */
		gUvmEscalThread.stamp = 1;
		msleep(gUvmEscalThread.mSleep);
	}

	/* Exit : with Stamps & Mark */
	gUvmEscalThread.stamp = 0;
	gUvmEscalThread.isAlive = 0;

}

static void __UVM_ESCAL_MONITOR_Set_InitDevhandler(volatile UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *pDevHandler, bool isResume)
{
	volatile UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *_p = pDevHandler;

	do {
		UVM_ESCAL_PRINT("initialize uvm escal device handler\n");

		/* Check Pointer */
		if(_p == NULL) {
			UVM_ESCAL_PRINT("null pointer\n");
			break;
		}

		/* Mem set */
		memset((UVM_ESCAL_MONITOR_DEVICE_HANDLER_T *)_p, 0, sizeof(UVM_ESCAL_MONITOR_DEVICE_HANDLER_T);

	} while(0);

	return;
}
