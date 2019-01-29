#pragma once
#include "constants.hpp"
#include <cstdint>

static inline constexpr uint32_t bits2bytes(uint32_t bits) noexcept {
	return bits >> 3;
}

// get rowsize including padding
static inline constexpr int32_t row_size(int32_t width, ColorDepth depth) noexcept {
	return ((width * depth + 31) / 32) * 4;
}

// tested only with truecolor
// width%4 == 0 ? 4 : ((width/4) + 1) * 4
static inline constexpr uint32_t row_padding(int32_t width, ColorDepth depth) noexcept {
	return (bits2bytes(width*depth) & 3 ? ((bits2bytes(width*depth) >> 2) + 1) << 2 : bits2bytes(width*depth)) - bits2bytes(width*depth);
}