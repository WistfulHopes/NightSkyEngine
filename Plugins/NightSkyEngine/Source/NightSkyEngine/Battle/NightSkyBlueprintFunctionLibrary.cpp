// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyBlueprintFunctionLibrary.h"

#include "NightSkyEngine/Battle/Globals.h"

int32 UNightSkyBlueprintFunctionLibrary::Vec2Angle_x1000(int32 x, int32 y)
{
	int32 Angle = static_cast<int>(atan2(y, x) * 57295.77791868204) % 360000;
	if (Angle < 0)
		Angle += 360000;
	return Angle;
}

int32 UNightSkyBlueprintFunctionLibrary::Cos_x1000(int32 Deg_x10)
{
	int32 Tmp1 = (Deg_x10 + 900) % 3600;
	int32 Tmp2 = Deg_x10 + 3600;
	if (Tmp1 >= 0)
		Tmp2 = Tmp1;
	if (Tmp2 < 900)
		return gSinTable[Tmp2];
	if (Tmp2 < 1800)
		return gSinTable[1799 - Tmp2];
	if (Tmp2 >= 2700)
		return -gSinTable[3599 - Tmp2];
	return -gSinTable[Tmp2 - 1800];
}

int32 UNightSkyBlueprintFunctionLibrary::Sin_x1000(int32 Deg_x10)
{
	int32 Tmp1 = Deg_x10 % 3600;
	int32 Tmp2 = Deg_x10 + 3600;
	if (Tmp1 >= 0)
		Tmp2 = Tmp1;
	if (Tmp2 < 900)
		return gSinTable[Tmp2];
	if (Tmp2 < 1800)
		return gSinTable[1799 - Tmp2];
	if (Tmp2 >= 2700)
		return -gSinTable[3599 - Tmp2];
	return -gSinTable[Tmp2 - 1800];
}
