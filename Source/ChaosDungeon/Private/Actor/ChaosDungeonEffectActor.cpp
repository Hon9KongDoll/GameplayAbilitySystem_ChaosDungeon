#include "Actor/ChaosDungeonEffectActor.h"
#include "AbilitySystem/ChaosDungeonAttributeSet.h"

// Engine
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AChaosDungeonEffectActor::AChaosDungeonEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

void AChaosDungeonEffectActor::BeginPlay()

{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void AChaosDungeonEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UChaosDungeonAttributeSet* ChaosDungeonAttributeSet = Cast<UChaosDungeonAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UChaosDungeonAttributeSet::StaticClass()));

		UChaosDungeonAttributeSet* MutableChaosDungeonAttributeSet = const_cast<UChaosDungeonAttributeSet*>(ChaosDungeonAttributeSet);
		MutableChaosDungeonAttributeSet->SetHealth(MutableChaosDungeonAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AChaosDungeonEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
