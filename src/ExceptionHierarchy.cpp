#include "ExceptionHierarchy.h"

LoadFileError::LoadFileError(std::string msg)
	: GameError("Error Can't Load File : " + msg)
{

}

TextureError::TextureError(std::string msg)
	: LoadFileError("Texture : " + msg)
{

}

FontError::FontError(std::string msg)
	: LoadFileError("Font : " + msg)
{

}

