#include "TerrainGeneration/Public/VoxelData.h"
#include "TerrainGeneration/Public/MinecraftTextureType.h"
#include "TerrainGeneration/Public/Voxel.h"

TArray<FVoxel>& UVoxelData::GetVoxelTypes()
{
	return VoxelTypes;
}

TArray<FIntVector>& UVoxelData::GetVoxelVertices()
{
	return VoxelVertices;
}

TArray<FSecondDimensionArray>& UVoxelData::GetVoxelSides()
{
	return VoxelSides;
}

TArray<FIntVector>& UVoxelData::GetSideChecks()
{
	return SideChecks;
}

TMap<EMinecraftTextureType, FUVCoordinates>& UVoxelData::GetTextureTypeUVMapping()
{
	return TextureTypeUVMapping;
}

// TMap<EMinecraftTextureType, TArray<FVector2D>> UVoxelData::TextureTypeUVMapping
// {
// 	{
// 		EMinecraftTextureType::StoneTexture, TArray{
// 			FVector2D(0.25f, 0.f),
// 			FVector2D(0.f, 0.f),
// 			FVector2D(0.f, 0.25f),
// 			FVector2D(0.25f, 0.25f)
// 		},
// 	},
// 	{
// 		EMinecraftTextureType::DirtTexture, TArray{
// 			FVector2D(0.5f, 0.f),
// 			FVector2D(0.25f, 0.f),
// 			FVector2D(0.25f, 0.25f),
// 			FVector2D(0.5f, 0.25f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::GrassDirtTexture, TArray{
// 			FVector2D(0.5f, 0.f),
// 			FVector2D(0.5f, 0.25f),
// 			FVector2D(0.75f, 0.25f),
// 			FVector2D(0.75f, 0.f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::SnowDirtTexture, TArray{
// 			FVector2D(0.75f, 0.f),
// 			FVector2D(0.75f, 0.25f),
// 			FVector2D(1.f, 0.25f),
// 			FVector2D(1.f, 0.f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::SnowTexture, TArray{
// 			FVector2D(0.25f, 0.25f),
// 			FVector2D(0.f, 0.25f),
// 			FVector2D(0.f, 0.5f),
// 			FVector2D(0.25f, 0.5f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::WoodSideTexture, TArray{
// 			FVector2D(0.5f, 0.25f),
// 			FVector2D(0.25f, 0.25f),
// 			FVector2D(0.25f, 0.5f),
// 			FVector2D(0.5f, 0.5f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::WoodTopBottomTexture, TArray{
// 			FVector2D(0.75f, 0.25f),
// 			FVector2D(0.5f, 0.25f),
// 			FVector2D(0.5f, 0.5f),
// 			FVector2D(0.75f, 0.5f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::GrassTopTexture, TArray{
// 			FVector2D(1.f, 0.25f),
// 			FVector2D(0.75f, 0.25f),
// 			FVector2D(0.75f, 0.5f),
// 			FVector2D(1.f, 0.5f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::BedrockTexture, TArray{
// 			FVector2D(0.5f, 0.5f),
// 			FVector2D(0.25f, 0.5f),
// 			FVector2D(0.25f, 0.75f),
// 			FVector2D(0.5f, 0.75f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::SandTexture, TArray{
// 			FVector2D(0.75f, 0.5f),
// 			FVector2D(0.5f, 0.5f),
// 			FVector2D(0.5f, 0.75f),
// 			FVector2D(0.75f, 0.75f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::GreenLeafTexture, TArray{
// 			FVector2D(1.f, 0.5f),
// 			FVector2D(0.75f, 0.5f),
// 			FVector2D(0.75f, 0.75f),
// 			FVector2D(1.f, 0.75f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::BirchTopBottomTexture, TArray{
// 			FVector2D(0.75f, 0.75f),
// 			FVector2D(0.5f, 0.75f),
// 			FVector2D(0.5f, 1.f),
// 			FVector2D(0.75f, 1.f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::BirchSideTexture, TArray{
// 			FVector2D(0.75f, 0.75f),
// 			FVector2D(0.5f, 0.75f),
// 			FVector2D(0.5f, 1.f),
// 			FVector2D(0.75f, 1.f)
// 		}
// 	},
// 	{
// 		EMinecraftTextureType::BrownLeafTexture, TArray{
// 			FVector2D(1.f, 0.75f),
// 			FVector2D(0.75f, 0.75f),
// 			FVector2D(0.75f, 1.f),
// 			FVector2D(1.f, 1.f)
// 		}
// 	}
// };
