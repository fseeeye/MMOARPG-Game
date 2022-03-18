#include "SimpleComboType.h"

#include "Interface/SimpleCombatInterface.h"

FSimpleComboAttack::FSimpleComboAttack()
	: bLongPress(false)
	, bShortPress(false)
	, ComboIndex(INDEX_NONE)
	, MaxIndex(0)
	, OutCharacter(nullptr)
{

}

void FSimpleComboAttack::OnUpdate()
{
	check(MaxIndex > 0);
	
	//if (ComboIndex >= MaxIndex)
	//{
	//	ComboIndex = 1;
	//}
	//else
	//{
	//	++ComboIndex;
	//}

	ComboIndex++;
	if (ComboIndex >= MaxIndex)
	{
		ComboIndex = 0;
	}
}

void FSimpleComboAttack::OnPress()
{
	if (ComboIndex == INDEX_NONE)
	{
		++ComboIndex;

		OutCharacter->NormalAttack(ComboAbilityName);
	}

	bShortPress = true;
	bLongPress = true;
}

void FSimpleComboAttack::OnReleased()
{
	bLongPress = false;
}

void FSimpleComboAttack::OnReset()
{
	ComboIndex = INDEX_NONE;
}
