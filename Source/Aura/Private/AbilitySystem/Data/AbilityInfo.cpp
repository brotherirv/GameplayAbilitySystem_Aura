// Copyright Druid Mechanics


#include "AbilitySystem/Data/AbilityInfo.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{

	for (const FAuraAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AbilityTag [%s] on AbilityInfo [%s]."), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	
	return FAuraAbilityInfo();
}
