// Copyright Epic Games, Inc. All Rights Reserved.


#include "etc_DelegateTestGameModeBase.h"

#include "MyPawn.h"

Aetc_DelegateTestGameModeBase::Aetc_DelegateTestGameModeBase()
{
	//DefaultPawnClass = AMyPawn::StaticClass();

	ConstructorHelpers::FClassFinder<AActor> BP_Pawn(TEXT("Blueprint'/Game/MyMyPawn.MyMyPawn_C'"));

	if(BP_Pawn.Succeeded())
	{
		DefaultPawnClass = BP_Pawn.Class;
	}
}
