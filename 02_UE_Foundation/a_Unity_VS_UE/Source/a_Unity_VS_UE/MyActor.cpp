// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �Ϲ����� cppó�� new�� ���������ϴ� ���� �ƴϴ�.
	// �𸮾��� CreateDefaultSubobject ���� �޼ҵ�(������ ����Ʈ������)�� ����Ѵ�.
	// CreateDefaultSubobject<������ Ÿ��>(TEXT(���� �̸�));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;
	hp = 100;

	// Props�� �ִ� �޽� �� �ϳ��� ��θ� ����ؼ� �� �޽��� ã�ƿ´�.
	// ��δ� ������ �������� �޽� �� �ϳ��� Ctrl+C �� ����ϸ� ���� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));

	// �޽��� �ҷ����µ� �����ߴٸ�
	if (SM.Succeeded())
	{
		// Mesh�� �ش� �޽��� �ڴ´�.
		Mesh->SetStaticMesh(SM.Object);
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

