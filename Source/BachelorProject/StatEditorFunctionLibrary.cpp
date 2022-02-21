// Fill out your copyright notice in the Description page of Project Settings.

#include "StatEditorFunctionLibrary.h"
#include "UObject/Class.h"
#include "Engine/SCS_Node.h"
#include "BachelorProject.h"
#include "StatValue.h"

UObject* UStatEditorFunctionLibrary::GetDefaultObject(TSubclassOf<UObject> ObjectClass) 
{
	if (ObjectClass)
	{
		return ObjectClass->GetDefaultObject();
	}
	return nullptr;
}

void UStatEditorFunctionLibrary::GetDefaultObjectSubobjects(TSubclassOf<UObject> ObjectClass, TArray<UObject*>& defaultSubobjects)
{
    if (ObjectClass)
    {
        try
        {
            ObjectClass->GetDefaultObject()->CollectDefaultSubobjects(defaultSubobjects, true);
        }
        catch (const std::exception&)
        {
            return;
        }
        
    }
}

TSubclassOf<UObject> UStatEditorFunctionLibrary::GetClassFromBlueprint(UBlueprint* blueprint)
{
    try
    {
        return blueprint->GeneratedClass;
    }
    catch (const std::exception&)
    {
        return nullptr;
    }
	
}


//ForumStuff zur lösung vom problem: der default actor hat keine components 
// https://answers.unrealengine.com/questions/558236/how-to-get-a-component-from-a-classdefaultobject.html

UActorComponent* UStatEditorFunctionLibrary::FindDefaultComponentByClass(const TSubclassOf<AActor> InActorClass,
    const TSubclassOf<UActorComponent> InComponentClass)
{
    if (!IsValid(InActorClass))
    {
        return nullptr;
    }

    // Check CDO.
    AActor* ActorCDO = InActorClass->GetDefaultObject<AActor>();
    UActorComponent* FoundComponent = ActorCDO->FindComponentByClass(InComponentClass);

    if (FoundComponent != nullptr)
    {
        return FoundComponent;
    }

    // Check blueprint nodes. Components added in blueprint editor only (and not in code) are not available from
    // CDO.
    UBlueprintGeneratedClass* RootBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(InActorClass);
    UClass* ActorClass = InActorClass;

    // Go down the inheritance tree to find nodes that were added to parent blueprints of our blueprint graph.
    do
    {
        UBlueprintGeneratedClass* ActorBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(ActorClass);
        if (!ActorBlueprintGeneratedClass)
        {
            return nullptr;
        }

        const TArray<USCS_Node*>& ActorBlueprintNodes =
            ActorBlueprintGeneratedClass->SimpleConstructionScript->GetAllNodes();

        for (USCS_Node* Node : ActorBlueprintNodes)
        {
            if (Node->ComponentClass->IsChildOf(InComponentClass))
            {
                return Node->GetActualComponentTemplate(RootBlueprintGeneratedClass);
            }
        }

        ActorClass = Cast<UClass>(ActorClass->GetSuperStruct());

    } while (ActorClass != AActor::StaticClass());

    return nullptr;
}

