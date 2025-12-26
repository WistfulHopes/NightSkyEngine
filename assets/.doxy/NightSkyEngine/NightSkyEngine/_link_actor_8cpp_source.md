

# File LinkActor.cpp

[**File List**](files.md) **>** [**Actors**](dir_51f67430d2b061bf5371397678dcec7e.md) **>** [**LinkActor.cpp**](_link_actor_8cpp.md)

[Go to the documentation of this file](_link_actor_8cpp.md)


```C++
// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkActor.h"


// Sets default values
ALinkActor::ALinkActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALinkActor::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ALinkActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

```


