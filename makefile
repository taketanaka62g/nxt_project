# nxtOSEKルートディレクトリ
NXTOSEK_ROOT = ../../nxtOSEK

# ターゲット実行形式ファイル名
TARGET = sample_01_OK_8

# インクルードパス
USER_INC_PATH= $(NXTOSEK_ROOT)/ecrobot/nxtway_gs_balancer

# ライブラリ
USER_LIB = nxtway_gs_balancer

# NXT標準タイヤ使用 (not RCX用モータサイクルタイヤ)
USER_DEF = NXT_STD_TIRE

# User application source
# Cソースファイル
TARGET_SOURCES := \
	balancer_param.c \
	Robot.c \
	Running.c \
	Hook.c

# OSEK OIL file
# TOPPERS/ATK(OSEK)設定ファイル
TOPPERS_OSEK_OIL_SOURCE := ./sample_01_OK.oil

# 下記のマクロは変更しないでください
O_PATH ?= build
include $(NXTOSEK_ROOT)/ecrobot/ecrobot.mak
