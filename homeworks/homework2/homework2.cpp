#include <iostream>
#include <vector>
#include <fstream>
#include <limits.h> // INT_MAX
#include <set>
using std::vector;
using std::set;

// constants
static const int INPUT_MAX = 2048;
static const char I1 = '!', I2 = '~'; // limitations
static const int MAX_VERTICES = (int)(I2 - I1) + 1;
enum distConstants
{
        TRIVIAL = 0,
        INF = INT_MAX
};

inline bool isCorrect(char c)
{
        return (c >= I1 && c <= I2);
}

inline char map(char c) // mapped values from 0 to MAX_VERTICES
{
        return c - I1;
}

inline char unmap(char c)
{
        return c + I1;
}

struct Edge
{
        char src;
        char dest;
        int weight; // time

        Edge(char _from, char _to, int _weight)
                : src(_from), dest(_to), weight(_weight)
        {
        }

        friend std::ostream& operator<<(std::ostream& os, const Edge& e) // helper
        {
                os << '{' << e.src << "->" << e.dest << ',' << e.weight << '}';
                return os;
        }
};

struct Graph
{
        vector<Edge> edgesList;
        set<char> vertices;

        Graph()
        {
                edgesList.reserve(MAX_VERTICES); // heuristic optimization to avoid copying
        }

        size_t V() const
        {
                return vertices.size();
        }

        size_t E() const
        {
                return edgesList.size();
        }

        void addVertex(char v)
        {
                vertices.insert(v);
        }

        void addEdge(Edge& e)
        {
                edgesList.push_back(e);
        }
};

// globals
static vector<char> necklace1, necklace2;
static Graph g;

void read(std::istream& is);
void Floyd(int **&dist, const int size = MAX_VERTICES);
void solve();
void testPrint();

int main()
{
        char fileName[INPUT_MAX]; // expecting .txt file :)
        std::cin >> fileName;
        std::ifstream is;
        is.open(fileName, std::ios::in);
        if (!is)
                throw std::runtime_error("Could not open file.\n");
        read(is);
        is.close();

        if (necklace1.size() != necklace2.size()) {
                std::cout << -1 << std::endl << "Not possible" << std::endl;
                return 0;
        }
        else {
                solve();
        }

        return 0;
}

void read(std::istream& is)
{
        int N, M;
        is >> N >> M;
        is.get(); // cleaning the stream for std::getline

        // speed optimization - avoiding dynamic resize
        necklace1.reserve(N + 1);
        necklace2.reserve(N + 1);

        // reading necklaces:
        { // memory optimization - auto destroying variables from stack momory
                char input[INPUT_MAX];
                is.getline(input, INPUT_MAX);
                int written = 0, i = 0;
                while (written < N && input[i]) {
                        char candidate = input[i];
                        if (isCorrect(candidate)) {
                                necklace1.push_back(candidate);
                                if (g.vertices.find(candidate) == g.vertices.end()) { // not found in vertices
                                        g.vertices.insert(candidate);
                                }
                                ++i;
                                ++written;
                        }
                        else
                                ++i;
                }
                written = 0;
                while (written < N && input[i]) {
                        char candidate = input[i];
                        if (isCorrect(candidate)) {
                                necklace2.push_back(candidate);
                                if (g.vertices.find(candidate) == g.vertices.end()) { // not found in vertices
                                        g.vertices.insert(candidate);
                                }
                                ++i;
                                ++written;
                        }
                        else
                                ++i;
                }
        }

        // reading the "transformations":
        char f, t;
        int how;
        for (int i = 0; i < M; ++i) {
                is >> f >> t >> how;
                if (g.vertices.find(f) == g.vertices.end())
                        g.vertices.insert(f);
                if (g.vertices.find(t) == g.vertices.end())
                        g.vertices.insert(t);

                g.edgesList.emplace_back(Edge{ f, t, how }); // avoid copying
        }
}

void testPrint()
{
        for (char i : necklace1)
                std::cout << i;
        std::cout << "\t";
        for (char i : necklace2)
                std::cout << i;
        std::cout << std::endl;

        for (char v : g.vertices)
                std::cout << v << " ";
        std::cout << std::endl;
        for (size_t i = 0; i < g.edgesList.size(); ++i)
                std::cout << g.edgesList.at(i);
        std::cout << std::endl;
}

void solve()
{
        int totalTime = 0;
        int sz = necklace1.size();
        int** dist = nullptr; // mapped values
        bool distCalculated = false;
        vector<char> ans;
        ans.reserve(sz); // heuristic - expected size
        for (int i = 0; i < sz; ++i) {
                if (necklace1[i] == necklace2[i]) {
                        ans.push_back(necklace1[i]);
                }
                else {
                        if (!distCalculated) { // doing Floyd's algo exactly one time, that's why this algorithm has been choosen
                                dist = new int*[MAX_VERTICES];
                                for (int j = 0; j < MAX_VERTICES; ++j)
                                        dist[j] = new int[MAX_VERTICES];
                                Floyd(dist);
                                distCalculated = true;
                        }

                        vector<std::pair<int, int>> candidates; // using for less cash misses
                                                                // .first = index, .second = value
                        candidates.reserve(MAX_VERTICES);
                        char one = map(necklace1[i]), two = map(necklace2[i]);
                        // pushing all candidates
                        for (int j = 0; j < MAX_VERTICES; ++j) {
                                if (dist[one][j] < INF && dist[two][j] < INF) {
                                        candidates.emplace_back(std::make_pair(j, dist[one][j] + dist[two][j]));
                                }
                        }
                        // finding the minimum
                        if (candidates.empty()) {
                                std::cout << -1 << std::endl << "Not possible" << std::endl;
                                return;
                        }
                        std::pair<int, int> minimum = candidates.back(); // .first = index, .second = value
                        candidates.pop_back();
                        while (!candidates.empty()) {
                                std::pair<int, int> x = candidates.back();
                                candidates.pop_back();
                                if (x.second < minimum.second)
                                        minimum = x;
                        }
                        totalTime += minimum.second;
                        ans.push_back(unmap(minimum.first));
                }
        }
        if (dist) {
                for (int i = 0; i < MAX_VERTICES; ++i)
                        delete[] dist[i];
                delete[] dist;
                dist = nullptr;
        }
        // print answer
        std::cout << totalTime << std::endl;
        for (char c : ans)
                std::cout << c;
        std::cout << std::endl;
}

void Floyd(int **&dist, int size)
{
        int i, j, k;

        for (i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                        i == j ? dist[i][j] = TRIVIAL : dist[i][j] = INF;

        int E = g.E();
        for (i = 0; i < E; ++i) {
                int src, dest, weight;
                src = map(g.edgesList[i].src);
                dest = map(g.edgesList[i].dest);
                weight = g.edgesList[i].weight;
                dist[src][dest] = weight;
        }

        for (k = 0; k < size; ++k) {
                for (i = 0; i < size; ++i) {
                        for (j = 0; j < size; ++j) {
                                if (((unsigned long long)(unsigned)dist[i][k] + (unsigned long long)(unsigned)dist[k][j]) < (unsigned long long)(unsigned)dist[i][j])
                                        dist[i][j] = dist[i][k] + dist[k][j];
                        }
                }
        }
}
