#include "MMOARPGAttributeSet.h"


UMMOARPGAttributeSet::UMMOARPGAttributeSet()
{

}

void UMMOARPGAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// TODO: Calc to modify attributes.

}
