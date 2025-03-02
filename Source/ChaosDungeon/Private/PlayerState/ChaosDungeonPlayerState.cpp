#include "PlayerState/ChaosDungeonPlayerState.h"
#include "AbilitySystem/DoCAbilitySystemComponent.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"

AChaosDungeonPlayerState::AChaosDungeonPlayerState()
{
	// 网络更新频率
	SetNetUpdateFrequency(100.F);

	AbilitySystemComponent = CreateDefaultSubobject<UDoCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UChaosDungeonAttributeSet>(TEXT("AttributeSet"));
}
