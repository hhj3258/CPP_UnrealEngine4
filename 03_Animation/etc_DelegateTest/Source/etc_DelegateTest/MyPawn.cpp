// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMesh(
		TEXT("StaticMesh'/Game/StarterContent/Props/SM_MatPreviewMesh_02.SM_MatPreviewMesh_02'"));

	if (BodyMesh.Succeeded())
		SMesh->SetStaticMesh(BodyMesh.Object);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	DelegateTest.AddDynamic(this, &AMyPawn::ChangeVisible);
	DelegateTest.AddDynamic(this, &AMyPawn::ChangeScale);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;
	int timeTemp = static_cast<int>(timer) / 1;
	if (timeTemp >= 1)
	{
		timer = 0.f;

		if (DelegateTest.IsBound())
			DelegateTest.Broadcast();
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->
		BindAction(TEXT("Visible"), IE_Pressed, this, &AMyPawn::ChangeScale);
	PlayerInputComponent->
		BindAction(TEXT("Visible"), IE_Pressed, this, &AMyPawn::ChangeVisible);
}

void AMyPawn::ChangeVisible()
{
	SMesh->SetVisibility(bIsVisible = bIsVisible ? false : true);
}

void AMyPawn::ChangeScale()
{
	ScaleVector += FVector(0.1f, 0.1f, 0.1f);
	//UE_LOG(LogTemp,Warning,TEXT("%f,%f,%f"),ScaleVector.X,ScaleVector.Y,ScaleVector.Z);
	SMesh->SetRelativeScale3D(ScaleVector);
}
