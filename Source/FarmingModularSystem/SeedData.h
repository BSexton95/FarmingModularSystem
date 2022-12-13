// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SeedData.generated.h"

/**
 * Seed data
 */
UCLASS()
class FARMINGMODULARSYSTEM_API USeedData : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString Type;

	UPROPERTY(EditAnywhere)
	int DaysToGrowth;

};
