#pragma once  
#include "Prerequisites.h"  
#include "Window.h"  

/**  
* @class BaseApp  
* @brief Represents the base application class responsible for managing the main application lifecycle.  
*/  
class BaseApp {  
public:  
   /**  
    * @brief Default constructor for BaseApp.  
    */  
    BaseApp() = default;  

   /**  
    * @brief Destructor for BaseApp.  
    */  
    ~BaseApp();  

   /**  
    * @brief Executes the application.  
    *  
    * This function is intended to be called from the main function to start the application.  
    * @return int Exit code of the application.  
    */  
    int run();  

   /**  
    * @brief Initializes the application.  
    *  
    * This function sets up all necessary resources and configurations for the application.  
    * @return bool True if initialization is successful, false otherwise.  
    */  
    bool init();  

   /**  
    * @brief Updates the application state.  
    *  
    * This function is called once per frame to update the application logic.  
    */  
    void update();  

   /**  
    * @brief Renders the application.  
    *  
    * This function is responsible for drawing all graphical elements on the screen.  
    */  
    void render();  

   /**  
    * @brief Destroys the application.  
    *  
    * This function releases all resources and performs cleanup operations.  
    */  
    void destroy();  

private:  
   /**  
    * @brief Pointer to the main application window.  
    */  
    Window* m_window;  

   /**  
    * @brief Pointer to a circle shape used for rendering.  
    */  
    sf::CircleShape* m_circle;  
};
