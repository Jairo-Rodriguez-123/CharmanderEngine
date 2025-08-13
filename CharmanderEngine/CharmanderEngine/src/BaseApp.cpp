#include "BaseApp.h"
#include "ResourceManager.h"
#include "ActorPicker.h"
#include "ActorSerializer.h"
#include "Circuits/Circuit1.h"

BaseApp::~BaseApp() {}

int
BaseApp::run() {
  if (!init()) { ERROR("BaseApp", "run", "Initialization failed."); }
  while (m_windowPtr->isOpen()) {
    m_windowPtr->handleEvents(m_engineGUI);
    ImGui::SFML::Update(*m_windowPtr->m_windowPtr, m_windowPtr->deltaTime);
    update();
    render();
  }
  destroy();
  return 0;
}

bool
BaseApp::init() {
  ResourceManager& resourceMan = ResourceManager::getInstance();

  m_windowPtr =
    EngineUtilities::MakeShared<Window>(1920, 1080, "VektorCoreEngine");
  if (m_windowPtr.isNull()) {
    ERROR("BaseApp", "init", "Failed to create window pointer.");
    return false;
  }

  m_engineGUI.init(m_windowPtr);

  /* Track */
  m_ATrack = EngineUtilities::MakeShared<Actor>("Track Actor");
  if (m_ATrack) {
    m_ATrack->getComponent<CShape>()->createShape(RECTANGLE);
    m_ATrack->getComponent<CShape>()->setFillColor(sf::Color::White);
    m_ATrack->getComponent<Transform>()
      ->setPosition(sf::Vector2f(450.f, 0.f));
    m_ATrack->getComponent<Transform>()
      ->setScale(sf::Vector2f(10.f, 19.5f));
    if (!resourceMan.loadTexture("sprites/Track", "png")) {
      MESSAGE("BaseApp", "Init", "Can't load texture.");
    }
    m_ATrack->setTexture(resourceMan.getTexture("sprites/Track"));
  }

  /* Player */
  m_player = EngineUtilities::MakeShared<A_Player>("Player");
  if (m_player) {
    m_player->getComponent<CShape>()->createShape(CIRCLE);
    m_player->getComponent<CShape>()->setFillColor(sf::Color::Cyan);
    m_player->getComponent<Transform>()
      ->setScale(sf::Vector2f(2.f, 2.f));
    m_player->setPosition(EngineMathLib::CVector2(880.f, 880.f));
    m_player->setControlMode(PlayerControlMode::Direct);
    m_player->setAcceleration(700.f);
    m_player->setFriction(6.f);
    m_player->setMaxSpeed(m_sharedMaxSpeed);
    if (!resourceMan.loadTexture("sprites/mushroom", "png")) {
      MESSAGE("BaseApp", "Init", "Can't load texture.");
    }
    m_player->setTexture(resourceMan.getTexture("sprites/mushroom"));
  }

  /* NPC */
  m_racerNPC = EngineUtilities::MakeShared<A_Racer>("NPC_1");
  if (m_racerNPC) {
    m_racerNPC->getComponent<CShape>()->createShape(CIRCLE);
  }
  if (m_racerNPC) {
    m_racerNPC->getComponent<CShape>()->createShape(CIRCLE);
    m_racerNPC->getComponent<CShape>()->setFillColor(sf::Color::Green);
    m_racerNPC->getComponent<Transform>()
      ->setScale(sf::Vector2f(2.f, 2.f));
    if (!resourceMan.loadTexture("sprites/mushroom", "png")) {
      MESSAGE("BaseApp", "Init", "Can't load texture.");
    }
    m_racerNPC->setTexture(resourceMan.getTexture("sprites/mushroom"));
    m_racerNPC->setSpeed(m_sharedMaxSpeed);
    m_racerNPC->setArriveRadius(40.f);
    m_racerNPC->setMode(SteeringMode::Arrive);
    m_racerNPC->enableSteering(false);
    m_racerNPC->setPosition(EngineMathLib::CVector2(855.f, 855.f));
  }
  m_npcs.clear();
  if (!m_racerNPC.isNull()) m_npcs.push_back(m_racerNPC);

  /* Waypoints */
  m_waypoints = getCircuitWaypoints();

  /* Systems */
  {
    PlayerInputConfig pic;
    pic.player = m_player;
    pic.renderWindow = m_windowPtr->m_windowPtr.get();
    m_playerInputSystem =
      EngineUtilities::MakeUnique<PlayerInputSystem>(pic);
  }
  {
    WaypointFollowConfig wfc;
    wfc.racers = m_npcs;
    wfc.waypoints = &m_waypoints;
    wfc.arriveRadiusForAdvance = 22.f;
    wfc.reactionDelay = 0.5f;
    wfc.waypointNoiseRadius = 6.f;
    wfc.lookAhead = 2;
    wfc.mistakeProb = 0.03f;
    wfc.mistakeCooldown = 2.0f;
    wfc.corridorWidth = 80.f;
    wfc.cornerSlowdownEnabled = true;
    wfc.cornerMinAngleDeg = 25.f;
    wfc.cornerMaxAngleDeg = 95.f;
    wfc.cornerMinFactor = 0.82f;
    m_waypointFollowSystem =
      EngineUtilities::MakeUnique<WaypointFollowSystem>(wfc);
    m_waypointFollowSystem->primeFromPositions();
  }
  {
    SteeringConfig sc; sc.racers = m_npcs; sc.seekRange = 10.f;
    m_steeringSystem = EngineUtilities::MakeUnique<SteeringSystem>(sc);
  }
  {
    RaceConfig rc;
    if (!m_player.isNull())   rc.actors.push_back(m_player);
    for (auto& npc : m_npcs)  rc.actors.push_back(npc);
    rc.waypoints = &m_waypoints;
    rc.checkpointRadius = 12.f;
    m_raceSystem = EngineUtilities::MakeUnique<RaceSystem>(rc);
  }

  /* Menu starts ON; countdown will arm when user presses "Start Race" */
  m_inMenu = true;
  m_menuPage = MenuPage::Main;
  m_raceArmed = false;
  m_raceLive = false;
  m_raceFinished = false;
  m_finalPlace = -1;
  m_npcFinished = false;
  m_colorIdx = 0;
  m_trackIdx = 0;
  applyPlayerColor();

  return true;
}

