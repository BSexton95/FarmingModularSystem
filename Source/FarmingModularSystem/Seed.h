// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Seed.generated.h"

/// <summary>
/// This class represents a seed that can be planted on a plot
/// </summary>
UCLASS()
class FARMINGMODULARSYSTEM_API ASeed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASeed();

public:
	/// <returns>The current data stored in the seed data</returns>
	class USeedData* GetSeedData() { return SeedData; }
	/// <summary>
	/// Set the data on the seed
	/// </summary>
	/// <param name="seedData">The data to attach to the seed</param>
	void SetSeedData(USeedData* seedData) { SeedData = seedData; }

public:	
	/// <summary>
	/// This function handles the overlap events
	/// </summary>
	/// <param name="OverlappedComp">The seed</param>
	/// <param name="OtherActor">The other actor envolved in the overlap</param>
	/// <param name="OtherComp">The component on the other actor envolved in the overlap</param>
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// A Box to detect collision
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	// Mesh component
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	// Data of this seed
	UPROPERTY(EditAnywhere)
	USeedData* SeedData;

	// Pointer to the player
	UPROPERTY(EditAnywhere)
	class AFarmingModularSystemCharacter* playerCharacter;
};
