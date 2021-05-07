 // Lin & Yin's Witchcraft 2020


#include "CUI_Menu.h"
#include "Witchcraft.h"
#include "Gameplay/CUI_Gameplay.h"

#include "CanvasPanelSlot.h"


void UCUI_Menu::EnterPage(int32 zOrder)
{
	UE_LOG(LogMenu, Display, TEXT("%s - EnterPage - zOrder: %d"), *GetName(), zOrder);

	if (UCanvasPanelSlot* tempSlot = Cast<UCanvasPanelSlot>(Slot))
	{
		tempSlot->SetZOrder(zOrder);
	}

	OnEnterPage();
}

void UCUI_Menu::ExitPage()
{
	UE_LOG(LogMenu, Display, TEXT("%s - ExitPage"), *GetName());

	OnExitPage();
}

void UCUI_Menu::ReenterPage()
{
	UE_LOG(LogMenu, Display, TEXT("%s - ReenterPage"), *GetName());

	OnReenterPage();
}

void UCUI_Menu::GoBackMenu()
{
	if (m_GameplayUI)
	{

	}
}

void UCUI_Menu::OnEnterPage_Implementation()
{

}

void UCUI_Menu::OnExitPage_Implementation()
{

}

void UCUI_Menu::OnReenterPage_Implementation()
{

}
