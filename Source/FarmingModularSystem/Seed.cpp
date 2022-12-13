// Fill out your copyright notice in the Description page of Project Settings.


#include "Seed.h"
#include <Components/SphereComponent.h>
#include <Components/MeshComponent.h>
#include "SeedData.h"

// Sets default values
ASeed::ASeed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a collision sphere and set it as the root component
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	RootComponent = CollisionSphere;

	// Create a mesh that is attacehd to the collision sphere
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	// When something collides with this seed, the OnOverlapBegin function is called.
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASeed::OnOverlapBegin);
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

void ASeed::OnOverlapBegin(UPrimitiveComponent* overlapedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int bodyIndex, bool bFromSweep, const FHitResult& hitResult)
{
	// If the other actor and the other component is not null and the other actor is not this actor...
	if (otherActor != nullptr && otherActor != this && otherComponent != nullptr)
	{
		Mesh->SetVisibility(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