TArray<UClass*> UStatEditorFunctionLibrary::GetSubclassesOfStatValue()
{
    TArray<UClass*> Subclasses;
    for (TObjectIterator<UClass> It; It; ++It)
    {
        if (It->IsChildOf(UStatValue::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
        {
            if (*It != UStatValue::StaticClass())
            {
                bool isSkeleton = false;
                FString ClassName = *It->GetName();

                if (ClassName.Len() > 4)
                {
                    if (ClassName[0] == 'S' && ClassName[1] == 'K' && ClassName[2] == 'E' && ClassName[3] == 'L')
                    {
                        isSkeleton = true;
                    }
                }
                if (ClassName.Len() > 6)
                {
                    if (ClassName[0] == 'R' && ClassName[1] == 'E' && ClassName[2] == 'I' && ClassName[3] == 'N' && ClassName[4] == 'S' && ClassName[5] == 'T')
                    {
                        isSkeleton = true;
                    }
                }
                if (ClassName.Len() > 11)
                {
                    if (ClassName[0] == 'H' && ClassName[1] == 'O' && ClassName[2] == 'T' && ClassName[3] == 'R' && ClassName[4] == 'E' && ClassName[5] == 'L' && ClassName[6] == 'O' && ClassName[7] == 'A' && ClassName[8] == 'D' && ClassName[9] == 'E' && ClassName[10] == 'D')
                    {
                        isSkeleton = true;
                    }
                }
                
                if (!isSkeleton)
                {
                    Subclasses.Add(*It);
                }
            }
        }
    }
    return Subclasses;
}

TArray<UClass*> UStatEditorFunctionLibrary::GetSubclassesOf(UClass* c)
{
    TArray<UClass*> Subclasses;
    for (TObjectIterator<UClass> It; It; ++It)
    {
        if (It->IsChildOf(c->StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
        {
            if (*It != c->StaticClass())
            {
                bool isSkeleton = false;
                FString ClassName = *It->GetName();

                if (ClassName.Len() > 4)
                {
                    if (ClassName[0] == 'S' && ClassName[1] == 'K' && ClassName[2] == 'E' && ClassName[3] == 'L')
                    {
                        isSkeleton = true;
                    }
                }
                if (ClassName.Len() > 6)
                {
                    if (ClassName[0] == 'R' && ClassName[1] == 'E' && ClassName[2] == 'I' && ClassName[3] == 'N' && ClassName[4] == 'S' && ClassName[5] == 'T')
                    {
                        isSkeleton = true;
                    }
                }
                if (ClassName.Len() > 11)
                {
                    if (ClassName[0] == 'H' && ClassName[1] == 'O' && ClassName[2] == 'T' && ClassName[3] == 'R' && ClassName[4] == 'E' && ClassName[5] == 'L' && ClassName[6] == 'O' && ClassName[7] == 'A' && ClassName[8] == 'D' && ClassName[9] == 'E' && ClassName[10] == 'D')
                    {
                        isSkeleton = true;
                    }
                }

                if (!isSkeleton)
                {
                    Subclasses.Add(*It);
                }
            }
        }
    }
    return Subclasses;
}

FLinearColor UStatEditorFunctionLibrary::GetColorFromStatValueClass(UObject* context, TSubclassOf<UStatValue> type)
{
    if (type)
    {
        UStatValue* temp = NewObject<UStatValue>(context, type);
        temp->Initialize("");
        if (temp != nullptr)
        {
            return temp->GetDisplayColor();
        }
    }
    return FLinearColor(1,0,1);
}

TArray<FString> UStatEditorFunctionLibrary::GetInputOptionsFromStatValueClass(UObject* context, TSubclassOf<UStatValue> type)
{
    if (type)
    {
        UStatValue* temp = NewObject<UStatValue>(context, type);
        temp->Initialize("");
        if (temp != nullptr)
        {
            return temp->GetInputOptions();
        }
    }
    return TArray<FString>();
}

bool UStatEditorFunctionLibrary::StringIsStatValue(UObject* context, FString input, TSubclassOf<UStatValue> type)
{
    if (type)
    {
        UStatValue* temp = NewObject<UStatValue>(context, type);
        temp->Initialize("");
        if (temp != nullptr)
        {
            return temp->StringIsValidStatValue(input);
        }
    }
    return false;
}

UStatValue* UStatEditorFunctionLibrary::AddModifier(UStatValue* target, UStatValue* modifier, int priority, TEnumAsByte<EIsType>& Outcome)
{
    Outcome = EIsType::Failure;
    if (target->StaticClass() == modifier->StaticClass())
    {
        Outcome = EIsType::Success;
        target->AddModifier(modifier, priority);
    }
    return target;
}
