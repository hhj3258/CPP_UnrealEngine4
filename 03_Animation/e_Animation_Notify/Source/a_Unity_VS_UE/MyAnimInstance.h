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

public:
	// 프레임마다 호출됨.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeInitializeAnimation() override;

	UMyAnimInstance();

	void PlayAttackMontage();

	FName GetMontageName(int32 SectionIndex);

	void JumpToSection(int32 SectionIndex);

	bool GetIsFalling() const;

private:
	// 애니메이션 노티파이의 이름과 맞춰줘야 함
	// AnimNotify_노티파이명
	UFUNCTION()
	void AnimNotify_AttackHit();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess))
	float UpDownSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess))
	float LeftRightSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess))
	UAnimMontage* AttackMontage;

	UPROPERTY()
	APawn* Pawn;
};
