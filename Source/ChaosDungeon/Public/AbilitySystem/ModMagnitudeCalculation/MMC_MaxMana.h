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

	// ���������С���� - ʵ��
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const;

private:
	// ��ϷЧ�����Բ�����
	FGameplayEffectAttributeCaptureDefinition IntelligenceDefinition;
	
};
