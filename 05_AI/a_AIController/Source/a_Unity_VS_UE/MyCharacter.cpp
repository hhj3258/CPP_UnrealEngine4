// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "DrawDebugHelpers.h"
#include "MyAIController.h"
#include "MyAnimInstance.h"
#include "MyCharacterWidget.h"
#include "MyStatComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region SpringArm & Camera
	// Character의 하위 컴포넌트로 붙여줌
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	// 계층구조 : Character - CapsuleComponent - SpringArm - Camera
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	// 플레이어와 카메라 사이 거리
	SpringArm->TargetArmLength = 500.f;
	// 카메라 각도 조절, (pitch,yaw,roll) == (y,z,x)
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	SpringArm->bUsePawnControlRotation = true;
#pragma endregion

#pragma region Mesh Setting
	// 메쉬의 위치와 회전 설정
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.0f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(
		TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
#pragma endregion

	MyStatComponent = CreateDefaultSubobject<UMyStatComponent>(TEXT("STAT"));

#pragma region HpBar Widget
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetWidgetSpace(EWidgetSpace::Screen); // Screen과 World가 있다. Screen이면 화면에 고정되는 듯
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
	}
#pragma endregion

	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// BeginPlay보다 생명주기 상으로 먼저 실행됨
void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// AnimInstance는 Mesh에 붙어있다.
	// UAnimInstance 를 UMyAnimInstance로 다운캐스팅
	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		// OnMontageEnded : 몽타주가 끝난 시점에 실행할 함수들을 추가해줄 수 있음. 델리게이트.
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);

		// Collision 테스트 관련 
		AnimInstance->OnAttackHit.AddUObject(this, &AMyCharacter::AttackCheck);
	}

	// 위젯 초기화 메소드
	// 안해도 되는데 하는 게 좋음(오류방지)
	HpBar->InitWidget();

	const auto HpWidget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
		HpWidget->BindHp(MyStatComponent);
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
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMyCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMyCharacter::EndSprint);

	// "Attack" 인풋이 발생하면 Attack함수를 호출
	PlayerInputComponent->
		BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
}

void AMyCharacter::UpDown(float Value)
{
	if (IsAttacking)
		return;

	if (isRunning)
	{
		UpDownValue = Value * 2;
	}
	else
	{
		UpDownValue = Value;
	}

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::LeftRight(float Value)
{
	if (IsAttacking)
	{
		return;
	}

	if (isRunning)
	{
		LeftRightValue = Value * 2;
	}
	else
	{
		LeftRightValue = Value;
	}

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

// "Attack" 인풋 발생시 호출
void AMyCharacter::Attack()
{
	if (AnimInstance->GetIsFalling())
		return;
	if (IsAttacking)
		return;
	else
		IsAttacking = true;

	if (AnimInstance)
		AnimInstance->PlayAttackMontage();

	//UE_LOG(LogTemp,Warning,TEXT("AttackIndex = %d"),AttackIndex);
	// 호출될 때마다 Section 변경을 위해 설정
	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;
}

void AMyCharacter::AttackCheck()
{
	// 캐릭터 기준으로 앞쪽에 캡슐형태로 공격 범위 판정할 것임
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	// Capsule 형태로 판정
	float AttackRange = 100.f; // 길이
	float AttackRadius = 50.f; // 너비

	// SweepSingleByChannel : 트레이스 채널을 사용해서 물리적 충돌 여부를 가린다.
	// - 특정 도형을 월드에서 Sweep(쓸기)하면서 특정 채널을 사용하여 첫 번째로 block된 hit를 반환한다.
	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRange),
		Params
	);

	if (bResult && HitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *HitResult.Actor->GetName());

		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(MyStatComponent->GetAttack(), DamageEvent, GetController(), this);
	}

	FVector VecAttackRange = GetActorForwardVector() * AttackRange;
	FVector VecCenter = GetActorLocation() + VecAttackRange * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(VecAttackRange).ToQuat();
	FColor DrawColor;
	if (bResult)
	{
		DrawColor = FColor::Green;
	}
	else
	{
		DrawColor = FColor::Red;
	}
	DrawDebugCapsule(GetWorld(), VecCenter, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);
}

void AMyCharacter::StartSprint()
{
	isRunning = true;
	GetCharacterMovement()->MaxWalkSpeed *= 2;
}

void AMyCharacter::EndSprint()
{
	isRunning = false;
	GetCharacterMovement()->MaxWalkSpeed /= 2;
}

// 몽타주가 끝나면 호출
void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	MyStatComponent->OnAttacked(DamageAmount, this);

	return Damage;
}
