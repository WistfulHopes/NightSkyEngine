// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(State)

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
