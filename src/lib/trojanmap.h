#ifndef TROJAN_MAP_H
#define TROJAN_MAP_H
#define DOT_SIZE 5
#define LINE_WIDTH 3

#include <iostream>
#include <map>
#include <vector>

using namespace std;

// A Node is the location of one point in the map.
class Node {
 public:
  string id;                 // A unique id assigned to each point
  double lat;                // Latitude
  double lon;                // Longitude
  string name;               // Name of the location
  vector<string> neighbors;  // List of the ids of all neighbor points

  Node(){};
  Node(const Node &n) {
    id = n.id;
    lat = n.lat;
    lon = n.lon;
    name = n.name;
    neighbors = n.neighbors;
  }
};

class TrojanMap {
 public:
  // A map of ids to Nodes.
  map<string, Node> data;

  //-----------------------------------------------------
  // TODO: You do not and should not change the following functions:

  // Create the menu.
  void PrintMenu();

  // Create the Dynamic menu.
  // void DynamicPrintMenu();

  // Read in the data
  void CreateGraphFromCSVFile();

  // Visualization
  // Given a location id, plot the point on the map.
  void PlotPoint(string id);

  // Given a lat and lon, plot the point on the map.
  void PlotPoint(double lat, double lon);

  // Given a vector of location ids draws the path (connects the points)
  void PlotPath(vector<string> &location_ids);

  // Given a vector of location ids draws the points on the map (no path).
  void PlotPoints(vector<string> &location_ids);

  // Given a vector of location ids draws the points on the map with path.
  void PlotPointsandEdges(vector<string> &location_ids, vector<double> &square);

  // Given a vector of location ids draws the points with their order on the map (no path).
  void PlotPointsOrder(vector<string> &location_ids);

  // Create the videos of the progress to get the path
  void CreateAnimation(vector<vector<string>>);

  // Transform the location to the position on the map
  pair<double, double> GetPlotLocation(double lat, double lon);
  //-----------------------------------------------------
  // TODO: Implement these functions and create unit tests for them:

  // Get the Latitude of a Node given its id.
  double GetLat(string id);

  // Get the Longitude of a Node given its id.
  double GetLon(string id);

  // Get the name of a Node given its id.
  string GetName(string id);

  // Get the Node given its name.
  Node GetNode(string name);

  string GetID(const string &name);

  // Get the neighbor ids of a Node.
  vector<string> GetNeighborIDs(string id);

  // Get the distance between 2 nodes.
  double CalculateDistance(const Node &a, const Node &b);

  // Calculates the total path length for the locations inside the vector.
  double CalculatePathLength(const vector<string> &path);

  // Returns a vector of names given a partial name.
  vector<string> Autocomplete(string name);

  // Returns lat and long of the given the name.
  pair<double, double> GetPosition(string name);

  // Given the name of two locations, it should return the **ids** of the nodes
  // on the shortest path.
  vector<string> CalculateShortestPath_Dijkstra(string location1_name, string location2_name);
  vector<string> CalculateShortestPath_Bellman_Ford(string location1_name, string location2_name);

  // Given CSV filename, it read and parse locations data from CSV file,
  // and return locations vector for topological sort problem.
  vector<string> ReadLocationsFromCSVFile(string locations_filename);

  // Given CSV filenames, it read and parse dependencise data from CSV file,
  // and return dependencies vector for topological sort problem.
  vector<vector<string>> ReadDependenciesFromCSVFile(string dependencies_filename);

  // Given a vector of location names, it should return a sorting of nodes
  // that satisfies the given dependencies.
  vector<string> DeliveringTrojan(vector<string> &location_names, vector<vector<string>> &dependencies);

  // Given a vector of location ids, it should reorder them such that the path
  // that covers all these points has the minimum length.
  // The return value is a pair where the first member is the total_path,
  // and the second member is the reordered vector of points.
  // (Notice that we don't find the optimal answer. You can return an estimated
  // path.)
  pair<double, vector<vector<string>>> TravellingTrojan(vector<string> &location_ids);
  void TravellingTrojan_(vector<string> &ids, vector<vector<string>> &path, vector<string> &cur_path, double &cur_dis,
                         double &min_dis);

  pair<double, vector<vector<string>>> TravellingTrojan_2opt(vector<string> &location_ids);

  // Given a subgraph specified by a square-shape area, determine whether there is a
  // cycle or not in this subgraph.
  // vector square has 4 elements: left/right/top/bottom bound in order.
  bool CycleDetection(vector<double> &square);

  //----------------------------------------------------- User-defined functions
};

#endif