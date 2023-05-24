// Fill out your copyright notice in the Description page of Project Settings.


#include "RpcConnectionManager.h"


RpcConnectionManager::RpcConnectionManager()
{
}

RpcConnectionManager::~RpcConnectionManager()
{
}

int RpcConnectionManager::SendTo(const char* buffer, int len, int flags, int connection_id)
{
	TArray<int8> scheduledMessage((int8*)buffer,len);
	sendSchedule.AddTail(scheduledMessage);

	return 0;
}

int RpcConnectionManager::RecvFrom(char* buffer, int len, int flags, int* connection_id)
{
	if (receiveSchedule.Num() == 0)
		return -1;
	auto msg = receiveSchedule.GetTail();
	
	auto msgVal = msg->GetValue();
	auto rec = (char*)msgVal.GetData();
	auto leng = msgVal.Num(); // int* to char* size
	if (leng == 0)
		return -1;
	memcpy(buffer, rec, leng);
	receiveSchedule.Empty();
	*connection_id = playerIndex;
	return leng;
}
