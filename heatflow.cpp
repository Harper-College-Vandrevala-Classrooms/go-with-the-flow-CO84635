#include <iostream>
#include "heatflow.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

HeatFlow::HeatFlow (int initial_temperature, int number_of_sections, double k, map<int, double> sources_and_sinks) {
    this->initial_temperature = initial_temperature;
    this->number_of_sections = number_of_sections;
    this->k = k;
    this->sources_and_sinks = sources_and_sinks;
    for (int i = 0; i < number_of_sections; i++){
        heatflow_data.push_back(initial_temperature);
    }

    for (const auto& pair : sources_and_sinks) {
        heatflow_data[pair.first] = pair.second;
        known_sources_and_sinks_locations.push_back(pair.first);
    }
}

void HeatFlow::tick()
{
    diffusion_equation();
}

vector<double> HeatFlow::getHeatFlowData() const{
    return heatflow_data;
}

void HeatFlow::pretty_print() {
    std::stringstream top_and_bottom_brace;
    std::stringstream middle_data;

    top_and_bottom_brace << corner;
    for (int i = 0; i < number_of_sections; i++) {
        top_and_bottom_brace << std::setw(6) << std::setfill('-') << horizontal << corner;
    }
    top_and_bottom_brace << std::endl;

    
    middle_data << vertical; 
    for (int i = 0; i < number_of_sections; i++) {
        middle_data << std::setw(6) << std::setfill(' ') << std::fixed << std::setprecision(1) << heatflow_data[i] << vertical; 
    }
    middle_data << endl;

    std::cout << top_and_bottom_brace.str();
    std::cout << middle_data.str();
    std::cout << top_and_bottom_brace.str(); 
}

