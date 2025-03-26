#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxMana.generated.h"

UCLASS()
class CHAOSDUNGEON_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxMana();

	// 计算基础大小函数 - 实现
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const;

private:
	// 游戏效果属性捕获定义
	FGameplayEffectAttributeCaptureDefinition IntelligenceDefinition;
	
};
