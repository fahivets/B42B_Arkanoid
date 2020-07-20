#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include "utility/NonCopyable.h"
#include "utility/NonMovable.h"

using SDLFontUPtr = std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>>;

class FontManager : public NonCopyable, public NonMovable
{
public:
	// Constructors/Destructors
	FontManager() = delete;
	FontManager(const std::string& folder, const std::string& extention);
	~FontManager();

	// Functions
	bool isExists(const std::string& name) const;
	void set(const std::string& name, const int& fontSize);
	TTF_Font* get(const std::string& name) const;
	void init();

private:
	// Private functions
	SDLFontUPtr loadFont(const std::string& path, const int& fontSize);
	std::string getFullFileName(const std::string& name);

private:
	//	bool m_status{ false };
	const std::string m_folder;
	const std::string m_extention;
	std::unordered_map<std::string, SDLFontUPtr> m_fontMap;
};

#endif