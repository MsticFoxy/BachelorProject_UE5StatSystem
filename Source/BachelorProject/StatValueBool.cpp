// Fill out your copyright notice in the Description page of Project Settings.


#include "StatValueBool.h"
UStatValueBool::UStatValueBool()
{
	displayColor = FLinearColor(0.3f, 0.0f, 0.0f);
}

void UStatValueBool::Initialize(FString name)
{
	if (name.IsEmpty())
	{
		statName = name;
	}
}

bool UStatValueBool::StringIsValidStatValue_Implementation(const FString& input)
{
	return GetInputOptions().Contains(input);
}

void UStatValueBool::StackStatValue_Implementation(UStatValue* stack)
{
	UStatValueBool* val = Cast<UStatValueBool>(stack);
	if (val)
	{
		boolValue = baseValue;
		switch (val->operation)
		{
		case EBoolOperation::Set:
			boolValue = val->boolValue;
			break;
		case EBoolOperation::Equal:
			boolValue = (val->boolValue == boolValue);
			break;
		case EBoolOperation::And:
			boolValue = (val->boolValue && boolValue);
			break;
		case EBoolOperation::Or:
			boolValue = (val->boolValue || boolValue);
			break;
		case EBoolOperation::ExclusiveOr:
			boolValue = (val->boolValue != boolValue);
			break;
		}
		if (val->invertResult)
		{
			boolValue = !boolValue;
		}
		baseValue = boolValue;
	}
}

void UStatValueBool::ParseStatValue_Implementation(const FString& value)
{
	bool val = false;
	if (value.Equals("true"))
	{
		val = true;
	}
	else if (value.Equals("false"))
	{
		val = false;
	}
	SetBaseValue(val);
}

TArray<FString> UStatValueBool::GetInputOptions_Implementation()
{
	TArray<FString> ret = TArray<FString>();
	ret.Add("true");
	ret.Add("false");
	return ret;
}

void UStatValueBool::SetBaseValue(bool value)
{
	baseValue = value;
}

bool UStatValueBool::GetBoolValue()
{
	UStatValueBool* stacked = Cast<UStatValueBool>(GetStackedValue());
	stacked->baseValue = stacked->boolValue;
	return stacked->baseValue;
}
