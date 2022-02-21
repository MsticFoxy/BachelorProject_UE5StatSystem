// Fill out your copyright notice in the Description page of Project Settings.


#include "StatValueFloat.h"

UStatValueFloat::UStatValueFloat()
{
	displayColor = FLinearColor(0.35f, 1.0f, 0.06f);
}

void UStatValueFloat::Initialize(FString name)
{
	
	if (name.IsEmpty())
	{
		statName = name;
	}
	multiplyValuePreaddition = 1;
	multiplyValuePostaddition = 1;
}

bool UStatValueFloat::StringIsValidStatValue_Implementation(const FString& input)
{
	return input.IsNumeric();
	//float out = FCString::Atof(*input);
}

void UStatValueFloat::StackStatValue_Implementation(UStatValue* stack)
{
	UStatValueFloat* val = Cast<UStatValueFloat>(stack);
	if (val)
	{
		addValuePremultiply += val->addValuePremultiply;
		multiplyValuePreaddition += val->multiplyValuePreaddition;
		addValue += val->addValue;
		multiplyValuePostaddition += val->multiplyValuePostaddition;
		addValuePostmultiply += val->addValuePostmultiply;
		scaleValue *= val->scaleValue;
	}
}

void UStatValueFloat::ParseStatValue_Implementation(const FString& value)
{
	SetBaseValue(FCString::Atof(*value));
}

void UStatValueFloat::SetBaseValue(float value)
{
	baseValue = value;
}

float UStatValueFloat::GetFloatValue()
{
	UStatValueFloat* stacked = Cast<UStatValueFloat>(GetStackedValue());
	stacked->baseValue += stacked->addValuePremultiply;
	stacked->baseValue *= stacked->multiplyValuePreaddition;
	stacked->baseValue += stacked->addValue;
	stacked->baseValue *= stacked->multiplyValuePostaddition;
	stacked->baseValue += stacked->addValuePostmultiply;
	stacked->baseValue *= stacked->scaleValue;
	return stacked->baseValue;
}
