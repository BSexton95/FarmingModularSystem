// Fill out your copyright notice in the Description page of Project Settings.


#include "Plot.h"/*
#include <Components/StaticMeshComponent>*/

// Sets default values
APlot::APlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plot"));
	RootComponent = Mesh;
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



