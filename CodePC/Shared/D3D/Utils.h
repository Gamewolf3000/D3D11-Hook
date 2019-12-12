#pragma once

static D3DXVECTOR3 GetRandomVector()
{
	D3DXVECTOR3 vec(
		-RAND_MAX * 0.5f + rand() % RAND_MAX,
		-RAND_MAX * 0.5f + rand() % RAND_MAX,
		-RAND_MAX * 0.5f + rand() % RAND_MAX
		);

	D3DXVec3Normalize(&vec, &vec);

	return vec;
}