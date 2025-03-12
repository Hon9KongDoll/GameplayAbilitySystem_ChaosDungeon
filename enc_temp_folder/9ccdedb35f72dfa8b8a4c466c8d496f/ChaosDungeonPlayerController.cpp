#include "PlayerController/ChaosDungeonPlayerController.h"
#include "Character/ChaosDungeonCharacter.h"

// Engine
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/EnemyInterface.h"

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

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Turn);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::Zoom);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);

		EnhancedInputComponent->BindAction(MouseLeftAction, ETriggerEvent::Started, this, &ThisClass::OnLeftMousePressed);
		EnhancedInputComponent->BindAction(MouseLeftAction, ETriggerEvent::Completed, this, &ThisClass::OnLeftMouseReleased);

		EnhancedInputComponent->BindAction(MouseRightAction, ETriggerEvent::Started, this, &ThisClass::OnRightMousePressed);
		EnhancedInputComponent->BindAction(MouseRightAction, ETriggerEvent::Completed, this, &ThisClass::OnRightMouseReleased);
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
