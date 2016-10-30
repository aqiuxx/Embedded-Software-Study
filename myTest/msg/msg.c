/***************************************************************************************
建立源文件"msg.c"
****************************************************************************************/
#include "msg.h"
#include "stdlib.h"

//////////////////////// 消息队列 ////////////////////////
//消息队列发送的是消息指针

/*
 @FUNCTION  创建消息队列
 @INPUT     pQ    消息队列控制块
            start 消息队列首地址
            size  消息队列大小
 @OUTPUT    MSG_Q_ERR      创建消息队列失败，数据错误
            MSG_Q_SUCCESS  创建消息队列成功
 **/
char MsgQCreate(_msg_q* pQ, void **start, int size)
{
	if(pQ == 0 || start == 0 || size == 0)
	{
		return MSG_Q_ERR;
	}
	else
	{
		pQ->QStart   = start;
		pQ->QEnd     = &start[size];
		pQ->QIn      = start;
		pQ->QOut     = start;
		pQ->QSize    = size;
		pQ->QEntries = 0u;
		
		return MSG_Q_SUCCESS;
	}
}

/*
 @Function : 发送消息指针
 @Input	    : pQ   消息队列控制块
             pmsg 消息指针
 @Output   : MSG_Q_SUCCESS  发送成功
             MSG_Q_FULL     消息队列已满
             MSG_Q_ERR      数据错误
 **/
char MsgQPost(_msg_q* pQ, void* pmsg)
{
	if(pQ == 0 || pmsg == 0)
	{
		return MSG_Q_ERR;
	}
	if(pQ->QEntries >= pQ->QSize)
	{
		return MSG_Q_FULL; 
	}
	pQ->QEntries++;
	*pQ->QIn++ = pmsg;
	if(pQ->QIn == pQ->QEnd)
	{
		pQ->QIn = pQ->QStart;
	}

	return MSG_Q_SUCCESS;
}

/*
 @Function : 请求消息队列
 @Input	    : pQ   消息队列控制块
             err  错误信息
                      MSG_Q_SUCCESS  发送成功
                      MSG_Q_NONE     消息队列空
                      MSG_Q_ERR      数据错误
 @Output   : 消息指针接收器
 **/
void* MsgQPend(_msg_q* pQ, char* err)
{
	void* pmsg = NULL;

	if(pQ == 0)
	{
		*err = MSG_Q_ERR;
	}
	else if(pQ->QEntries <= 0)
	{
		*err = MSG_Q_NONE;
	}
	else
	{
		pmsg = *pQ->QOut++;
		pQ->QEntries--;
		if(pQ->QOut == pQ->QEnd)
		{
			pQ->QOut = pQ->QStart;
		}
		*err = MSG_Q_SUCCESS;
	}
	return pmsg;
}

/*
 @Function : 数据复制
 @Input	    : ptrdes
             ptrsrc
             len    复制的字节长度
 @Output   : 目的地址
 **/
static void* mymemcpy(void* pdes, void* psrc, unsigned int len)
{
	char* ptrdes = (char*)pdes; 
	char* ptrsrc = (char*)psrc;

	if(pdes == 0 || psrc == 0)
		return pdes;
	if(ptrdes>ptrsrc?(ptrdes-ptrsrc<len):(ptrsrc-ptrdes<len))//有重叠
	{
		return pdes;
	}	
    while(len--)
    {
        *ptrdes++ = *ptrsrc++;
    }
	return pdes;
}

//////////////////////// 消息的发送和接收 ////////////////////////
//消息发送的是消息内容，消息以结构体_msg封装起来
//将消息内容复制存放在一个新分配的内存空间中再将此空间指针进行传递，
//MQGetMessage接收到指针后将该空间内容复制出来，而后再释放掉该空间。

/*
 @Function : 发送消息
 @Input	    : pQ  消息队列控制块
             msg 消息
 @Output   : MSG_Q_SUCCESS      发送成功
             MSG_MALLOC_FAILED  内存分配失败
             其他
 **/
char MQPostMessage(_msg_q* pQ, _msg msg)
{
	unsigned char *buffer;
	char res;

	buffer = (unsigned char *)malloc(2+msg.dataSize);
	if(buffer == 0)
	{
		buffer = (unsigned char *)malloc(2+msg.dataSize);
		if(buffer == 0)
		{
			return MSG_MALLOC_FAILED;
		}
	}

	buffer[0] = msg.msgType;
	buffer[1] = msg.dataSize;
	mymemcpy(&buffer[2], msg.msgData, (unsigned int)msg.dataSize);
	
	res = MsgQPost(pQ, (void*)buffer);

	return res;
}

/*
 @Function : 接收消息
 @Input	    : pQ            消息队列控制块
             msg           消息接收器
 @Output   : MSG_Q_SUCCESS 接收成功
             其他
 **/
char MQGetMessage(_msg_q* pQ, _msg* msg)
{
	unsigned char* buffer;
	char res;
	
	buffer = (unsigned char*)MsgQPend(pQ, &res);
	if(res == MSG_Q_SUCCESS)
	{
		msg->msgType  = buffer[0];
		msg->dataSize = buffer[1];
		mymemcpy(msg->msgData, &buffer[2], (unsigned int)msg->dataSize);
		free(buffer);
	}
	return res;
}
