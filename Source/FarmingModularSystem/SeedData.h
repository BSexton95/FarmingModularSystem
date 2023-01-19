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
public:
	/// <returns>What type of seed it is</returns>
	FString SeedType() { return Type; }
	
	/// <returns>The time it takes for the seed to grow</returns>
	float SeedGrowthTime() { return TimeToGrowth; }

public:
	// The type of plant
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type;

	// The time to growth
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToGrowth;

};
