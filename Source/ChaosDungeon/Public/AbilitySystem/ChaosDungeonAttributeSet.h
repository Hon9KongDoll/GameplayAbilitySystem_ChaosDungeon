#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ChaosDungeonAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature);

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle GameplayEffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

UCLASS()
class CHAOSDUNGEON_API UChaosDungeonAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UChaosDungeonAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	
	// 允许你在属性值正式改变之前对其进行修改或限制
	// const FGameplayAttribute& Attribute : 当前发生变化的属性
	// float& NewValue : 传递即将生效的新值 (可以在此修改)
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// 在 GameplayEffect 应用到目标身上后执行，主要用于最终处理计算后的 Attribute 变更
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UFUNCTION()
	void OnRep_Attack(const FGameplayAttributeData& OldAttack) const;

	UFUNCTION()
	void OnRep_PhysicalDEF(const FGameplayAttributeData& OldPhysicalDEF) const;

	UFUNCTION()
	void OnRep_LegalDEF(const FGameplayAttributeData& OldLegalDEF) const;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

public:

	/*	Basic Attributes - 基础属性	*/
	
	// 智力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "BasicAttributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Intelligence);

	// 耐力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "BasicAttributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Stamina);

	// 攻击
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Attack, Category = "BasicAttributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Attack);

	// 物防
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDEF, Category = "BasicAttributes")
	FGameplayAttributeData PhysicalDEF;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, PhysicalDEF);

	// 法防
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LegalDEF, Category = "BasicAttributes")
	FGameplayAttributeData LegalDEF;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, LegalDEF);

	// 生命值，最大生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "VitalAttributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "VitalAttributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, MaxHealth);
	
	// 魔法值，最大魔法值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "VitalAttributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Mana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "VitalAttributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, MaxMana);

	TMap<FGameplayTag, FAttributeSignature> TagToAttributes;
};
