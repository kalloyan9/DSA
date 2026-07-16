#include "ConnectedComponentsSolver.h"
#include "InputReader.h"
#include "Logger.h"
#include <cassert>
#include <cstddef>
#include <iostream>

// Test 1: Empty matrix (all zeros)
void test_empty_matrix()
{
    ConnectedComponentsSolver solver(3, 3);
    // Without setting any cells, all are false (0)
    unsigned result = solver.countComponents();
    assert(0 == result);
    std::cout << "Test 1 passed: Empty matrix has 0 components\n";
}

// Test 2: Single cell (1x1 matrix with value 1)
void test_single_cell_one()
{
    ConnectedComponentsSolver solver(1, 1);
    solver.setCell(0, 0, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 2 passed: Single cell with 1 has 1 component\n";
}

// Test 3: Two adjacent cells horizontally
void test_two_adjacent_horizontal()
{
    ConnectedComponentsSolver solver(1, 2);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 3 passed: Two adjacent horizontal cells form 1 component\n";
}

// Test 4: Two adjacent cells vertically
void test_two_adjacent_vertical()
{
    ConnectedComponentsSolver solver(2, 1);
    solver.setCell(0, 0, true);
    solver.setCell(1, 0, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 4 passed: Two adjacent vertical cells form 1 component\n";
}

// Test 5: Two non-adjacent cells in same row
void test_two_non_adjacent_horizontal()
{
    ConnectedComponentsSolver solver(1, 3);
    solver.setCell(0, 0, true);
    solver.setCell(0, 2, true);
    unsigned result = solver.countComponents();
    assert(2 == result);
    std::cout << "Test 5 passed: Two non-adjacent horizontal cells form 2 components\n";
}

// Test 6: Two non-adjacent cells in same column
void test_two_non_adjacent_vertical()
{
    ConnectedComponentsSolver solver(3, 1);
    solver.setCell(0, 0, true);
    solver.setCell(2, 0, true);
    unsigned result = solver.countComponents();
    assert(2 == result);
    std::cout << "Test 6 passed: Two non-adjacent vertical cells form 2 components\n";
}

// Test 7: Diagonal cells (should be separate)
void test_diagonal_cells()
{
    ConnectedComponentsSolver solver(2, 2);
    solver.setCell(0, 0, true);
    solver.setCell(1, 1, true);
    unsigned result = solver.countComponents();
    assert(2 == result);
    std::cout << "Test 7 passed: Diagonal cells form 2 separate components\n";
}

// Test 8: 2x2 square (all ones)
void test_2x2_square_full()
{
    ConnectedComponentsSolver solver(2, 2);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.setCell(1, 0, true);
    solver.setCell(1, 1, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 8 passed: 2x2 full square forms 1 component\n";
}

// Test 9: Checkerboard pattern (2x2)
void test_checkerboard_2x2()
{
    ConnectedComponentsSolver solver(2, 2);
    solver.setCell(0, 0, true);
    solver.setCell(1, 1, true);
    unsigned result = solver.countComponents();
    assert(2 == result);
    std::cout << "Test 9 passed: 2x2 checkerboard has 2 components\n";
}

// Test 10: Horizontal line of 5 cells
void test_horizontal_line_5()
{
    ConnectedComponentsSolver solver(1, 5);
    for (unsigned i = 0; i < 5; ++i) {
        solver.setCell(0, i, true);
    }
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 10 passed: Horizontal line of 5 cells forms 1 component\n";
}

// Test 11: Vertical line of 5 cells
void test_vertical_line_5()
{
    ConnectedComponentsSolver solver(5, 1);
    for (unsigned i = 0; i < 5; ++i) {
        solver.setCell(i, 0, true);
    }
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 11 passed: Vertical line of 5 cells forms 1 component\n";
}

// Test 12: L-shaped component
void test_l_shaped()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 0, true);
    solver.setCell(1, 0, true);
    solver.setCell(2, 0, true);
    solver.setCell(2, 1, true);
    solver.setCell(2, 2, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 12 passed: L-shaped component forms 1 component\n";
}

// Test 13: T-shaped component
void test_t_shaped()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.setCell(0, 2, true);
    solver.setCell(1, 1, true);
    solver.setCell(2, 1, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 13 passed: T-shaped component forms 1 component\n";
}

// Test 14: Plus-shaped component
void test_plus_shaped()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 1, true);
    solver.setCell(1, 0, true);
    solver.setCell(1, 1, true);
    solver.setCell(1, 2, true);
    solver.setCell(2, 1, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 14 passed: Plus-shaped component forms 1 component\n";
}

// Test 15: Rectangle outline (hollow)
void test_rectangle_outline()
{
    ConnectedComponentsSolver solver(4, 4);
    // Top and bottom rows
    for (unsigned j = 0; j < 4; ++j) {
        solver.setCell(0, j, true);
        solver.setCell(3, j, true);
    }
    // Left and right columns (middle rows)
    for (unsigned i = 1; i < 3; ++i) {
        solver.setCell(i, 0, true);
        solver.setCell(i, 3, true);
    }
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 15 passed: Rectangle outline forms 1 component\n";
}

// Test 16: Three separate components
void test_three_separate_components()
{
    ConnectedComponentsSolver solver(3, 5);
    // Component 1: top-left
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    // Component 2: middle
    solver.setCell(1, 2, true);
    solver.setCell(1, 3, true);
    // Component 3: bottom-right
    solver.setCell(2, 4, true);
    unsigned result = solver.countComponents();
    assert(3 == result);
    std::cout << "Test 16 passed: Three separate components correctly identified\n";
}

// Test 17: Center cluster
void test_center_cluster()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(1, 1, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 17 passed: Single center cell forms 1 component\n";
}

// Test 18: Four corners
void test_four_corners()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 0, true);
    solver.setCell(0, 2, true);
    solver.setCell(2, 0, true);
    solver.setCell(2, 2, true);
    unsigned result = solver.countComponents();
    assert(4 == result);
    std::cout << "Test 18 passed: Four corners form 4 separate components\n";
}

