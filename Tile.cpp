#include "Tile.h"
#include <sstream>
#include <map>
#include "SDLUtils.h"
#include "Render.h"
#include "Font.h"

// [TODO] fix text sizes

struct TileStyle
{
	SDL_Color bgColor;
	SDL_Color fgColor;
	Font *font;
};

static std::map<int, TileStyle> tileStyleMap;
static TileStyle superTileStyle;

static SDL_Color tileColor = { 0xEE, 0xE4, 0xDA, 0xFF };
static SDL_Color tileGoldColor = { 0xED, 0xC2, 0x2E, 0xFF };

static SDL_Color specialColors[] =
{
	{ 0xF7, 0x8E, 0x48, 0xFF }, // 8
	{ 0xFC, 0x5E, 0x2E, 0xFF }, // 16
	{ 0xFF, 0x33, 0x33, 0xFF }, // 32
	{ 0xFF, 0x00, 0x00, 0xFF }, // 64
};

static SDL_Color textColor = { 0x77, 0x6E, 0x65, 0xFF };
static SDL_Color brightTextColor = { 0xF9, 0xF6, 0xF2, 0xFF };

static Font numFontLarge;
static Font numFontMedium;
static Font numFontSmall;
static Font numFontXSmall;

static void BuildTileStyles()
{
	int power = 2;
	int exponent = 1;
	int limit = 11;

	while(exponent <= limit) {
		TileStyle style;
		double goldRatio = (exponent - 1.0) / (limit - 1.0);
		style.bgColor = Color_Mix(tileGoldColor, tileColor, goldRatio);

		if(power >= 8 && power <= 64) {
			SDL_Color &specialColor = specialColors[exponent - 3];
			style.bgColor = Color_Mix(specialColor, style.bgColor, 0.55);
		}

		style.fgColor = (power >= 8) ? brightTextColor : textColor;

		style.font = &numFontLarge;
		if(power >= 100 && power < 1000)
			style.font = &numFontMedium;
		else if(power >= 1000)
			style.font = &numFontSmall;

		tileStyleMap[power] = style;

		exponent++;
		power *= 2;
	}

	SDL_Color c = { 0x33, 0x33, 0x33, 0xFF };
	superTileStyle.bgColor = Color_Mix(c, tileGoldColor, 0.95);
	superTileStyle.fgColor = brightTextColor;
	superTileStyle.font = &numFontXSmall;
}

void Tile_LoadMetaData()
{
	const char *fontPath = "ClearSans-Bold.ttf";
	numFontLarge.init(fontPath, 55);
	numFontMedium.init(fontPath, 45);
	numFontSmall.init(fontPath, 35);
	numFontXSmall.init(fontPath, 30);

	BuildTileStyles();
}

void Tile_UnloadMetaData()
{
	numFontLarge.free();
	numFontMedium.free();
	numFontSmall.free();
	numFontXSmall.free();
}

//////////////////////////////////////////////////////////////////////

int tileSize = 100;
int gridSpacing = 15;

void calculatePosition(int row, int col, int *pX, int *pY)
{
	*pX = col * (tileSize + gridSpacing);
	*pY = row * (tileSize + gridSpacing);
}

Tile::Tile(int row, int col, int value)
{
	std::stringstream buf;
	Texture numTexture;
	buf << value;
	numTexture.loadFromLatinText(&numFontLarge, buf.str().c_str(), tileStyleMap[value].fgColor);

	m_texture.createBlank(tileSize, tileSize, SDL_TEXTUREACCESS_TARGET);
	m_texture.enableAlpha();
	g_render.setTarget(m_texture.sdl_texture());
	g_render.setDrawColor(tileStyleMap[value].bgColor);
	g_render.clear();
	numTexture.render((tileSize - numTexture.width()) / 2, (tileSize - numTexture.height()) / 2);
	g_render.setTarget(NULL);

	m_row = row;
	m_col = col;
	calculatePosition(row, col, &m_x, &m_y);

	m_opacity = 1.0;
	m_scale = 1.0;
}

void Tile::render()
{
	m_texture.setAlpha(static_cast<Uint8>(255 * m_opacity));
	m_texture.renderScaled(m_x, m_y, m_scale);
}

void Tile::setProperty(int propertyID, double value)
{
	switch(propertyID) {
	case 1:
		m_x = static_cast<int>(value);
		break;
	case 2:
		m_y = static_cast<int>(value);
		break;
	case 3:
		m_opacity = value;
		break;
	case 4:
		// [TODO] consider using texture redraw to implement tile scaling
		m_scale = value;
		calculatePosition(m_row, m_col, &m_x, &m_y);
		m_x -= tileSize * (m_scale - 1) / 2;
		m_y -= tileSize * (m_scale - 1) / 2;
	}
}

void Tile::update(int delta_ms)
{
	if(m_animationExecutor) {
		m_animationExecutor->progress(delta_ms);
	}
}

void Tile::attachAnimation(std::shared_ptr<Animation> animation)
{
	m_animationExecutor = std::make_shared<AnimationExecutor>(animation, this);
	m_animationExecutor->init();
}
