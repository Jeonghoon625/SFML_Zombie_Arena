#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include <map>

using namespace sf;
using namespace std;

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;
	list<Keyboard::Key> positiveKeys;
	list<Keyboard::Key> negativeKeys;

	float sensi;
	float limit;
	float value; // -1.0 ~ 1.0
};

class InputMgr
{
private:
	static map<Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key> downKeys;
	static list<Keyboard::Key> ingKeys;
	static list<Keyboard::Key> upKeys;


public:
	static void Init();

	static void ClearInput();
	static void ProcessInput(const Event& event);
	static void Update(float dt);

	static float GetAxis(Axis axis);	// -1.0 ~ 1.0

	static int GetAxisRaw(const list<Keyboard::Key>& positive, const list<Keyboard::Key>& negaive);
	static int GetAxisRaw(Axis axis);	// -1, 0, 1

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	static Vector2i GetMousePosition();
};