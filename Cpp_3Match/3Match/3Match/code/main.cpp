#include <GSgame.h>
#include "renderer\Renderer.h"

#include "data\DataManager.h"
#include "data\define\TextureLoadDesc.h"
#include "play\Play.h"
class MyGame : public gslib::Game
{
public:
	MyGame()
		:Game(500, 600, false)
	{
	}
private:
	virtual void start() override
	{
		DataManager::load(TextureLoadDesc(TEXTURE_ID::RED, "red"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::BLUE, "blue"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::GREEN, "green"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::PURPLE, "purple"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::YELLOW, "yellow"));
	}

	// çXêV
	virtual void update(float deltaTime) override
	{
		m_play.update(deltaTime);
	}
	// ï`âÊ
	virtual void draw() override
	{
		m_play.draw(m_renderer);
	}
	// èIóπ
	virtual void end() override
	{
		DataManager::release();
	}
private:
	Renderer m_renderer;
	Play m_play;
};

int main()
{
	return MyGame().run();
}
