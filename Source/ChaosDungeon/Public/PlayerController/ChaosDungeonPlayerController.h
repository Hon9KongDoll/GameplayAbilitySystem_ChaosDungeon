#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChaosDungeonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AChaosDungeonPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnDestinationStarted();
	void OnDestinationTriggered();
	void OnDestinationReleased();
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> ChaosDungeonInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> DestinationClickAction;

	// 按压时长
	float PressDuration;

	// 缓存目标位置
	FVector CachedDestinationLocation;
	
	// 按压时长阈值
	UPROPERTY(EditAnywhere, Category = "Input")
	float PressDurationThreshold;
};
