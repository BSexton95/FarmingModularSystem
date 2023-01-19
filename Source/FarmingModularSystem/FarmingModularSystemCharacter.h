// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FarmingModularSystemCharacter.generated.h"

/// <summary>
/// This class is for the player character and handles camera control, movement, and
/// temporary inventory management.
/// </summary>
UCLASS(config=Game)
class AFarmingModularSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AFarmingModularSystemCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/// <summary>
	/// Allows other class to access the array of seeds but not change it
	/// </summary>
	/// <returns>The seed array</returns>
	TArray<class ASeed*> GetSeedArray() { return SeedArray; }
	void SetSeedArray(TArray<ASeed*> newSeedArray) { SeedArray = newSeedArray; }

	/// <summary>
	/// This function handles overlap events
	/// </summary>
	/// <param name="OverlappedComp">The component on the player</param>
	/// <param name="OtherActor">The actor that is involved in the overlap</param>
	/// <param name="OtherComp">The component on the actor that is involved in the overlap</param>
	/// <param name="OtherBodyIndex">The index of the affected body of the actors physics asset(Not being used)</param>
	/// <param name="bFromSweep">Boolean indicating whether the overlap was generated as a result of a seep (Not being used)</param>
	/// <param name="SweepResult">This is a struct containing information about the hit result of the seedp if bFromSweep is true (Not being used)</param>
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// This function is called every time the player presses E
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void OnInteract();
	

public:
	//The max size of the array of seeds
	UPROPERTY(EditAnywhere)
	int MaxArraySize = 4;

private:
	// Pointer to the plot actor
	UPROPERTY()
	class APlot* m_plotActor = nullptr;

	// Pointer to seedDatat
	UPROPERTY()
	class USeedData* m_seedData = nullptr;
	
	// An array that holds seeds
	// This represents an inventory in the character class
	// Should be replaced with an inventroy system
	UPROPERTY()
	TArray<class ASeed*> SeedArray;

	//Pointer to the timer
	UPROPERTY()
	class UTimer* m_timer = nullptr;
};