#include "TerrainGeneration/Public/Chunk.h"
#include "TerrainGeneration/Public/ChunkData.h"
#include "TerrainGeneration/Public/GameWorld.h"
#include "TerrainGeneration/Public/VoxelData.h"
#include "TerrainGeneration/Public/ChunkLoaderAsync.h"
#include "TerrainGeneration/Public/Voxel.h"
#include "TerrainGeneration/Public/BlockType.h"

#include "ProceduralMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AChunk::AChunk() :
	bIsVoxelMapPopulated(false)
{
	PrimaryActorTick.bCanEverTick = false;

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	RootComponent = ProceduralMeshComponent;

	const ConstructorHelpers::FObjectFinder<UMaterial> Material(
		TEXT("Material'/Game/_Game/Materials/Blocks_Material.Blocks_Material'"));

	checkf(Material.Object, TEXT("Material is not valid."));
	ProceduralMeshComponent->SetMaterial(0, Material.Object);
	ProceduralMeshComponent->SetMaterial(1, Material.Object);
}

void AChunk::BeginPlay()
{
	Super::BeginPlay();
}

void AChunk::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChunk::RenderChunk(const TArray<FVector>& InVertices, const TArray<int32>& InTriangles, const TArray<FVector2D>& InUVs)
{
	ProceduralMeshComponent->CreateMeshSection_LinearColor(RenderFlip, InVertices, InTriangles, TArray<FVector>(), InUVs, TArray<FLinearColor>{}, TArray<FProcMeshTangent>{}, true);
	RenderFlip = 1 - RenderFlip;
	ProceduralMeshComponent->ClearMeshSection(RenderFlip);
}

void AChunk::ModifyVoxel(const FIntVector& InPosition, const EBlockType InVoxelType)
{
	if (!VoxelMap.Contains(InPosition))
		return;

	FVoxel FoundVoxel = VoxelMap.FindRef(InPosition);
	FoundVoxel.ModifyVoxel(InVoxelType);
	VoxelMap.Emplace(InPosition, FoundVoxel);
	VoxelMapModifications.Add(InPosition, FoundVoxel);
}

void AChunk::UpdateChunkWithVoxel(const FVector& Position, const EBlockType InVoxelType)
{
	FIntVector NewPos = FVectorToFlooredVector(Position);

	NewPos.X -= FMath::FloorToInt((float)SpawnLocation.X);
	NewPos.Y -= FMath::FloorToInt((float)SpawnLocation.Y);

	ModifyVoxel(NewPos, InVoxelType);

	UpdateSurroundingChunks(NewPos);
	RebuildChunk();
}

void AChunk::MakeExplosionAt(const FVector& InPositionOfInitialExplosion, const int32 InRadius)
{
	FIntVector InitialPosition = FVectorToFlooredVector(InPositionOfInitialExplosion);

	InitialPosition.X -= FMath::FloorToInt((float)SpawnLocation.X);
	InitialPosition.Y -= FMath::FloorToInt((float)SpawnLocation.Y);

	const int32 HoleExplosionStartIndex = -(InRadius / 2);
	const int32 HoleExplosionEndIndex = InRadius / 2;

	for (int32 XOffset = HoleExplosionStartIndex; XOffset < HoleExplosionEndIndex; XOffset += 100)
	{
		for (int32 YOffset = HoleExplosionStartIndex; YOffset < HoleExplosionEndIndex; YOffset += 100)
		{
			for (int32 ZOffset = HoleExplosionStartIndex; ZOffset < HoleExplosionEndIndex; ZOffset += 100)
			{
				FIntVector VoxelPosition = FIntVector{InitialPosition.X + XOffset, InitialPosition.Y + YOffset, InitialPosition.Z + ZOffset};
				ModifyVoxel(VoxelPosition, EBlockType::AirBlock);
			}
		}
	}

	UpdateSurroundingChunks(InitialPosition);

	RebuildChunk();
}

void AChunk::UpdateSurroundingChunks(const FIntVector& InVoxelPosition) const
{
	for (int32 ChunkSide = 0; ChunkSide < 6; ChunkSide++)
	{
		const FVector PositionToCheck = FVector(InVoxelPosition + VoxelData->GetSideChecks()[ChunkSide]);

		if (PositionToCheck.X < 0 || PositionToCheck.Y < 0
			|| PositionToCheck.X >= FChunkData::ChunkWidthSize
			|| PositionToCheck.Y >= FChunkData::ChunkWidthSize)
		{
			GameWorld->GetChunkFromWorldPosition(FVector(FVector(SpawnLocation) + PositionToCheck))->RebuildChunk();
		}
	}
}

void AChunk::RebuildChunk()
{
	InitializeChunk(GameWorld, SpawnLocation, VoxelData);
}

void AChunk::LoadChunkAsync()
{
	(new FAutoDeleteAsyncTask<FChunkLoaderAsync>(SpawnLocation, VoxelMap, VoxelMapModifications, GameWorld->GetChunkArray(), VoxelData))->StartBackgroundTask();
}

FIntVector AChunk::FVectorToFlooredVector(const FVector& InFVector)
{
	FIntVector FlooredVector{FMath::FloorToInt(InFVector.X), FMath::FloorToInt(InFVector.Y), FMath::FloorToInt(InFVector.Z)};

	FlooredVector.X = FMath::FloorToInt((float)FlooredVector.X / 100) * 100;
	FlooredVector.Y = FMath::FloorToInt((float)FlooredVector.Y / 100) * 100;
	FlooredVector.Z = FMath::FloorToInt((float)FlooredVector.Z / 100) * 100;

	return FlooredVector;
}

void AChunk::SetChunkIsActive(const bool bIsActive)
{
	if (bIsActive)
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}

void AChunk::InitializeChunk(AGameWorld* InGameWorld, const FIntVector& InSpawnLocation, UVoxelData* InVoxelData)
{
	checkf(InGameWorld != nullptr, TEXT("GameWorld is not valid."));

	GameWorld = InGameWorld;
	SpawnLocation = InSpawnLocation;
	VoxelData = InVoxelData;
	LoadChunkAsync();
}

FVoxel AChunk::GetVoxelFromGlobalFVector(const FVector& InPosition) const
{
	FIntVector NewPost = FVectorToFlooredVector(InPosition);

	NewPost.X -= FMath::FloorToInt((float)SpawnLocation.X);
	NewPost.Y -= FMath::FloorToInt((float)SpawnLocation.Y);

	if (VoxelMap.Contains(NewPost))
		return VoxelMap.FindRef(NewPost);

	return VoxelMap.FindRef(FIntVector{0, 0, 0});
}
