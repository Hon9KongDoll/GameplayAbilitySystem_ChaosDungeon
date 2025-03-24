#include "Character/ChaosDungeonCharacterBase.h"
#include "AbilitySystem/DoCAbilitySystemComponent.h"

// Engine
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

AChaosDungeonCharacterBase::AChaosDungeonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RightHandedWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandedWeapon"));
	RightHandedWeapon->SetupAttachment(GetMesh(), FName(TEXT("Weapon_R")));
	RightHandedWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftHandedWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandedWeapon"));
	LeftHandedWeapon->SetupAttachment(GetMesh(), FName(TEXT("Weapon_L")));
	LeftHandedWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AChaosDungeonCharacterBase::InitializePrimaryAttributes() const
{
	check(AbilitySystemComponent);

	check(DefaultPrimaryAttributes);

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();

	FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.0, ContextHandle);

	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), AbilitySystemComponent);
}

void AChaosDungeonCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;

	UDoCAbilitySystemComponent* DoCAbilitySystemComponent = Cast<UDoCAbilitySystemComponent>(GetAbilitySystemComponent());

	if (DoCAbilitySystemComponent)
	{
		DoCAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
	}
}

FVector AChaosDungeonCharacterBase::GetCombatSocketLocation()
{
	return RightHandedWeapon->GetComponentLocation();
}

void AChaosDungeonCharacterBase::InitAbilityActorInfo()
{
}
