#pragma once

class Camera
{
public:
	Camera();
	void SetCenter(int x, int y);
	void CheckMouse();
	float x;
	float z;
	float pitch;
	float heading;
	int m_cx,m_cy;
	float dirx, diry, dirz;
	float dirLx, dirLy, dirLz;

protected:
private:
};