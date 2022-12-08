// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Seed.generated.h"

UCLASS()
class FARMINGMODULARSYSTEM_API ASeed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* overlapedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,int bodyIndex, bool bFromSweep, const FHitResult& hitResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// A Sphere to detect collision
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphere;

	// Mesh component
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

	// Data of this seed
	UPROPERTY(EditAnywhere)
	class USeedData* SeedData;

};
