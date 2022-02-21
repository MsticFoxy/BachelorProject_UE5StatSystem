// Fill out your copyright notice in the Description page of Project Settings.


#include "StatValue.h"


void UStatValue::Initialize(FString name)
{
	if (name.IsEmpty())
	{
		statName = name;
	}
}

FString UStatValue::GetName()
{
	return statName;
}

void UStatValue::RenameStat(FString newName)
{
	statName = newName;
}

FLinearColor UStatValue::GetDisplayColor()
{
	return displayColor;
}


void UStatValue::AddModifier(UStatValue* modifier, int priority)
{
	modifiers.Add(priority, modifier);
	modifiers.KeySort([](int a, int b) {
		return a < b;
	});
}

void UStatValue::RemoveModifier(UStatValue* modifier)
{
	for (auto& pair : modifiers)
	{
		TArray<UStatValue*> out;
		modifiers.MultiFind(pair.Key, out);
		for (UStatValue* val : out)
		{
			if (val == modifier)
			{
				modifiers.Remove(pair.Key, modifier);
				return;
			}
		}
	}
}



bool UStatValue::StringIsValidStatValue_Implementation(const FString& input)
{
	return false;
}

void UStatValue::StackStatValue_Implementation(UStatValue* stack)
{
}

void UStatValue::ParseStatValue_Implementation(const FString& value)
{
}

TArray<FString> UStatValue::GetInputOptions_Implementation()
{
	return TArray<FString>();
}

UStatValue* UStatValue::GetStackedValue()
{
	UStatValue* ret = DuplicateObject(this, nullptr);

	for (auto& pair : modifiers)
	{
		TArray<UStatValue*> out;
		modifiers.MultiFind(pair.Key, out);
		for (UStatValue* val : out)
		{
			ret->StackStatValue(val);
		}
	}

	return ret;
}
