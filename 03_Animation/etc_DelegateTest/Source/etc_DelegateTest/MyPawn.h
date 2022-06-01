// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMultiDelegate);

UCLASS()
class ETC_DELEGATETEST_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION()
	void ChangeVisible();
	UFUNCTION()
	void ChangeScale();

	UPROPERTY(Category=Pawn, BlueprintCallable, VisibleAnywhere)
	FMultiDelegate DelegateTest;
	
public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SMesh;

	UPROPERTY(VisibleAnywhere, Category=Pawn)
	bool bIsVisible = true;

	UPROPERTY(VisibleAnywhere)
	FVector ScaleVector = FVector(1.f,1.f,1.f);

	UPROPERTY()
	float timer=0.f;
};
