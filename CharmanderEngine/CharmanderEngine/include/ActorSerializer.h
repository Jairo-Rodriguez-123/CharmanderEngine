#// ActorSerializer.h
#pragma once
#include "ECS/Actor.h"
#include "Prerequisites.h"

/**
 * @namespace ActorSerializer
 * @brief Provides functions to save and load actors from files.
 *
 * @details
 * These functions serialize or deserialize a list of actors to/from a
 * file, allowing the game state or level layout to be persisted.
 */
namespace ActorSerializer {

  /**
   * @brief Save a list of actors to a file.
   *
   * @details
   * Serializes the given actors and writes them to the specified file
   * in a format understood by the loading function.
   *
   * @param filename Path to the file where actors will be saved.
   * @param actors List of actors to serialize.
   * @return True on success, false if saving fails.
   */
  bool
    saveActorsToFile(
      const std::string& filename,
      const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors
    );

  /**
   * @brief Load a list of actors from a file.
   *
   * @details
   * Reads actor data from the specified file and populates the actors
   * vector. Existing contents of the vector may be replaced.
   *
   * @param filename Path to the file to load from.
   * @param actors Output vector to store the loaded actors.
   * @return True on success, false if loading fails.
   */
  bool
    loadActorsFromFile(
      const std::string& filename,
      std::vector<EngineUtilities::TSharedPointer<Actor>>& actors
    );
}