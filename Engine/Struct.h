#pragma once

struct Vec2
{
	float x;
	float y;

	Vec2() : x(0), y(0)
	{
	}

	Vec2(float x, float y) : x(x), y(y)
	{
	}

	Vec2 operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2& operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2 operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2& operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	template <typename T>
	Vec2 operator*(const T& num) const
	{
		return Vec2(x * num, y * num);
	}

	template <typename T>
	Vec2& operator*=(const T& num)
	{
		x *= num;
		y *= num;

		return *this;
	}

	template <typename T>
	Vec2 operator/(const T& num) const
	{
		assert(0 != num && "Vector cannot divide by 0");
		return Vec2(x / num, y / num);
	}

	template <typename T>
	Vec2& operator/=(const T& num)
	{
		assert(0 != num && "Vector cannot divide by 0");
		x /= num;
		y /= num;

		return *this;
	}

	float Magnitude() const
	{
		return sqrtf(x * x + y * y);
	}

	// �Ÿ�����(��Ÿ���)�� ��Ʈ������ ������ ���� �ð��� �䱸�ϱ� ������
	// �Ÿ��� ���̸� ���ϰ� ���� ��� ��Ʈ������ ���� ���� ������ �������� ��
	float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	float Length() const
	{
		return Magnitude();
	}

	// ����ȭ(ǥ��ȭ) : ���̰� 1�� ����(��������)�� ��ȯ
	// ���⼺���Ϳ� ���� ���̰� 1�� ���Ͱ� �ʿ��� ��� ��ȯ
	void Normalize()
	{
		if (SqrMagnitude() == 0)
		{
			x = 0;
			y = 0;
		}
		else
		{
			float length = Length();
			x = x / length;
			y = y / length;
		}
	}

	// �������͸� ��ȯ
	Vec2 Normalized() const
	{
		if (SqrMagnitude() == 0)
		{
			return Vec2(0, 0);
		}
		else
		{
			float length = Length();
			return Vec2(x / length, y / length);
		}
	}
};