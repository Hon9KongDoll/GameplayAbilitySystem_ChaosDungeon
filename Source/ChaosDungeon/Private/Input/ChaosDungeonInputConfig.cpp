#include "Input/ChaosDungeonInputConfig.h"

// Engine
#include "InputAction.h"

const UInputAction* UChaosDungeonInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FChaosDungeonInputAction& ChaosDungeonInputAction : AbilityInputActions)
	{
		if (ChaosDungeonInputAction.InputAction && ChaosDungeonInputAction.InputTag == InputTag)
		{
			return ChaosDungeonInputAction.InputAction;
		}
	}

	return nullptr;
}
