#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ChaosDungeonAssetManager.generated.h"

UCLASS()
class CHAOSDUNGEON_API UChaosDungeonAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UChaosDungeonAssetManager& Get();

protected:
	virtual void StartInitialLoading();
};
