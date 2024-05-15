// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

void UState::Exec_Implementation()
{
}

void UState::CallExec()
{
	CelIndex = 0;
	Exec();
}

bool UState::CanEnterState_Implementation()
{
	return true;
}
