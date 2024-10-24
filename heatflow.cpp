#include <iostream>
#include "heatflow.hpp"

using namespace std;

HeatFlow::HeatFlow (int initial_temperature, int number_of_sections, double K, std::map<int, float> sources_and_sinks) {
    this->initial_temperature = initial_temperature;
    this->number_of_sections = number_of_sections;
    this->k = k;
    this->sources_and_sinks = sources_and_sinks;
}

void HeatFlow::tick()
{

}

void HeatFlow::pretty_print()
{
    cout << ""

};

