// Fill out your copyright notice in the Description page of Project Settings.


#include "Plot.h"
#include "Seed.h"
#include "SeedData.h"
#include "FarmingModularSystemCharacter.h"
#include <Components/BoxComponent.h>
#include <GameFramework/Actor.h>
#include <TimerManager.h>

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

// Called when the game starts or when spawned
void APlot::BeginPlay()
{
	Super::BeginPlay();

}

void APlot::SeedPlanted(ASeed* seedPlanted)
{
	if (seedPlanted == nullptr)
		return;

	//m_seedPlanted->SetSeedData(m_seedPlanted->GetSeedData());
	
	

	m_hasSeed = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Seed has been planted"));
	
	//GetWorld()->GetTimerManager().SetTimer(TimerToGrowth, this, &APlot::OnHarvest, 1.0f, true, seedData->SeedGrowthTime());
	
}

void APlot::Harvest()
{
		m_hasSeed = false;
		m_canHarvest = false;
		UE_LOG(LogTemp, Warning, TEXT("RESET"));
}

void APlot::OnHarvest()
{
	if (GetWorldTimerManager().GetTimerRemaining(TimerToGrowth) <= 0)
	{
		
		GetWorldTimerManager().ClearTimer(TimerToGrowth);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Plant ready to be harvested"));
		m_canHarvest = true;
		return;
	}
	else
		return;
}

// Called every frame
void APlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (OtherActor->IsA(AFarmingModularSystemCharacter::StaticClass()))
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Press E"));*/
}