void
BaseApp::update() {
  if (!m_windowPtr.isNull()) { m_windowPtr->update(); }
  const float dt = m_windowPtr->deltaTime.asSeconds();

  /* === MENU: no race systems while the menu is visible === */
  if (m_inMenu) {
    drawMainMenu();

    /* minimal visuals update */
    if (!m_ATrack.isNull())    m_ATrack->update(dt);
    if (!m_player.isNull())    m_player->update(dt);
    if (!m_racerNPC.isNull())  m_racerNPC->update(dt);

    /* panels kept usable */
    m_engineGUI.menuBar();
    m_engineGUI.hierarchy(actorsVector);
    m_engineGUI.inspector(actorsVector);
    m_engineGUI.console();
    m_engineGUI.fileManagerPanel(actorsVector);

    /* prepare actors list for GUI */
    actorsVector.clear();
    if (!m_ATrack.isNull())    actorsVector.push_back(m_ATrack);
    if (!m_player.isNull())    actorsVector.push_back(m_player);
    if (!m_racerNPC.isNull())  actorsVector.push_back(m_racerNPC);
    return;
  }

  /* === Countdown gate === */
  std::string cdText;
  if (m_raceArmed && !m_raceLive) {
    cdText = m_countdown.tick(dt);
    if (m_countdown.isFinished()) {
      m_raceLive = true;
      m_raceArmed = false;
      if (!m_racerNPC.isNull()) { m_racerNPC->enableSteering(true); }
      if (!m_raceSystem.isNull()) { m_raceSystem->setTimingActive(true); }
    }
  }

  /* enforce speeds */
  if (!m_player.isNull()) {
    float playerMax = m_player->getMaxSpeed();
    if (playerMax <= 0.f) playerMax = m_sharedMaxSpeed;
    m_player->setMaxSpeed(playerMax);
    if (!m_racerNPC.isNull()) {
      float npcMax = playerMax * m_npcSpeedFactor;
      m_racerNPC->setSpeed(npcMax);
    }
  }

  /* systems */
  if (m_raceLive && !m_raceFinished) {
    if (!m_playerInputSystem.isNull())    m_playerInputSystem->update(dt);
    if (!m_waypointFollowSystem.isNull()) m_waypointFollowSystem->update(dt);
    if (!m_steeringSystem.isNull())       m_steeringSystem->update(dt);
  }
  if (!m_raceSystem.isNull())             m_raceSystem->update(dt);

  /* finish logic (player or NPC) */
  if (!m_raceFinished && !m_raceSystem.isNull()) {
    const int playerLapVisible = m_raceSystem->getLapData(0).lap;
    const int npcVirt = m_raceSystem->getNpcLaps(1);
    bool someoneFinished =
      (playerLapVisible >= m_lapsToWin) || (npcVirt >= m_lapsToWin);
    if (someoneFinished) {
      m_raceFinished = true; m_raceLive = false;
      std::vector<int> order = m_raceSystem->getStandings();
      m_finalPlace = -1;
      for (size_t k = 0; k < order.size(); ++k)
        if (order[k] == 0) { m_finalPlace = (int)k + 1; break; }
    }
  }

  /* update actors */
  if (!m_ATrack.isNull())    m_ATrack->update(dt);
  if (!m_player.isNull())    m_player->update(dt);
  if (!m_racerNPC.isNull())  m_racerNPC->update(dt);

  /* actors for GUI */
  actorsVector.clear();
  if (!m_ATrack.isNull())    actorsVector.push_back(m_ATrack);
  if (!m_player.isNull())    actorsVector.push_back(m_player);
  if (!m_racerNPC.isNull())  actorsVector.push_back(m_racerNPC);

  /* Panels */
  m_engineGUI.menuBar();
  m_engineGUI.hierarchy(actorsVector);
  m_engineGUI.inspector(actorsVector);
  m_engineGUI.console();
  m_engineGUI.fileManagerPanel(actorsVector);

  /* Picking */
  if (!ImGui::GetIO().WantCaptureMouse &&
    sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    int pickedIdx =
      ActorPicker::pickActorUnderMouse(m_windowPtr->m_windowPtr.get(),
        actorsVector);
    if (pickedIdx != -1) m_engineGUI.selectedActorIndex = pickedIdx;
  }

  /* Countdown overlay (drawn even if systems are stopped) */
  if (!m_raceLive && !m_raceFinished && m_raceArmed && !cdText.empty()) {
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::SetNextWindowPos(
      ImVec2((float)m_windowPtr->m_windowPtr->getSize().x * 0.5f, 90.f),
      ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("##countdown_overlay", nullptr,
      ImGuiWindowFlags_NoDecoration |
      ImGuiWindowFlags_NoInputs |
      ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SetWindowFontScale(2.2f);
    ImGui::Text("%s", cdText.c_str());
    ImGui::End();
  }

  /* === HUD === */
  if (!m_raceSystem.isNull() && !m_raceFinished) {
    /* standings and player place */
    std::vector<int> order = m_raceSystem->getStandings();
    int playerPlace = -1;
    for (size_t k = 0; k < order.size(); ++k)
      if (order[k] == 0) { playerPlace = (int)k + 1; break; }
    int lapHUD = m_raceSystem->getLapData(0).lap + 1; /* visual 1..N */

    float bestLap = m_raceSystem->getPlayerBestLapTime();
    float currLap = m_raceSystem->getPlayerCurrentLapTime();

    /* left: position badge big number */
    drawPositionBadge(playerPlace);

    /* top-center: LAP X/Y */
    drawLapTopCenter(lapHUD, m_lapsToWin);

    /* top-right: time box (TIME, BEST, CURRENT) */
    drawTimeBoxTopRight(currLap, bestLap);

    /* left vertical cards (rank + name) */
    drawStandingsPortraits(order, 8 /* up to 8 slots */);
  }

  /* Finish overlay */
  if (m_raceFinished) {
    ImGui::SetNextWindowBgAlpha(0.2f);
    ImGui::SetNextWindowPos(
      ImVec2((float)m_windowPtr->m_windowPtr->getSize().x * 0.5f,
        (float)m_windowPtr->m_windowPtr->getSize().y * 0.5f),
      ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("##finish_overlay", nullptr,
      ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SetWindowFontScale(3.0f);
    if (m_finalPlace == 1) ImGui::Text("You win! 1st");
    else if (m_finalPlace > 0)
      ImGui::Text("Finished %d%s", m_finalPlace,
        (m_finalPlace == 2 ? "nd" : (m_finalPlace == 3 ? "rd" : "th")));
    else ImGui::Text("Race finished");
    ImGui::SetWindowFontScale(1.2f);
    ImGui::Spacing();
    if (ImGui::Button("Retry", ImVec2(240.f, 60.f))) {
      resetRace(); m_inMenu = true; m_menuPage = MenuPage::Main;
    }
    ImGui::SameLine();
    if (ImGui::Button("Main Menu", ImVec2(240.f, 60.f))) {
      m_inMenu = true; m_menuPage = MenuPage::Main;
    }
    ImGui::End();
  }
}

void
BaseApp::render() {
  if (m_windowPtr.isNull()) return;
  m_windowPtr->clear();

  if (m_ATrack)    m_ATrack->getComponent<CShape>()->render(m_windowPtr);
  if (m_player)    m_player->getComponent<CShape>()->render(m_windowPtr);
  if (m_racerNPC)  m_racerNPC->getComponent<CShape>()->render(m_windowPtr);

  m_engineGUI.drawSelectedOutline(m_windowPtr->m_windowPtr.get(),
    actorsVector);

  m_windowPtr->render();
  m_engineGUI.render(m_windowPtr);
  m_windowPtr->display();
}

void
BaseApp::destroy() { m_engineGUI.destroy(); }

/* ======================= HUD helpers ======================= */

const char*
BaseApp::nameFromStandingsIndex(int idx) const {
  if (idx == 0) return "Player";
  size_t npcIdx = (idx > 0) ? static_cast<size_t>(idx - 1) : 0;
  if (npcIdx < m_npcs.size() && !m_npcs[npcIdx].isNull())
    return m_npcs[npcIdx]->getName().c_str();
  return "Unknown";
}

std::string
BaseApp::formatTime(float sec) {
  if (sec < 0.f) return std::string("--:--.--");
  int ms = (int)(sec * 1000.f + 0.5f);
  int mm = ms / 60000;
  int ss = (ms / 1000) % 60;
  int cc = (ms % 1000) / 10;
  char b[32];
  std::snprintf(b, sizeof(b), "%02d:%02d.%02d", mm, ss, cc);
  return std::string(b);
}

std::string
BaseApp::ordinalString(int place) {
  if (place <= 0) return std::string("--");
  int mod100 = place % 100;
  int mod10 = place % 10;
  const char* suf = "th";
  if (mod100 < 11 || mod100 > 13) {
    if (mod10 == 1) suf = "st";
    else if (mod10 == 2) suf = "nd";
    else if (mod10 == 3) suf = "rd";
  }
  char b[16];
  std::snprintf(b, sizeof(b), "%d%s", place, suf);
  return std::string(b);
}

void
BaseApp::drawPositionBadge(int place) const {
  ImGui::SetNextWindowBgAlpha(0.20f);
  ImGui::SetNextWindowPos(ImVec2(28.f, 26.f), ImGuiCond_Always);
  ImGui::Begin("##hud_pos_badge", nullptr,
    ImGuiWindowFlags_NoDecoration |
    ImGuiWindowFlags_NoInputs |
    ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::SetWindowFontScale(2.0f);
  std::string ord = ordinalString(place);
  ImGui::Text("%s", ord.c_str());
  ImGui::SetWindowFontScale(1.0f);
  ImGui::End();
}

void
BaseApp::drawLapTopCenter(int lapHUD, int lapsToWin) const {
  ImGui::SetNextWindowBgAlpha(0.25f);
  ImVec2 center((float)m_windowPtr->m_windowPtr->getSize().x * 0.5f, 20.f);
  ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.f));
  ImGui::Begin("##hud_lap_top", nullptr,
    ImGuiWindowFlags_NoDecoration |
    ImGuiWindowFlags_NoInputs |
    ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::SetWindowFontScale(1.4f);
  ImGui::Text("LAP %d/%d", lapHUD, lapsToWin);
  ImGui::SetWindowFontScale(1.0f);
  ImGui::End();
}

void
BaseApp::drawTimeBoxTopRight(float currentLap, float bestLap) const {
  const float w = (float)m_windowPtr->m_windowPtr->getSize().x;
  ImGui::SetNextWindowBgAlpha(0.25f);
  ImGui::SetNextWindowPos(ImVec2(w - 32.f, 26.f), ImGuiCond_Always,
    ImVec2(1.f, 0.f));
  ImGui::Begin("##hud_time_topright", nullptr,
    ImGuiWindowFlags_NoDecoration |
    ImGuiWindowFlags_NoInputs |
    ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::SetWindowFontScale(1.1f);
  ImGui::Text("TIME   %s", formatTime(currentLap).c_str());
  ImGui::Separator();
  ImGui::Text("BEST   %s", formatTime(bestLap).c_str());
  ImGui::Text("CURRENT %s", formatTime(currentLap).c_str());
  ImGui::SetWindowFontScale(1.0f);
  ImGui::End();
}

/* Left-side vertical portraits (blue cards w/ red border + name) */
void
BaseApp::drawStandingsPortraits(const std::vector<int>& order, int slots) const {
  /* layout constants; tweak to taste */
  const float x = 38.f;     /* left margin */
  const float y0 = 120.f;    /* top start   */
  const float w = 132.f;    /* card width  */
  const float h = 132.f;    /* card height */
  const float gap = 36.f;     /* vertical spacing */

  const ImU32 colFill = IM_COL32(20, 60, 240, 255); /* blue   */
  const ImU32 colFrame = IM_COL32(230, 30, 30, 255); /* red    */
  const ImU32 colText = IM_COL32(255, 255, 255, 255);

  ImDrawList* dl = ImGui::GetForegroundDrawList();
  const int count = std::min(slots, (int)order.size());

  for (int i = 0; i < count; ++i) {
    const float y = y0 + i * (h + gap);
    const ImVec2 p0(x, y);
    const ImVec2 p1(x + w, y + h);

    /* card rectangle */
    dl->AddRectFilled(p0, p1, colFill, 10.0f);
    dl->AddRect(p0, p1, colFrame, 10.0f, 0, 6.0f);

    /* rank number (small) */
    char rankTxt[8]; std::snprintf(rankTxt, sizeof(rankTxt), "%d", i + 1);
    dl->AddText(ImVec2(x + 8.f, y + 6.f), colText, rankTxt);

    /* actor name centered inside the card */
    const int idx = order[(size_t)i];
    const char* nm = nameFromStandingsIndex(idx);
    /* approximate center text: place near center-left */
    dl->AddText(ImVec2(x + 18.f, y + h * 0.5f - 8.f), colText, nm);
  }
}

/* ======================= helpers ======================= */

void
BaseApp::resetRace() {
  if (!m_player.isNull())
    m_player->setPosition(EngineMathLib::CVector2(880.f, 880.f));
  if (!m_racerNPC.isNull()) {
    m_racerNPC->setPosition(EngineMathLib::CVector2(855.f, 855.f));
    m_racerNPC->enableSteering(false);
  }

  /* rebuild systems that rely on runtime state */
  {
    WaypointFollowConfig wfc;
    wfc.racers = m_npcs; wfc.waypoints = &m_waypoints;
    wfc.arriveRadiusForAdvance = 22.f; wfc.reactionDelay = 0.14f;
    wfc.waypointNoiseRadius = 6.f; wfc.lookAhead = 1;
    wfc.mistakeProb = 0.03f; wfc.mistakeCooldown = 2.0f;
    wfc.corridorWidth = 80.f; wfc.cornerSlowdownEnabled = true;
    wfc.cornerMinAngleDeg = 25.f; wfc.cornerMaxAngleDeg = 95.f;
    wfc.cornerMinFactor = 0.82f;
    m_waypointFollowSystem =
      EngineUtilities::MakeUnique<WaypointFollowSystem>(wfc);
    m_waypointFollowSystem->primeFromPositions();
  }
  {
    RaceConfig rc;
    rc.actors.clear();
    if (!m_player.isNull())   rc.actors.push_back(m_player);
    for (auto& npc : m_npcs)  rc.actors.push_back(npc);
    rc.waypoints = &m_waypoints; rc.checkpointRadius = 12.f;
    m_raceSystem = EngineUtilities::MakeUnique<RaceSystem>(rc);
  }

  m_countdown = RaceCountdown{ 3.f };
  m_raceArmed = false; /* armed at Start Race */
  m_raceLive = false;
  m_raceFinished = false;
  m_finalPlace = -1;
  m_npcFinished = false;
  if (!m_raceSystem.isNull()) m_raceSystem->setTimingActive(false);
}

/* set player color from selection */
void
BaseApp::applyPlayerColor() {
  if (m_player) {
    auto shp = m_player->getComponent<CShape>();
    if (shp) shp->setFillColor(
      m_colorOptions[std::max(0, std::min(3, m_colorIdx))]);
  }
}

/* start 3..2..1..GO */
void
BaseApp::armAndStartCountdown() {
  m_countdown = RaceCountdown{ 3.f };
  m_countdown.start();
  m_raceArmed = true;
  m_raceLive = false;
  m_raceFinished = false;
  m_finalPlace = -1;
  if (!m_racerNPC.isNull())
    m_racerNPC->enableSteering(false); /* starts after GO */
  if (!m_raceSystem.isNull()) m_raceSystem->setTimingActive(false);
}

/* === ImGui Main Menu === */
void
BaseApp::drawMainMenu() {
  const ImVec2 center(
    (float)m_windowPtr->m_windowPtr->getSize().x * 0.5f,
    (float)m_windowPtr->m_windowPtr->getSize().y * 0.5f);
  ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
  ImGui::Begin("MainMenu", nullptr,
    ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);

  ImGui::SetWindowFontScale(2.0f);
  ImGui::TextUnformatted("MARIO KART 2D - MENU");
  ImGui::SetWindowFontScale(1.0f);
  ImGui::Separator();

  if (m_menuPage == MenuPage::Main) {
    if (ImGui::Button("Play", ImVec2(280, 40)))
      m_menuPage = MenuPage::PlayerColor;
    if (ImGui::Button("Track", ImVec2(280, 40)))
      m_menuPage = MenuPage::Track;
    if (ImGui::Button("Settings", ImVec2(280, 40)))
      m_menuPage = MenuPage::Settings;
    if (ImGui::Button("Exit", ImVec2(280, 40)))
      m_windowPtr->m_windowPtr->close();
  }
  else if (m_menuPage == MenuPage::PlayerColor) {
    ImGui::TextUnformatted("Choose your color:");
    const char* labels[4] = { "Cyan", "Red", "Yellow", "Magenta" };
    for (int i = 0; i < 4; ++i) {
      if (ImGui::RadioButton(labels[i], m_colorIdx == i)) m_colorIdx = i;
    }
    ImGui::Spacing();
    if (ImGui::Button("Back", ImVec2(130, 36))) {
      m_menuPage = MenuPage::Main; applyPlayerColor();
    }
    ImGui::SameLine();
    if (ImGui::Button("Start Race", ImVec2(130, 36))) {
      applyPlayerColor();
      m_inMenu = false;
      armAndStartCountdown();
    }
  }
  else if (m_menuPage == MenuPage::Track) {
    ImGui::TextUnformatted("Select track:");
    ImGui::RadioButton("Circuit 1 (default)", &m_trackIdx, 0); /* single */
    ImGui::Spacing();
    if (ImGui::Button("Back", ImVec2(130, 36)))
      m_menuPage = MenuPage::Main;
  }
  else if (m_menuPage == MenuPage::Settings) {
    static float dummyVol = 0.7f, dummyFx = 0.6f;
    ImGui::SliderFloat("Music", &dummyVol, 0.f, 1.f);
    ImGui::SliderFloat("SFX", &dummyFx, 0.f, 1.f);
    ImGui::TextDisabled("Decorative for now.");
    ImGui::Spacing();
    if (ImGui::Button("Back", ImVec2(130, 36)))
      m_menuPage = MenuPage::Main;
  }

  ImGui::End();
}