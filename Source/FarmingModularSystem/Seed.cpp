// Fill out your copyright notice in the Description page of Project Settings.


#include "Seed.h"
#include <Components/BoxComponent.h>
#include <Components/MeshComponent.h>
#include "SeedData.h"
#include "FarmingModularSystemCharacter.h"

// Sets default values
ASeed::ASeed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a collision sphere and set it as the root component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionBox;

	// Create a mesh that is attacehd to the collision sphere
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASeed::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



