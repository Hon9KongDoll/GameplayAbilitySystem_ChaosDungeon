#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "ChaosDungeonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UChaosDungeonInputConfig;
class UDoCAbilitySystemComponent;
struct FInputActionValue;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AChaosDungeonPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
	
	UDoCAbilitySystemComponent* GetDoCAbilitySystemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void Jump();
	void OnLeftMousePressed();
	void OnLeftMouseReleased();
	void OnRightMousePressed();
	void OnRightMouseReleased();
	void CursorTrace();
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> ChaosDungeonInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MouseLeftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MouseRightAction;

	uint32 bLeftMouseDown:1;
	uint32 bRightMouseDown:1;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UChaosDungeonInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UDoCAbilitySystemComponent> DoCAbilitySystemComponent;
};
