# nxtOSEK���[�g�f�B���N�g��
NXTOSEK_ROOT = ../../nxtOSEK

# �^�[�Q�b�g���s�`���t�@�C����
TARGET = sample_01_OK_8

# �C���N���[�h�p�X
USER_INC_PATH= $(NXTOSEK_ROOT)/ecrobot/nxtway_gs_balancer

# ���C�u����
USER_LIB = nxtway_gs_balancer

# NXT�W���^�C���g�p (not RCX�p���[�^�T�C�N���^�C��)
USER_DEF = NXT_STD_TIRE

# User application source
# C�\�[�X�t�@�C��
TARGET_SOURCES := \
	balancer_param.c \
	Robot.c \
	Running.c \
	Hook.c

# OSEK OIL file
# TOPPERS/ATK(OSEK)�ݒ�t�@�C��
TOPPERS_OSEK_OIL_SOURCE := ./sample_01_OK.oil

# ���L�̃}�N���͕ύX���Ȃ��ł�������
O_PATH ?= build
include $(NXTOSEK_ROOT)/ecrobot/ecrobot.mak
