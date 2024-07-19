// Copyright Druid Mechanics


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
 
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));


}




void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();


	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	//We're creating the FGameplayEffectContextHandlle from the Target
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();

	//We put AddSourceObject to know what actor caused the effect
	EffectContextHandle.AddSourceObject(this);

	//MakeOutgoingSpec Creates the FGameplayEffectSpecHandle
	const FGameplayEffectSpecHandle  EffectSpecHandle =TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	// .Get() Gets a pointer. We need a const reference, which is why we dereference. Data is storing FGameplaySpecPointer
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}



