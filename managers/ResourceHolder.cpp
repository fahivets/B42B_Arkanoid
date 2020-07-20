#include "stdafx.h"
#include "ResourceHolder.h"

ResourceHolder& ResourceHolder::get()
{
	static ResourceHolder INSTANCE;
	return (INSTANCE);
}

ResourceHolder::ResourceHolder()
	: textures("textures", "png")
	, fonts("fonts", "ttf")
	, audio("audio", "wav")
{}