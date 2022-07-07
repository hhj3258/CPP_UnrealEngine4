// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "CollidingPawnMovementComponet.h"
#include "RevolutionSceneComponent.h"
#include "SpawnSceneComponent.h"

// Sets default values
ACollidingPawn::ACollidingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Collision Settings
	SphereComponent = SetUpCollision(SphereComponent);
	//UE_LOG(LogTemp, Warning, TEXT("Constructor : %s"), SphereComponent ? TEXT("true") : TEXT("false"));

	// StaticMesh Settings
	UStaticMeshComponent* SphereVisual =
		CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	// Particle System Settings
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual); // MeshComponent에 붙인다
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.f, 0.f, 20.f));
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(
		TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// SpringArm Settings
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true; // 스프링 암의 길이가 부드럽게 변경된다.
	SpringArm->CameraLagSpeed = 3.f; // 얼마나 부드럽게 할지

	// Camera Settings
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	// USpringArmComponent::SocketName : 스프링 암 끝에 붙인다? 근데 없어도 되는거 같음;;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// 플레이어 컨트롤 받기 : 카메라, 인풋 등 받는 듯
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponet>(TEXT("CustomMovementComponent"));
	// MovementComponent가 업데이트 해줄 컴포넌트를 RootComponent로 지정
	OurMovementComponent->UpdatedComponent = RootComponent;

	// 직접 해보기 1
	// USceneComponent* RevolutionComponent = CreateDefaultSubobject<URevolutionSceneComponent>(TEXT("RevolutionComponent"));
	// RevolutionComponent->SetupAttachment(RootComponent);

	// 직접 해보기 2
	USceneComponent* SpawnSceneComponent = CreateDefaultSubobject<USpawnSceneComponent>(TEXT("SpawnSceneComponent"));
	SpawnSceneComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->
		BindAction(FName("ParticleToggle"), IE_Pressed, this, &ACollidingPawn::ParticleToggle);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ACollidingPawn::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ACollidingPawn::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ACollidingPawn::Turn);
}

USphereComponent* ACollidingPawn::SetUpCollision(USphereComponent* Component)
{
	// 인스턴스를 생성함.
	Component = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));

	// 물리 적용 true
	Component->SetSimulatePhysics(true);
	
	RootComponent = Component;
	Component->InitSphereRadius(40.0f);
	//UE_LOG(LogTemp,Warning,TEXT("Col Profile : %s"), *Component->GetCollisionProfileName().ToString());
	// 콜리전 프로필을 "Pawn"으로 변경함.
	Component->SetCollisionProfileName(TEXT("Pawn"));
	//UE_LOG(LogTemp,Warning,TEXT("Col Profile : %s"), *Component->GetCollisionProfileName().ToString());

	return Component;
}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}
