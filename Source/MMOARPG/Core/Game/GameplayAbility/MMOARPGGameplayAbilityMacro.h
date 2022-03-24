#pragma once

#include <AttributeSet.h>

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define SET_ATTRIBUTE_SIMPLE(AttributeData, SimpleAttributeData) \
AttributeData.SetBaseValue(SimpleAttributeData.BaseValue); \
AttributeData.SetCurrentValue(SimpleAttributeData.CurrentValue);
