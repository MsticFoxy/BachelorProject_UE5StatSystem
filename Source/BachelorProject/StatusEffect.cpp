// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"
#include "StatBlock.h"

void UStatusEffect::CallTick(float DeltaTime)
{
	TickPerFrame(DeltaTime);
	remainingTimeToTick -= DeltaTime;
	if (remainingTimeToTick <= 0)
	{
		Tick(tickInterval);
		remainingTimeToTick = tickInterval;
	}
}

void UStatusEffect::TickPerFrame_Implementation(float DeltaTime)
{
}


void UStatusEffect::Tick_Implementation(float DeltaTime)
{
}


void UStatusEffect::Begin_Implementation()
{
}

void UStatusEffect::End_Implementation()
{
}

void UStatusEffect::RemoveFromOwner()
{
	owner->RemoveStatusEffect(this);
}
