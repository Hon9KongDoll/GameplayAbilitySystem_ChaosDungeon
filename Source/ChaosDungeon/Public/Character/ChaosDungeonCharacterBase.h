#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ChaosDungeonCharacterBase.generated.h"

class UStaticMeshComponent;
class UAbilitySystemComponent;
class UAttributeSet;

// Abstract宏 : 无法进行实例化，可能包含需要在子类中实现的纯虚函数
UCLASS(Abstract)
class CHAOSDUNGEON_API AChaosDungeonCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AChaosDungeonCharacterBase();
	
protected:
	// 右手武器
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> RightHandedWeapon;

	// 左手武器
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> LeftHandedWeapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
