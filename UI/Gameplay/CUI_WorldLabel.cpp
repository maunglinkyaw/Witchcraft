// Lin & Yin's Witchcraft 2020


#include "CUI_WorldLabel.h"
#include "Witchcraft.h"

#include "TextBlock.h"
#include "Image.h"
#include "InvalidationBox.h"

void UCUI_WorldLabel::UpdateLabelName(const FText& inName)
{
	UE_LOG(LogMenu, Display, TEXT("%s - UpdateLabelName - NameText: %s"), *GetName(), *GetNameSafe(NameText));

	if (NameText)
		NameText->SetText(inName);

}
