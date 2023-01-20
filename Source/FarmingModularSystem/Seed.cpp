// Fill out your copyright notice in the Description page of Project Settings.


#include "Seed.h"
#include <Components/BoxComponent.h>
#include <Components/MeshComponent.h>
#include "SeedData.h"
#include "FarmingModularSystemCharacter.h"
#include "Plot.h"
#include <Kismet/KismetTextLibrary.h>

// Sets default values
ASeed::ASeed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a collision box and set it as the root component
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionBox;

	// Create a mesh that is attacehd to the collision box
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	// Dynamic delegate that calls OnOverlapBegin in the ASeed class when the OnComponentBegineOverlap event is triggered
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASeed::OnOverlapBegin);
}

void ASeed::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If the other actor is the player...
	if (APawn* player = Cast<APawn>(OtherActor))
	{
		// ... set the player pawn to be a player character
		playerCharacter = Cast<AFarmingModularSystemCharacter>(player);

		// set a temp array to be the array on the player character
		TArray<ASeed*> playerCharacterArray = playerCharacter->GetSeedArray();

		// If the number of the array is at its max...
		if (playerCharacterArray.Num() == playerCharacter->MaxArraySize)
		{
			//...exit the function
			return;
		}
		// Otherwise...
		else
		{
			//...add the seed the the array
			playerCharacterArray.Add(this);
		}

		FString ArrayString = " ";
		for (int i = 0; i < playerCharacterArray.Num(); i++)
		{
			ArrayString += FString::Printf(TEXT(", %s"), *playerCharacterArray[i]->SeedData->SeedType());
			
		}
		
		GEngine->ClearOnScreenDebugMessages();
		GEngine->AddOnScreenDebugMessage(-1, FLT_MAX, FColor::Green, FString::Printf(TEXT("You are holding {%s}"), *ArrayString.Mid(2)));

		// Set the new array to be the array on the player character
		playerCharacter->SetSeedArray(playerCharacterArray);
	}
}



