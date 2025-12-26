

# File SerializableObj.cpp

[**File List**](files.md) **>** [**Battle**](dir_59b3558fc0091a3111c9e7dd8d94b2ea.md) **>** [**Misc**](dir_4fd921e402b7a240656c31e280e3875c.md) **>** [**SerializableObj.cpp**](_serializable_obj_8cpp.md)

[Go to the documentation of this file](_serializable_obj_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializableObj.h"

#include "Serialization/ObjectReader.h"
#include "Serialization/ObjectWriter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SerializableObj)

TArray<uint8> USerializableObj::SaveForRollback()
{
    TArray<uint8> SaveData;
    FObjectWriter Writer(SaveData);
    Writer.ArIsSaveGame = true;
    GetClass()->SerializeBin(Writer, this);
    return SaveData;
}

void USerializableObj::LoadForRollback(const TArray<uint8>& InBytes)
{
    if (InBytes.Num() <= 1) return;
    FObjectReader Reader(InBytes);
    Reader.ArIsSaveGame = true;
    GetClass()->SerializeBin(Reader, this);
}

void USerializableObj::ResetToCDO()
{
    const auto CDO = Cast<USerializableObj>(GetClass()->GetDefaultObject());
    LoadForRollback(CDO->SaveForRollback());
}
```


