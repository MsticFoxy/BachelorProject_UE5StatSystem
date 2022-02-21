// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatValue.h"
#include "Math/Color.h"
#include "StatValueFloat.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BACHELORPROJECT_API UStatValueFloat : public UStatValue
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
		float baseValue;

public:
	UStatValueFloat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float addValuePremultiply = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float multiplyValuePreaddition = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float addValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float multiplyValuePostaddition = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float addValuePostmultiply = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		float scaleValue = 1;


	virtual void Initialize(FString name) override;
	virtual bool StringIsValidStatValue_Implementation(const FString& input) override;
	virtual void StackStatValue_Implementation(UStatValue* stack) override;
	virtual void ParseStatValue_Implementation(const FString& value) override;


	UFUNCTION()
		void SetBaseValue(float value);

	UFUNCTION(BlueprintCallable)
		float GetFloatValue();
};
