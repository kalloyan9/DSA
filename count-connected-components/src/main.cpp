#include <iostream>
#include <limits>
#include <vector>
#include <queue>

// Complex types for matrix and cell representation
typedef std::pair<unsigned, unsigned> Cell;
typedef std::vector<std::vector<bool>> Matrix;

// Global variables used in the program
static const unsigned DIM_MAX = std::numeric_limits<unsigned>::max(); // Maximum dimension for the matrix
static Matrix matrix;
static Matrix visited;
static unsigned n = 0u;
static unsigned m = 0u;
static unsigned number_of_connected_components = 0u;

void get_user_input(std::istream& is = std::cin, std::ostream& os = std::cout, std::ostream& err = std::cerr)
{
    os << "Enter the number of rows (n) and columns (m):" << std::endl;
    is >> n >> m;
    // Validating user input for matrix dimensions
    if (0u == n || 0u == m || n > DIM_MAX || m > DIM_MAX) {
        std::cerr << "[ERROR]: Invalid matrix dimensions. Please ensure 0 < n <= " << DIM_MAX << " and 0 < m <= " << DIM_MAX << "." << std::endl;
        exit(EXIT_FAILURE);
    }

    matrix.resize(n, std::vector<bool>(m, false));
    visited.resize(n, std::vector<bool>(m, false));
    bool cell;

    os << "Enter the matrix values (0 or 1) row by row:" << std::endl;
    for (unsigned i = 0u; i < n; ++i) {
        for (unsigned j = 0u; j < m; ++j) {
            is >> cell;
            if (cell != 0 && cell != 1) {
                std::cerr << "[ERROR]: Invalid matrix value. Please enter only 0 or 1." << std::endl;
                exit(EXIT_FAILURE);
            }
            matrix[i][j] = cell;
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
        if (i < n - 1 && matrix[i + 1][j] && !visited[i + 1][j]) {
            visited[i + 1][j] = true;
            q.push({i + 1, j});
        }
        if (j > 0 && matrix[i][j - 1] && !visited[i][j - 1]) {
            visited[i][j - 1] = true;
            q.push({i, j - 1});
        }
        if (j < m - 1 && matrix[i][j + 1] && !visited[i][j + 1]) {
            visited[i][j + 1] = true;
            q.push({i, j + 1});
        }
    }
    return isConnectedComponent;
}

int main()
{
    get_user_input(std::cin, std::cout, std::cerr);
    for (unsigned i = 0u; i < n; ++i) {
        for (unsigned j = 0u; j < m; ++j) {
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
