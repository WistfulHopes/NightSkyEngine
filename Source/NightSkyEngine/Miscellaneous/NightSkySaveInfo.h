#pragma once
#include "GameFramework/SaveGame.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "NightSkySaveInfo.generated.h"

struct FNightSkySaveArchive : FObjectAndNameAsStringProxyArchive
{
	FNightSkySaveArchive(FArchive& InInnerArchive)
		: FObjectAndNameAsStringProxyArchive(InInnerArchive, true)
	{
		ArIsSaveGame = true;
		ArNoDelta = true;
	}
};

USTRUCT(BlueprintType)
struct FObjectRecord
{
	GENERATED_BODY()

	// class that this object is
	UPROPERTY(BlueprintReadWrite)
	UClass* Class;

	// save the outer used for object so they get loaded back in the correct hierarchy
	UPROPERTY(BlueprintReadWrite)
	UObject* Outer;

	// save the outer used for object so they get loaded back in the correct hierarchy
	UPROPERTY(BlueprintReadWrite)
	int32 OuterID;

	// if the outer is an actor otherwise will be UObject
	UPROPERTY(BlueprintReadWrite)
	bool bActor;

	// this is for loading only, store a pointer for the loaded object here so you can loop for the records later to de-serialize all the data
	UPROPERTY(BlueprintReadWrite)
	UObject* Self;

	// Name of the object
	UPROPERTY(BlueprintReadWrite)
	FName Name;

	// serialized data for all UProperties that are 'SaveGame' enabled
	UPROPERTY(BlueprintReadWrite)
	TArray<uint8> Data;

	// Spawn location if it's an actor
	UPROPERTY(BlueprintReadWrite)
	FTransform Transform;

	FObjectRecord()
	{
		Class = nullptr;
		Outer = nullptr;
		Self = nullptr;
	}
};

UCLASS()
class UNightSkySaveInfo : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<uint8> Data;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjectRecord> ObjectRecords;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UObject*> TempObjects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UObject*> PersistentOuters;

	// basically just a wrapper so you don't have to do a for loop in blueprints
	UFUNCTION(BlueprintCallable)
	void ActorArraySaver(UPARAM(ref)TArray<AActor*>& SaveActors);

	// Save individual Actors
	UFUNCTION(BlueprintCallable)
	void ActorSaver(AActor* SaveActor);

	// Create all saved actors without any data serialized yet
	UFUNCTION(BlueprintCallable)
	void ActorPreloader(AActor* WorldActor, FObjectRecord& ActorRecord);

	// basically just a wrapper so you don't have to do a for loop in blueprints
	UFUNCTION(BlueprintCallable)
	void UObjectArraySaver(UPARAM(ref) TArray<UObject*>& SaveObjects);

	// Save individual objects
	UFUNCTION(BlueprintCallable)
	void UObjectSaver(UObject* SaveObject);

	// create all saved objects without any data serialized yet
	UFUNCTION(BlueprintCallable)
	void UObjectsPreloader(AActor* WorldActor);

	// load all data after all objects exist so all pointers will load
	UFUNCTION(BlueprintCallable)
	void UObjectDataLoader();

	// serialize the data
	UFUNCTION(BlueprintCallable)
	void SaveData(UObject* Object, TArray<uint8>& InData);

	// de-serialize the data
	UFUNCTION(BlueprintCallable)
	void LoadData(UObject* Object, UPARAM(ref) TArray<uint8>& InData);
};
