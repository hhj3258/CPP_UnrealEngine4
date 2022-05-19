// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));

	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 폰 인풋 메서드
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// '프로젝트 셋팅 - 입력' 에서 Axis 세팅을 이름을 동일하게 세팅해줘야 함.
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPawn::LeftRight);
}

void AMyPawn::UpDown(float Value)
{
	if (Value == 0.f)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), Value);
	// GetActorForwardVector 에 Value 값을 곱하는 식으로 구현되어 있음.
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyPawn::LeftRight(float Value)
{
	if (Value == 0.f)
		return;

	UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value);
	// GetActorRightVector : 액터의 오른쪽 벡터
	AddMovementInput(GetActorRightVector(), Value);
}