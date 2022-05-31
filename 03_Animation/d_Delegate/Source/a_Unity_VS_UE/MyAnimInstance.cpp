// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Pawn))
	{
		//Speed = Pawn->GetVelocity().Size();

		const auto Character = Cast<ACharacter>(Pawn);

		// W = 1, S = -1, A = -1, D = 1
		UpDownSpeed = Character->GetInputAxisValue(TEXT("UpDown"));
		LeftRightSpeed = Character->GetInputAxisValue(TEXT("LeftRight"));

		//UE_LOG(LogTemp,Log,TEXT("speed : %f"), Speed);

		if (IsValid(Character))
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
}

// 생성자
UMyAnimInstance::UMyAnimInstance()
{
	// 몽타주 경로를 통해서 검색해서 찾아온다.
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(
		TEXT("AnimMontage'/Game/Animations/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));

	// 정상적으로 찾았으면
	if (AM.Succeeded())
	{
		// 몽타주 변수에 할당
		AttackMontage = AM.Object;
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	// Montage_Play(플레이할 몽타주, 재생 속도) 
	Montage_Play(AttackMontage, 1.f);
}
