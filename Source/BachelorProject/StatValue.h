// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Math/Color.h"
#include "Containers/Map.h"
#include "StatValue.generated.h"


USTRUCT(BlueprintType)
struct FStatValueContainer
{
	GENERATED_BODY()

public:
	FStatValueContainer(){
		statValue = nullptr;
		inheritenceClass = nullptr;
	}
	FStatValueContainer(TSubclassOf<UStatValue> valueType)
	{
		type = valueType;
		statValue = nullptr;
		inheritenceClass = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UClass* inheritenceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UStatValue> type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<UClass*, FString> statBaseValueInheritence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString statBaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStatValue* statValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString group;
};
/**
 * 
 */
UCLASS(Blueprintable)
class BACHELORPROJECT_API UStatValue : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	FString statName;

	TMultiMap<int, UStatValue*> modifiers;

public:

	UPROPERTY(EditAnywhere)
	FLinearColor displayColor = FLinearColor(1,1,0);

	virtual void Initialize(FString name);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetName();

	UFUNCTION()
	void RenameStat(FString newName);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FLinearColor GetDisplayColor();

	// modifier is always the same class as this class
	UFUNCTION()
	void AddModifier(UStatValue* modifier, int priority);

	UFUNCTION(BlueprintCallable)
	void RemoveModifier(UStatValue* modifier);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Category = "Stat Value")
	bool StringIsValidStatValue(const FString& input);

	// meistens nicht allzu viele modifier. deshalb cast to stat value specific type ok
	UFUNCTION(BlueprintNativeEvent, Category = "Stat Value")
	void StackStatValue(UStatValue* stack);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stat Value")
	void ParseStatValue(const FString& value);

	//Returns a list of inputs for a dropdown menu.
	//leave empty to get a text field
	//if not empty -> you have to implement StringIsValidStatValue anyway
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stat Value")
	TArray<FString> GetInputOptions();

	UFUNCTION(BlueprintCallable)
		UStatValue* GetStackedValue();
};
