#include "AbilitySystem/ChaosDungeonAttributeSet.h"
#include "ChaosDungeonGameplayTags.h"

// Engine
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"

UChaosDungeonAttributeSet::UChaosDungeonAttributeSet()
{
	const FChaosDungeonGameplayTags& GameplayTags = FChaosDungeonGameplayTags::Get();

	FAttributeSignature IntelligenceDelegate;
	IntelligenceDelegate.BindStatic(GetIntelligenceAttribute);
	TagToAttributes.Add(GameplayTags.Attributes_BasicAttributes_Intelligence, IntelligenceDelegate);
}

void UChaosDungeonAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, PhysicalDEF, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UChaosDungeonAttributeSet, LegalDEF, COND_None, REPNOTIFY_Always);
}

void UChaosDungeonAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UChaosDungeonAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UChaosDungeonAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, Intelligence, OldIntelligence);
}

void UChaosDungeonAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, Stamina, OldStamina);
}

void UChaosDungeonAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, Attack, OldAttack);
}

void UChaosDungeonAttributeSet::OnRep_PhysicalDEF(const FGameplayAttributeData& OldPhysicalDEF) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, PhysicalDEF, OldPhysicalDEF);
}

void UChaosDungeonAttributeSet::OnRep_LegalDEF(const FGameplayAttributeData& OldLegalDEF) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, LegalDEF, OldLegalDEF);
}

void UChaosDungeonAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, Health, OldHealth);
}

void UChaosDungeonAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, MaxHealth, OldMaxHealth);
}

void UChaosDungeonAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, Mana, OldMana);
}

void UChaosDungeonAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UChaosDungeonAttributeSet, MaxMana, OldMaxMana);
}

void UChaosDungeonAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.GameplayEffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceAbilitySystemComponent = Props.GameplayEffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (Props.SourceAbilitySystemComponent && Props.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() &&
		Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
		else
		{
			if (Props.SourceAvatarActor)
			{
				if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
				{
					Props.SourceController = Pawn->GetController();
					Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
				}
			}
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}