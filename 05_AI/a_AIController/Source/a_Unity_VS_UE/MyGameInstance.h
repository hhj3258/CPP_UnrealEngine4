// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// 데이터 테이블의 Row마다 저장될 정보들
USTRUCT()
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;
};

UCLASS()
class A_UNITY_VS_UE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();
	
	virtual void Init() override;

	// 데이터테이블의 Level에 해당하는 Row 하나를 return
	FMyCharacterData* GetStatData(int32 Level);
	
private:
	// 데이터 테이블을 저장할 UDataTable*
	UPROPERTY()
	class UDataTable* MyStats;
};
