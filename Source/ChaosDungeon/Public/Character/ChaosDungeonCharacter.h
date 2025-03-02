#pragma once

#include "CoreMinimal.h"
#include "Character/ChaosDungeonCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "ChaosDungeonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonCharacter : public AChaosDungeonCharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AChaosDungeonCharacter();

	USpringArmComponent* GetCameraBoom() { return CameraBoom; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
};
