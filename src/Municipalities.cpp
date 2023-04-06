#include "Municipalities.h"


void Municipalities::execute() {

    mun_map.clear();

    // Get all the municipalities
    municipalitiesFind();
    vector<pair<string, int>> mun_vector(mun_map.begin(), mun_map.end());
    sort(mun_vector.begin(), mun_vector.end(), compareValue);

    // Get the number of districts and municipalities
    int nMunicipalities = 0;
    bool is_valid = false;

    while(!is_valid){
        cout << "\033[34mInsert the number of municipalities that will be displayed (máx: 134): " << "\033[0m";
        getInput(nMunicipalities);

        if (nMunicipalities <= 0 || nMunicipalities > mun_vector.size()){
            cout << endl;
            cout << "\033[31m - Invalid input - " << "\033[0m";
            cout << endl;
            cout << endl;
            continue;
        } else {
            is_valid = true;
        }
    }

    for (auto i = 0; i < nMunicipalities; i++) {
        if (i == 0){
            cout << "\nMunicipalities: " << endl;
        }
        cout << mun_vector[i].first << " " << mun_vector[i].second << endl;
    }

    for(auto n : graph.getVertexSet()){
        n.second->setVisited(false);
    }
}


void Municipalities::municipalitiesFind(){
    for(auto n : graph.getVertexSet()){
        n.second->setFlow(0);
    }

    auto extremesMun = graph.getExtremesMunicipalities();
    for (auto v1: extremesMun) {
        for (auto v2: extremesMun) {
            if (v1->getMunicipality() == v2->getMunicipality() && v1->getId() != v2->getId()) {
                if(v1->getId() < v2->getId()){
                    int flow = graph.getMunMaxFlow(v1, v2);
                    if(v2->getFlow() < flow){
                        v2->setFlow(flow);
                    }
                }
            }
        }
    }
    auto ConnectedMunicipalities = connectedComponents();
    for (auto cc : ConnectedMunicipalities){
        if(mun_map.count(cc.first) == 0){
            mun_map[cc.first] = 0;
        }
        for (int i = 0; i < cc.second.size(); i++){
            mun_map[cc.first] += cc.second[i];
        }
    }
}

map<string,vector<int>> Municipalities::connectedComponents() {
    map<string,vector<int>> flows;
    flows.clear();
    for(auto v : graph.getVertexSet()){
        v.second->setVisited(false);
    }

    for(auto v : graph.getVertexSet()){
        int flow = 0;
        if(!v.second->isVisited()){
            dfs(v.second, flow);
        }
        if (flows.count(v.second->getMunicipality()) == 0){
            flows[v.second->getMunicipality()] = vector<int>();
        }
        if (flow > 0){
            flows[v.second->getMunicipality()].push_back(flow);
        }
    }

    return flows;
}

void Municipalities::dfs(Vertex* n, int &flow) {
    n->setVisited(true);
    for(auto e : n->getAdj()){
        auto w = e->getDest();
        if(n->getMunicipality() != w->getMunicipality()){
            continue;
        }
        if(w->getFlow() > flow){
            flow = w->getFlow();
        }
        if(!w->isVisited()){
            dfs(w, flow);
        }
    }
}

Municipalities::Municipalities(int &currMenuPage, Graph &gh) : MenuItem(currMenuPage, gh) {
    this->graph = gh;
}