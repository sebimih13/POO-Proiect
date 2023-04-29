#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

class GameError : public std::runtime_error
{
	using std::runtime_error::runtime_error;
};

class LoadFileError : public GameError
{
public:
	explicit LoadFileError(std::string msg);
};

class TextureError : public LoadFileError
{
public:
	explicit TextureError(std::string msg);
};

class FontError : public LoadFileError
{
public:
	explicit FontError(std::string msg);
};

