// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"

#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// InitializeComponent() 메소드를 호출하기 위한 작업
	// true 일 때만 호출된다.
	bWantsInitializeComponent = true;

	Level = 1;
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UMyStatComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		// Level에 따른 StatData를 받아온다.
		auto StatData = MyGameInstance->GetStatData(Level);
		if (StatData)
		{
			Level = StatData->Level;
			Attack = StatData->Attack;
			Hp = StatData->MaxHp;
		}
	}
}

void UMyStatComponent::OnAttacked(float DamageAmount, AActor* DamageCauser)
{
	Hp -= DamageAmount;
	if (Hp <= 0)
		Hp = 0;

	UE_LOG(LogTemp, Warning, TEXT("%s OnAttacked, Hp = %d"), *GetOwner()->GetName(), Hp);
}
