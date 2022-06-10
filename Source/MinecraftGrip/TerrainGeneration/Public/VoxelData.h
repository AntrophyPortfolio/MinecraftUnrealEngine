#pragma once
#include "Voxel.h"

#include "VoxelData.generated.h"

enum class EMinecraftTextureType : uint8;

/**
 * Structure used to help create a 2D array of ints.
 */
USTRUCT()
struct FSecondDimensionArray
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName SideName;

	UPROPERTY(EditDefaultsOnly)
	TArray<int32> VoxelSides;
};

USTRUCT()
struct FUVCoordinates
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FVector2D> TextureCoordinates;
};

/**
 * Structure that contains definite voxel data.
 */
UCLASS(Blueprintable)
class UVoxelData final : public UDataAsset
{
	GENERATED_BODY()

public: // Getters

	TArray<FVoxel>& GetVoxelTypes();
	
	TArray<FIntVector>& GetVoxelVertices();
	
	TArray<FSecondDimensionArray>& GetVoxelSides();
	
	TArray<FIntVector>& GetSideChecks();
	
	TMap<EMinecraftTextureType, FUVCoordinates>& GetTextureTypeUVMapping();
	
private: // Properties set from blueprint.
	
	// Different voxel types with its default values set.
	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = "BlockType"))
	TArray<FVoxel> VoxelTypes;

	// The distance between each vertices.
	UPROPERTY(EditDefaultsOnly)
	TArray<FIntVector> VoxelVertices;

	// If you imagine a cube with all the vertices numbered, you would have 8 vertices.
	// This array contains sides that consist of numbered vertices.
	UPROPERTY(EditDefaultsOnly, meta = (TitleProperty = "SideName"))
	TArray<FSecondDimensionArray> VoxelSides;

	// This array contains coordinates for check whether something is next to it,
	// above or below to know whether a render for that side is needed.
	UPROPERTY(EditDefaultsOnly)
	TArray<FIntVector> SideChecks;

	// Every block has different textures for their sides, this will map the texture to specific sides.
	UPROPERTY(EditDefaultsOnly)
	TMap<EMinecraftTextureType, FUVCoordinates> TextureTypeUVMapping;

};
