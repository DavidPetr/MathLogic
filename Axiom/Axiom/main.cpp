#include <iostream>
#include <map>
#include <string>
#include <utility>

using axiomMap = std::map<int, int>;

void print(const axiomMap& map)
{
	for (auto inst : map)
	{
		std::cout << inst.second << " ";
	}
	std::cout << "\n";
}

int mapGenerator(axiomMap& map, int& index)
{
	if (map[index] < 2)
	{
		++map[index];
	}
	else
	{
		while (map[index] == 2)
		{
			if (index == map.size()-1)
			{
				//std::cout << "Error \n";
				return 1;
			}
			map[index] = 0;
			++index;
		}
		++map[index];
		index = 0;
	}
	return 0;
}

int implication(const axiomMap& map, int a, int b)
{
	return map.at(b * 3 + a);
}
int opp(int a, const axiomMap& oppMap)
{
	int values[3];
	int i = 0;
	for (auto val : oppMap)
	{
		values[i++] = val.second;
	}
	return values[a];
}

bool axiom1(const axiomMap& map, int coef1, int coef2)
{
	bool good = false;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int b = implication(map, j, i);
			int a = implication(map, i, b);
			if (a == coef1 || a == coef2)
			{
				//std::cout << "i= " << i << " j= " << j << " a= " << a << " b= " << b << std::endl;
				good = true;
			}
			else
			{
				return false;
			}
		}
	}
	return good;
}
bool axiom2(const axiomMap& map, int coef1, int coef2)
{
	bool good = false;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				int a = implication(map, i, j);
				int b = implication(map, j, k);
				int c = implication(map, i, b);
				int d = implication(map, i, k);
				int e = implication(map, c, d);
				int f = implication(map, a, e);
				if (f == coef1 || f == coef2)
				{
					//std::cout << "i= " << i << " j= " << j << " k= " << k << std::endl;
					good = true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return good;
}
bool axiom3(const axiomMap& map, const axiomMap& oppMap, int coef1)
{
	bool bad = false;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int a = implication(map, opp(i, oppMap), j);
			int b = implication(map, opp(i, oppMap), opp(j, oppMap));
			int c = implication(map, b, i);
			int d = implication(map, a, c);
			if (d== coef1)
			{
				//std::cout << "i= " << i << " j= " << j << " a= " << a << " b= " << b << " c= " << c << " d= " << d << std::endl;
				bad = true;
			}
			else
			{
				return false;
			}
		}
	}
	return bad;
}
bool mp(const axiomMap& map, int coef1, int coef2)
{
	bool good = false;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if ((i == coef1 && implication(map, i, j) == coef1 && j== coef1) || (i == coef2 && implication(map, i, j) == coef2 && j == coef2))
			{
				good = true;
			}
			else
			{
				return false;
			}
		}
	}
	return good;
}

int main()
{
	axiomMap initMap
	{
		{ 0,0 },
		{ 1,0 },
		{ 2,0 },
		{ 3,0 },
		{ 4,0 },
		{ 5,0 },
		{ 6,0 },
		{ 7,0 },
		{ 8,0 }
	};

	axiomMap map{ initMap };
	axiomMap oppMap
	{
		{0,0},
		{1,0},
		{2,0}
	};

	int count=10, count1 = 0, count2 = 0, count3 = 0;
	int index1 = 0, index2 = 0;
	while (mapGenerator(oppMap,index1) == 0)
	{
		++count1;
		for (int i = 0; i < 3; ++i)
		{
			++count2;
			index2 = 0;
			while (mapGenerator(map, index2) == 0)
			{
				++count3;
				if (axiom1(map, (4 + i) % 3, (5 + i) % 3) && axiom2(map, (4 + i) % 3, (5 + i) % 3) && mp(map, (4 + i) % 3, (5 + i) % 3) && axiom3(map,oppMap, i))
				{
					print(map);
					std::cout<<"i= " << i << std::endl;
					print(oppMap);
				}
			}
			map = initMap;
		}
	}
	std::cout << count1 << " " << count2 << " " << count3 << " End\n";
	getchar();
	getchar();
	return 0;
}
/*
std::make_pair(0,0)
std::make_pair(1,0)
std::make_pair(2,0)
std::make_pair(0,1)
std::make_pair(1,1)
std::make_pair(2,1)
std::make_pair(0,2)
std::make_pair(1,2)
std::make_pair(2,2)

std::make_pair(index % 3, index / 3)
*/