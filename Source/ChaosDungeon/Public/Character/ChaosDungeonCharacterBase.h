#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaosDungeonCharacterBase.generated.h"

// Abstract宏 : 无法进行实例化，可能包含需要在子类中实现的纯虚函数
UCLASS(Abstract)
class CHAOSDUNGEON_API AChaosDungeonCharacterBase : public ACharacter
{
	GENERATED_BODY()
	
};
