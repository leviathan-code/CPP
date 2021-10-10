#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct Vertex {
	bool visited;
	int weight;
	vector <pair<int, int>>neighbor;//пара:№ соседа - стоимость ребра в него
};

typedef vector <Vertex> Graph;
Graph graph;

void Deikstra(int v1) {
	set < pair<int, int>>s;

	s.insert(make_pair(0, v1));
	while (!s.empty())
	{
		pair<int, int>p = *(s.begin());
		s.erase(s.begin());
		if (graph[p.second].visited == 1)//если уже вершина обработана
			continue;
		graph[p.second].visited = 1;
		graph[p.second].weight = p.first;

		for (auto it = graph[p.second].neighbor.begin(); it != graph[p.second].neighbor.end(); it++) {
			if (graph[it->first].visited == 0)
				s.insert(make_pair(graph[p.second].weight + (it->second),(it->first)));
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	cin >> n;

	graph.resize(n);

	for (int i = 0; i < graph.size(); i++)
		graph[i].visited = 0;
	int m;
	cin >> m;

	int sum = 0;
	for (int i = 0; i < m; i++) {
		int a, b, w;
		cout << "vvedy nach i konec rebra" << endl;
		cin >> a >> b;
		cout << "weight" << endl;
		cin >> w;
		sum += w;
		graph[a - 1].neighbor.push_back(make_pair(b - 1, w));
		graph[a - 1].neighbor.push_back(make_pair(b - 1, w));
	}

	for (int i = 0; i < n; i++)
		graph[i].weight = sum += 1;
	cout << "vvedy vershinu istochnica";
	int v;
	cin >> v;
	Deikstra(v - 1);
	for (int i = 0; i < graph.size(); i++)
		if (graph[i].weight != sum + 1)
			cout << "stoimost puty" << i + 1 << "= " << graph[i].weight << endl;
		else cout << "no way" << endl;
	system("pause");
	return 0;
}
