// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class A_UNITY_VS_UE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	// 프레임마다 호출됨.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess))
	float Speed;

	UPROPERTY()
	APawn* Pawn;
};
