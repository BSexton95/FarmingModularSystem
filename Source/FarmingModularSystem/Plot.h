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

	void SeedPlanted(class ASeed* seedPlanted);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

private:
	ASeed* m_seedPlanted;


};
