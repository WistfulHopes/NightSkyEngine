// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "include/connection_manager.h"

/**
 * 
 */
class NIGHTSKYENGINE_API RpcConnectionManager: public ConnectionManager
{
public:
	RpcConnectionManager();
	virtual ~RpcConnectionManager() override;
	
	virtual int SendTo(const char* buffer, int len, int flags, int connection_id);
	virtual int RecvFrom(char* buffer, int len, int flags, int* connection_id);
	
	int playerIndex;
	TDoubleLinkedList<TArray<int8>> sendSchedule;
	TDoubleLinkedList<TArray<int8>> receiveSchedule;
};

