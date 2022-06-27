// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class A_UNITY_VS_UE_API UMyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyStatComponent();

	virtual void InitializeComponent() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetLevel(int32 NewLevel);	// ex) 초기 생성, Level Up 등
	void OnAttacked(float DamageAmount, AActor* DamageCauser);
	
	int32 GetLevel() const { return Level; }
	int32 GetHp() const { return Hp; }
	int32 GetAttack() const { return Attack; }

private:
	UPROPERTY(EditAnywhere, Category=Stat, meta=(AllowPrivateAccess));
	int32 Level;

	UPROPERTY(EditAnywhere, Category=Stat, meta=(AllowPrivateAccess));
	int32 Hp;

	UPROPERTY(EditAnywhere, Category=Stat, meta=(AllowPrivateAccess));
	int32 Attack;
};
