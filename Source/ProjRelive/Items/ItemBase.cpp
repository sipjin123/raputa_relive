// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "Components/SphereComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	CollisionSphere->SetSphereRadius(35);
	CollisionSphere->SetCollisionProfileName("SphereCollision");
	CollisionSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnComponentOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnComponentEndOverlap);
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	float Distance = FVector::Dist(GetActorLocation(), OtherActor->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin with Component: "), Distance);
}

void AItemBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	float Distance = FVector::Dist(GetActorLocation(), OtherActor->GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Overlap END with Component: %f"), Distance);
}
