#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <utility>
#include <stdexcept>
#include <queue> 

namespace globalTypes
{
    using CoordinatesType = std::pair<unsigned long long, unsigned long long>;
    using LineType = std::vector<unsigned long long>;

    enum Algo
    {
        UNDEF = 0,
        BFS,
        LINE
    };
}

class InputReader
{
public:
    // c-tor
    explicit InputReader(std::istream &inputStream) : _inputStream(inputStream) {}

    // This SHOULD read unsigned long long N, M and then NxM matrix from unsigned long long from the std::cin as default
    globalTypes::CoordinatesType readDimensions()
    {
        unsigned long long n, m;
        _inputStream >> n >> m;
        
        // validate input
        if (0ull < n &&
            0ull < m &&
            n <= std::numeric_limits<unsigned long long>::max() && 
            m <= std::numeric_limits<unsigned long long>::max())
        {
            return globalTypes::CoordinatesType{n, m};
        }
        else
        {
            std::throw "invalid input";
        }
    }
 
    // reading line with N elements from the _inputStream, validating the input and returning it as a vector
    globalTypes::LineType readLine(unsigned long long n)
    {
        globalTypes::LineType line;
        unsigned long long element;
        for (auto i = 0; i < n; ++i)
        {
            _inputStream >> element;
            // validating input
            if (0ull == element || 1ull == element)
            {
                line.emplace_back(element);
            }
            else
            {
                throw "invalid input";
            }
        }
        return line;
    }

    private:
    std::istream &_inputStream;
};
 
class OutputWritter
{
public:
    // c-tor
    explicit OutputWritter(std::ostream &outputWritter) : _outputWritter(outputWritter) {}
 
    // This SHOULD write the result to the std::cout as default
    template <typename T>
    void write(const T &value)
    {
        _outputWritter << value << std::endl;
    }
private:
    std::ostream &_outputWritter;
};

class Matrix
{
public:
    // c-tor
    explicit Matrix(unsigned long long n_threshold = _DEFAULT_SIZE_THRESHOLD,
                    unsigned long long m_threshold = _DEFAULT_SIZE_THRESHOLD,
                    InputReader *inputReader = nullptr)
        :   _n(0ull),
            _m(0ull),
            _n_threshold(n_threshold),
            _m_threshold(m_threshold),
            _algo(globalTypes::Algo::UNDEF),
            _figures_counter(0ull),
            _inputReader(inputReader ? inputReader : &InputReader(std::cin)),
            _matrix(),
            _visited(),
            _line(),
            _coordsRemembered()
    {
    }

    globalTypes::Algo decideAlgo()
    {
        if (_n <= _n_threshold && _m <= _m_threshold)
        {
            _algo = globalTypes::Algo::BFS;
        }
        else
        {
            _algo = globalTypes::Algo::LINE;
        }
        return _algo;
    }
 
    void setDimensions(unsigned long long n, unsigned long long m)
    {
        _n = n;
        _m = m;
    }
 
    unsigned long long solve()
    {
        _figures_counter = 0ull;
        switch (_algo) 
        {
            case globalTypes::Algo::BFS:
                // read the whole matrix
                for (auto i = 0; i < _m; ++i)
                {
                    // static so init only once, and then reuse the same memory for each line read
                    static globalTypes::LineType l;
                    l = _inputReader->readLine(_n); // TODO: fix me
                    _matrix[i] = l;
                }
                solve_with_bfs();
            break;
 
            case globalTypes::Algo::LINE:
                for (auto i = 0; i < _m; ++i)
                {
                    _line = _inputReader->readLine(_n); // TODO: fix me
                    solve_by_line(i);
                }
            break;
 
            default:
                throw "invalid algo";
            break;
        }
    }
 
