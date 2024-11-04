#ifndef HEATFLOW_H
#define HEATFLOW_H
#include <vector>
#include <map>

class HeatFlow {
private:
    int initial_temperature;
    int number_of_sections;
    double k;
    std::vector<double> heatflow_data;
    std::map<int, double> sources_and_sinks;
    std::vector<int> known_sources_and_sinks_locations;
    std::string horizontal = "------";
    std::string vertical = "|";
    std::string corner = "+";
    std::string white_space = " ";

    void diffusion_equation(){
        std::vector<double> new_heatflow_data = heatflow_data;
        
        for (int i = 0; i < number_of_sections; i++) {

            bool t_is_source_or_sink = false;

            for (int j : known_sources_and_sinks_locations) {
                if (i == j){
                    t_is_source_or_sink = true;
                    break;
                }
            }

            if (!t_is_source_or_sink) 
            {
                double t = heatflow_data.at(i);
                double t_negative_one = (i > 0) ? heatflow_data.at(i - 1) : t;
                double t_positive_one = (i < number_of_sections - 1) ? heatflow_data.at(i + 1) : t;

                new_heatflow_data[i] = t + k * (t_positive_one - 2 * t + t_negative_one);
            }
        }

        heatflow_data = new_heatflow_data;
    };

public: 
    HeatFlow(int initial_temperature, int number_of_sections, double K, std::map<int, double> sources_and_sinks);
    std::vector<double> getHeatFlowData() const;
    void tick();
    void pretty_print();
};

#endif // HEATFLOW_H