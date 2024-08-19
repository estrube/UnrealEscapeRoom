// Fill out your copyright notice in the Description page of Project Settings.

#include "Poster.h"


// Sets default values
APoster::APoster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("itemMesh"));
	RootComponent = itemMesh;

}

// Called when the game starts or when spawned
void APoster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

