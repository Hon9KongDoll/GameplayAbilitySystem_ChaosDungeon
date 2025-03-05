#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChaosDungeonEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AChaosDungeonEffectActor();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

protected:
	// EditAnywhere : 用于标记 UCLASS USTRUCT UOBJECT 的成员变量，使其可以在编辑器的详情面板 DetailsPanel 中进行调整
	// 即时游戏效果类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	// 持续时间游戏效果类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
};
