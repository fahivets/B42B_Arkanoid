#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

namespace DISPLAY
{
	namespace WINDOW
	{
		constexpr unsigned int WIDTH{ 800 };
		constexpr unsigned int HEIGTH{ 600 };
	
	}	/*	end namespace Window	*/
	
}	/*	end namespace Display	*/

namespace BALL
{
	constexpr float RADIUS{ 10.0f };
	constexpr float VELOCITY{ 0.5f };

}	/*	end namespace Ball	*/

namespace PADDLE
{
	constexpr float WIDTH{ 60.0f };
	constexpr float HEIGTH{ 20.0f };
	constexpr float VELOCITY{ 0.6f };
} /*	end namespace Paddle	*/

namespace BRICK
{
	constexpr float WIDTH{ 60.0f };
	constexpr float HEIGTH{ 20.0f };
	constexpr int COUNT_X{ 11 };
	constexpr int COUNT_Y{ 4 };

	constexpr float VELOCITY{ 0.0f };
} /*	end namespace Brick*/

#endif
