#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include "heatflow.hpp"

using namespace std;

int main() {
    // Test case 1: Base Case
    {
        HeatFlow heatflow(0, 1, 0.1, {});
        heatflow.tick();
        assert(heatflow.getHeatFlowData() == vector<double>{0.0});
    }

    // Test case 2: Multiple Sections
    {
        HeatFlow heatflow(10, 5, 0.1, {});
        heatflow.tick();
        assert(heatflow.getHeatFlowData() == vector<double>{10.0, 10.0, 10.0, 10.0, 10.0});
    }

    // Test case 3: Single Source
    {
        HeatFlow heatflow(10, 5, 0.1, {{0, 100}});
        heatflow.tick();
        assert(heatflow.getHeatFlowData() == vector<double>{100.0, 10.0, 10.0, 10.0, 10.0});
    }

    // Test case 4: Multiple Sources
    {
        HeatFlow heatflow(10, 5, 0.1, {{0, 100}, {4, 50}});
        heatflow.tick();
        assert(heatflow.getHeatFlowData() == vector<double>{100.0, 10.0, 10.0, 10.0, 50.0});
    }

    // Test case 5: Source and Sink
    {
        HeatFlow heatflow(10, 5, 0.1, {{0, 100}, {4, 0}});
        heatflow.tick();
        assert(heatflow.getHeatFlowData() == vector<double>{100.0, 10.0, 10.0, 10.0, 0.0});
    }

    // Test case 6: Edge Cases
    {
        HeatFlow heatflow(-100, 1, 0.1, {});
        heatflow.tick();
        assert(heatflow.getHeatFlowData() == vector<double>{-100.0});
    }

    cout << "All tests completed successfully!" << endl;
    return 0;
}
