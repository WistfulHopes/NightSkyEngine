

# File LinkActor.h

[**File List**](files.md) **>** [**Actors**](dir_51f67430d2b061bf5371397678dcec7e.md) **>** [**LinkActor.h**](_link_actor_8h.md)

[Go to the documentation of this file](_link_actor_8h.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LinkActor.generated.h"

UCLASS()
class NIGHTSKYENGINE_API ALinkActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ALinkActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    UFUNCTION(BlueprintImplementableEvent)
    void Init();
    
    UFUNCTION(BlueprintImplementableEvent)
    void Update();
    
    UFUNCTION(BlueprintImplementableEvent)
    void Exit();
};
```


