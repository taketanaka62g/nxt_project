/**
 *******************************************************************************
 **	�t�@�C���� : balancer_param.c
 **
 **	�T�v       : �|���U�q����p�����[�^
 **
 ** ���L       : �|���U�q����p�����[�^�͐�������ɑ傫�ȉe����^���܂��B
 **
 *******************************************************************************
 **/

//#include "ecrobot_interface.h"

/*============================================================================
 * �f�[�^��`
 *===========================================================================*/
float A_D = 0.8F;	/* ���[�p�X�t�B���^�W��(���E�ԗւ̕��ω�]�p�x�p) */
float A_R = 0.996F;	/* ���[�p�X�t�B���^�W��(���E�ԗւ̖ڕW���ω�]�p�x�p) */

/* 
 * NOTE: When NXT standard tires are used for NXTway-GS, a compiler macro (NXT_STD_TIRE)
 *       has to be added to USER_DEF macro definition in user Makefile
 *       E.g. USER_DEF = NXT_STD_TIRE
 */

#ifdef NXT_STD_TIRE
	/* �T�[�{����p��ԃt�B�[�h�o�b�N�W�� NXT�W���^�C�� */
	/* servo control state feedback gain for NXT standard tire */
	float K_F[4] = {-0.834434F, -38.1749F, -1.0985F, -3.55477F};
#else
	/* �T�[�{����p��ԃt�B�[�h�o�b�N�W�� RCX�p���[�^�T�C�N���^�C�� */
	float K_F[4] = {-0.870303F, -31.9978F, -1.1566F, -2.78873F};
#endif

float K_I = -0.44721F;   /* �T�[�{����p�ϕ��t�B�[�h�o�b�N�W�� */
float K_PHIDOT = 25.0F;  /* �ԑ̖ڕW����p���x�W�� */
//float K_PHIDOT = 25.0F*2.5F;  /* �ԑ̖ڕW����p���x�W�� */
float K_THETADOT = 7.5F; /* ���[�^�ڕW��]�p���x�W�� */

const float BATTERY_GAIN = 0.001089F;	/* PWM�o�͎Z�o�p�o�b�e���d���␳�W�� */
const float BATTERY_OFFSET = 0.625F;	/* PWM�o�͎Z�o�p�o�b�e���d���␳�I�t�Z�b�g */

/******************************** END OF FILE ********************************/
