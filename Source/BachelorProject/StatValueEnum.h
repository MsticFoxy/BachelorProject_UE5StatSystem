// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatValue.h"
#include "Engine/UserDefinedEnum.h"
#include "StatValueEnum.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BACHELORPROJECT_API UStatValueEnum : public UStatValue
{
	GENERATED_BODY()
private:
	UPROPERTY()
		uint8 baseValue;
public:
	UPROPERTY(EditAnywhere)
		UEnum* enumType;

	UPROPERTY(BlueprintReadWrite, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		uint8 enumValue;

	UStatValueEnum();

	virtual void Initialize(FString name) override;
	virtual bool StringIsValidStatValue_Implementation(const FString& input) override;
	virtual void StackStatValue_Implementation(UStatValue* stack) override;
	virtual void ParseStatValue_Implementation(const FString& value) override;
	virtual TArray<FString> GetInputOptions_Implementation() override;

	UFUNCTION(BlueprintCallable)
		uint8 GetEnumAsByteValue();

	UFUNCTION()
		void SetBaseValue(uint8 value);

	UFUNCTION()
		TArray<FString> GetNameList();
};
