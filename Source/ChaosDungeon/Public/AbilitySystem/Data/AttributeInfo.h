#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FChaosDungeonAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

UCLASS()
class CHAOSDUNGEON_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FChaosDungeonAttributeInfo FindAttributeInfoByTag(const FGameplayTag& AttributeTag);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FChaosDungeonAttributeInfo> AttributeInformation;
};
