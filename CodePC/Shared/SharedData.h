#pragma once

#include <cstdint>

struct StatsData
{
	unsigned int nrOfVertexShaders;
	unsigned int nrOfGeometryShaders;
	unsigned int nrOfPixelShaders;
	unsigned int nrOfShaderResources;
};

struct PerFrameStats
{
	std::uint64_t nrOfDrawCalls = 0;
	std::uint64_t nrOfDrawIndexedCalls = 0;
	std::uint64_t nrOfDrawInstanced = 0;
	std::uint64_t nrOfDrawIndexedInstanced = 0;
	std::uint64_t nrOfTotalVerticesDrawn = 0;
	std::uint64_t nrOfVertexShadersUsed = 0;
	std::uint64_t nrOfHullShadersUsed = 0;
	std::uint64_t nrOfDomainShadersUsed = 0;
	std::uint64_t nrOfGeometryShadersUsed = 0;
	std::uint64_t nrOfPixelShadersUsed = 0;
	std::uint64_t nrOfRasterizerStates = 0;
};

struct PerFrameBuffer
{
	std::uint8_t lastReadFrom = 0;
	std::uint8_t lastWrittenTo = 1;
	PerFrameStats stats[2];
};