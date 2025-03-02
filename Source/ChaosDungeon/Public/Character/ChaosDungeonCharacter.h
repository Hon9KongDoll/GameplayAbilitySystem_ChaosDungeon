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

	USpringArmComponent* GetCameraBoom() { return CameraBoom; }
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
};
