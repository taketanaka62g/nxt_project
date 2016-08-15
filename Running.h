/*********************************************************
 * ファイル名 : Running.h
 * 責務       : 走行・姿勢維持
 * 作成日     : 2012.11.27
 * 作成者     : BackSLASH DESIGN Co.,Ltd
 * 修正日     : yyyy.mm.dd : Name : reason
 * 備考       : 
 *********************************************************/

/**********************************************************
 * システムヘッダ#include
 *********************************************************/
/**********************************************************
 * ユーザ作成ヘッダ#include
 *********************************************************/
/**********************************************************
 * #define
 *********************************************************/
/**********************************************************
 * typedef
 *********************************************************/
/**********************************************************
 * enum
 *********************************************************/
/**********************************************************
 * struct/union
 *********************************************************/
/**********************************************************
 * extern変数宣言(出来る限り無し)
 *********************************************************/
/**********************************************************
 * extern関数宣言
 *********************************************************/
extern void rn_init(void);
extern void rn_term(void);
extern void rn_evFrontRun(void);
extern void rn_evBackRun(void);
extern void rn_evStopFrontBackRun(void);
extern void rn_evRightRun(void);
extern void rn_evLeftRun(void);
extern void rn_evStopRightLeftRun(void);
