#pragma once

#include "Voxel.h"

#include "Async/AsyncWork.h"

class UVoxelData;
struct FChunkWidth;
enum class EBlockType : uint8;
enum class EMinecraftTextureType : uint8;

// Structure that is passed out from the async task to the main thread
struct FMeshData
{
	int32 XCoordinate;
	int32 YCoordinate;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;

	TMap<FIntVector, FVoxel> VoxelMap;
};

/**
 * Async task that generates a mesh for a chunk
 */

struct FChunkLoaderAsync : FNonAbandonableTask
{
public:
	
	FChunkLoaderAsync(const FIntVector& InWorldPosition,
	                  const TMap<FIntVector, FVoxel>& InVoxelMap,
	                  const TMap<FIntVector, FVoxel>& InModifiedVoxelMap,
	                  const TArray<FChunkWidth>& InChunkArray,
	                  UVoxelData* InVoxelData);

	static TStatId GetStatId();
	
	void DoWork();

private: // Prepare data for rendering
	
	void PopulateVoxelMap();
	
	void GenerateVertices();
	
	void UpdateMeshData(const FIntVector& InPosition);
	
	void AddTexture(const EMinecraftTextureType InTextureType);

private: // Checks for populating mesh data
	
	bool IsVoxelSideOccupied(const FVector& InPosition) const;
	
	bool VoxelExistsAndIsSolid(const FVector& InPosition) const;

private: // Generate additional details to the world
	
	void GenerateTreeTop(const FVector& InPosition, const EBlockType InTreeTopType);
	
	void GenerateTreeAtLocation(const FIntVector& InLocation, const EBlockType TreeTrunkType);
	
	void GenerateLeafAtPosition(const FVector& InLocation, const EBlockType InTreeTopType);

private: // Utility method
	
	FVoxel GetVoxelFromWorldPosition(const FVector& InPosition) const;

private: // Attributes that are needed for the async task
	
	TArray<FChunkWidth> ChunkArray;

	TMap<FIntVector, FVoxel> ModifiedVoxelMap;
	
	FIntVector SpawnPosition;
	
	int32 VertexIndex;
	
	FMeshData MeshData;

	UVoxelData* VoxelData;
	
};
