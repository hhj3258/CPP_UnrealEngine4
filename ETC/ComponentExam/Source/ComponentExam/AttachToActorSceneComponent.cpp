// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachToActorSceneComponent.h"

// Sets default values for this component's properties
UAttachToActorSceneComponent::UAttachToActorSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//
}

// Called when the game starts
void UAttachToActorSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AttachedActor->SetActorLocation(FVector(0.f,0.f,50.f));
	AttachedActor->AttachToActor(AttachActor, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void UAttachToActorSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
