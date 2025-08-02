// Copyright Druid Mechanics


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include <AbilitySystem/AuraAttributeSet.h>
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>


void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	
	check(AttributeInfo);

	for (auto& Pair : GetAuraAS()->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

	AttributePointsChangedDelegate.Broadcast(GetAuraPS()->GetAttributePoints());

}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagsToAttributes)
	{

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});

	}

	
	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 Points)
		{
			AttributePointsChangedDelegate.Broadcast(Points);
		}
	);

}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
	
	AttributePointsChangedDelegate.Broadcast(AuraPlayerState->GetAttributePoints());

}


