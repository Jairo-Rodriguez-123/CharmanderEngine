#pragma once

/**
 * @class RaceCountdown
 * @brief Simple countdown timer for race starts ("3", "2", "1", "GO!").
 *
 * @details
 * Non-blocking timer that can be used in the main game loop without halting
 * other systems like track updates or UI. Intended for use in BaseApp to
 * gate which systems are active during the countdown phase.
 */
class
  RaceCountdown {

public:
  /**
   * @brief Construct a countdown with a total time in seconds.
   * @param seconds Total countdown duration (default 3.0f).
   */
  RaceCountdown(float seconds = 3.f)
    : total_(seconds),
    remaining_(seconds),
    started_(false),
    finished_(false) {
  }

  /** @brief Default destructor. */
  ~RaceCountdown() = default;

  /**
   * @brief Start the countdown from the full total time.
   */
  void
    start() {
    started_ = true;
    finished_ = false;
    remaining_ = total_;
  }

  /**
   * @brief Stop the countdown immediately.
   */
  void
    stop() { started_ = false; }

  /**
   * @brief Check if the countdown is currently running.
   * @return True if started and not yet finished.
   */
  bool
    isStarted() const { return started_; }

  /**
   * @brief Check if the countdown has completed.
   * @return True if "GO!" has been reached.
   */
  bool
    isFinished() const { return finished_; }

  /**
   * @brief Advance countdown and get the display text for this frame.
   *
   * @details
   * Decrements remaining time by @p dt. Returns:
   * - "3", "2", or "1" while counting down.
   * - "GO!" when countdown reaches zero.
   * - "" (empty) if not running or already finished.
   *
   * @param dt Seconds elapsed since the last tick.
   * @return Countdown text for this frame.
   */
  std::string
    tick(float dt) {
    if (!started_ || finished_) return "";
    remaining_ = std::max(0.f, remaining_ - dt);
    if (remaining_ == 0.f) {
      finished_ = true;
      started_ = false;
    }
    int num = static_cast<int>(remaining_ + 0.999f); // ceil-like display
    if (finished_) return "GO!";
    return (num >= 1) ? std::to_string(num) : "GO!";
  }

private:
  /** Total countdown duration in seconds. */
  float total_;

  /** Time remaining in the countdown. */
  float remaining_;

  /** True if countdown is active. */
  bool  started_;

  /** True if countdown has finished ("GO!"). */
  bool  finished_;
};
