// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class COMPONENTEXAM_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	class USphereComponent* ACollidingPawn::SetUpCollision(USphereComponent* Component);
	
	// 기존 GetMovementComponent 함수를 내가 만든 MovementComponent를 반환하도록 오버라이딩 함.
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void ParticleToggle();
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MySettings")
	class USphereComponent* SphereComponent;
	
	UParticleSystemComponent* OurParticleSystem;

	class UCollidingPawnMovementComponet* OurMovementComponent;
};
