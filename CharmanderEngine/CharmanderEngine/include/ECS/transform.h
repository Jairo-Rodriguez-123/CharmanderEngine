#pragma once
#include "Prerequisites.h"
#include "SFML/System/Vector2.hpp"
#include "ECS/Component.h"
#include "../Window.h"
/*
  *  @brief Encapsulates an SFML RenderWindow for rendering and window management. It is a forward declaration to avoid circular dependencies.
*/
class
  Window;

/*
  *  @class Transform
  *  @brief Transform component for position, rotation, and scale in ECS.
  *
  *  The Transform class is a component used in the Entity Component System (ECS) architecture
  *  to manage the spatial properties of an entity, including its position, rotation, and scale.
  *  It provides getter and setter methods for these properties, allowing other systems and components
  *  to query and modify the entity's transform. The class inherits from Component and implements
  *  the required lifecycle methods: start, update, render, and destroy.
  *
  *  @note This component does not perform any rendering itself, but its data can be used by
  *  rendering systems to position and orient entities in the scene.
*/
class
  Transform : public Component {
public:
  /*
    *  @brief Default constructor for Transform.
  */
  //Transform() = default;

  /*
    *  @brief Constructor for Transform.
  */
  Transform() :
    m_position(0.0f, 0.0f),
    m_rotation(0.0f, 0.0f),
    m_scale(1.0f, 1.0f),
    Component(ComponentType::TRANSFORM) {
  }

  /*
    *  @brief Virtual destructor for Transform.
  */
  virtual
    ~Transform() = default;

  //Component
  /**
   * @brief Starts the Transform component.
   *
   * This method is called once when the component is initialized.
   * It can be used to set up any necessary state or resources for the Transform.
   */
  void
    start() override;

  /**
   * @brief Updates the Transform component.
   *
   * @param deltaTime Time elapsed since last update.
   *
   * This method is called every frame to update the state of the Transform.
   * It can be used to apply movement, rotation, or scaling logic based on deltaTime.
   */
  void
    update(float deltaTime) override;

  /**
   * @brief Renders the Transform component.
   *
   * @param window Shared pointer to the Window for rendering.
   *
   * This method is called to render the Transform component.
   * Note: The Transform itself does not render anything, but this method can be used
   * by derived classes or systems that need to visualize the transform.
   */
  void
    render(const EngineUtilities::TSharedPointer<Window>& window) override;

  /**
   * @brief Destroys the Transform component and releases resources.
   *
   * This method is called when the component is being destroyed.
   * It should release any resources or perform cleanup as needed.
   */
  void
    destroy() override;

  // Getters
  /**
   * @brief Gets the position of the Transform.
   * @return The position as sf::Vector2f.
   */
  sf::Vector2f
    getPosition() const { return m_position; }

  /**
   * @brief Gets the rotation of the Transform.
   * @return The rotation as sf::Vector2f.
   */
  sf::Vector2f
    getRotation() const { return m_rotation; }

  /**
   * @brief Gets the scale of the Transform.
   * @return The scale as sf::Vector2f.
   */
  sf::Vector2f
    getScale() const { return m_scale; }

  // Setters
  /**
   * @brief Sets the position of the Transform.
   * @param position The new position as sf::Vector2f.
   */
  void
    setPosition(const sf::Vector2f& position) { m_position = position; }

  /**
   * @brief Sets the rotation of the Transform.
   * @param rotation The new rotation as sf::Vector2f.
   */
  void
    setRotation(const sf::Vector2f& rotation) { m_rotation = rotation; }

  /**
   * @brief Sets the scale of the Transform.
   * @param scale The new scale as sf::Vector2f.
   */
  void
    setScale(const sf::Vector2f& scale) { m_scale = scale; }

  /**
   * @brief Moves the Transform towards a target position using a seek behavior with look-ahead.
   *
   * This method calculates the direction towards the target position, applies a look-ahead distance,
   * and moves the Transform towards the look-ahead target at the specified speed.
   *
   * @param targetPosition The position to seek towards.
   * @param speed The movement speed.
   * @param deltaTime The time elapsed since the last update.
   * @param range The minimum distance to start seeking.
   * @param lookAheadDistance The distance to look ahead in the direction of movement.
   */
  void
    seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range, float lookAheadDistance)
  {
    sf::Vector2f pos = getPosition();
    sf::Vector2f direction = targetPosition - pos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0.0f) {
      direction /= length;
      // Look Ahead: adelanta el objetivo en la direcci?n del movimiento
      sf::Vector2f lookAheadTarget = targetPosition + direction * lookAheadDistance;
      sf::Vector2f desired = lookAheadTarget - pos;
      float desiredLength = std::sqrt(desired.x * desired.x + desired.y * desired.y);
      if (desiredLength > 0.0f) {
        desired /= desiredLength;
      }
      sf::Vector2f velocity = desired * speed * deltaTime;
      setPosition(pos + velocity);
    }
  }

  /*
    void
    seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range) {
      sf::Vector2f direction = targetPosition - m_position;

      float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

      if (length > range) {
        direction /= length;
        m_position += direction * speed * deltaTime;
      }
    }
   */

   /**
    * @brief Gets a pointer to the position data.
    * @return Pointer to the first element of the position vector.
    *
    * This method returns a pointer to the x component of the position vector.
    * Useful for passing the position data to APIs that require a float pointer.
    */
  float*
    getPosData() {
    return &m_position.x; // Retorna un puntero al primer elemento del vector de posici?n
  }

  /**
   * @brief Gets a pointer to the rotation data.
   * @return Pointer to the first element of the rotation vector.
   *
   * This method returns a pointer to the x component of the rotation vector.
   * Useful for passing the rotation data to APIs that require a float pointer.
   */
  float*
    getRotData() {
    return &m_rotation.x; // Retorna un puntero al primer elemento del vector de rotaci?n
  }

  /**
   * @brief Gets a pointer to the scale data.
   * @return Pointer to the first element of the scale vector.
   *
   * This method returns a pointer to the x component of the scale vector.
   * Useful for passing the scale data to APIs that require a float pointer.
   */
  float*
    getScaleData() {
    return &m_scale.x; // Retorna un puntero al primer elemento del vector de escala
  }

private:
  /**
   * @brief Position of the Transform component.
   *
   * Stores the 2D position of the entity in world space.
   */
  sf::Vector2f m_position;
  /**
   * @brief Rotation of the Transform component.
   *
   * Stores the 2D rotation of the entity. Typically, only the x component is used for rotation in 2D.
   */
  sf::Vector2f m_rotation;
  /**
   * @brief Scale of the Transform component.
   *
   * Stores the 2D scale factors of the entity.
   */
  sf::Vector2f m_scale;
};