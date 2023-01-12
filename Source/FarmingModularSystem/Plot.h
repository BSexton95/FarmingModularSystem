// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plot.generated.h"

class ASeed;

//DECLARE_DELEGATE_OneParam(FOnSeedPlantedDelegate, ASeed*);

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SeedPlanted(class ASeed* seedPlanted);

	/// <returns>true if plot has a seed</returns>
	bool HasSeed() { return m_hasSeed; }

	UFUNCTION()
	void Harvest();

	bool CanHarvest() { return m_canHarvest; }

	void OnHarvest();

public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	FTimerHandle TimerToGrowth;
	//FOnSeedPlantedDelegate OnSeedPlanted;

private:
	ASeed* m_seedPlanted;
	bool m_hasSeed = false;
	bool m_canHarvest = false;
	
};
