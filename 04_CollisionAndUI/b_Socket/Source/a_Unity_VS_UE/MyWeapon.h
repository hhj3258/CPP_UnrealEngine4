// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWeapon.generated.h"

UCLASS()
class A_UNITY_VS_UE_API AMyWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category="MySetting")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Trigger;
};
