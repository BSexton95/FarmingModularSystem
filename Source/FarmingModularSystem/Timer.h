// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Timer.generated.h"

/// <summary>
/// This is a timer component that can be added to other actors in the game
/// </summary>
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMINGMODULARSYSTEM_API UTimer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimer();

public:	
	/// <summary>
	/// Called when timer should start
	/// </summary>
	UFUNCTION()
	void StartTimer();
	/// <summary>
	/// Set the plot pointer to the current plot
	/// </summary>
	/// <param name="plot">The plot</param>
	UFUNCTION()
	void SetPlot(class APlot* plot) { m_plot = plot; }
	/// <summary>
	/// Sets the seed pointer to the current seed
	/// </summary>
	/// <param name="seedPlanted">The seed planted</param>
	UFUNCTION()
	void SetSeedPlanted(class ASeed* seedPlanted) { m_seed = seedPlanted; }
	/// <summary>
	/// Sets the IsTimerUp variable to the value passed
	/// </summary>
	/// <param name="isTimerUp">Ture if timer is up</param>
	UFUNCTION()
	void SetIsTimerUp(bool isTimerUp) { IsTimerUp = isTimerUp; }
	/// <summary>
	/// Ends the timer and sets the IsTimerUp property to true
	/// </summary>
	UFUNCTION()
	void EndTimer();

public:
	//The handle for the timer, keeps track of the remaining time
	FTimerHandle TimeToGrowth;

	// Boolean for if the timer is up or not
	UPROPERTY(BlueprintReadOnly, Category = "Timer")
	bool IsTimerUp;
	
private:
	// Pointer to the seed, used to access its properties and methods
	ASeed* m_seed;
	// Pointer to the data, used to access its properties and methods
	class USeedData* m_seedData;
	// Pointer to the plot, used to access its properties an dmethods
	APlot* m_plot;
};
