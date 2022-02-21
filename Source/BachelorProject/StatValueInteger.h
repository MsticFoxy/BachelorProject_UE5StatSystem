// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatValue.h"
#include "StatValueInteger.generated.h"

/**
 * 
 */
UCLASS()
class BACHELORPROJECT_API UStatValueInteger : public UStatValue
{
	GENERATED_BODY()
protected:
		UPROPERTY()
		int baseValue;

public:
	UStatValueInteger();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		int addValuePremultiply = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float multiplyValuePreaddition = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		int addValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float multiplyValuePostaddition = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		int addValuePostmultiply = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float scaleValue = 1;


	virtual void Initialize(FString name) override;
	virtual bool StringIsValidStatValue_Implementation(const FString& input) override;
	virtual void StackStatValue_Implementation(UStatValue* stack) override;
	virtual void ParseStatValue_Implementation(const FString& value) override;


	UFUNCTION()
		void SetBaseValue(int value);

	UFUNCTION(BlueprintCallable)
		int GetIntegerValue();
};
