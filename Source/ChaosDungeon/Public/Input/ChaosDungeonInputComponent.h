#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/ChaosDungeonInputConfig.h"
#include "ChaosDungeonInputComponent.generated.h"

UCLASS()
class CHAOSDUNGEON_API UChaosDungeonInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UChaosDungeonInputConfig* InputConifg,
		UserClass* Object,
		PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc,
		HeldFuncType HeldFunc);
	
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void UChaosDungeonInputComponent::BindAbilityActions(const UChaosDungeonInputConfig* InputConifg, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConifg);

	for (const FChaosDungeonInputAction& InputAction : InputConifg->AbilityInputActions)
	{
		if (InputAction.InputAction && InputAction.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, InputAction.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, InputAction.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputAction.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputAction.InputTag);
			}
		}
	}
}
