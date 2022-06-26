// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	//DefaultPawnClass = AMyCharacter::StaticClass();

	// 블루프린트 클래스를 불러올 땐 경로 마지막에 _C 를 붙여줘야 함.
	static ConstructorHelpers::FClassFinder<ACharacter> BP_Char(
		TEXT("Blueprint'/Game/BluePrints/BP_MyCharacter.BP_MyCharacter_C'"));

	if(BP_Char.Succeeded())
		DefaultPawnClass = BP_Char.Class;
}