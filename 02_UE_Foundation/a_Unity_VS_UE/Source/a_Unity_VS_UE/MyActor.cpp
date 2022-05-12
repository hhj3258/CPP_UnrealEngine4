// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 일반적인 cpp처럼 new로 동적생성하는 것이 아니다.
	// 언리얼의 CreateDefaultSubobject 같은 메소드(일종의 스마트포인터)를 사용한다.
	// CreateDefaultSubobject<포인터 타입>(TEXT(액터 이름));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;
	hp = 100;

	// Props에 있는 메쉬 중 하나의 경로를 사용해서 그 메쉬를 찾아온다.
	// 경로는 콘텐츠 브라우저의 메쉬 중 하나에 Ctrl+C 를 사용하면 복사 가능
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));

	// 메쉬를 불러오는데 성공했다면
	if (SM.Succeeded())
	{
		// Mesh에 해당 메쉬를 박는다.
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

