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
	
	// ������������ֵ��ʽ�ı�֮ǰ��������޸Ļ�����
	// const FGameplayAttribute& Attribute : ��ǰ�����仯������
	// float& NewValue : ���ݼ�����Ч����ֵ (�����ڴ��޸�)
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// �� GameplayEffect Ӧ�õ�Ŀ�����Ϻ�ִ�У���Ҫ�������մ�������� Attribute ���
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

	/*	Basic Attributes - ��������	*/
	
	// ����
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "BasicAttributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Intelligence);

	// ����
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "BasicAttributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Stamina);

	// ����
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Attack, Category = "BasicAttributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Attack);

	// ���
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDEF, Category = "BasicAttributes")
	FGameplayAttributeData PhysicalDEF;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, PhysicalDEF);

	// ����
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LegalDEF, Category = "BasicAttributes")
	FGameplayAttributeData LegalDEF;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, LegalDEF);

	// ����ֵ���������ֵ
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "VitalAttributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Health);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "VitalAttributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, MaxHealth);
	
	// ħ��ֵ�����ħ��ֵ
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "VitalAttributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, Mana);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "VitalAttributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UChaosDungeonAttributeSet, MaxMana);

	TMap<FGameplayTag, FAttributeSignature> TagToAttributes;
};
