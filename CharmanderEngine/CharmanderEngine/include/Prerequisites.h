#pragma once

//Librer�as STD - Est�ndar
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
#include <Memory\TsharedPointer.h>
#include <Memory\TWeakPointer.h>
#include <Memory\TStaticPtr.h>
#include <Memory\TUniquePtr.h>
#include "Utilities/CVector2.h"

//Imgui - Interfaz de usuario
#include <imgui.h>
#include <imgui-SFML.h>

// MACRO for safe release of resources
/**
 * @def SAFE_PTR_RELEASE(x)
 * @brief Safely releases a pointer and sets it to nullptr.
 * This macro checks if the pointer @p x is not nullptr, deletes it, and then sets it to nullptr.
 * It is useful for preventing memory leaks and dangling pointers.
 *
 * @param x Pointer to be safely released.
 */
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

 /**
  * @def MESSAGE(classObj, method, state)
  * @brief Logs a resource creation message to the standard error stream.
  * This macro constructs and outputs a message indicating the creation of a resource,
  * including the class, method, and state information.
  *
  * @param classObj Name of the class where the message originates.
  * @param method Name of the method where the message originates.
  * @param state State or description of the resource creation.
  */
#define MESSAGE(classObj, method, state)                      \
{                                                             \
  std::ostringstream os_;                                   \
  os_ << classObj << "::" << method << " : "                \
      << "[CREATION OF RESOURCE" << ": " << state "] \n";\
  std::cerr << os_.str();                                   \
}

  /**
   * @def ERROR(classObj, method, errorMSG)
   * @brief Logs an error message and terminates the program.
   * This macro constructs and outputs an error message to the standard error stream,
   * including the class, method, and error message. The program then exits with code 1.
   *
   * @param classObj Name of the class where the error occurred.
   * @param method Name of the method where the error occurred.
   * @param errorMSG Description of the error.
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
   * @brief Enumerates the different types of shapes supported by the application.
   * This enumeration defines the available shape types that can be used within the system.
   * Each value corresponds to a specific geometric shape.
   */
enum
  ShapeType
{
  EMPTY = 0,     /**< No shape or uninitialized state. */
  CIRCLE = 1,    /**< Circle shape. */
  RECTANGLE = 2, /**< Rectangle shape. */
  TRIANGLE = 3,  /**< Triangle shape. */
  POLYGON = 4    /**< Polygon shape. */
};

enum
  ConsolErrorType
{
  INFO = 0,      /**< Informational message. */
  WARNING = 1,   /**< Warning message indicating a potential issue. */
  ERROR = 2,     /**< Error message indicating a failure or critical issue. */
};