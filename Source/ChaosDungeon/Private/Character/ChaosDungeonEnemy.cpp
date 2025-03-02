#include "Character/ChaosDungeonEnemy.h"

AChaosDungeonEnemy::AChaosDungeonEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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
