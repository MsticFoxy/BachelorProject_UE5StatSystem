// Fill out your copyright notice in the Description page of Project Settings.


#include "StatValueInteger.h"

UStatValueInteger::UStatValueInteger()
{
	displayColor = FLinearColor(0.13f, 0.76f, 0.43f);
}

void UStatValueInteger::Initialize(FString name)
{
	if (name.IsEmpty())
	{
		statName = name;
	}
	multiplyValuePreaddition = 1;
	multiplyValuePostaddition = 1;
}

bool UStatValueInteger::StringIsValidStatValue_Implementation(const FString& input)
{
	if (input.IsNumeric())
	{
		float out = FCString::Atof(*input);
		return ((out - FMath::FloorToFloat(out)) == 0) && !input.Contains(".");
	}
	return false;
}

void UStatValueInteger::StackStatValue_Implementation(UStatValue* stack)
{
	UStatValueInteger* val = Cast<UStatValueInteger>(stack);
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

void UStatValueInteger::ParseStatValue_Implementation(const FString& value)
{
	SetBaseValue(FCString::Atoi(*value));
}

void UStatValueInteger::SetBaseValue(int value)
{
	baseValue = value;
}

int UStatValueInteger::GetIntegerValue()
{
	UStatValueInteger* stacked = Cast<UStatValueInteger>(GetStackedValue());
	stacked->baseValue += stacked->addValuePremultiply;
	stacked->baseValue = (int)stacked->baseValue * stacked->multiplyValuePreaddition;
	stacked->baseValue += stacked->addValue;
	stacked->baseValue = (int)stacked->baseValue * stacked->multiplyValuePostaddition;
	stacked->baseValue += stacked->addValuePostmultiply;
	stacked->baseValue = (int)stacked->baseValue * stacked->scaleValue;
	return stacked->baseValue;
}
