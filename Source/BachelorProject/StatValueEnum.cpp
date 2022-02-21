// Fill out your copyright notice in the Description page of Project Settings.


#include "StatValueEnum.h"
UStatValueEnum::UStatValueEnum()
{
	displayColor = FLinearColor(0.0f, 0.16f, 0.13f);
}

void UStatValueEnum::Initialize(FString name)
{
	if (name.IsEmpty())
	{
		statName = name;
	}
}

bool UStatValueEnum::StringIsValidStatValue_Implementation(const FString& input)
{
	return GetInputOptions().Contains(input);
}

void UStatValueEnum::StackStatValue_Implementation(UStatValue* stack)
{
	UStatValueEnum* val = Cast<UStatValueEnum>(stack);
	if (val)
	{
		enumValue = val->enumValue;
	}
}

void UStatValueEnum::ParseStatValue_Implementation(const FString& value)
{
	enumType->GetValueByNameString(value);
}

TArray<FString> UStatValueEnum::GetInputOptions_Implementation()
{
	return GetNameList();
}

uint8 UStatValueEnum::GetEnumAsByteValue()
{
	UStatValueEnum* stacked = Cast<UStatValueEnum>(GetStackedValue());
	stacked->baseValue;
	return stacked->baseValue;
}

void UStatValueEnum::SetBaseValue(uint8 value)
{
	baseValue = value;
}

TArray<FString> UStatValueEnum::GetNameList()
{
	TArray<FString> names = TArray<FString>();
	if (enumType)
	{
		int num = enumType->NumEnums();
		for (int i = 0; i < num - 1; i++)
		{
			names.Add(enumType->GetDisplayNameTextByIndex(i).ToString());
		}
	}
	return names;
}
