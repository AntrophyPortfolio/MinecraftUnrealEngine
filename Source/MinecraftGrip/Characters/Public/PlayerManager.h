#pragma once

#include "TerrainGeneration/Public/Voxel.h"
#include "GameFramework/Character.h"
#include "PlayerManager.generated.h"

class UVoxelData;
class AGameWorld;
class AMinecraftMode;
class USpringArmComponent;
class ABlockPlacer;
class UCameraComponent;
/**
 * Class that manages the player's character movement and camera.
 */
UCLASS()
class MINECRAFTGRIP_API APlayerManager final : public ACharacter
{
	GENERATED_BODY()

public:
	
	APlayerManager();
	
public: // Getters

	// Returns current digging status
	FORCEINLINE bool GetDigging() const { return bDigging; }

	// Returns index of selected block type by mouse scroll wheel
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetSelectedBlockTypeIndex() const { return SelectedBlockIndex; }
	
protected: // Overriden methods
	
	virtual void BeginPlay() override;
	
	virtual void Tick(const float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private: // Setup player movement and visuals
	
	void SetupPlayerMovement() const;
	
	void SetupPlayerVisuals() const;

private: // Setup player camera
	
	void SetupPlayerCamera();
	
	void ToggleThirdPerson();

private: // Handle player input
	
	void HandleMoveForward(const float Value);
	
	void HandleMoveRight(const float Value);
	
	void HandleStartDigging();
	
	void HandleStopDigging();
	
	void HandleStartSprinting();
	
	void HandleStopSprinting();
	
	void HandlePlaceBlock();
	
	void HandleMouseScrollUp();
	
	void HandleMouseScrollDown();
	
	void HandleSaveGame();

private: // Handle block interaction
	
	void PlaceCursorBlock();
	
	void DestroyVoxel(const float DeltaTime);

private: // Attributes camera
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	UVoxelData* VoxelData;

private: // Attributes block interaction
	
	int32 SelectedBlockIndex;
	
	float CheckIncrement;
	
	float ReachableVoxelDistance;
	
	FVector DiggedVoxelPosition;
	
	bool CanManipulateBlocks;
	
	bool DiggingStarted;

	UPROPERTY()
	FVoxel DiggedVoxel;
	
	float TimeToDestroyVoxel;
	
	UPROPERTY()
	ABlockPlacer* HighlightBlock;
	
	UPROPERTY()
	ABlockPlacer* PlaceBlock;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDigging;

private: // Basic attributes
	
	UPROPERTY()
	AGameWorld* GameWorld;
	
	UPROPERTY()
	AMinecraftMode* GameMode;
	
};
