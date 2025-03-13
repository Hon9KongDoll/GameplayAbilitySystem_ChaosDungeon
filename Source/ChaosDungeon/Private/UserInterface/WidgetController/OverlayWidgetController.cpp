#include "UserInterface/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"
#include "AbilitySystem/DoCAbilitySystemComponent.h"

// Engine
#include "GameplayEffectTypes.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	if (const UChaosDungeonAttributeSet* ChaosDungeonAttributeSet = Cast<UChaosDungeonAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(ChaosDungeonAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(ChaosDungeonAttributeSet->GetMaxHealth());
		OnManaChanged.Broadcast(ChaosDungeonAttributeSet->GetMana());
		OnMaxManaChanged.Broadcast(ChaosDungeonAttributeSet->GetMaxMana());
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	const UChaosDungeonAttributeSet* ChaosDungeonAttributeSet = Cast<UChaosDungeonAttributeSet>(AttributeSet);

	check(ChaosDungeonAttributeSet);

	// 获取属性值的变化委托,绑定回调函数监听属性变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosDungeonAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosDungeonAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosDungeonAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosDungeonAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);
	
	UDoCAbilitySystemComponent* DocASC = Cast<UDoCAbilitySystemComponent>(AbilitySystemComponent);
	if (DocASC)
	{
		Cast<UDoCAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& GameplayTagContainer)
			{
				for (const FGameplayTag& Tag : GameplayTagContainer)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						FUIWidgetRow* Row = GetDataTableByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}