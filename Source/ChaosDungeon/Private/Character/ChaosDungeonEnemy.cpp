#include "Character/ChaosDungeonEnemy.h"
#include "AbilitySystem/DoCAbilitySystemComponent.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"

AChaosDungeonEnemy::AChaosDungeonEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UDoCAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	
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
