#include "stdafx.h"
#include "ResourceHolder.h"

ResourceHolder& ResourceHolder::get()
{
	static ResourceHolder INSTANCE;
	return (INSTANCE);
}

ResourceHolder::ResourceHolder()
	: textures("resource/textures/")
	, fonts("fonts", "ttf")
	, audio("audio", "wav")
{
}