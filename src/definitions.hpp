#pragma once

// 640x480 4:3, 1280x960 16:9,
inline constexpr int SCREEN_WIDTH = 1280;
inline constexpr int SCREEN_HEIGHT = 960;
inline constexpr int BLOCK_SIZE = 20;

inline constexpr int COLS = SCREEN_WIDTH / BLOCK_SIZE;
inline constexpr int ROWS = SCREEN_HEIGHT / BLOCK_SIZE;
inline constexpr unsigned int ANIMATION_FRAMES_DELAY = 30;