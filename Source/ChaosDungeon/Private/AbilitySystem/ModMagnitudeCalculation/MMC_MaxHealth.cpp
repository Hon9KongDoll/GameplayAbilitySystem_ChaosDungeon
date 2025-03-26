#include "AbilitySystem/ModMagnitudeCalculation/MMC_MaxHealth.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// 游戏属性捕获
	VigorDefinition.AttributeToCapture = UChaosDungeonAttributeSet::GetVigorAttribute();

	// 游戏属性来源
	VigorDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	VigorDefinition.bSnapshot = false;
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// 从源和目标收集标签
	const FGameplayTagContainer* SourceTags  = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDefinition, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max(Vigor, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
