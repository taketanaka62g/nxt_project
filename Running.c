/*********************************************************
 * ファイル名 : Running.c
 *              rn
 * 責務       : 走行・姿勢維持
 * 作成日     : 2012.11.27
 * 作成者     : BackSLASH DESIGN Co.,Ltd
 * 修正日     : yyyy.mm.dd : Name : reason
 * 備考       :
 *********************************************************/

/**********************************************************
 * 自ヘッダ#include
 *********************************************************/
#include "Running.h"
/**********************************************************
 * システムヘッダ#include
 *********************************************************/
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h" /* 倒立振子制御用ヘッダファイル */
/**********************************************************
 * ユーザ作成ヘッダ#include
 *********************************************************/
/**********************************************************
 * #define
 *********************************************************/
#define PORT_MOTOR_R NXT_PORT_B	 /* 右サーボモータポート */
#define PORT_MOTOR_L NXT_PORT_C	 /* 左サーボモータポート */
#define PORT_GYRO    NXT_PORT_S4 /* ジャイロセンサポート */

#define GYRO_OFFSET 610 //585 /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
/**********************************************************
 * typedef
 *********************************************************/
/**********************************************************
 * enum
 *********************************************************/
typedef enum
{
	eFront			= 20,		/* 前進状態				*/
	eBack			= -30,		/* 後退状態				*/
	eNoFrontBack	= 0,		/* 前後停止状態			*/
}eFrontBackState;
typedef enum
{
	eRight			= 50,		/* 右旋回状態			*/
	eLeft			= -50,		/* 左旋回状態			*/
	eNoRightLeft	= 0,		/* 左右停止状態			*/
}eRightLeftState;
/**********************************************************
 * struct/union
 *********************************************************/
/**********************************************************
 * 変数
 *********************************************************/
static eFrontBackState FrontBackState;
static eRightLeftState RightLeftState;

/**********************************************************
 * タスク
 *********************************************************/
DeclareTask(Task_Standing);

/**********************************************************
 * 関数
 *********************************************************/
void rn_init(void);
void rn_term(void);
static void rn_setMotorSpeed(signed char pwm_left, signed char pwm_right);
static void rn_controlRobotBalance(float cmd_forward, float cmd_turn, signed char *pwm_left, signed char *pwm_right);
static void rn_running(void);

/**********************************************************
 * 関数名 ： rn_init
 * 機能　 ： 初期化処理
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
void rn_init(void)
{
  balance_init();
  rn_setMotorSpeed(0, 0);

  FrontBackState = eNoFrontBack;
  RightLeftState = eNoRightLeft;
  return;
}

/**********************************************************
 * 関数名 ： rn_term
 * 機能　 ： 終了処理
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
void rn_term(void)
{
  rn_setMotorSpeed(0, 0);
  return;
}

/**********************************************************
 * 関数名 ： rn_evFrontRun
 * 機能　 ： 前進命令
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
void rn_evFrontRun(void)
{
	switch(FrontBackState){
		case eFront:
			break;
		case eBack:
			FrontBackState = eFront;
			break;
		case eNoFrontBack:
			FrontBackState = eFront;
			break;
		default:
			break;
	}
}

/**********************************************************
 * 関数名 ： rn_evBackRun
 * 機能　 ： 後進命令
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
void rn_evBackRun(void)
{
	switch(FrontBackState){
		case eFront:
			FrontBackState = eBack;
			break;
		case eBack:
			break;
		case eNoFrontBack:
			FrontBackState = eBack;
			break;
		default:
			break;
	}
}

/**********************************************************
 * 関数名 ： rn_evStopFrontBackRun
 * 機能　 ： 前後進停止命令
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
void rn_evStopFrontBackRun(void)
{
	switch(FrontBackState){
		case eFront:
			FrontBackState = eNoFrontBack;
			break;
		case eBack:
			FrontBackState = eNoFrontBack;
			break;
		case eNoFrontBack:
			break;
		default:
			break;
	}
}


/**********************************************************
 * 関数名 ： rn_evRightRun
 * 機能　 ： 右旋回命令
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
void rn_evRightRun(void)
{
	switch(RightLeftState){
		case eRight:
			break;
		case eLeft:
			RightLeftState = eRight;
			break;
		case eNoRightLeft:
			RightLeftState = eRight;
			break;
		default:
			break;
	}
}

/**********************************************************
 * 関数名 ： rn_evLeftRun
 * 機能　 ： 左旋回命令
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
void rn_evLeftRun(void)
{
	switch(RightLeftState){
		case eRight:
			RightLeftState = eLeft;
			break;
		case eLeft:
			break;
		case eNoRightLeft:
			RightLeftState = eLeft;
			break;
		default:
			break;
	}
}

/**********************************************************
 * 関数名 ： rn_evStopRightLeftRun
 * 機能　 ： 左右旋回停止命令
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
void rn_evStopRightLeftRun(void)
{
	switch(RightLeftState){
		case eRight:
			RightLeftState = eNoRightLeft;
			break;
		case eLeft:
			RightLeftState = eNoRightLeft;
			break;
		case eNoRightLeft:
			break;
		default:
			break;
	}
}

/**********************************************************
 * 関数名 ： rn_setMotorSpeed
 * 機能　 ： モータ回転速度設定
 * 引数　 ： (1)左モータPWM出力
 *           (2)右モータPWM出力
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
static void rn_setMotorSpeed(signed char pwm_left, signed char pwm_right)
{
  nxt_motor_set_speed(PORT_MOTOR_L, pwm_left, 1);
  nxt_motor_set_speed(PORT_MOTOR_R, pwm_right, 1);
  return;
}

/**********************************************************
 * 関数名 ： rn_controlRobotBalance
 * 機能　 ： 姿勢制御
 * 引数　 ： (1)前後進命令値
 *           (2)旋回命令値
 * 戻値　 ： (1)左モータPWM出力
 *           (2)右モータPWM出力
 * 備考　 ：
 *********************************************************/
static void rn_controlRobotBalance(float cmd_forward, float cmd_turn, signed char *pwm_left, signed char *pwm_right)
{
  balance_control(cmd_forward,
		  cmd_turn,
		  (float)ecrobot_get_gyro_sensor(PORT_GYRO),
		  (float)GYRO_OFFSET,
		  (float)nxt_motor_get_count(PORT_MOTOR_L),
		  (float)nxt_motor_get_count(PORT_MOTOR_R),
		  (float)ecrobot_get_battery_voltage(),
		  pwm_left,
		  pwm_right);
  return;
}

/**********************************************************
 * 関数名 ： rn_running
 * 機能　 ： 走行処理
 * 引数　 ： 無
 * 戻値　 ： 無
 * 備考　 ：
 *********************************************************/
static void rn_running(void)
{
  signed char pwm_L, pwm_R;
  rn_controlRobotBalance(FrontBackState, RightLeftState, &pwm_L, &pwm_R);
  rn_setMotorSpeed(pwm_L, pwm_R);
  return;
}

/**********************************************************
 * タスク名 ： Task_Standing
 * 機能　   ： 走行・姿勢維持タスク
 * 備考　   ： 4msec周期起動
 *********************************************************/
TASK(Task_Standing)
{
  rn_running();
  TerminateTask();
}
