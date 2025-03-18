#include "ChaosDungeonAssetManager.h"
#include "ChaosDungeonGameplayTags.h"

UChaosDungeonAssetManager& UChaosDungeonAssetManager::Get()
{
	check(GEngine);

	UChaosDungeonAssetManager* ChaosDungeonAssetManager = Cast<UChaosDungeonAssetManager>(GEngine->AssetManager);
	return *ChaosDungeonAssetManager;
}

void UChaosDungeonAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FChaosDungeonGameplayTags::InitializeNativeGameplayTags();
}
