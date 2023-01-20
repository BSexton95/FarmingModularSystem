// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plot.generated.h"

UCLASS()
class FARMINGMODULARSYSTEM_API APlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	/// <summary>
	/// Function is called when a seed has been planted.
	/// </summary>
	/// <param name="seedPlanted">Seed being planted</param>
	UFUNCTION()
	virtual void SeedPlanted(class ASeed* seedPlanted);

	/// <returns>true if plot has a seed</returns>
	virtual bool HasSeed() { return m_hasSeed; }

	/// <summary>
	/// Function is called when the player has pressed E
	/// </summary>
	UFUNCTION()
	virtual void Harvest();

	/// <summary>
	/// Function is called when the timer is up
	/// </summary>
	UFUNCTION()
	virtual void OnHarvest();

	UFUNCTION()
	virtual void OnWater();

	/// <returns>The timer that was created on the plot</returns>
	UFUNCTION()
	class UTimer* GetTimer() { return m_timer; }

public:
	// The mesh attached to the plot
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	// The collision box
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

private:
	// Pointer to a seed which represents a seed that has been planted on the plot
	ASeed* m_seedPlanted = nullptr;
	// Boolean indicating whether a seed is currently planted on the plot
	bool m_hasSeed = false;
	// Material for the plot
	class UMaterialInterface* m_material = nullptr;
	// pointer to a dynamic material used to change the material of the mesh
	class UMaterialInstanceDynamic* m_materialInstance = nullptr;
	// Pointer to the character class representing the player character
	class AFarmingModularSystemCharacter* m_player = nullptr;
	// Pointer to a timer that keeps track of the time passed since the seed was planted
	UTimer* m_timer = nullptr;
};
