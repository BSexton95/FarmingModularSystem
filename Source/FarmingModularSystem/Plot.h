// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plot.generated.h"

//DECLARE_DELEGATE(FInteractDelegate);

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

	void SeedPlanted(class ASeed* seedPlanted);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void Interact(AFarmingModularSystemCharacter* player);

public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	/*UPROPERTY()
	FInteractDelegate InteractDelegate;*/
	//AFarmingModularSystemCharacter* m_player;
private:
	ASeed* m_seedPlanted;
	
};
