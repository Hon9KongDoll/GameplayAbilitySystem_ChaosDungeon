#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class CHAOSDUNGEON_API IEnemyInterface
{
	GENERATED_BODY()

public:
	virtual void HightLightActor() = 0;
	virtual void UnHightLightActor() = 0;
};
