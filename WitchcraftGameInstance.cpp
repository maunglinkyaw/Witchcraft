// Lin & Yin's Witchcraft 2020


#include "WitchcraftGameInstance.h"
#include "C_SystemSave.h"

#include "Kismet/GameplayStatics.h"
#include "Witchcraft.h"


void UWitchcraftGameInstance::SaveSystemSave()
{
	if (UC_SystemSave* saveGame = Cast<UC_SystemSave>(UGameplayStatics::CreateSaveGameObject(UC_SystemSave::StaticClass())))
	{
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		SavedDelegate.BindUObject(this, &UWitchcraftGameInstance::OnSaveGameDone);

		// Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(saveGame, m_SystemSaveName, 0, SavedDelegate);
	}
}

void UWitchcraftGameInstance::LoadSystemSave()
{
	UE_LOG(LogSystem, Display, TEXT("%s - LoadSystemSave"), *GetName());

	// Set up the delegate.
	FAsyncLoadGameFromSlotDelegate loadedDelegate;
	// USomeUObjectClass::LoadGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData
	loadedDelegate.BindUObject(this, &UWitchcraftGameInstance::OnLoadGameDone);
	
	UGameplayStatics::AsyncLoadGameFromSlot(m_SystemSaveName, 0, loadedDelegate);
}

void UWitchcraftGameInstance::OnSaveGameDone(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{

}

void UWitchcraftGameInstance::OnLoadGameDone(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	UE_LOG(LogSystem, Display, TEXT("%s - OnLoadGameDone"), *GetName());

	if (UC_SystemSave* loadedGame = Cast<UC_SystemSave>(LoadedGameData))
	{
		m_TempSystemSave = loadedGame;
	}
}

TArray<FString> UWitchcraftGameInstance::GetAllSaveGameSlotNames()
{
	//////////////////////////////////////////////////////////////////////////////
	class FFindSavesVisitor : public IPlatformFile::FDirectoryVisitor
	{
	public:
		FFindSavesVisitor() {}

		virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			if (!bIsDirectory)
			{
				FString FullFilePath(FilenameOrDirectory);
				if (FPaths::GetExtension(FullFilePath) == TEXT("sav"))
				{
					FString CleanFilename = FPaths::GetBaseFilename(FullFilePath);
					CleanFilename = CleanFilename.Replace(TEXT(".sav"), TEXT(""));
					SavesFound.Add(CleanFilename);
				}
			}
			return true;
		}
		TArray<FString> SavesFound;
	};
	//////////////////////////////////////////////////////////////////////////////

	TArray<FString> Saves;
	const FString SavesFolder = FPaths::ProjectDir() + TEXT("SaveGames");

	if (!SavesFolder.IsEmpty())
	{
		FFindSavesVisitor Visitor;
		FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*SavesFolder, Visitor);
		Saves = Visitor.SavesFound;
	}

	return Saves;
}
