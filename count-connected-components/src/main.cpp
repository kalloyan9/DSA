#include <iostream>
#include <queue>

static const unsigned DIM = 5u;
static bool matrix[DIM][DIM];
static bool visited[DIM][DIM];
static unsigned number_of_connected_components = 0u;

typedef std::pair<unsigned, unsigned> Cell;

void get_user_input() 
{
    std::cout << "Enter the matrix values (0 or 1) row by row:" << std::endl;
    for (unsigned i = 0u; i < DIM; ++i) {
        for (unsigned j = 0u; j < DIM; ++j) {
            std::cin >> matrix[i][j];
            visited[i][j] = false;
        }
    }
}

bool find_connected_component_bfs(unsigned start_i, unsigned start_j) 
{
    bool isConnectedComponent = false;
    std::queue<Cell> q;
    q.push({start_i, start_j});
    visited[start_i][start_j] = true;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();
        isConnectedComponent = true;

        unsigned i = current.first;
        unsigned j = current.second;

        // Check all 4 adjacent cells
        if (i > 0 && matrix[i - 1][j] && !visited[i - 1][j]) {
            visited[i - 1][j] = true;
            q.push({i - 1, j});
        }
        if (i < DIM - 1 && matrix[i + 1][j] && !visited[i + 1][j]) {
            visited[i + 1][j] = true;
            q.push({i + 1, j});
        }
        if (j > 0 && matrix[i][j - 1] && !visited[i][j - 1]) {
            visited[i][j - 1] = true;
            q.push({i, j - 1});
        }
        if (j < DIM - 1 && matrix[i][j + 1] && !visited[i][j + 1]) {
            visited[i][j + 1] = true;
            q.push({i, j + 1});
        }
    }
    return isConnectedComponent;
}

int main()
{
    get_user_input();
    for (unsigned i = 0u; i < DIM; ++i) {
        for (unsigned j = 0u; j < DIM; ++j) {
            if (matrix[i][j] && !visited[i][j]) {
                if (find_connected_component_bfs(i, j)) {
                    std::cout << "[INFO]: Found a connected component starting at (" << i << ", " << j << ")" << std::endl;
                    ++number_of_connected_components;
                }
            }
        }
    }
    std::cout << "Total number of connected components: " << number_of_connected_components << std::endl;
    return 0;
}