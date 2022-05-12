// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()	// 언리얼 빌드 과정에 필요한 추가정보(리플렉션)
class A_UNITY_VS_UE_API AMyActor : public AActor
{
	GENERATED_BODY()	// 기본으로 만들어지는 몸체
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// VisibleAnywhere : 외부에서 보이게 설정(하이어라키 등)
	// 하지만 이 경우에는 하이어라키에서 static mesh 변경 가능
	UPROPERTY(VisibleAnywhere)	
	UStaticMeshComponent* Mesh;	// static mesh 를 추가한다.

	// 보이기 가능, Category => 그룹화
	UPROPERTY(VisibleAnyWhere, Category = BattleStat)
	int hp;

	// 수정 가능, Category => 그룹화
	UPROPERTY(EditAnyWhere, Category = BattleStat)
	int mp;
};
