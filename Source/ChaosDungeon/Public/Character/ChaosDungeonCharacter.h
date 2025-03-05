#pragma once

#include "CoreMinimal.h"
#include "Character/ChaosDungeonCharacterBase.h"
#include "ChaosDungeonCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonCharacter : public AChaosDungeonCharacterBase
{
	GENERATED_BODY()

public:
	AChaosDungeonCharacter();

	// 在角色被服务器或 AI 控制时会调用
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;
	
	USpringArmComponent* GetCameraBoom() { return CameraBoom; }

private:
	void InitAbilityActorInfo();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
};
