// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCbot.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Controller_StartMenu.h"
#include "Components/SceneComponent.h"
#include "Engine.h"
#include "MyPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyNPCbot::AMyNPCbot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->SetupAttachment(this->GetCapsuleComponent());
	CollisionSphere->InitSphereRadius(250.0f);
	

	isTalk = false;



}

void AMyNPCbot::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);
	Super::FaceRotation(CurrentRotation, DeltaTime);
}

// Called when the game starts or when spawned
void AMyNPCbot::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyNPCbot::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AMyNPCbot::OnOverlapEnd);
}

// Called every frame
void AMyNPCbot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//ACharacter* myCharLoc = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//FRotator Loc = myCharLoc->GetActorRotation();

	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	FVector myLoc = GetActorLocation();

	FVector Forward = (PlayerPos - myLoc);

	FRotator PlayerRot = FRotationMatrix::MakeFromX(Forward).Rotator();

	if (isTalk)
	{
		FaceRotation(PlayerRot, 0.01f);
		
	}
	else
	{
		//FaceRotation(PlayerRot, 0.f);
	}

	

	//FVector Direction = FVector(Direction.X, Direction.Y,0);
	//FRotator Rot = FRotationMatrix::MakeFromX(Direction).Rotator();

}



void AMyNPCbot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor&&(OtherActor!=this)&&!isTalk)
	{

		UGameplayStatics::PlaySound2D(this, InteractSound);
		isTalk = true;
		
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Touch!!"));

		
	}
	


	//AController_StartMenu* con = Cast<AController_StartMenu>(APawn::GetController());
	//con->ShowShopUI();
	//if (IsValid(con))
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);

	//	if (isTalk)
	//	{
	//		isTalk = false;
	//	}
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("I can't find controller"));
	//}
	

}

void AMyNPCbot::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	if (OtherActor && (OtherActor != this) && isTalk)
	{
		//isTalk = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Out!"));
	}
	
}

