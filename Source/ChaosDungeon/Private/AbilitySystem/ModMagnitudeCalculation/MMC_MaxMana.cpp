#include "AbilitySystem/ModMagnitudeCalculation/MMC_MaxMana.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	// 游戏属性捕获
	IntelligenceDefinition.AttributeToCapture = UChaosDungeonAttributeSet::GetIntelligenceAttribute();

	// 游戏属性来源
	IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	IntelligenceDefinition.bSnapshot = false;
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// 从源和目标收集标签
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDefinition, Spec, EvaluateParameters, Intelligence);
	Intelligence = FMath::Max(Intelligence, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f + 2.5f * Intelligence + 15.f * PlayerLevel;
}
