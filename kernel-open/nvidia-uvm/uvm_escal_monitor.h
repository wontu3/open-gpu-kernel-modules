/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     won.hur
 *  @version    1.0
 *  @date       2023-06-05
 *  @note       Additional information.
 */

#ifndef	_UVM_ESCAL_MONITOR_H_
#define	_UVM_ESCAL_MONITOR_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define UVM_ESCAL_THREAD_INITIAL_SLEEP_MS	(30)
	

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef
#define UVM_ESCAL_PRINT()		printk()
#endif

/**
 * Bit field mask
 * @param m	width
 * @param n shift
 */
#ifndef MSK
#define MSK(m, n)		(((1 << (m)) - 1) << (n))
#endif

/**
 * Bit mask
 * @param n shift
 */
#ifndef BIT
#define BIT(n)			MSK(1, (n))
#endif

#ifndef RET_OK
#define RET_OK		(0)
#endif

#ifndef RET_ERROR
#define RET_ERROR	(-5)
#endif

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/* Main Thread Handler */
typedef struct {
	struct task_struct* pThread;
	volatile int isAlive;
	volatile int stamp;
	int mSleep;
} UVM_ESCAL_THREAD_CONTROLLER_T;

typedef struct
{
	bool initiated;

} UVM_ESCAL_MONITOR_DEVICE_HANDLER_T;

	
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int UVM_ESCAL_Init(void);
int UVM_ESCAL_InitThread(void);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

