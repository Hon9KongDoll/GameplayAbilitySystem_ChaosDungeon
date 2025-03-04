#include "UserInterface/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"

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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosDungeonAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosDungeonAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosDungeonAttributeSet->GetManaAttribute()).AddUObject(this, &ThisClass::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ChaosDungeonAttributeSet->GetMaxManaAttribute()).AddUObject(this, &ThisClass::MaxManaChanged);
	
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
