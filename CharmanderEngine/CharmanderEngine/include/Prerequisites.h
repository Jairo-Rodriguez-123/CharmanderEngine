#pragma once

// ========================
// Standard Libraries
// ========================
#include <iostream>      ///< For standard input/output streams.
#include <string>        ///< For string manipulation.
#include <sstream>       ///< For string stream formatting.
#include <vector>        ///< For dynamic array container.
#include <thread>        ///< For multithreading support.
#include <map>           ///< For ordered key-value container.
#include <fstream>       ///< For file input/output operations.
#include <unordered_map> ///< For hash map container.

// ========================
// Third Party Libraries
// ========================
#include <SFML/Graphics.hpp> 
///< Simple and Fast Multimedia Library for rendering 2D graphics.

#include "Memory/TSharedPointer.h"  ///< Custom shared pointer implementation.
#include "Memory/TWeakPointer.h"    ///< Custom weak pointer implementation.
#include "Memory/TStaticPtr.h"      ///< Custom static pointer implementation.
#include "Memory/TUniquePtr.h"      ///< Custom unique pointer implementation.

// Imgui
#include <imgui.h>
#include <imgui-SFML.h>


// ========================
// Macros
// ========================

/**
 * @brief Safely releases a pointer and sets it to nullptr.
 *
 * Example usage:
 * @code
 * SAFE_PTR_RELEASE(myPointer);
 * @endcode
 */
#define SAFE_PTR_RELEASE(x) \
	if (x != nullptr) { delete x; x = nullptr; }

 /**
	* @brief Outputs a formatted message indicating the state of a
	* resource creation.
	*
	* @param classObj The name of the class.
	* @param method The method where the message is generated.
	* @param state The current state or detail of the resource creation.
	*
	* Example usage:
	* @code
	* MESSAGE("MyClass", "initialize", "Success");
	* @endcode
	*/
#define MESSAGE(classObj, method, state)                        \
{                                                               \
	std::ostringstream os_;                                     \
	os_ << classObj << "::" << method << " : "                  \
		<< "[CREATION OF RESOURCE" << ": " << state << "] \n";  \
	std::cerr << os_.str();                                     \
}

	/**
	 * @brief Outputs a formatted error message and exits the application.
	 *
	 * @param classObj The name of the class.
	 * @param method The method where the error occurred.
	 * @param errorMSG A description of the error.
	 *
	 * Example usage:
	 * @code
	 * ERROR("MyClass", "loadFile", "File not found");
	 * @endcode
	 */
#define ERROR(classObj, method, errorMSG)                          \
{                                                                  \
	std::ostringstream os_;                                        \
	os_ << "ERROR : " << classObj << "::" << method << " : "       \
		<< "  Error in data from params [" << errorMSG << "] \n";  \
	std::cerr << os_.str();                                        \
	exit(1);                                                       \
}

	 // ========================
	 // Enums
	 // ========================

	 /**
		* @enum ShapeType
		* @brief Defines the possible shape types that can be
		* rendered or created in the system.
		*/
enum
	ShapeType {
	EMPTY = 0,     ///< No shape defined.
	CIRCLE = 1,    ///< Circle shape.
	RECTANGLE = 2, ///< Rectangle shape.
	TRIANGLE = 3,  ///< Triangle shape.
	POLYGON = 4    ///< Custom polygon shape.
};