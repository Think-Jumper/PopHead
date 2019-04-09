#ifndef POPHEAD_INPUT_ACTIONMANAGER_H_
#define POPHEAD_INPUT_ACTIONMANAGER_H_

#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <map>

//#include "Base/gameData.hpp"

namespace PopHead {
    namespace Base{ class GameData; }
namespace Input {

class ActionManager
{
public:
    ActionManager();

    void addAction( const std::string& action, const std::vector<sf::Keyboard::Key>& );
    void addAction( const std::string& action, sf::Keyboard::Key );
    void addKeyToAction( const std::string& toWhichAction, sf::Keyboard::Key );
    void deleteKeyFromAction( const std::string& toWhichAction, sf::Keyboard::Key );
    void clearAction(const std::string& action);

    bool isActionPressed( const std::string& action );
    bool isActionJustPressed( const std::string& action ) const;
    bool isActionJustReleased( const std::string& action ) const;

    void setGameData(Base::GameData* gameData){mGameData = gameData;}

private:
    bool isKeyJust(sf::Event::EventType, sf::Keyboard::Key) const;

private:
    std::map< std::string, std::vector<sf::Keyboard::Key> > mActions;
    Base::GameData* mGameData;
};

}}

#endif // !POPHEAD_INPUT_ACTIONMANAGER_H_
