#pragma once
 
//Librerias STD
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <map>
#include <fstream>
#include <unordered_map>

//Third Parties
#include <SFML/Graphics.hpp>
#include <Memory/TSharedPointer.h>
#include <Memory/TStaticPtr.h>
#include <Memory/TUniquePtr.h>
#include <Memory/TWeakPointer.h>
//Imgui

// MACRO for safe release of resources
/**
* @brief Safely releases a pointer and sets it to nullptr.
*
* This macro checks if the pointer is not null, deletes the object it points to,
* and then sets the pointer to nullptr to avoid dangling pointers.
*
* @param x Pointer to be safely released.
*/
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

/**
* @brief Logs a message indicating the creation of a resource.
*
* This macro generates a formatted message that includes the class name,
* method name, and the state of the resource creation. The message is output
* to the standard error stream.
*
* @param classObj Name of the class where the resource is being created.
* @param method Name of the method where the resource is being created.
* @param state State or status of the resource creation.
*/
#define MESSAGE(classObj, method, state)                      \
{                                                             \
 std::ostringstream os_;                                   \
 os_ << classObj << "::" << method << " : "                \
     << "[CREATION OF RESOURCE" << ": " << state "] \n";\
 std::cerr << os_.str();                                   \
}
/**
* @brief Macro to log an error message and terminate the program.
*
* This macro generates a formatted error message that includes the class name,
* method name, and a detailed error message. The message is output to the
* standard error stream, and the program is terminated with an exit code of 1.
*
* @param classObj Name of the class where the error occurred.
* @param method Name of the method where the error occurred.
* @param errorMSG Detailed error message describing the issue.
*/
#define ERROR(classObj, method, errorMSG)                         \
{                                                                 \
  std::ostringstream os_;                                       \
  os_ << "ERROR : " << classObj << "::" << method << " : "      \
      << "  Error in data from params [" << errorMSG"] \n"; \
  std::cerr << os_.str();                                       \
    exit(1);                                                      \
}

//ENUMS
/**  
* @enum ShapeType  
* @brief Represents different types of shapes.  
*  
* This enumeration defines various shape types that can be used  
* in graphical applications or other contexts where shape  
* categorization is required.  
*/  
enum ShapeType {  
  EMPTY = 0,      /**< Represents an empty or undefined shape. */  
  CIRCLE = 1,     /**< Represents a circular shape. */  
  RECTANGLE = 2,  /**< Represents a rectangular shape. */  
  TRIANGLE = 3,   /**< Represents a triangular shape. */  
  POLYGON = 4,    /**< Represents a polygonal shape. */  
};