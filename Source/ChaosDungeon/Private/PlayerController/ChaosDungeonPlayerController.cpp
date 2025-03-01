#include "PlayerController/ChaosDungeonPlayerController.h"

// Engine
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AChaosDungeonPlayerController::AChaosDungeonPlayerController()
{
	bReplicates = true;
	
	PressDuration = 0.f;
	PressDurationThreshold = 0.f;
	CachedDestinationLocation = FVector::ZeroVector;
}

void AChaosDungeonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(ChaosDungeonInputMappingContext);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AChaosDungeonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ChaosDungeonInputMappingContext, 0);
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(DestinationClickAction, ETriggerEvent::Started, this, &ThisClass::OnDestinationStarted);
		EnhancedInputComponent->BindAction(DestinationClickAction, ETriggerEvent::Triggered, this, &ThisClass::OnDestinationTriggered);
		EnhancedInputComponent->BindAction(DestinationClickAction, ETriggerEvent::Canceled, this, &ThisClass::OnDestinationReleased);
		EnhancedInputComponent->BindAction(DestinationClickAction, ETriggerEvent::Completed, this, &ThisClass::OnDestinationReleased);
	}
}

void AChaosDungeonPlayerController::OnDestinationStarted()
{
	StopMovement();
}

void AChaosDungeonPlayerController::OnDestinationTriggered()
{
	PressDuration += GetWorld()->GetDeltaSeconds();

	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult))
	{
		CachedDestinationLocation = HitResult.Location;
	}
	
	if (APawn* ControlledPawn = GetPawn())
	{
		FVector WorldDirection = (CachedDestinationLocation - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AChaosDungeonPlayerController::OnDestinationReleased()
{
	if (PressDuration <= PressDurationThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestinationLocation);
	}

	PressDuration = 0.f;
}
