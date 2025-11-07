// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/AuraFirebolt.h"
#include "Aura/Public/AuraGameplayTags.h"

FString UAuraFirebolt::GetDescription(int32 Level)
{
	

	const float ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);


	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>FIRE BOLT</>\n\n"
			//Description
			"<Default>Launches a bolt of fire, exploding on impact and dealing: </>"
			//Damage
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>\n\n"
			//Mana Cost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n\n"
			//Cooldown
			"<Small>Cooldown: </> <Cooldown>%.1f</>\n\n"
			//Level
			"<Small>Level: </><Level>%d</>"), 
			//Variables
			ScaledDamage,
			ManaCost,
			Cooldown,
			Level);

	}
	else
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>NEXT LEVEL</>\n\n"
			//Description
			"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
			//Damage
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>\n\n"
			//Mana Cost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n\n"
			//Cooldown
			"<Small>Cooldown: </> <Cooldown>%.1f</>\n\n"
			//
			
			//Level
			"<Small>Level: </><Level>%d</>"),
			//Variables
			FMath::Min(Level, NumProjectiles),
			ScaledDamage,
			ManaCost,
			Cooldown,
			Level);
	}
}

FString UAuraFirebolt::GetNextLevelDescription(int32 Level)
{
	const float ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);

	return FString::Printf(TEXT(
		//Title
		"<Title>FIRE BOLT</>\n\n"
		//Description
		"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
		//Damage
		"<Damage>%d</>"
		"<Default> fire damage with a chance to burn</>\n\n"
		//Mana Cost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n\n"
		//Cooldown
		"<Small>Cooldown: </> <Cooldown>%.1f</>\n\n"
		//Level
		"<Small>Level: </><Level>%d</>"),
		//Variables
		FMath::Min(Level, NumProjectiles),
		ScaledDamage,
		ManaCost,
		Cooldown,
		Level);
}