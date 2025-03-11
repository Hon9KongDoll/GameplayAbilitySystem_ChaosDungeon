#include "Actor/ChaosDungeonEffectActor.h"

// Engine
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AChaosDungeonEffectActor::AChaosDungeonEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AChaosDungeonEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AChaosDungeonEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfinitesEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AChaosDungeonEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfinitesEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfinitesEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		
		if (AbilitySystemComponent)
		{
			TArray<FActiveGameplayEffectHandle> RemoveActiveGameplayEffectHandle;

			for (TPair< FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveGameplayEffectHandle : ActiveGameplayEffectHandles)
			{
				if (ActiveGameplayEffectHandle.Value == AbilitySystemComponent)
				{
					AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveGameplayEffectHandle.Key);
					RemoveActiveGameplayEffectHandle.Add(ActiveGameplayEffectHandle.Key);
				}
			}

			for (FActiveGameplayEffectHandle ActiveGameplayEffectHandle : RemoveActiveGameplayEffectHandle)
			{
				ActiveGameplayEffectHandles.FindAndRemoveChecked(ActiveGameplayEffectHandle);
			}
		}
	}
}

void AChaosDungeonEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	check(GameplayEffectClass);

	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (AbilitySystemComponent == nullptr) return;

	// 作用是生成一个效果上下文，用来存储施加者(Instigator)、来源对象(SourceObject)、命中目标等附加信息，以便 GameplayEffect 处理时使用
	FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);

	// 实例化一个 UGameplayEffect，并为其提供必要的上下文信息(如等级、来源信息)，以便后续应用到自己或目标
	// FGameplayEffectSpecHandle MakeOutgoingSpec(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle Context);
	// GameplayEffectClass : 用于指定要应用的 GameplayEffect,通常是在编辑器中创建的 GameplayEffect 资产
	// Level : 指定 GameplayEffect 的等级，可以用于影响数值计算
	// Context : 传递额外的上下文信息(如伤害来源、命中目标等)
	FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, GameplayEffectContextHandle);

	// 允许 Actor(通常是角色) 对自己应用一个 GameplayEffect(游戏效果)，用于修改属性、应用状态效果、触发伤害
	// FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf (const FGameplayEffectSpec& GameplayEffectSpec, FPredictionKey PredictionKey = FPredictionKey());
	// FGameplayEffectSpec : 是 UGameplayEffect 的实例化版本，包含持续时间、强度、目标属性等数据
	// PredictionKey : 主要用于网络预测同步, 对于客户端预测的 Gameplay Effect，可以用于防止延迟同步问题
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

	// 判断游戏效果 GameplayEffectSpecHandle 是否是无限持续
	if (GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
	{
		// 判断无限效果移除策略是否为移除结束重叠
		if (InfinitesEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
		{
			ActiveGameplayEffectHandles.Add(ActiveGameplayEffectHandle, AbilitySystemComponent);
		}
	}
}