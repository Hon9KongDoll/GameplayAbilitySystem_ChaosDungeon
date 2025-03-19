#include "AbilitySystem/ChaosDungeonAbilitySystemLibrary.h"
#include "UserInterface/HUD/ChaosDungeonHUD.h"
#include "PlayerState/ChaosDungeonPlayerState.h"

// Engine
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemComponent.h"

UOverlayWidgetController* UChaosDungeonAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

	if (PlayerController)
	{
		if (AChaosDungeonHUD* ChaosDungeonHUD = Cast<AChaosDungeonHUD>(PlayerController->GetHUD()))
		{
			if (AChaosDungeonPlayerState* ChaosDungeonPlayerState = PlayerController->GetPlayerState<AChaosDungeonPlayerState>())
			{
				UAbilitySystemComponent* AbilitySystemComponent = ChaosDungeonPlayerState->GetAbilitySystemComponent();
				UAttributeSet* AttributeSet = ChaosDungeonPlayerState->GetAttributeSet();

				const FWidgetControllerParams WidgetControllerParams(PlayerController, ChaosDungeonPlayerState, AbilitySystemComponent, AttributeSet);
				return ChaosDungeonHUD->GetOverlayWidgetController(WidgetControllerParams);
			}
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UChaosDungeonAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

	if (PlayerController)
	{
		if (AChaosDungeonHUD* ChaosDungeonHUD = Cast<AChaosDungeonHUD>(PlayerController->GetHUD()))
		{
			if (AChaosDungeonPlayerState* ChaosDungeonPlayerState = PlayerController->GetPlayerState<AChaosDungeonPlayerState>())
			{
				UAbilitySystemComponent* AbilitySystemComponent = ChaosDungeonPlayerState->GetAbilitySystemComponent();
				UAttributeSet* AttributeSet = ChaosDungeonPlayerState->GetAttributeSet();

				const FWidgetControllerParams WidgetControllerParams(PlayerController, ChaosDungeonPlayerState, AbilitySystemComponent, AttributeSet);
				return ChaosDungeonHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
			}
		}
	}

	return nullptr;
}
