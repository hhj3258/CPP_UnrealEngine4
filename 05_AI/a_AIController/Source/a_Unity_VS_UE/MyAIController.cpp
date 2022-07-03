// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMyAIController::AMyAIController()
{
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// SetTimer(핸들, 타이머 호출할 객체, 호출할 함수, 반복할 시간, 루프여부)
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyAIController::RandomMove, 3.f, true);
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AMyAIController::RandomMove()
{
	auto CurrentPawn = GetPawn();

	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (!IsValid(NavSystem))
	{
		return;
	}

	FNavLocation RandomLocation; // 여기에 이동 후 좌표가 들어올 것
	// GetRandomPointInNavigableRadius : 주변으로 원을 그리고 그 중 이동 가능한 랜덤한 좌표를 얻어온다.
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	{
		// SimpleMoveToLocation : 시작점과 도착점을 매개변수로하여 실제로 이동시킨다.
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
	}
}
