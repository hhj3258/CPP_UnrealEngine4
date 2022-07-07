// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CollidingPawnMovementComponet.generated.h"

/**
 * 
 */
UCLASS()
class COMPONENTEXAM_API UCollidingPawnMovementComponet : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	// 매 프레임마다 호출됨.
	virtual void TickComponent(
		float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
