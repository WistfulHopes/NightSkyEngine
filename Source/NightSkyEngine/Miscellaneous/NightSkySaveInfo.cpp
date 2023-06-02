#include "NightSkySaveInfo.h"
#include "GameFramework/Actor.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
#include "Engine/World.h"

void UNightSkySaveInfo::ActorArraySaver(TArray<AActor*>& SaveActors)
{
	for (AActor* SaveActor : SaveActors)
	{
		ActorSaver(SaveActor);
	}
}

void UNightSkySaveInfo::ActorSaver(AActor* SaveActor)
{
	const int32 Index = ObjectRecords.Emplace();
	FObjectRecord& ObjectRecord = ObjectRecords[Index];

	ObjectRecord.Name = SaveActor->GetFName();
	ObjectRecord.Transform = SaveActor->GetTransform();
	ObjectRecord.Class = SaveActor->GetClass();
	ObjectRecord.bActor = true;

	SaveData(SaveActor, ObjectRecord.Data);

	this->TempObjects.Add(SaveActor);
	UE_LOG(LogTemp, Display, TEXT("Complete Save Actor %s"), *SaveActor->GetName())
}

void UNightSkySaveInfo::ActorPreloader(AActor* WorldActor, FObjectRecord& ActorRecord)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = ActorRecord.Name;

	// TODO: change this to SpawnActorDeferred so you can de-serialize and apply data before it calls constructor\BeginPlay
	AActor* NewActor = WorldActor->GetWorld()->SpawnActor(ActorRecord.Class, &ActorRecord.Transform, SpawnParams);
	//AActor* NewActor = WorldActor->GetWorld()->SpawnActorDeferred
        
	// BUG? actor doesn't appear to load scale correctly using transform so I specifically apply the scale after loading
	NewActor->SetActorScale3D(ActorRecord.Transform.GetScale3D());

	// don't load now, load after all objects are preloaded
	//LoadData(LoadObject, ObjectRecord.Data);

	// add to temp array for lookup it another object using already loaded objects as outers (array gets cleared once all objects loaded)
	this->TempObjects.Add(NewActor);

	UE_LOG(LogTemp, Display, TEXT("Complete Load Actor %s"), *NewActor->GetPathName())
}

void UNightSkySaveInfo::UObjectArraySaver(TArray<UObject*>& SaveObjects)
{
	for (UObject* SaveObject : SaveObjects)
	{
		UObjectSaver(SaveObject);
	}
}

void UNightSkySaveInfo::UObjectSaver(UObject* SaveObject)
{
	if (SaveObject == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Save Object!"))
		return;
	}

	if (SaveObject->HasAnyFlags(EObjectFlags::RF_Transient))
	{
		UE_LOG(LogTemp, Warning, TEXT("Saving RF_Transient object"))
		return;
	}

	if (SaveObject->IsA(AActor::StaticClass()))
	{
		ActorSaver(Cast<AActor>(SaveObject));
		return;
	}

	const int32 Index = ObjectRecords.Emplace();
	FObjectRecord& ObjectRecord = ObjectRecords[Index];

	// Use custom IDs for save / retrieving outer pointers
	// * Negative IDs if outer is a permanent map object (i.e. not loaded from SaveGame)
	// * Negative IDs start from -2 because -1 is already assigned to INDEX_NONE, and 0+ is used for SaveGame loaded objects
	ObjectRecord.OuterID = TempObjects.Find(SaveObject->GetOuter());
	ObjectRecord.bActor = false;

	// if outer is a saved object then don't try to save the direct object pointer
	if (ObjectRecord.OuterID == INDEX_NONE)
	{
		ObjectRecord.OuterID = PersistentOuters.Find(SaveObject->GetOuter());
		if (ObjectRecord.OuterID != INDEX_NONE)
		{
			ObjectRecord.OuterID = -(ObjectRecord.OuterID + 2);
		}
		else
		{
			const int32 Index2 = PersistentOuters.Add(SaveObject->GetOuter());
			ObjectRecord.OuterID = -(Index2 + 2);
			UE_LOG(LogTemp, Display, TEXT("Save Outer %s"), *SaveObject->GetOuter()->GetPathName())

		}
	}

	ObjectRecord.Name = SaveObject->GetFName();
	ObjectRecord.Class = SaveObject->GetClass();

	SaveData(SaveObject, ObjectRecord.Data);

	this->TempObjects.Add(SaveObject);

	UE_LOG(LogTemp, Display, TEXT("Complete Save UObject %s"), *SaveObject->GetName())
}

void UNightSkySaveInfo::UObjectsPreloader(AActor* WorldActor)
{
	UObject* LoadOuter = nullptr;

	for (FObjectRecord& ObjectRecord : ObjectRecords)
	{
		if (ObjectRecord.bActor == false)
		{
			if (ObjectRecord.OuterID != INDEX_NONE)
			{
				if (TempObjects.IsValidIndex(ObjectRecord.OuterID) == true)
				{
					LoadOuter = TempObjects[ObjectRecord.OuterID];
					if (LoadOuter == nullptr)
					{
						UE_LOG(LogTemp, Error, TEXT("Unable to find Outer for object (invalid array object)"))
					}
				}
				else
				{
					const int32 NewIndex = FMath::Abs(ObjectRecord.OuterID) - 2;

					if (PersistentOuters.IsValidIndex(NewIndex)) 
					{
						LoadOuter = PersistentOuters[NewIndex];
					}
					else 
					{
						UE_LOG(LogTemp, Error, TEXT("Unable to find Outer for object (invalid ID)"))
					}   
				}
			}
			if (LoadOuter == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Unable to find Outer for object (no pointer)"))
				continue;
			}

			UObject* LoadObject = NewObject<UObject>(LoadOuter, ObjectRecord.Class, ObjectRecord.Name);
            
			if (LoadObject == nullptr) return;

			// don't load now, load after all objects are preloaded
			//LoadData(LoadObject, ObjectRecord.Data);

			// add to here to cycle through and keep a pointer temporarily to avoid garbage collection (not sure if required but to be safe)
			this->TempObjects.Add(LoadObject);

			UE_LOG(LogTemp, Display, TEXT("Complete Load UObject %s %d"), *LoadObject->GetPathName(), this->TempObjects.Num() - 1)
		}

		else
		{
			ActorPreloader(WorldActor, ObjectRecord);
		}
	}
}

void UNightSkySaveInfo::UObjectDataLoader()
{
	for (int32 a = 0 ; ObjectRecords.IsValidIndex(a) ; a++)
	{
		// Load now after all objects are preloaded
		LoadData(TempObjects[a], ObjectRecords[a].Data);
	}
}

void UNightSkySaveInfo::SaveData(UObject* Object, TArray<uint8>& InData)
{
	if (Object == nullptr) return;

	FMemoryWriter MemoryWriter = FMemoryWriter(Data, true);
	FNightSkySaveArchive MyArchive = FNightSkySaveArchive(MemoryWriter);

	Object->Serialize(MyArchive);
}

void UNightSkySaveInfo::LoadData(UObject* Object, TArray<uint8>& InData)
{
	if (Object == nullptr) return;

	FMemoryReader MemoryReader(Data, true);

	FNightSkySaveArchive Ar(MemoryReader);
	Object->Serialize(Ar);
}

