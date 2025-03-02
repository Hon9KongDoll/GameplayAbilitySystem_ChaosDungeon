#pragma once

#include "CoreMinimal.h"
#include "Character/ChaosDungeonCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "ChaosDungeonEnemy.generated.h"

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonEnemy : public AChaosDungeonCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AChaosDungeonEnemy();
	
	virtual void HightLightActor() override;
	virtual void UnHightLightActor() override;

protected:
	virtual void BeginPlay() override;
};
