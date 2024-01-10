#include <iostream>
#include <limits>


int main(void)
{
    int firestations, intersections;
    int i, j, k, saved_value;
    int cost, min_cost, best_place_to_build_the_goddamn_station;
    int station, from, to, length; //inputs
    const int MAX_INTERSECTIONS = 500;
    //always loop from 1 to the number of intersections
    int distance[MAX_INTERSECTIONS+1][MAX_INTERSECTIONS+1];
    int distance_to_closest_station[MAX_INTERSECTIONS + 1];
    const int INFINITY = 100000000;// std::numeric_limits<int>::max();

    //for each test case
    int test_cases;
    std::cin >> test_cases;
    while(test_cases--) {
        std::cin >> firestations >> intersections;

        //set every station's distance to a sentinal value
        for(i = 1; i <= intersections; i++)
            distance_to_closest_station[i] = INFINITY;
        //read stations
        for(i = 1; i <= firestations; i++) {
            std::cin >> station;
            //node is station IIF distance_to_closest_station[node] == 0
            distance_to_closest_station[station] = 0;
        }

        //Floyd-Warshall's algorithm

        //initiate distance between every pair to a sentinal except the path from a node to itself
        for(i = 1; i <= intersections; i++) {
            for(j = 1; j <= intersections; j++)
                distance[i][j] = INFINITY;
            distance[i][i] = 0;
        }

        //read roads and add edges
        for(i = 1; i <= intersections; i++) {
            std::cin >> from >> to >> length;
            distance[from][to] = distance[to][from] = length;
        }

        //compute shortest paths between every pair
        for(k = 1; k <= intersections; k++)
            for(i = 1; i <= intersections; i++)
                for(j = 1; j <= intersections; j++)
                    if(distance[i][j] > distance[i][k] + distance[k][j])
                        distance[i][j] = distance[i][k] + distance[k][j];


        //minimizing cost ("the maximum distance from any intersection to its nearest fire station")
        min_cost = INFINITY;
        //for every non-station node, compute cost if it were a station
        for(k = 1; k <= intersections; k++) {
            if(distance_to_closest_station[k] == 0) continue;

            //making it a station
            saved_value = distance_to_closest_station[k];
            distance_to_closest_station[k] = 0;

            for(i = 1; i <= intersections; i++)
                if(distance_to_closest_station[i] != 0)
                    distance_to_closest_station[i] = INFINITY;
            //for every non-station node, update its distance to closest station
            for(i = 1; i <= intersections; i++)
                for(j = 1; j <= intersections; j++)
                    if(distance_to_closest_station[i] == 0 //if i is a station
                       && distance[i][j] < distance_to_closest_station[j])
                        distance_to_closest_station[j] = distance[i][j];
            //to compute cost
            cost = 0;
            for(i = 1; i <= intersections; i++)
                cost += distance_to_closest_station[i];
            std::cerr << "Cost if we build station at " << k << " is " << cost << std::endl;


            if(cost < min_cost) {
                min_cost = cost;
                best_place_to_build_the_goddamn_station = k;
            }

            //restore old distance for next iteration
            distance_to_closest_station[k] = saved_value;
        }

        std::cout << best_place_to_build_the_goddamn_station << std::endl;
    }
}