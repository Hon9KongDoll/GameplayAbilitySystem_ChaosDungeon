#include "AbilitySystem/Data/AttributeInfo.h"

FChaosDungeonAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& AttributeTag)
{
	for (const FChaosDungeonAttributeInfo& ChaosDungeonAttributeInfo : AttributeInformation)
	{
		// MatchesTag ����ǩ�Ƿ�ƥ��
		if (ChaosDungeonAttributeInfo.AttributeTag.MatchesTag(AttributeTag))
		{
			return ChaosDungeonAttributeInfo;
		}
	}

	return FChaosDungeonAttributeInfo();
}
