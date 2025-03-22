#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChaosDungeonProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class CHAOSDUNGEON_API AChaosDungeonProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AChaosDungeonProjectile();

protected:
	virtual void BeginPlay();

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
