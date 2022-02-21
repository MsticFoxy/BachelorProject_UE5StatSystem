// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StatValue.h"
#include "StatBlock.h"
#include "StatEditorFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BACHELORPROJECT_API UStatEditorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UObject* GetDefaultObject(TSubclassOf<UObject> ObjectClass);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void GetDefaultObjectSubobjects(TSubclassOf<UObject> ObjectClass, TArray<UObject*>& defaultSubobjects);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static TSubclassOf<UObject> GetClassFromBlueprint(UBlueprint* blueprint);

	UFUNCTION(BlueprintCallable)
	static UActorComponent* FindDefaultComponentByClass(const TSubclassOf<AActor> InActorClass, const TSubclassOf<UActorComponent> InComponentClass);

	UFUNCTION(BlueprintCallable)
	static TArray<UClass*> GetSubclassesOfStatValue();

	UFUNCTION(BlueprintCallable)
	static TArray<UClass*> GetSubclassesOf(UClass* c);

	UFUNCTION(BlueprintCallable)
	static FLinearColor GetColorFromStatValueClass(UObject* context, TSubclassOf<UStatValue> type);

	UFUNCTION(BlueprintCallable)
	static TArray<FString> GetInputOptionsFromStatValueClass(UObject* context, TSubclassOf<UStatValue> type);

	UFUNCTION(BlueprintCallable)
	static bool StringIsStatValue(UObject* context, FString input, TSubclassOf<UStatValue> type);

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Outcome", DeterminesOutputType = "target"))
		static UStatValue* AddModifier(UStatValue* target, UStatValue* modifier, int priority, TEnumAsByte<EIsType>& Outcome);
};
