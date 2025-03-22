#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "ChaosDungeonCharacterBase.generated.h"

class UStaticMeshComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

// Abstract宏 : 无法进行实例化，可能包含需要在子类中实现的纯虚函数
UCLASS(Abstract)
class CHAOSDUNGEON_API AChaosDungeonCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AChaosDungeonCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:
	void InitializeBasicAttributes() const;

	void AddCharacterAbilities();

	virtual FVector GetCombatSocketLocation();

private:
	virtual void InitAbilityActorInfo();

protected:
	// 右手武器
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> RightHandedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	FName RightHandedWeaponSocketName;

	// 左手武器
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UStaticMeshComponent> LeftHandedWeapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// 用于初始化基础属性
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultBasicAttributes;

	// 游戏开始赋予的能力
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