// Test 19: Single row matrix
void test_single_row_alternating()
{
    ConnectedComponentsSolver solver(1, 5);
    solver.setCell(0, 0, true);
    solver.setCell(0, 2, true);
    solver.setCell(0, 4, true);
    unsigned result = solver.countComponents();
    assert(3 == result);
    std::cout << "Test 19 passed: Single row with alternating 1s has 3 components\n";
}

// Test 20: Single column matrix
void test_single_column_alternating()
{
    ConnectedComponentsSolver solver(5, 1);
    solver.setCell(0, 0, true);
    solver.setCell(2, 0, true);
    solver.setCell(4, 0, true);
    unsigned result = solver.countComponents();
    assert(3 == result);
    std::cout << "Test 20 passed: Single column with alternating 1s has 3 components\n";
}

// Test 21: Spiral pattern
void test_spiral_pattern()
{
    ConnectedComponentsSolver solver(4, 4);
    // Create a spiral
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.setCell(0, 2, true);
    solver.setCell(0, 3, true);
    solver.setCell(1, 3, true);
    solver.setCell(2, 3, true);
    solver.setCell(3, 3, true);
    solver.setCell(3, 2, true);
    solver.setCell(3, 1, true);
    solver.setCell(3, 0, true);
    solver.setCell(2, 0, true);
    solver.setCell(1, 0, true);
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 21 passed: Spiral pattern forms 1 component\n";
}

// Test 22: Matrix dimensions and getters
void test_matrix_dimensions()
{
    ConnectedComponentsSolver solver(5, 7);
    assert(5 == solver.rows());
    assert(7 == solver.cols());
    std::cout << "Test 22 passed: Matrix dimensions correctly stored\n";
}

// Test 23: Large 5x5 full matrix
void test_5x5_full_matrix()
{
    ConnectedComponentsSolver solver(5, 5);
    for (unsigned i = 0; i < 5; ++i) {
        for (unsigned j = 0; j < 5; ++j) {
            solver.setCell(i, j, true);
        }
    }
    unsigned result = solver.countComponents();
    assert(1 == result);
    std::cout << "Test 23 passed: 5x5 full matrix forms 1 component\n";
}

// Test 24: Repeated countComponents() returns same result
void test_count_components_repeatable()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.setCell(1, 0, true);

    const std::size_t firstCount = solver.countComponents();
    const std::size_t secondCount = solver.countComponents();

    assert(1 == firstCount);
    assert(1 == secondCount);
    std::cout << "Test 24 passed: countComponents() is repeatable\n";
}

// Test 25: setCell() throws for out-of-range coordinates
void test_set_cell_out_of_range()
{
    ConnectedComponentsSolver solver(2, 2);
    bool threw = false;

    try {
        solver.setCell(2, 0, true);
    } catch (const std::out_of_range&) {
        threw = true;
    }

    assert(threw);
    std::cout << "Test 25 passed: setCell() rejects out-of-range coordinates\n";
}

void runSolverTests()
{
    std::cout << "Running ConnectedComponentsSolver Unit Tests...\n\n";

    test_empty_matrix();
    test_single_cell_one();
    test_two_adjacent_horizontal();
    test_two_adjacent_vertical();
    test_two_non_adjacent_horizontal();
    test_two_non_adjacent_vertical();
    test_diagonal_cells();
    test_2x2_square_full();
    test_checkerboard_2x2();
    test_horizontal_line_5();
    test_vertical_line_5();
    test_l_shaped();
    test_t_shaped();
    test_plus_shaped();
    test_rectangle_outline();
    test_three_separate_components();
    test_center_cluster();
    test_four_corners();
    test_single_row_alternating();
    test_single_column_alternating();
    test_spiral_pattern();
    test_matrix_dimensions();
    test_5x5_full_matrix();
    test_count_components_repeatable();
    test_set_cell_out_of_range();

    std::cout << "ConnectedComponentsSolver tests passed.\n";
}
