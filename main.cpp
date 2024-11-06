#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <map>
#include "heatflow.hpp"

using namespace std;

int main() {
    // Test case 1: Single section with a heat source
    {
        std::map<int, double> sources_and_sinks;
        sources_and_sinks[0] = 90.0;  
        int initial_temperature = 20;  
        int number_of_sections = 1;
        double K = 0.1;

        HeatFlow h(initial_temperature, number_of_sections, K, sources_and_sinks);
        h.tick();
        auto data1 = h.getHeatFlowData();
        assert(data1[0] < 90.01);
        assert(data1[0] > 89.99); 
    }

    // Test case 2: Multiple sections with heat source at the start
    {
        std::map<int, double> sources_and_sinks;
        sources_and_sinks[0] = 50.0;  
        int initial_temperature = 20;  
        int number_of_sections = 3;  
        double K = 0.3;

        HeatFlow h(initial_temperature, number_of_sections, K, sources_and_sinks);
        h.tick();
        auto data2 = h.getHeatFlowData();
        double expected_T1 = 20 + K * (50 - 2 * 20 + 20);
        assert(data2[0] < 50.01);  
        assert(data2[0] > 49.99);
        assert(data2[1] < (expected_T1 + 0.01));
        assert(data2[1] > (expected_T1 - 0.01));  
        assert(data2[2] < 20.01);  
        assert(data2[2] > 19.99);
    }

    // Test case 3: Heat source in the middle
    {
        std::map<int, double> sources_and_sinks;
        sources_and_sinks[2] = 200.0;  
        int initial_temperature = 40;  
        int number_of_sections = 5;  
        double K = 0.1;

        HeatFlow h(initial_temperature, number_of_sections, K, sources_and_sinks);
        h.tick();
        auto data3 = h.getHeatFlowData();
        double expected_T2 = 40 + K * (200 - 2 * 40 + 40);
        assert(data3[0] < 40.01);
        assert(data3[0] > 39.99);     
        assert(data3[1] < (expected_T2 + 0.01));
        assert(data3[1] > (expected_T2 - 0.01));    
        assert(data3[2] < 200.01);
        assert(data3[2] > 199.99);     
        assert(data3[3] < (expected_T2 + 0.01));
        assert(data3[3] > (expected_T2 - 0.01));     
        assert(data3[4] < 40.01);
        assert(data3[4] > 39.99);      
    }

    // Test case 4: Heat source at start and sink at end
    {
        std::map<int, double> sources_and_sinks;
        sources_and_sinks[0] = 80.0;  
        sources_and_sinks[3] = 15.0;  
        int initial_temperature = 35;  
        int number_of_sections = 4;  
        double K = 0.2;

        HeatFlow h(initial_temperature, number_of_sections, K, sources_and_sinks);
        h.tick();
        auto data4 = h.getHeatFlowData();
        double expected_T3 = 35 + K * (80 - 2 * 35 + 35);
        assert(data4[0] < 80.01);
        assert(data4[0] > 79.99); 
        assert(data4[1] < (expected_T3 + 0.01));
        assert(data4[1] > (expected_T3 - 0.01));  
        assert(data4[2] < 31.01);
        assert(data4[2] > 30.99);  
        assert(data4[3] < 15.01);
        assert(data4[3] > 14.99);  
    }

    // Test case 5: No heat source, just initial temperature
    {
        std::map<int, double> sources_and_sinks;  
        int initial_temperature = 60;  
        int number_of_sections = 4;  
        double K = 0.1;

        HeatFlow h(initial_temperature, number_of_sections, K, sources_and_sinks);
        h.tick();        
        auto data5 = h.getHeatFlowData();
        for (int i = 0; i < number_of_sections; i++) {
            assert(data5[i] < (initial_temperature + 0.01));
            assert(data5[i] > (initial_temperature - 0.01)); 
        }
    }

    cout << "All assertions passed, temperatures are less than slightly increased expected values!" << endl;
    return 0;
}
