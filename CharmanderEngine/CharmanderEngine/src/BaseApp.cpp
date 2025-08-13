#include "BaseApp.h"
#include "ResourceManager.h"

BaseApp::~BaseApp() {
}

int
BaseApp::run() {
	if (!init()) {
		ERROR("BaseApp",
			"run",
			"Initializes result on a false statemente, check method validations");
	}

	while (m_windowPtr->isOpen()) {
		m_windowPtr->handleEvents(m_engineGUI);
		update();
		render();
	}

	destroy();
	return 0;
}

bool
BaseApp::init() {
	ResourceManager& resourceMan = ResourceManager::getInstance();


	m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Labrid Engine");
	if (!m_windowPtr) {
		ERROR("BaseApp",
			"init",
			"Failed to create window pointer, check memory allocation");
		return false;
	}

	// Initialize ImGui
	m_engineGUI.init(m_windowPtr);

	// Create Circle Actor
	m_ACirlce = EngineUtilities::MakeShared<Actor>("Circle Actor");
	if (m_ACirlce) {
		m_ACirlce->getComponent<CShape>()->createShape(CIRCLE);
		m_ACirlce->getComponent<CShape>()->setFillColor(sf::Color::White);
		m_ACirlce->getComponent<Transform>()->setPosition(sf::Vector2f(200.f, 150.f));
		m_ACirlce->getComponent<Transform>()->setScale(sf::Vector2f(2.f, 2.f));

		// Cargar la textura para el actor 
		if (!resourceMan.loadTexture("Sprites/Mushroom", "png")) {
			MESSAGE("BaseApp", "Init", "Can't load the texture")
		}
		m_ACirlce->setTexture(resourceMan.getTexture("Sprites/Mushroom"));

		// Add Actor to the list of actors
		m_actors.push_back(m_ACirlce);
	}
	else {
		ERROR("BaseApp",
			"init",
			"Failed to create Circle Actor, check memory allocation");
		return false;
	}
	return true;
}

void
BaseApp::update() {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->update();
	}

	// Update ImGui
	m_engineGUI.update(m_windowPtr, m_windowPtr->deltaTime);
	m_engineGUI.outliner(m_actors);
	m_engineGUI.inspector(m_actors);
	ImGui::ShowDemoWindow();
	// Update actors
	if (!m_ACirlce.isNull()) {
		m_ACirlce->update(m_windowPtr->deltaTime.asSeconds());

		// Posicion del destino (Punto recorrido)
		sf::Vector2f targetPos(1200.f, 150.f);

		// Llamar al seek del Transform
		//m_ACirlce->getComponent<Transform>()->seek(targetPos, 200.0f, m_windowPtr->deltaTime.asSeconds(), 10.0f);
	}
}

void
BaseApp::render() {
	if (!BaseApp::m_windowPtr) {
		return;
	}

	BaseApp::m_windowPtr->clear();

	if (!m_ACirlce.isNull()) {
		m_ACirlce->getComponent<CShape>()->render(m_windowPtr);
	}
	m_windowPtr->render();

	// Render Imgui
	m_engineGUI.render(m_windowPtr);

	m_windowPtr->display();
}

void
BaseApp::destroy() {

	// Destroy ImGui
	m_engineGUI.destroy();


	//m_shapePtr.reset();
	//m_window->destroy();
}