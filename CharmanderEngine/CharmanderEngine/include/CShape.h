/**  
* @class CShape  
* @brief Represents a graphical shape that can be created, updated, rendered, and manipulated.  
*  
* The CShape class provides functionality to create and manage shapes of different types,  
* set their properties such as position, color, rotation, and scale, and render them on a window.  
*/  
class CShape {  
public:  
 /**  
  * @brief Default constructor for CShape.  
  */  
 CShape() = default;  

 /**  
  * @brief Constructs a CShape with a specified shape type.  
  * @param shapeType The type of shape to initialize.  
  */  
 CShape(ShapeType shapeType) : m_shape(nullptr), m_shapeType(ShapeType::EMPTY) { }  

 /**  
  * @brief Default destructor for CShape.  
  */  
 ~CShape() = default;  

 /**  
  * @brief Creates a shape of the specified type.  
  * @param shapeType The type of shape to create.  
  * @return A pointer to the created shape.  
  */  
 sf::Shape* createShape(ShapeType shapeType);  

 /**  
  * @brief Updates the shape's state.  
  * @param deltaTime The time elapsed since the last update.  
  */  
 void 
   update(float deltaTime);  

 /**  
  * @brief Renders the shape on the specified window.  
  * @param window The window where the shape will be rendered.  
  */  
 void 
   render(Window& window);  

 /**  
  * @brief Sets the position of the shape.  
  * @param x The x-coordinate of the position.  
  * @param y The y-coordinate of the position.  
  */  
void 
setPosition(float x, float y);  

 /**  
  * @brief Sets the position of the shape using a vector.  
  * @param position The position vector.  
  */  
void 
setPosition(const sf::Vector2f& position);  

 /**  
  * @brief Sets the fill color of the shape.  
  * @param color The fill color to apply.  
  */  
void 
setFillColor(const sf::Color& color);  

 /**  
  * @brief Sets the rotation angle of the shape.  
  * @param angle The rotation angle in degrees.  
  */  
void 
setRotation(float angle);  

 /**  
  * @brief Sets the scale of the shape.  
  * @param scl The scale vector to apply.  
  */  
void 
setScale(const sf::Vector2f& scl);  

 /**  
  * @brief Retrieves the shape object.  
  * @return A pointer to the shape.  
  */  
 sf::Shape* getShape() {  
   return m_shape;  
 }  

private:  
 sf::Shape* m_shape; /**< Pointer to the shape object. */  
 ShapeType m_shapeType; /**< The type of the shape. */  
 sf::VertexArray* m_line; /**< Pointer to a vertex array for line representation. */  
};