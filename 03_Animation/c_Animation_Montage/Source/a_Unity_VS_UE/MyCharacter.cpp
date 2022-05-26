// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "MyAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Character의 하위 컴포넌트로 붙여줌
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	// 계층구조 : Character - CapsuleComponent - SpringArm - Camera
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	// 메쉬의 위치와 회전 설정
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.0f), FRotator(0.f, -90.f, 0.f));

	// 플레이어와 카메라 사이 거리
	SpringArm->TargetArmLength = 500.f;
	// 카메라 각도 조절, (pitch,yaw,roll) == (y,z,x)
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(
		TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	SpringArm->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyCharacter::Pitch);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
}

void AMyCharacter::UpDown(float Value)
{
	if (Value == 0.f)
		return;

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::LeftRight(float Value)
{
	if (Value == 0.f)
		return;

	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::Yaw(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::Pitch(float Value)
{
	AddControllerPitchInput(-Value);
}

void AMyCharacter::Attack()
{
	// UAnimInstance 를 UMyAnimInstance로 다운캐스팅
	const auto AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayAttackMontage();
	}
}
