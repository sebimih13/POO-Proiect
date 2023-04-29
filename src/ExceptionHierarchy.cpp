#include "ExceptionHierarchy.h"

LoadFileError::LoadFileError(const std::string& msg)
	: GameError("Error Can't Load File : " + msg)
{

}

TextureError::TextureError(const std::string& msg)
	: LoadFileError("Texture : " + msg)
{

}

FontError::FontError(const std::string& msg)
	: LoadFileError("Font : " + msg)
{

}

