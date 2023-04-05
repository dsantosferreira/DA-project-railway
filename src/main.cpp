//
// Created by tomas on 17/03/2023.
//

#include <iostream>
#include "Scraper.h"
#include "Graph.h"
#include "Program.h"
#include "ExampleGraphs.h"


int main(){
    Graph gh;
    auto line_map = Scraper::scrape_stations("../src/data/stations.csv", gh);
    Scraper::scrape_networks("../src/data/network.csv", gh);
    Scraper::fix_graph(gh);
    Scraper::findExtremes(line_map, gh);

    return 0;
}


