// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()	// �𸮾� ���� ������ �ʿ��� �߰�����(���÷���)
class A_UNITY_VS_UE_API AMyActor : public AActor
{
	GENERATED_BODY()	// �⺻���� ��������� ��ü
	
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
	// VisibleAnywhere : �ܺο��� ���̰� ����(���̾��Ű ��)
	// ������ �� ��쿡�� ���̾��Ű���� static mesh ���� ����
	UPROPERTY(VisibleAnywhere)	
	UStaticMeshComponent* Mesh;	// static mesh �� �߰��Ѵ�.

	// ���̱� ����, Category => �׷�ȭ
	UPROPERTY(VisibleAnyWhere, Category = BattleStat)
	int hp;

	// ���� ����, Category => �׷�ȭ
	UPROPERTY(EditAnyWhere, Category = BattleStat)
	int mp;
};
