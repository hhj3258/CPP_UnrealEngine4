// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class A_UNITY_VS_UE_API UMyCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UMyStatComponent* StatComp);

	void UpdateHp();
	
private:
	// BindWidget : 위젯 블루프린트 상의 'PB_HpBar'와 같은 이름의 변수를 자동으로 바인딩해준다.
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* PB_HpBar;

	TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;

	// UPROPERTY()
	// class UMyStatComponent* CurrentStatComp;
};
