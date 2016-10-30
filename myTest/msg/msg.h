/***************************************************************************************
建立头文件"msg.h"
****************************************************************************************/
#ifndef __MSG_H
#define __MSG_H

//////////////////////// 参数配置 ////////////////////////
//结构体_msg的数据接收器msgData最大大小
#define MSG_DATA_LEN        (20ul)

/* 消息 */
#define MSG_DATA_NONE                      0x00 //空

#define MSG_TYPE_SYSMODE_SWITCH       0x00      //模式切换
	#define MSG_DATA_SYSMODE_AUTO          0x00 //切换成自动模式
	#define MSG_DATA_SYSMODE_TP            0x01 //切换成定时器模式
	#define MSG_DATA_SYSMODE_HOLIDAY       0x02 //切换成度假模式
	#define MSG_DATA_SYSMODE_MANUAL        0x03 //切换成 Manual ONOFF模式
	#define MSG_DATA_SYSMODE_TEST          0x04 //切换成测试模式

#define MSG_TYPE_PASSWORD_RESET       0x01 //密码恢复
#define MSG_TYPE_ENERGY_DATE_UPDATE   0x02 //能源管理日期更新
#define MSG_TYPE_LAMP_LUX_UPDATE      0x03 //更新灯光亮度，并重新计算offlux

//////////////////////////////////////////////////////////


//消息队列控制块
typedef struct
{
  void **QStart;  /* Pointer to start of queue data                              */
  void **QEnd;    /* Pointer to end   of queue data                              */
  void **QIn;     /* Pointer to where next message will be inserted  in   the Q  */
  void **QOut;    /* Pointer to where next message will be extracted from the Q  */
  int  QSize;     /* Size of queue (maximum number of entries)                   */
  int  QEntries;  /* Current number of entries in the queue                      */
} _msg_q;

//消息
typedef struct {
  unsigned char msgType;                  /* Message type            */
  unsigned char msgData[MSG_DATA_LEN];    /* Message data buffer     */
  unsigned char dataSize;                 /* Length of message data  */
} _msg;

#define MSG_Q_SUCCESS         ((unsigned char)0)  //成功
#define MSG_Q_NONE            ((unsigned char)1)  //无消息，消息队列空
#define MSG_Q_FULL            ((unsigned char)2)  //消息队列满
#define MSG_Q_ERR             ((unsigned char)3)  //错误
#define MSG_MALLOC_FAILED     ((unsigned char)4)  //内存分配失败

char MsgQCreate(_msg_q* pQ, void **start, int size);
char MsgQPost(_msg_q* pQ, void* pmsg);
void* MsgQPend(_msg_q* pQ, char* err);
char MQPostMessage(_msg_q* pQ, _msg msg);
char MQGetMessage(_msg_q* pQ, _msg* msg);

#endif /*__MSG_H*/





