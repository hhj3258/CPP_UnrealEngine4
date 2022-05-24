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
