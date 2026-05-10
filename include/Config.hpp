#pragma once

inline constexpr float WINDOW_SIZE = 800;
inline constexpr float GRID_SIZE = 640;
inline constexpr float GAP_TO_TILE_SPACE_RATIO = 0.24;
inline constexpr int GRID_DIMENSION = 4;


inline constexpr float GRID_OFFSET = (WINDOW_SIZE - GRID_SIZE) / 2;
inline constexpr float TILE_SIZE = GRID_SIZE * (1 - GAP_TO_TILE_SPACE_RATIO) / GRID_DIMENSION;
inline constexpr float GAP_SIZE = GRID_SIZE * GAP_TO_TILE_SPACE_RATIO / (GRID_DIMENSION + 1);
inline constexpr float GRID_LINE_WIDTH = GAP_SIZE / 4;


inline constexpr int FONT_SIZE = TILE_SIZE * 2/3;

inline constexpr float ANIM_TIME = 0.1;