#pragma once

#include "Voxel.generated.h"

class UVoxelData;
class AGameWorld;
enum class EBlockType : uint8;
enum class EMinecraftTextureType : uint8;

/**
 * Details about the voxel, base building block of the world.
 */
USTRUCT()
struct FVoxel
{
	GENERATED_BODY()

public:

	FVoxel();
	
public:

	// Based on height from PositionInChunk attribute, choose the type of the block. 
	EBlockType DetermineBlockTypeBasedOnHeight() const;

	// Based on the side, the method will return texture type, e.g. side 1 will return side texture.
	EMinecraftTextureType GetTextureType(const int32 InSideIndex) const;

	// Based on the current type of the attribute BlockType, assign the properties.
	void AssignPropertiesBasedOnType();

	// Initialize a voxel with default values.
	void InitializeVoxel(const FVector& InPosition, UVoxelData* InVoxelData);

	// Create a specific voxel type that will be used for assigning properties based on type.
	void InitializeVoxelType(const bool InbIsSolid, const EBlockType InBlockType, const float InDestroyTime, const EMinecraftTextureType InSideTexture,
	                         const EMinecraftTextureType InTopTexture, const EMinecraftTextureType InBottomTexture, UVoxelData* InVoxelData);

	// Initializes a voxel with any block type. The properties will be assigned based on the type passed.
	void InitializeSpecificVoxel(const FVector& InPosition, EBlockType InBlockType, UVoxelData* InVoxelData);

	// Modifies current voxel with a new block type and updates properties.
	void ModifyVoxel(const EBlockType NewBlockType);

	// Checks if the voxel is outside of its chunk.
	static bool IsVoxelOutsideChunk(const FIntVector& Position);

	// Checks if the voxel is in the world.
	static bool IsVoxelInWorld(const FVector& Position);

	// Uses 3D Perlin Noise to create caves beneath the ground.
	EBlockType GenerateBlockBelowGround(const int32 InCurrentPosition,const int32 InHighestBlockPosition,const EBlockType InVoxelType) const;

	FVector PositionInChunk;

	UPROPERTY(EditDefaultsOnly)
	EMinecraftTextureType SideTexture;
	
	UPROPERTY(EditDefaultsOnly)
	EMinecraftTextureType TopTexture;
	
	UPROPERTY(EditDefaultsOnly)
	EMinecraftTextureType BottomTexture;
	
	UPROPERTY(EditDefaultsOnly)
	bool bIsSolid;
	
	UPROPERTY(EditDefaultsOnly)
	float DestroyTime;
	
	UPROPERTY(EditDefaultsOnly)
	EBlockType BlockType;

	UPROPERTY()
	UVoxelData* VoxelData;

};

