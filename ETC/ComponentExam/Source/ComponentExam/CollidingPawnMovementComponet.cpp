// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponet.h"

void UCollidingPawnMovementComponet::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 이 무브먼트 컴포넌트를 소유하고 있는 폰이 없거나
	// 업데이트 시켜줄 컴포넌트(즉, 이 무브먼트 컴포넌트를 부착시켜줄 컴포넌트)가 없거나
	// 컴포넌트가 이동할 수 없거나, 렌더링 할 수 없다면
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
		return;

	float Speed = 150.f;
	// ConsumeInputVector : 인풋값을 받아옴
	// GetClampedToMaxSize : 인풋값의 magnitude의 Max값을 설정함
	// 최대 속도는 150임
	const FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * Speed;
	// 이번 프레임의 이동값이 거의 0과 같다면
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		// 언리얼 엔진 피직스를 이용해 장애물을 피해 폰 무브먼트 컴포먼트를 이동시켜준다.
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// Hit한 물체가 존재한다면
		if (Hit.IsValidBlockingHit())
		{
			// Hit한 물체의 표면을 따라 미끄러지듯이 이동하도록 함.
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}
