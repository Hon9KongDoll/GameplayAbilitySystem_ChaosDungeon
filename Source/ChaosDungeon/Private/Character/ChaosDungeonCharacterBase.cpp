#include "Character/ChaosDungeonCharacterBase.h"

// Engine
#include "Components/StaticMeshComponent.h"

AChaosDungeonCharacterBase::AChaosDungeonCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RightHandedWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandedWeapon"));
	RightHandedWeapon->SetupAttachment(GetMesh(), FName(TEXT("Weapon_R")));
	RightHandedWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftHandedWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandedWeapon"));
	LeftHandedWeapon->SetupAttachment(GetMesh(), FName(TEXT("Weapon_L")));
	LeftHandedWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
