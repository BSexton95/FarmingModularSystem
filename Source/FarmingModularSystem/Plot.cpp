// Fill out your copyright notice in the Description page of Project Settings.


#include "Plot.h"
#include "Seed.h"
#include "SeedData.h"
#include <Components/BoxComponent.h>
#include <GameFramework/Actor.h>
#include <TimerManager.h>
#include <GameFramework/Controller.h>

// Sets default values
APlot::APlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plot"));
	RootComponent = Mesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(Mesh);

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

	m_seedPlanted = seedPlanted;
	m_hasSeed = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Seed has been planted"));
}

void APlot::Harvest()
{
		m_hasSeed = false;
		//m_canHarvest = false;
		UE_LOG(LogTemp, Warning, TEXT("RESET"));
}

void APlot::OnHarvest()
{
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MeshMaterial, Mesh);
	DynamicMaterial->SetVectorParameterValue(TEXT("Green"), FLinearColor::Green);

	Mesh->SetMaterial(0, DynamicMaterial);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Plant ready to be harvested"));
		
}

// Called every frame
void APlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

