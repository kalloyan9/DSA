#include "ConnectedComponentsSolver.h"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <stdexcept>

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

// Component Membership Tests

// Test 24: Adjacent cells same component
void test_component_membership_adjacent()
{
    ConnectedComponentsSolver solver(1, 2);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.countComponents();
    
    unsigned comp0 = solver.getComponentId(0, 0);
    unsigned comp1 = solver.getComponentId(0, 1);
    assert(0 != comp0);
    assert(comp0 == comp1);
    std::cout << "Test 24 passed: Adjacent cells belong to same component\n";
}

// Test 25: Non-adjacent cells different components
void test_component_membership_non_adjacent()
{
    ConnectedComponentsSolver solver(1, 3);
    solver.setCell(0, 0, true);
    solver.setCell(0, 2, true);
    solver.countComponents();
    
    unsigned comp0 = solver.getComponentId(0, 0);
    unsigned comp2 = solver.getComponentId(0, 2);
    assert(0 != comp0);
    assert(0 != comp2);
    assert(comp0 != comp2);
    std::cout << "Test 25 passed: Non-adjacent cells belong to different components\n";
}

// Test 26: Disconnected cell has ID 0
void test_component_membership_disconnected()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 0, true);
    solver.countComponents();
    
    unsigned compCell = solver.getComponentId(0, 0);
    unsigned compEmpty = solver.getComponentId(1, 1);
    assert(0 != compCell);
    assert(0 == compEmpty);
    std::cout << "Test 26 passed: Disconnected cells have component ID 0\n";
}

// Test 27: L-shaped component membership
void test_component_membership_l_shaped()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 0, true);
    solver.setCell(1, 0, true);
    solver.setCell(2, 0, true);
    solver.setCell(2, 1, true);
    solver.setCell(2, 2, true);
    solver.countComponents();
    
    unsigned comp00 = solver.getComponentId(0, 0);
    unsigned comp10 = solver.getComponentId(1, 0);
    unsigned comp20 = solver.getComponentId(2, 0);
    unsigned comp21 = solver.getComponentId(2, 1);
    unsigned comp22 = solver.getComponentId(2, 2);
    
    assert(0 != comp00);
    assert(comp00 == comp10);
    assert(comp10 == comp20);
    assert(comp20 == comp21);
    assert(comp21 == comp22);
    std::cout << "Test 27 passed: All L-shaped cells belong to same component\n";
}

// Test 28: Three separate components have different IDs
void test_component_membership_three_separate()
{
    ConnectedComponentsSolver solver(3, 5);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.setCell(1, 2, true);
    solver.setCell(1, 3, true);
    solver.setCell(2, 4, true);
    solver.countComponents();
    
    unsigned comp00 = solver.getComponentId(0, 0);
    unsigned comp01 = solver.getComponentId(0, 1);
    unsigned comp12 = solver.getComponentId(1, 2);
    unsigned comp13 = solver.getComponentId(1, 3);
    unsigned comp24 = solver.getComponentId(2, 4);
    
    assert(comp00 == comp01);
    assert(comp12 == comp13);
    assert(comp00 != comp12);
    assert(comp12 != comp24);
    assert(comp00 != comp24);
    std::cout << "Test 28 passed: Three separate components have different IDs\n";
}

// Test 29: Full 2x2 matrix all same component
void test_component_membership_2x2_full()
{
    ConnectedComponentsSolver solver(2, 2);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.setCell(1, 0, true);
    solver.setCell(1, 1, true);
    solver.countComponents();
    
    unsigned comp00 = solver.getComponentId(0, 0);
    unsigned comp01 = solver.getComponentId(0, 1);
    unsigned comp10 = solver.getComponentId(1, 0);
    unsigned comp11 = solver.getComponentId(1, 1);
    
    assert(comp00 == comp01);
    assert(comp01 == comp10);
    assert(comp10 == comp11);
    std::cout << "Test 29 passed: Full 2x2 matrix all cells in same component\n";
}

// Test 30: Plus-shaped component all same ID
void test_component_membership_plus_shaped()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 1, true);
    solver.setCell(1, 0, true);
    solver.setCell(1, 1, true);
    solver.setCell(1, 2, true);
    solver.setCell(2, 1, true);
    solver.countComponents();
    
    unsigned compTop = solver.getComponentId(0, 1);
    unsigned compLeft = solver.getComponentId(1, 0);
    unsigned compCenter = solver.getComponentId(1, 1);
    unsigned compRight = solver.getComponentId(1, 2);
    unsigned compBottom = solver.getComponentId(2, 1);
    
    assert(compTop == compCenter);
    assert(compLeft == compCenter);
    assert(compRight == compCenter);
    assert(compBottom == compCenter);
    std::cout << "Test 30 passed: Plus-shaped component all cells same ID\n";
}

