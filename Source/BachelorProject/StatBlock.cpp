// Fill out your copyright notice in the Description page of Project Settings.


#include "StatBlock.h"
#include "StatusEffect.h"
#include "StatValue.h"
#include "StatEditorFunctionLibrary.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UStatBlock::UStatBlock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	if (GetOwner() != nullptr)
	{
		//UpdateStatInheritence(GetOwner()->GetClass());
		//UpdateStatBases(GetOwner()->GetClass());
	}

	// ...
}


// Called when the game starts
void UStatBlock::BeginPlay()
{
	if (GetOwner() != nullptr)
	{
		UpdateStatInheritence(GetOwner()->GetClass());
	}
	TArray<FString> st;
	GetStatNamesSorted(st);
	for (FString c : st)
	{
		InitializeStat(c);
	}

	Super::BeginPlay();

	
	// ...
	
}


// Called every frame
void UStatBlock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto& pair : statusEffects)
	{
		TArray<UStatusEffect*> out;
		statusEffects.MultiFind(pair.Key, out);
		for (UStatusEffect* val : out)
		{
			val->CallTick(DeltaTime);
		}
	}

	// ...
}

void UStatBlock::UpdateStatBases(UClass* parentClass)
{
	for (auto& pair : stats)
	{
		if (pair.Value.statBaseValue.IsEmpty())
		{
			if (pair.Value.inheritenceClass != nullptr)
			{
				if (GetOwner() != nullptr)
				{
					if (pair.Value.statBaseValueInheritence.Contains(parentClass))
					{
						pair.Value.statBaseValue = *pair.Value.statBaseValueInheritence.Find(parentClass);
					}
				}
			}
		}
	}
}

void UStatBlock::UpdateStatInheritence(UClass* parentClass)
{
	UActorComponent* dsbComp = UStatEditorFunctionLibrary::FindDefaultComponentByClass(parentClass, UStatBlock::StaticClass());
	if (UStatBlock* sb = dynamic_cast<UStatBlock*>(dsbComp))
	{
		for (auto& pair : sb->stats)
		{
			if (!stats.Contains(pair.Key))
			{
				if (Cast<UStruct>(parentClass)->IsChildOf(pair.Value.inheritenceClass))
				{
					stats.Add(pair.Key, FStatValueContainer(pair.Value));
				}
			}
			else
			{
				if (Cast<UStruct>(parentClass)->IsChildOf(pair.Value.inheritenceClass))
				{
					FStatValueContainer con = FStatValueContainer(pair.Value);
					if (UStatEditorFunctionLibrary::StringIsStatValue(this, con.statBaseValue, con.type))
					{
						con.statBaseValue = stats.Find(pair.Key)->statBaseValue;
					}
					stats.Remove(pair.Key);
					stats.Add(pair.Key, con);
				}
			}
		}
	}

}

void UStatBlock::RemoveDepricatedInheritence()
{
	for (auto& pair : stats)
	{
		if (pair.Value.inheritenceClass != nullptr)
		{
			if (UActorComponent* inh = UStatEditorFunctionLibrary::FindDefaultComponentByClass(pair.Value.inheritenceClass, UStatBlock::StaticClass()))
			{
				if (UStatBlock* inhSB = dynamic_cast<UStatBlock*>(inh))
				{
					if (!inhSB->stats.Contains(pair.Key))
					{
						stats.Remove(pair.Key);
					}
				}
			}
		}
	}
}

void UStatBlock::AddStat(FString name, const TSubclassOf<UStatValue> type)
{
	if (!name.IsEmpty())
	{
		if (!stats.Contains(name))
		{
			if (type->IsChildOf(UStatValue::StaticClass()))
			{
				//UStatValue* newStat = NewObject<UStatValue>(type->StaticClass());
				//newStat->Initialize(name);
				stats.Add(name, FStatValueContainer(type));

				/*for (UStatBlock* var : GetInheritChildren())
				{
					if (var->stats.Contains(name))
					{
						FStatValueContainer cont;
						FString newName = "Child_" + name;
						var->stats.RemoveAndCopyValue(name, cont);
						if (cont.statValue != nullptr)
						{
							cont.statValue->RenameStat(newName);
						}
						var->stats.Add(newName, cont);
					}
					var->stats.Add(name, FStatValueContainer(type));
				}*/
			}
		}
	}
}

bool UStatBlock::RemoveStat(FString name)
{
	if (stats.Remove(name) > 0)
	{
		/*for (UStatBlock* var : GetInheritChildren())
		{
			var->stats.Remove(name);
		}*/
		return true;
	}
	return false;
}

UStatValue* UStatBlock::GetStat(FString name)
{
	if (stats.Contains(name))
	{
		return stats.Find(name)->statValue;
	}
	return nullptr;
}

UStatValue* UStatBlock::GetStatOfType(FString name, TSubclassOf<UStatValue> type, TEnumAsByte<EIsType>& Outcome)
{
	Outcome = EIsType::Failure;
	if (stats.Contains(name))
	{
		UStatValue* ret = stats.Find(name)->statValue;
		if (stats.Find(name)->type == type)
		{
			Outcome = EIsType::Success;
		}
		return ret;
	}
	return nullptr;
}

bool UStatBlock::ContainsStat(FString name)
{
	return stats.Contains(name);
}

FStatValueContainer UStatBlock::GetStatValueContainer(FString name)
{
	if (stats.Contains(name))
	{
		return *stats.Find(name);
	}
	return FStatValueContainer();
}

