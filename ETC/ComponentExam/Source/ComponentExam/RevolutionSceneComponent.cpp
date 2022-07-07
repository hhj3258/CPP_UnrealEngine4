// Fill out your copyright notice in the Description page of Project Settings.


#include "RevolutionSceneComponent.h"

// Sets default values for this component's properties
URevolutionSceneComponent::URevolutionSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RevolutionMesh"));
	Mesh->SetupAttachment(this);
	Mesh->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));
	Mesh->SetRelativeRotation(FRotator(0.f,0.f,90.f));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));

	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}
}


// Called when the game starts
void URevolutionSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void URevolutionSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FRotator MyRotation = GetComponentRotation();
	float Speed = 100.f;
	MyRotation.Yaw += DeltaTime * Speed;
	SetWorldRotation(MyRotation);
}
