#include "ShrineHeal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h" 
#include "EO1Character.h"
#include "TimerManager.h"

AShrineHeal::AShrineHeal()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true; // Activa la comunicación de red para este actor

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
    OverlapBox->SetupAttachment(MeshComp);

    bIsAvailable = true;
}

void AShrineHeal::BeginPlay()
{
    Super::BeginPlay();
    UpdateVisuals(bIsAvailable);
}

void AShrineHeal::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AShrineHeal, bIsAvailable);
}

void AShrineHeal::ProcessHealing(AEO1Character* PlayerToHeal)
{
    if (HasAuthority() && bIsAvailable && PlayerToHeal)
    {
        // Esta es la base de la lógica de curación en el server
        PlayerToHeal->VidaActual = FMath::Clamp(PlayerToHeal->VidaActual + HealAmount, 0.0f, PlayerToHeal->VidaMaxima);
        
        // Acá trabaja el host. Actualiza su UI a mano.
        if (PlayerToHeal->IsLocallyControlled()) { PlayerToHeal->OnRep_VidaActual(); }

        bIsAvailable = false;
        OnRep_IsAvailable();

        Multicast_PlayHealEffect();
        PlayerToHeal->Client_ShowHealMessage();

        GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &AShrineHeal::ResetShrine, CooldownTime, false);
    }
}

void AShrineHeal::ResetShrine()
{
    if (HasAuthority())
    {
        bIsAvailable = true;
        OnRep_IsAvailable();
    }
}

void AShrineHeal::OnRep_IsAvailable()
{
    UpdateVisuals(bIsAvailable);
}

void AShrineHeal::Multicast_PlayHealEffect_Implementation()
{
    TriggerHealEffects();
}