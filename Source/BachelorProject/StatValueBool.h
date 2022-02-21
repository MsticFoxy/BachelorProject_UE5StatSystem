// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatValue.h"
#include "StatValueBool.generated.h"

UENUM(Blueprintable)
enum EBoolOperation
{
	Set, Equal, And, Or, ExclusiveOr
};

/**
 * 
 */
UCLASS()
class BACHELORPROJECT_API UStatValueBool : public UStatValue
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		bool baseValue;

public:
	UStatValueBool();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		TEnumAsByte<EBoolOperation> operation = EBoolOperation::Set;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		bool boolValue = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		bool invertResult = false;
	


	virtual void Initialize(FString name) override;
	virtual bool StringIsValidStatValue_Implementation(const FString& input) override;
	virtual void StackStatValue_Implementation(UStatValue* stack) override;
	virtual void ParseStatValue_Implementation(const FString& value) override;
	virtual TArray<FString> GetInputOptions_Implementation() override;


	UFUNCTION()
		void SetBaseValue(bool value);

	UFUNCTION(BlueprintCallable)
		bool GetBoolValue();
};
