#include "AbilitySystem/AbilityTasks/TargetDataAbilityTasks.h"

UTargetDataAbilityTasks* UTargetDataAbilityTasks::CreateUTargetDataAbilityTasks(UGameplayAbility* OwningAbility)
{
	UTargetDataAbilityTasks* Object = NewAbilityTask<UTargetDataAbilityTasks>(OwningAbility);
	return Object;
}

void UTargetDataAbilityTasks::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseSelectData();
	}
}

void UTargetDataAbilityTasks::SendMouseSelectData()
{
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();

	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	
	Data->HitResult = HitResult;
}
