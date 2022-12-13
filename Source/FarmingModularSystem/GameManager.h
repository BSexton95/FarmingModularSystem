// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class FARMINGMODULARSYSTEM_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnPlantSeed(class ASeed* seed);
	void OnHarvestPlant(ASeed* seed);
	bool CanPlantSeed();
	
public:
	int CurrentDay;
	ASeed* SeedPlanted;

	static AGameManager* instance;
};
