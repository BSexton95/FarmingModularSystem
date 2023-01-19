// Fill out your copyright notice in the Description page of Project Settings.


#include "Timer.h"
#include "Seed.h"
#include "SeedData.h"
#include "Plot.h"

// Sets default values for this component's properties
UTimer::UTimer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTimer::StartTimer()
{
	// Set the IsTimerUp to false
	IsTimerUp = false;
	// Set the data on the seed to be the seed that was passed in data
	m_seedData = m_seed->GetSeedData();
	// Call function in the timer manger to start the timer
	// The OnHarvest function is called with the time is up
	GetWorld()->GetTimerManager().SetTimer(TimeToGrowth, m_plot, &APlot::OnHarvest, m_seedData->SeedGrowthTime(), true);
}

void UTimer::EndTimer()
{
	// Clears the timer
	GetWorld()->GetTimerManager().ClearTimer(TimeToGrowth);
}