TArray<UStatValue*> UStatBlock::GetStats(TArray<FString> names)
{
	TArray<UStatValue*> ret;
	for (FString key : names)
	{
		if (stats.Contains(key))
		{
			ret.Add(stats.Find(key)->statValue);
		}
	}
	return ret;
}

TArray<FStatValueContainer> UStatBlock::GetStatContainerList(TArray<FString> names)
{
	TArray<FStatValueContainer> ret;
	for (FString key : names)
	{
		if (stats.Contains(key))
		{
			ret.Add(*stats.Find(key));
		}
	}
	return ret;
}

void UStatBlock::GetStatNamesSorted(TArray<FString>& sortedStatValues)
{
	stats.KeySort([](const FString& a, const FString& b) { return a.Compare(b) < 0; });
	stats.GenerateKeyArray(sortedStatValues);
}

bool UStatBlock::RenameStat(FString oldName, FString newName)
{
	if (!newName.IsEmpty())
	{
		if (stats.Contains(oldName) && !stats.Contains(newName))
		{
			FStatValueContainer cont;
			stats.RemoveAndCopyValue(oldName, cont);
			if (cont.statValue != nullptr)
			{
				cont.statValue->RenameStat(newName);
			}
			stats.Add(newName, cont);

			/*for (UStatBlock* var : GetInheritChildren())
			{
				//(*var->stats.Find(name)).type = newType;
				var->stats.RemoveAndCopyValue(oldName, cont);
				if (cont.statValue != nullptr)
				{
					cont.statValue->RenameStat(newName);
				}
				var->stats.Add(newName, cont);
			}*/

			return true;
		}
	}
	return false;
}

bool UStatBlock::RetypeStat(FString name, TSubclassOf<UStatValue> newType)
{
	if (stats.Contains(name))
	{
		(*stats.Find(name)).type = newType;

		/*for(UStatBlock* var : GetInheritChildren())
		{
			(*var->stats.Find(name)).type = newType;
		}*/

		return true;
	}
	return false;
}

void UStatBlock::SetStatInitialValue(FString name, FString value)
{
	if (stats.Contains(name))
	{
		(*stats.Find(name)).statBaseValue = value;
	}
}

void UStatBlock::SetStatInitialInheritValue(FString name, FString value, UClass* inheritence)
{
	if (stats.Contains(name))
	{
		if ((*stats.Find(name)).statBaseValueInheritence.Contains(inheritence))
		{
			(*stats.Find(name)).statBaseValueInheritence.Remove(inheritence);
		}
		(*stats.Find(name)).statBaseValueInheritence.Add(inheritence, value);
	}
}

void UStatBlock::SetInheritenceClass(FString name, UClass* inheritor)
{
	if (stats.Contains(name))
	{
		(*stats.Find(name)).inheritenceClass = inheritor;
	}
}

UClass* UStatBlock::GetInheritenceClass(FString name)
{
	if (stats.Contains(name))
	{
		return (*stats.Find(name)).inheritenceClass;
	}
	return nullptr;
}

void UStatBlock::InitializeStat(FString name)
{
	if (stats.Contains(name))
	{
		FStatValueContainer cont = *stats.Find(name);
		if (cont.statValue == nullptr)
		{
			UStatValue* newStat = NewObject<UStatValue>(this, cont.type);
			newStat->Initialize(name);
			(*stats.Find(name)).statValue = newStat;
			FString* val = &cont.statBaseValue;
			if (val->IsEmpty())
			{
				val = cont.statBaseValueInheritence.Find(GetOwner()->GetClass());
			}


			//FString cval = val;
			if (val != nullptr && !val->IsEmpty() && newStat->StringIsValidStatValue(*val))
			{
				newStat->ParseStatValue(*val);
			}
		}
	}
}

void UStatBlock::AddStatusEffect(UStatusEffect* effect, int priority)
{
	bool contains = false;
	if (effect->owner == nullptr)
	{
		/*for (auto& pair : statusEffects)
		{
			TArray<UStatusEffect*> out;
			statusEffects.MultiFind(pair.Key, out);
			for (UStatusEffect* val : out)
			{
				if (val == effect)
				{
					contains = true;
					return;
				}
			}
		}*/
		statusEffects.Add(priority, effect);
		effect->owner = this;
		effect->Begin();
	}
}

void UStatBlock::RemoveStatusEffect(UStatusEffect* effect)
{
	for (auto& pair : statusEffects)
	{
		TArray<UStatusEffect*> out;
		statusEffects.MultiFind(pair.Key, out);
		for (UStatusEffect* val : out)
		{
			if (val == effect)
			{
				effect->End();
				statusEffects.Remove(pair.Key, effect);
				effect->owner = nullptr;
				return;
			}
		}
	}
}

TArray<UStatBlock*> UStatBlock::GetInheritChildren()
{
	TArray<UClass*> classes = UStatEditorFunctionLibrary::GetSubclassesOf(GetOwner()->StaticClass());

	TArray<UStatBlock*> sbs;

	for(UClass* var : classes)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "" + var->StaticClass()->GetFName().ToString());
		UActorComponent* sb = (UStatEditorFunctionLibrary::FindDefaultComponentByClass(var, UStatBlock::StaticClass()));
		if (sb != nullptr && sb->StaticClass() == UStatBlock::StaticClass())
		{
			
			//sbs.Add(dynamic_cast<UStatBlock*>(sb));
		}
	}

	return sbs;
}

void UStatBlock::SetStatGroup(FString name, FString group)
{
	if (stats.Contains(name))
	{
		(*stats.Find(name)).group = group;
	}
}

