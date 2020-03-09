#pragma once

#include <cstdint>
#include <atomic>

struct TotalStatsData
{
	unsigned int nrOfVertexShaders;
	unsigned int nrOfGeometryShaders;
	unsigned int nrOfPixelShaders;
	unsigned int nrOfShaderResources;
};

struct PerFrameStats
{
	std::atomic_uint_fast32_t nrOfDrawCalls = 0;
	std::atomic_uint_fast32_t nrOfDrawIndexedCalls = 0;
	std::atomic_uint_fast32_t nrOfDrawInstanced = 0;
	std::atomic_uint_fast32_t nrOfDrawIndexedInstanced = 0;
	std::atomic_uint_fast32_t nrOfTotalVerticesDrawn = 0;
	std::atomic_uint_fast32_t nrOfVertexShadersUsed = 0;
	std::atomic_uint_fast32_t nrOfHullShadersUsed = 0;
	std::atomic_uint_fast32_t nrOfDomainShadersUsed = 0;
	std::atomic_uint_fast32_t nrOfGeometryShadersUsed = 0;
	std::atomic_uint_fast32_t nrOfPixelShadersUsed = 0;
	std::atomic_uint_fast32_t nrOfRasterizerStates = 0;

	PerFrameStats& operator=(const PerFrameStats& other)
	{
		nrOfDrawCalls.store(other.nrOfDrawCalls.load(), std::memory_order_relaxed);
		nrOfDrawIndexedCalls.store(other.nrOfDrawIndexedCalls.load(), std::memory_order_relaxed);
		nrOfDrawInstanced.store(other.nrOfDrawInstanced.load(), std::memory_order_relaxed);
		nrOfDrawIndexedInstanced.store(other.nrOfDrawIndexedInstanced.load(), std::memory_order_relaxed);
		nrOfTotalVerticesDrawn.store(other.nrOfTotalVerticesDrawn.load(), std::memory_order_relaxed);
		nrOfVertexShadersUsed.store(other.nrOfVertexShadersUsed.load(), std::memory_order_relaxed);
		nrOfHullShadersUsed.store(other.nrOfHullShadersUsed.load(), std::memory_order_relaxed);
		nrOfDomainShadersUsed.store(other.nrOfDomainShadersUsed.load(), std::memory_order_relaxed);
		nrOfGeometryShadersUsed.store(other.nrOfGeometryShadersUsed.load(), std::memory_order_relaxed);
		nrOfPixelShadersUsed.store(other.nrOfPixelShadersUsed.load(), std::memory_order_relaxed);
		nrOfRasterizerStates.store(other.nrOfRasterizerStates.load(), std::memory_order_relaxed);

		return *this;
	}
};

struct PerFrameBuffer
{
	std::uint8_t nextToWriteTo = 0;
	PerFrameStats stats[2];
};