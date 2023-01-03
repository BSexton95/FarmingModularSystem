// Fill out your copyright notice in the Description page of Project Settings.


#include "Plot.h"
#include "Seed.h"
#include "FarmingModularSystemCharacter.h"
#include <Components/BoxComponent.h>
#include <GameFramework/Actor.h>
#include <Engine/Engine.h>

// Sets default values
APlot::APlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plot"));
	RootComponent = Mesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(Mesh);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlot::OnOverlapBegin);
}

void APlot::SeedPlanted(ASeed* seedPlanted)
{
	/*seedPlanted->SetSeedData(m_seedPlanted->GetSeedData());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Seed added to array"));*/
}

void APlot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AFarmingModularSystemCharacter::StaticClass()))
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Press E"));
}

// Called when the game starts or when spawned
void APlot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



