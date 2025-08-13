#pragma once
#include "Prerequisites.h"

/**
 * @struct LapComponent
 * @brief Stores lap timing and progress info for a racing entity.
 *
 * @details
 * Keeps current lap, best lap time, total race time, and progress
 * between checkpoints for gameplay logic and race tracking systems.
 */
struct
  LapComponent {
  /** Current lap number (starting at 0 or 1 depending on game rules). */
  int   lap = 0;

  /** Time elapsed since the start of the current lap (seconds). */
  float currentLapTime = 0.f;

  /** Fastest lap time achieved; initialized to infinity. */
  float bestLapTime = std::numeric_limits<float>::infinity();

  /** Total race time accumulated (seconds). */
  float totalTime = 0.f;

  /** Index of the last checkpoint reached in the lap. */
  size_t checkpoint = 0;

  /** Progress ratio (0..1) along the current segment toward the next checkpoint. */
  float  progressAlongSegment = 0.f;
};
