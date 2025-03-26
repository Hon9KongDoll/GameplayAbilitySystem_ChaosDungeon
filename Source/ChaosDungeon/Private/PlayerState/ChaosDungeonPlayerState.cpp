#include "PlayerState/ChaosDungeonPlayerState.h"
#include "AbilitySystem/DoCAbilitySystemComponent.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"

// Engine
#include "Net/UnrealNetwork.h"

AChaosDungeonPlayerState::AChaosDungeonPlayerState()
{
	// 网络更新频率
	SetNetUpdateFrequency(100.F);

	AbilitySystemComponent = CreateDefaultSubobject<UDoCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UChaosDungeonAttributeSet>(TEXT("AttributeSet"));
}

void AChaosDungeonPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChaosDungeonPlayerState, PlayerLevel);
}

void AChaosDungeonPlayerState::Rep_PlayerLevel(int32 OldPlayerLevel)
{
}
