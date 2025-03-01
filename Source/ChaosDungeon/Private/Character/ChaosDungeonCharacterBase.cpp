#include "Character/ChaosDungeonCharacterBase.h"

// Engine
#include "Components/StaticMeshComponent.h"

AChaosDungeonCharacterBase::AChaosDungeonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName(TEXT("Weapon_R")));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
