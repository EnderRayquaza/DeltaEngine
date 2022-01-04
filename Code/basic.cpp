#include "basic.hpp"

namespace DeltaEngine
{
	bool Id::isEgal(Id const rhs) const noexcept
	{
		return intKey == rhs.intKey && strKey == rhs.strKey;
	}

	bool operator==(Id const lhs, Id const rhs)
	{
		return lhs.isEgal(rhs);
	}

	bool operator!=(Id const lhs, Id const rhs)
	{
		return !(lhs == rhs);
	}

	AABB findAABBfromShape(const Shape& shape)
	{
		int xmin{ INFINITY }, xmax{ 0 }, ymin{ INFINITY }, ymax{ 0 };
		for (auto& vtx : shape.vertices)
		{
			if (vtx.x < xmin) xmin = vtx.x;
			if (vtx.x > xmax) xmax = vtx.x;
			if (vtx.y < ymin) ymin = vtx.y;
			if (vtx.y > ymax) ymax = vtx.y;
		}
		return { xmin, ymin, xmax, ymax };
	}

	json returnJson(std::string const jsonPath)
	{
		std::ifstream file(jsonPath); //Opens the file.
		if (!file) //Returns an error if it can't.
			std::cout << "Erreur : File not open (" << jsonPath << ")" << std::endl;
		json j{}; //Creates a json variable.
		file >> j; //Puts the data from the file in the json var.
		return j; //Returns it.
	}

	float area(const Shape& shape)
	{
		const size_t n{ shape.vertices.size() };
		std::vector<float> DX{}, DY{};
		float A{ 0 };
		for (size_t i{ 0 }; i < n; i++)
		{
			DX.push_back((shape.vertices[(i + 1) % n].x - shape.vertices[(i + n - 1) % n].x) / 2);
			DY.push_back((shape.vertices[(i + 1) % n].y - shape.vertices[(i + n - 1) % n].y) / 2);
		}
		for (size_t i{ 0 }; i < n; i++)
		{
			A += shape.vertices[i].x * DY[i] - shape.vertices[i].y * DX[i];
		}
		return fabs(A / 2.f);
	}

	Id createId(std::vector<Id> list)
	{
		Id id{};
		do
		{
			id = Id{ rand(), std::to_string(rand()) };
		} while (inVector(list, id));
		return id;
	}

	template <typename T>
	bool inVector(std::vector<T> vec, T& item)
	{
		return std::find(vec.begin(), vec.end(), item) != std::end;
	}

	template <typename T>
	sf::Vector2<T> operator*(sf::Vector2<T>& lhs, int rhs)
	{
		sf::Vector2<T> vec{};
		vec.x = lhs.x * rhs;
		vec.y = lhs.y * rhs;
		return vec;
	}
	template <typename T>
	sf::Vector2<T> operator*(int lhs, sf::Vector2<T>& rhs)
	{
		return rhs * lhs;
	}

	Identifiable::Identifiable():m_id(createId(listId))
	{}

	Id Identifiable::get_id() const noexcept
	{
		return m_id;
	}
}