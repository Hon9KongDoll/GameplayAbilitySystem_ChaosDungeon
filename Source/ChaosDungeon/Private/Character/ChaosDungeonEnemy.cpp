#include "Character/ChaosDungeonEnemy.h"
#include "AbilitySystem/DoCAbilitySystemComponent.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"

AChaosDungeonEnemy::AChaosDungeonEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UDoCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UChaosDungeonAttributeSet>(TEXT("AttributeSet"));
}

void AChaosDungeonEnemy::HightLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(0.f);
}

void AChaosDungeonEnemy::UnHightLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}

void AChaosDungeonEnemy::BeginPlay()
{
	Super::BeginPlay();

	check(AbilitySystemComponent);

	InitAbilityActorInfo();
}

void AChaosDungeonEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UDoCAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
