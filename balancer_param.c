/**
 *******************************************************************************
 **	ファイル名 : balancer_param.c
 **
 **	概要       : 倒立振子制御パラメータ
 **
 ** 注記       : 倒立振子制御パラメータは制御特性に大きな影響を与えます。
 **
 *******************************************************************************
 **/

//#include "ecrobot_interface.h"

/*============================================================================
 * データ定義
 *===========================================================================*/
float A_D = 0.8F;	/* ローパスフィルタ係数(左右車輪の平均回転角度用) */
float A_R = 0.996F;	/* ローパスフィルタ係数(左右車輪の目標平均回転角度用) */

/* 
 * NOTE: When NXT standard tires are used for NXTway-GS, a compiler macro (NXT_STD_TIRE)
 *       has to be added to USER_DEF macro definition in user Makefile
 *       E.g. USER_DEF = NXT_STD_TIRE
 */

#ifdef NXT_STD_TIRE
	/* サーボ制御用状態フィードバック係数 NXT標準タイヤ */
	/* servo control state feedback gain for NXT standard tire */
	float K_F[4] = {-0.834434F, -38.1749F, -1.0985F, -3.55477F};
#else
	/* サーボ制御用状態フィードバック係数 RCX用モータサイクルタイヤ */
	float K_F[4] = {-0.870303F, -31.9978F, -1.1566F, -2.78873F};
#endif

float K_I = -0.44721F;   /* サーボ制御用積分フィードバック係数 */
float K_PHIDOT = 25.0F;  /* 車体目標旋回角速度係数 */
//float K_PHIDOT = 25.0F*2.5F;  /* 車体目標旋回角速度係数 */
float K_THETADOT = 7.5F; /* モータ目標回転角速度係数 */

const float BATTERY_GAIN = 0.001089F;	/* PWM出力算出用バッテリ電圧補正係数 */
const float BATTERY_OFFSET = 0.625F;	/* PWM出力算出用バッテリ電圧補正オフセット */

/******************************** END OF FILE ********************************/
