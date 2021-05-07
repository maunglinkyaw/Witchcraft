// Lin & Yin's Witchcraft 2020

#include "CUI_Button.h"
#include "CUI_Menu.h"

void UCUI_Button::ChangeButtonStatus(E_ButtonStatus newStatus)
{
	switch (newStatus)
	{
	case E_ButtonStatus::DISABLED:
		OnButtonDisabled();
		BlueprintButtonDisabled();

		if (ButtonIsDisabled.IsBound())
			ButtonIsDisabled.Broadcast();

		break;

	case E_ButtonStatus::NORMAL:
		OnButtonNormal();
		BlueprintButtonNormal();

		if (ButtonIsNormal.IsBound())
			ButtonIsNormal.Broadcast();

		break;

	case E_ButtonStatus::FOCUSED:
		OnButtonFocused();
		BlueprintButtonFocused();

		if (ButtonIsFocused.IsBound())
			ButtonIsFocused.Broadcast();

		break;

	case E_ButtonStatus::PRESSED:
		OnButtonPressed();
		BlueprintButtonPressed();

		if (ButtonIsPressed.IsBound())
			ButtonIsPressed.Broadcast();

		break;

	}

	m_ButtonStatus = newStatus;
}


void UCUI_Button::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (m_ButtonStatus < E_ButtonStatus::NORMAL || !m_AcceptInput)
		return;

// 	UE_LOG(LogMenus, Display, TEXT("%s - NativeOnMouseEnter"), *GetName());
	
	m_IsCursorHovering = true;
	ChangeButtonStatus(E_ButtonStatus::FOCUSED);

	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UCUI_Button::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (m_ButtonStatus < E_ButtonStatus::NORMAL || !m_AcceptInput)
		return;

// 	UE_LOG(LogMenus, Display, TEXT("%s - NativeOnMouseLeave"), *GetName());

	m_IsCursorHovering = false;
	ChangeButtonStatus(E_ButtonStatus::NORMAL);

	Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UCUI_Button::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (m_ButtonStatus < E_ButtonStatus::NORMAL || !m_AcceptInput)
		return FReply::Handled();

 	//UE_LOG(LogMenus, Display, TEXT("%s - NativeOnMouseButtonDown - FKey: %s"), *GetName(), *InMouseEvent.GetEffectingButton().GetDisplayName().ToString());

	ChangeButtonStatus(E_ButtonStatus::PRESSED);

	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	return FReply::Handled();
}

FReply UCUI_Button::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (m_ButtonStatus < E_ButtonStatus::NORMAL || !m_AcceptInput)
		return FReply::Handled();

// 	UE_LOG(LogMenus, Display, TEXT("%s - NativeOnMouseButtonUp - FKey: %s"), *GetName(), *InMouseEvent.GetEffectingButton().GetDisplayName().ToString());

	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled();
}

FReply UCUI_Button::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (m_ButtonStatus < E_ButtonStatus::NORMAL || !m_AcceptInput)
		return FReply::Handled();

	//UE_LOG(LogMenus, Display, TEXT("%s - NativeOnMouseButtonDoubleClick - FKey: %s"), *GetName(), *InMouseEvent.GetEffectingButton().GetDisplayName().ToString());

	if (!m_HasDoubleClick)
	{
		NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
	else
	{
		Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	}

	return FReply::Handled();
}
