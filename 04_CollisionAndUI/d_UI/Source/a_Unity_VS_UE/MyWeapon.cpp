// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"
#include "Components/BoxComponent.h"
#include "MyCharacter.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionProfileName(TEXT("MyCollectible"));
	MeshComponent->SetRelativeRotation(FRotator(0.f,90.f,0.f));

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetupAttachment(MeshComponent);
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT(
		"StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));
	if (SW.Succeeded())
	{
		MeshComponent->SetStaticMesh(SW.Object);
	}
}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMyWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnCharacterOverlap);
}

void AMyWeapon::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));

	AMyCharacter* OverlappedActor = Cast<AMyCharacter>(OtherActor);
	if (OverlappedActor != nullptr)
	{
		const FName WeaponSocketName(TEXT("MyWeaponSocket"));

		AttachToComponent(OverlappedActor->GetMesh(),
		                  FAttachmentTransformRules::SnapToTargetIncludingScale,
		                  WeaponSocketName);
	}
}
