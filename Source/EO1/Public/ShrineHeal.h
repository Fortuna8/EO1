#pragma once

#include "EO1Character.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShrineHeal.generated.h"

UCLASS()
class EO1_API AShrineHeal : public AActor
{
	GENERATED_BODY()
    
public:    
	AShrineHeal();

protected:
	virtual void BeginPlay() override;

public:    
	// Registro de variables para la red
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- COMPONENTES ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* OverlapBox;

	// --- LÓGICA DE RED ---
	// Variable replicada: Notifica a los clientes cuando cambia el estado
	UPROPERTY(ReplicatedUsing = OnRep_IsAvailable, BlueprintReadOnly, Category = "State")
	bool bIsAvailable;

	UFUNCTION()
	void OnRep_IsAvailable();

	UPROPERTY(EditAnywhere, Category = "Config")
	float HealAmount = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float CooldownTime = 5.0f;

	FTimerHandle CooldownTimerHandle;

	// Función que procesa la curación (Solo en Servidor)
	void ProcessHealing(class AEO1Character* PlayerToHeal);

	void ResetShrine();

	// --- RPCs ---
	// NetMulticast
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_PlayHealEffect();

	// Con este evento se visualiza el cambio de estado del shrine. Va a generar partículas y sonido.
	UFUNCTION(BlueprintImplementableEvent, Category = "Visuals")
	void TriggerHealEffects();
	
	// Con este booleano cambio los colores del shrine
	UFUNCTION(BlueprintImplementableEvent, Category = "Visuals")
	void UpdateVisuals(bool bAvailable);
};