    private:
    // helper funcions:
    void solve_with_bfs()
    {
        // init used with zeroes
        _visited.assign(_n, std::vector<bool>(_m, false));
        _figures_counter = 0ull;

        for (auto i = 0; i < _n; ++i)
        {
            for (auto j = 0; j < _m; ++j)
            {
                if (0 != _matrix[i][j])
                {
                    ++_figures_counter;
                    // BFS
                    std::queue<globalTypes::CoordinatesType> q;
                    q.push(globalTypes::CoordinatesType{i, j});
                    _visited[i][j] = true;

                    while(!q.empty())
                    {
                        auto current = q.front();
                        q.pop();

                        // check all 4 directions
                        std::vector<globalTypes::CoordinatesType> directions = {
                            {current.first - 1, current.second}, // up
                            {current.first + 1, current.second}, // down
                            {current.first, current.second - 1}, // left
                            {current.first, current.second + 1}  // right
                        };

                        for (const auto& it : directions)
                        {
                            if (coords_validation(it) &&
                                false == _visited[it.first][it.second] &&
                                0 != _matrix[it.first][it.second])
                            {
                                q.push(it);
                                _visited[it.first][it.second] = true;
                            }
                        }
                    }
                }
            }
        }
    }
 
    // returns true if coordinates are in range, false - otherwise
    inline bool coords_validation(globalTypes::CoordinatesType coords)
    {
        return ((coords.first >= 0ull && coords.second >= 0ull) &&
                (coords.first < _n && coords.second < _m));
    }
 
    inline bool isElementInSet(globalTypes::CoordinatesType element)
    {
        return (_coordsRemembered.find(element) != _coordsRemembered.end());
    }
 
    inline void removeFromSet(globalTypes::CoordinatesType element)
    {
        if (isElementInSet(element))
        {
            _coordsRemembered.erase(element);
        }
    }
  
    void solve_by_line(unsigned long long currentM)
    {
        _figures_counter = 0ull;

        for (auto i = 0; i < _n; ++i)
        {
            auto element = _line[i];
            static globalTypes::CoordinatesType currentCoordinates = {i, currentM};
            static globalTypes::CoordinatesType prevOnTheSameRow = {i - 1ull, currentM};
            static globalTypes::CoordinatesType prevOnThePrevRow = {i, currentM - 1ull};
 
            // validity check the coords from the input
            if (false == coords_validation(currentCoordinates))
            {
                throw "invalid input";
            }
 
            // if element is not null, add it to the set
            if (0ull != _line[i])
            {
                _coordsRemembered.insert(currentCoordinates);
                // if it's not part of a figure, count a new figure has started
                if ((coords_validation(prevOnTheSameRow) && false == isElementInSet(prevOnTheSameRow)) &&
                    (coords_validation(prevOnThePrevRow) && false == isElementInSet(prevOnThePrevRow)))
                {
                    ++_figures_counter;
                }
            }
            // if element is null, remove the previous elements from the set - the figure ended in this dirrection
            else
            {
                if (coords_validation(prevOnTheSameRow))
                {
                    removeFromSet(prevOnTheSameRow);
                }
                if (coords_validation(prevOnThePrevRow))
                {
                    removeFromSet(prevOnThePrevRow);
                }
            }
        }
    }
 
    // data members
    static constexpr unsigned long long _DEFAULT_SIZE_THRESHOLD = 1'000'000ull; // default data
    unsigned long long _n, _m, _n_threshold, _m_threshold; // input data
    globalTypes::Algo _algo;
    unsigned long long _figures_counter;
 
    const InputReader *_inputReader;

    // data containers for bfs algo
    std::vector<globalTypes::LineType> _matrix; // container for small to mid data - using the BFS algo
    std::vector<std::vector<bool>> _visited;

    // data containers for line by line algo
    globalTypes::LineType _line; // container for big data - using the line algo
    std::set<globalTypes::CoordinatesType> _coordsRemembered; // container for the coordinates, used for line by line algo
};
 
int main()
{
    InputReader inputReader(std::cin);
    Matrix matrix(5ull, 5ull, &inputReader);
    OutputWritter outputWritter(std::cout);
 
    auto dim = inputReader.readDimensions(); // Coordinates::CoordinatesType
    matrix.setDimensions(dim.first, dim.second);
 
    matrix.solve();
    outputWritter.write(matrix);
 
    return 0;
}