// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUI_Menu.generated.h"



UCLASS()
class WITCHCRAFT_API UCUI_Menu : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	class UCUI_Gameplay* m_GameplayUI = nullptr;


	void EnterPage(int32 zOrder);
	void ExitPage();

	void ReenterPage();

	void GoBackMenu();

	UFUNCTION(BlueprintNativeEvent)
	void OnEnterPage();
	UFUNCTION(BlueprintNativeEvent)
	void OnExitPage();
	UFUNCTION(BlueprintNativeEvent)
	void OnReenterPage();

	void OnPressConfirm(bool isPress);
	void OnPressCancel(bool isPress);

// 	UFUNCTION(BlueprintImplementableEvent)
// 	void BlueprintOnEnterPage();
// 	UFUNCTION(BlueprintImplementableEvent)
// 	void BlueprintOnExitPage();
};
