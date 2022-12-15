// Fill out your copyright notice in the Description page of Project Settings.


#include "SeedData.h"

void USeedData::PrintObjectInfo()
{
	UE_LOG(LogType, Display, TEXT("Type: %s, Days To Growth: %d"), *Type, DaysToGrowth);
}