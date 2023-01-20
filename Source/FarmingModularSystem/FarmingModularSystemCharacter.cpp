// Copyright Epic Games, Inc. All Rights Reserved.

#include "FarmingModularSystemCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "SeedData.h"
#include "Seed.h"
#include "Plot.h"
#include "Timer.h"

//////////////////////////////////////////////////////////////////////////
// AFarmingModularSystemCharacter

AFarmingModularSystemCharacter::AFarmingModularSystemCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AFarmingModularSystemCharacter::OnOverlapBegin);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFarmingModularSystemCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFarmingModularSystemCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFarmingModularSystemCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFarmingModularSystemCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFarmingModularSystemCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFarmingModularSystemCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFarmingModularSystemCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFarmingModularSystemCharacter::OnResetVR);

	// Binds the OnInteract() function the every time the player presses E
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFarmingModularSystemCharacter::OnInteract);
}

void AFarmingModularSystemCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If the other acter that is involved in this overlap is a plot...
	if (APlot* plot = Cast<APlot>(OtherActor))
	{
		// ...set the pointer of the plot class to be this plot
		m_plotActor = plot;
	}
}

void AFarmingModularSystemCharacter::OnInteract()
{
	// After player presses E and if it is a plot actor...
	if (m_plotActor)
	{
		// ...set newPlot to be the plot that is being overlaped
		APlot* newPlot = m_plotActor;

		// If the plot actor is null...
		if (!newPlot)
			// ...exit this function
			return;

		// If the plot does not have a seed planted...
		if (!newPlot->HasSeed())
		{
			// If the seed array is empty...
			if (SeedArray.Num() <= 0)
				// ...exit this function
				return;
			// Otherwise...
			else
			{
				// ...Create a new seed and set it to be the first seed in the array of seeds
				ASeed* seedPlanted = SeedArray[0];
				// Create a new seed data and set it to be the data that is attached to the first seed in the array of seeds
				USeedData* seedData = seedPlanted->GetSeedData();

				// Call the plots SeedPlanted function passing the new seed in as a parameter.
				newPlot->SeedPlanted(seedPlanted);

				// Removes the seed that was planted from the arrray
				SeedArray.RemoveSingle(seedPlanted);

				GEngine->ClearOnScreenDebugMessages();
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("You Planted %s"), *seedData->SeedType()));

				FString ArrayString = " ";
				for (int i = 0; i < SeedArray.Num(); i++)
				{
					ArrayString += FString::Printf(TEXT(", %s"), *SeedArray[i]->SeedData->SeedType());
				}
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("You have left {%s}"), *ArrayString.Mid(2)));
			}
		}
		// else if there is a seed planted on the plot...
		else if (newPlot->HasSeed())
		{
			// If the timer that is on this plot is up...
			if (newPlot->GetTimer()->IsTimerUp)
			{
				// Call the plots Harvest function
				newPlot->Harvest();
			}
			// Otherwise...
			else
				// ...exit the function
				return;
		}
	}
	// Otherwise..
	else
		// ...exit function
		return;

	// Set the pointer to the plot class back to null
	m_plotActor = nullptr;
	
}

void AFarmingModularSystemCharacter::OnResetVR()
{
	// If FarmingModularSystem is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in FarmingModularSystem.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFarmingModularSystemCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AFarmingModularSystemCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AFarmingModularSystemCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFarmingModularSystemCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFarmingModularSystemCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFarmingModularSystemCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}