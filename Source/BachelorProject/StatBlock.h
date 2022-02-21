// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatValue.h"
#include "StatusEffect.h"
#include "Containers/Map.h"
#include "StatBlock.generated.h"

UENUM(Blueprintable)
enum EIsType
{
	Success,
	Failure
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BACHELORPROJECT_API UStatBlock : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatBlock();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TMap<FString, FStatValueContainer> stats;

	TMultiMap<int, UStatusEffect*> statusEffects;

	UPROPERTY()
	TArray<UStatBlock*> inheritingStatBlocks;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateStatBases(UClass* parentClass);

	UFUNCTION(BlueprintCallable)
	void UpdateStatInheritence(UClass* parentClass);

	UFUNCTION(BlueprintCallable)
	void RemoveDepricatedInheritence();

	UFUNCTION(BlueprintCallable)
	void AddStat(FString name, const TSubclassOf<UStatValue> type);

	UFUNCTION(BlueprintCallable)
	bool RemoveStat(FString name);

	UFUNCTION(BlueprintCallable)
	UStatValue* GetStat(FString name);

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Outcome", DeterminesOutputType = "type"))
	UStatValue* GetStatOfType(FString name, TSubclassOf<UStatValue> type, TEnumAsByte<EIsType>& Outcome);

	UFUNCTION(BlueprintCallable)
	bool ContainsStat(FString name);

	UFUNCTION(BlueprintCallable)
	FStatValueContainer GetStatValueContainer(FString name);

	UFUNCTION(BlueprintCallable)
	TArray<UStatValue*> GetStats(TArray<FString> names);

	UFUNCTION(BlueprintCallable)
	TArray<FStatValueContainer> GetStatContainerList(TArray<FString> names);

	UFUNCTION(BlueprintCallable)
	void GetStatNamesSorted(TArray<FString>& sortedStatValues);

	UFUNCTION(BlueprintCallable)
	bool RenameStat(FString oldName, FString newName);

	UFUNCTION(BlueprintCallable)
	bool RetypeStat(FString name, TSubclassOf<UStatValue> newType);

	UFUNCTION(BlueprintCallable)
	void SetStatInitialValue(FString name, FString value);

	UFUNCTION(BlueprintCallable)
	void SetStatInitialInheritValue(FString name, FString value, UClass* inheritence);

	UFUNCTION(BlueprintCallable)
	void SetInheritenceClass(FString name, UClass* inheritor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UClass* GetInheritenceClass(FString name);

	UFUNCTION()
	void InitializeStat(FString name);

	UFUNCTION(BlueprintCallable)
	void AddStatusEffect(UStatusEffect* effect, int priority);

	UFUNCTION(BlueprintCallable)
	void RemoveStatusEffect(UStatusEffect* effect);

	UFUNCTION()
	TArray<UStatBlock*> GetInheritChildren();

	UFUNCTION(BlueprintCallable)
	void SetStatGroup(FString name, FString group);
};
