// Fill out your copyright notice in the Description page of Project Settings.


#include "Plot.h"
#include "Seed.h"
#include "SeedData.h"
#include <Components/BoxComponent.h>
#include <GameFramework/Actor.h>
#include <GameFramework/Controller.h>
#include <Materials/MaterialInstanceDynamic.h>
#include "FarmingModularSystemCharacter.h"
#include "Timer.h"

// Sets default values
APlot::APlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Assign the mesh to a default subobject called plot and attach it to the root component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plot"));
	RootComponent = Mesh;

	// Assign the box component to a default subobject called box and attach it to the mesh
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void APlot::BeginPlay()
{
	Super::BeginPlay();

	// Set the material to be the material currently set on the mesh in the editor
	m_material = Mesh->GetMaterial(0);
	// Create and set a dynamic instance and set it to the material instance 
	m_materialInstance = Mesh->CreateAndSetMaterialInstanceDynamic(0);
}

void APlot::SeedPlanted(ASeed* seedPlanted)
{
	// If the seed that has been planted is null...
	if (seedPlanted == nullptr)
		// ...exit the function
		return;

	// Set the pointer to be the seed that has been planted
	m_seedPlanted = seedPlanted;
	// Set the boolean has seed to true
	m_hasSeed = true;

	// Create and start a timer
	m_timer = NewObject<UTimer>(this);
	// Set tje seed amd plot on the timer created
	m_timer->SetSeedPlanted(seedPlanted);
	m_timer->SetPlot(this);
	// Add the timer to the plot
	this->AddOwnedComponent(m_timer);
	// Call the timers start timer function
	m_timer->StartTimer();
}

void APlot::Harvest()
{
	// Set the boolean has seed to false
	m_hasSeed = false;

	// Change the meshs material back to red indicated ready for another seed
	m_materialInstance->SetVectorParameterValue(TEXT("Param"), FColor::Red);
}

void APlot::OnHarvest()
{
	// Sets the boolean in the timer to true indicated that the timer is up
	m_timer->SetIsTimerUp(true);
	// Resets the timer
	m_timer->EndTimer();
	// Set the meshs material to green indicated it is ready to harvest
	m_materialInstance->SetVectorParameterValue(TEXT("Param"), FColor::Green);
}