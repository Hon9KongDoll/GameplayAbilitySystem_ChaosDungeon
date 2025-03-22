#include "PlayerController/ChaosDungeonPlayerController.h"
#include "Character/ChaosDungeonCharacter.h"
#include "Input/ChaosDungeonInputComponent.h"
#include "AbilitySystem/DoCAbilitySystemComponent.h"

// Engine
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/EnemyInterface.h"
#include "AbilitySystemBlueprintLibrary.h"

AChaosDungeonPlayerController::AChaosDungeonPlayerController()
{
	bReplicates = true;

	bLeftMouseDown = false;
	bRightMouseDown = false;
}

void AChaosDungeonPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

UDoCAbilitySystemComponent* AChaosDungeonPlayerController::GetDoCAbilitySystemComponent()
{
	if (DoCAbilitySystemComponent == nullptr)
	{
		return CastChecked<UDoCAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return nullptr;
}

void AChaosDungeonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetControlRotation(FRotator(-45.f, 0.f, 0.f));

	bShowMouseCursor = true;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ChaosDungeonInputMappingContext, 0);
	}
}

void AChaosDungeonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UChaosDungeonInputComponent* ChaosDungeonInputComponent = CastChecked<UChaosDungeonInputComponent>(InputComponent))
	{
		ChaosDungeonInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		ChaosDungeonInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Turn);
		ChaosDungeonInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::Zoom);
		ChaosDungeonInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
		ChaosDungeonInputComponent->BindAction(MouseLeftAction, ETriggerEvent::Started, this, &ThisClass::OnLeftMousePressed);
		ChaosDungeonInputComponent->BindAction(MouseLeftAction, ETriggerEvent::Completed, this, &ThisClass::OnLeftMouseReleased);
		ChaosDungeonInputComponent->BindAction(MouseRightAction, ETriggerEvent::Started, this, &ThisClass::OnRightMousePressed);
		ChaosDungeonInputComponent->BindAction(MouseRightAction, ETriggerEvent::Completed, this, &ThisClass::OnRightMouseReleased);

		ChaosDungeonInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	}
}

void AChaosDungeonPlayerController::Move(const FInputActionValue& Value)
{
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->bUseControllerRotationYaw = false;
	}
	
	FVector2D InputVector = Value.Get<FVector2D>();
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		// 向前方向
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

		// 旋转矩阵
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		ControllerPawn->AddMovementInput(ForwardDirection, InputVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, InputVector.X);
	}
}

void AChaosDungeonPlayerController::Turn(const FInputActionValue& Value)
{
	if (bLeftMouseDown || bRightMouseDown)
	{
		FVector2D InputVector = Value.Get<FVector2D>();
		AddYawInput(InputVector.X);
		AddPitchInput(-InputVector.Y);

		if (APawn* ControllerPawn = GetPawn<APawn>())
		{
			if (bRightMouseDown && ControllerPawn->GetVelocity().Size() == 0.f)
			{
				ControllerPawn->bUseControllerRotationYaw = true;
			}
		}
	}
}

void AChaosDungeonPlayerController::Zoom(const FInputActionValue& Value)
{
	float ZoomValue = Value.Get<float>();

	if (AChaosDungeonCharacter* ChaosDungeonCharacter = GetPawn<AChaosDungeonCharacter>())
	{
		USpringArmComponent* CameraBoom = ChaosDungeonCharacter->GetCameraBoom();
		CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength + (ZoomValue * -50.0f), 300.0f, 1200.0f);
	}
}

void AChaosDungeonPlayerController::Jump()
{
	if (AChaosDungeonCharacter* ChaosDungeonCharacter = GetPawn<AChaosDungeonCharacter>())
	{
		ChaosDungeonCharacter->Jump();
	}
}

void AChaosDungeonPlayerController::OnLeftMousePressed()
{
	bLeftMouseDown = true;
}

void AChaosDungeonPlayerController::OnLeftMouseReleased()
{
	bLeftMouseDown = false;
}

void AChaosDungeonPlayerController::OnRightMousePressed()
{
	bRightMouseDown = true;
}

void AChaosDungeonPlayerController::OnRightMouseReleased()
{
	bRightMouseDown = false;
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->bUseControllerRotationYaw = false;
	}
}

void AChaosDungeonPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr){}
		else
		{
			ThisActor->HightLightActor();
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			LastActor->UnHightLightActor();
		}
		else
		{
			if (LastActor == ThisActor){}
			else
			{
				LastActor->UnHightLightActor();
				ThisActor->HightLightActor();
			}
		}
	}
}

void AChaosDungeonPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
}

void AChaosDungeonPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GetDoCAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
}

void AChaosDungeonPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	GetDoCAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
}
