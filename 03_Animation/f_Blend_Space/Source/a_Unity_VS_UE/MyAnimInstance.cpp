// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Pawn))
	{
		const auto Character = Cast<AMyCharacter>(Pawn);
		Speed = Character->GetVelocity().Size();

		HorizontalValue = Character->GetLeftRightValue();
		VerticalValue = Character->GetUpDownValue();
		
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
	Montage_Play(AttackMontage, 0.9f);
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	//UE_LOG(LogTemp, Warning, TEXT("Notify AttackHit"));
}

FName UMyAnimInstance::GetMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName SectionName = GetMontageName(SectionIndex);
	UE_LOG(LogTemp, Warning, TEXT("AttackIndex = %s"), *SectionName.ToString());
	Montage_JumpToSection(SectionName, AttackMontage);
}

bool UMyAnimInstance::GetIsFalling() const
{
	return IsFalling;
}
