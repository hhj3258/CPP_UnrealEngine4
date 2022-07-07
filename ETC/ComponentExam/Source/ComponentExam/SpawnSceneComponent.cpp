// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSceneComponent.h"

// Sets default values for this component's properties
USpawnSceneComponent::USpawnSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));

	for (int i = 1; i < 4; i++)
	{
		UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Child"), i));
		MeshComponent->SetupAttachment(this);
		const float theta = 120.f * i * (PI / 180.f);
		//UE_LOG(LogTemp,Warning,TEXT("degree=%f, rad=%f"),(120.f*i),theta);
		MeshComponent->SetRelativeLocation(FVector(FMath::Cos(theta), FMath::Sin(theta), 0.f) * 100.f);

		if (SM.Succeeded())
		{
			MeshComponent->SetStaticMesh(SM.Object);
		}

		ChildrenMeshes.Add(MeshComponent);
	}
}


// Called when the game starts
void USpawnSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USpawnSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// DestroyTimer += DeltaTime;
	// //UE_LOG(LogTemp,Warning,TEXT("timer=%f"),DestroyTimer);
	// if (DestroyTimer >= 3.f)
	// {
	// 	for(auto& MeshComponent:ChildrenMeshes)
	// 		MeshComponent->DestroyComponent();
	// 	DestroyComponent();
	// }

	FRotator MyRotation = GetComponentRotation();
	float Speed = 600.f;
	MyRotation.Yaw += DeltaTime * Speed;
	SetWorldRotation(MyRotation);
}
