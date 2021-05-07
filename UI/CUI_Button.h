// Lin & Yin's Witchcraft 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUI_Button.generated.h"

class UNamedSlot;
class UImage;

UENUM(Blueprintable)
enum class E_MenuNavigation : uint8
{
	DOWN UMETA(DisplayName = "Down"),
	UP UMETA(DisplayName = "Up"),
	RIGHT UMETA(DisplayName = "Right"),
	LEFT UMETA(DisplayName = "Left"),
};

UENUM(Blueprintable)
enum class E_ButtonStatus : uint8
{
	DISABLED = 0 UMETA(DisplayName = "Disabled"),
	NORMAL		UMETA(DisplayName = "Normal"),
	FOCUSED		UMETA(DisplayName = "Focused"),
	PRESSED		UMETA(DisplayName = "Pressed"),
// 	TRIGGERED	UMETA(DisplayName = "Confirmed"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnNormalButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnFocusButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnPressButton);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(F_OnDisableButton);

UCLASS(hidecategories = ("Navigation"))
class WITCHCRAFT_API UCUI_Button : public UUserWidget
{
	GENERATED_BODY()
	
public:
	 
// 	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
// 		UNamedSlot* CustomSlot;
// 	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
// 		UImage* ButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_ButtonStatus m_ButtonStatus = E_ButtonStatus::NORMAL;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool m_AcceptInput = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool m_IsCursorHovering = false;
	
	UPROPERTY(EditAnywhere, Category = "Setup|Events")
	bool m_HasDoubleClick = false;
	UPROPERTY(BlueprintAssignable, Category = "Setup|Events")
	F_OnNormalButton ButtonIsNormal;
	UPROPERTY(BlueprintAssignable, Category = "Setup|Events")
	F_OnFocusButton ButtonIsFocused;
	UPROPERTY(BlueprintAssignable, Category = "Setup|Events")
	F_OnPressButton ButtonIsPressed;
	UPROPERTY(BlueprintAssignable, Category = "Setup|Events")
	F_OnDisableButton ButtonIsDisabled;

	void ChangeButtonStatus(E_ButtonStatus newStatus);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup", meta = (DisplayName = "BlueprintButtonNormal"))
	void BlueprintButtonNormal();
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup", meta = (DisplayName = "BlueprintButtonFocused"))
	void BlueprintButtonFocused();
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup", meta = (DisplayName = "BlueprintButtonPressed"))
	void BlueprintButtonPressed();
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup", meta = (DisplayName = "BlueprintButtonDisabled"))
	void BlueprintButtonDisabled();
	
	virtual void OnButtonNormal() {};
	virtual void OnButtonFocused() {};
	virtual void OnButtonPressed() {};
	virtual void OnButtonDisabled() {};

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

};