// Test 31: Horizontal line component IDs
void test_component_membership_horizontal_line()
{
    ConnectedComponentsSolver solver(1, 4);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.setCell(0, 2, true);
    solver.setCell(0, 3, true);
    solver.countComponents();
    
    unsigned comp0 = solver.getComponentId(0, 0);
    unsigned comp1 = solver.getComponentId(0, 1);
    unsigned comp2 = solver.getComponentId(0, 2);
    unsigned comp3 = solver.getComponentId(0, 3);
    
    assert(comp0 == comp1);
    assert(comp1 == comp2);
    assert(comp2 == comp3);
    assert(0 != comp0);
    std::cout << "Test 31 passed: Horizontal line all cells same component ID\n";
}

// Test 32: Vertical line component IDs
void test_component_membership_vertical_line()
{
    ConnectedComponentsSolver solver(4, 1);
    solver.setCell(0, 0, true);
    solver.setCell(1, 0, true);
    solver.setCell(2, 0, true);
    solver.setCell(3, 0, true);
    solver.countComponents();
    
    unsigned comp0 = solver.getComponentId(0, 0);
    unsigned comp1 = solver.getComponentId(1, 0);
    unsigned comp2 = solver.getComponentId(2, 0);
    unsigned comp3 = solver.getComponentId(3, 0);
    
    assert(comp0 == comp1);
    assert(comp1 == comp2);
    assert(comp2 == comp3);
    assert(0 != comp0);
    std::cout << "Test 32 passed: Vertical line all cells same component ID\n";
}

// Test 33: Corner pairs have different IDs
void test_component_membership_corners()
{
    ConnectedComponentsSolver solver(3, 3);
    solver.setCell(0, 0, true);
    solver.setCell(0, 2, true);
    solver.setCell(2, 0, true);
    solver.setCell(2, 2, true);
    solver.countComponents();
    
    unsigned comp00 = solver.getComponentId(0, 0);
    unsigned comp02 = solver.getComponentId(0, 2);
    unsigned comp20 = solver.getComponentId(2, 0);
    unsigned comp22 = solver.getComponentId(2, 2);
    
    assert(comp00 != comp02);
    assert(comp02 != comp20);
    assert(comp20 != comp22);
    assert(comp00 != comp20);
    std::cout << "Test 33 passed: Four corners have different component IDs\n";
}

// Test 34: Component matrix access valid
void test_component_matrix_access()
{
    ConnectedComponentsSolver solver(2, 2);
    solver.setCell(0, 0, true);
    solver.setCell(0, 1, true);
    solver.countComponents();
    
    const auto& compMatrix = solver.getComponentMatrix();
    assert(2 == compMatrix.size());
    assert(2 == compMatrix[0].size());
    unsigned comp00 = compMatrix[0][0];
    unsigned comp01 = compMatrix[0][1];
    assert(comp00 == comp01);
    assert(0 != comp00);
    std::cout << "Test 34 passed: Component matrix access works correctly\n";
}

// Test 35: Checkerboard pattern components
void test_component_membership_checkerboard()
{
    ConnectedComponentsSolver solver(2, 2);
    solver.setCell(0, 0, true);
    solver.setCell(1, 1, true);
    solver.countComponents();
    
    unsigned comp00 = solver.getComponentId(0, 0);
    unsigned comp11 = solver.getComponentId(1, 1);
    unsigned comp01 = solver.getComponentId(0, 1);
    unsigned comp10 = solver.getComponentId(1, 0);
    
    assert(comp00 != comp11);
    assert(0 == comp01);
    assert(0 == comp10);
    assert(0 != comp00);
    assert(0 != comp11);
    std::cout << "Test 35 passed: Checkerboard pattern has correct component IDs\n";
}

int main()
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
    test_component_membership_adjacent();
    test_component_membership_non_adjacent();
    test_component_membership_disconnected();
    test_component_membership_l_shaped();
    test_component_membership_three_separate();
    test_component_membership_2x2_full();
    test_component_membership_plus_shaped();
    test_component_membership_horizontal_line();
    test_component_membership_vertical_line();
    test_component_membership_corners();
    test_component_matrix_access();
    test_component_membership_checkerboard();

    std::cout << "\n✓ All 35 tests passed!\n";
    return 0;
}
