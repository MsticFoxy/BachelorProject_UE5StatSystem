// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatusEffect.generated.h"

class UStatBlock;
/**
 * 
 */
UCLASS(Blueprintable)
class BACHELORPROJECT_API UStatusEffect : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
		UStatBlock* owner;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float tickInterval = 1.0f;
	UPROPERTY()
		float remainingTimeToTick = 0.0f;

	UFUNCTION()
		void CallTick(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent)
		void Begin();
	UFUNCTION(BlueprintNativeEvent)
		void TickPerFrame(float DeltaTime);
	UFUNCTION(BlueprintNativeEvent)
		void Tick(float DeltaTime);
	UFUNCTION(BlueprintNativeEvent)
		void End();

	UFUNCTION(BlueprintCallable)
		void RemoveFromOwner();
};
