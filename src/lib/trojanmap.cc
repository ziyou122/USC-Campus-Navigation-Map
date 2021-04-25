#include "trojanmap.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <cctype>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

using namespace std;

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 *
 */
void TrojanMap::PrintMenu() {
  string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Exit                                                     \n"
      "**************************************************************\n";
  cout << menu << endl;
  string input;
  getline(cin, input);
  char number = input[0];
  switch (number) {
    case '1': {
      menu =
          "**************************************************************\n"
          "* 1. Autocomplete                                             \n"
          "**************************************************************\n";
      cout << menu << endl;
      menu = "Please input a partial location: ";
      cout << menu;
      getline(cin, input);
      auto start = chrono::high_resolution_clock::now();
      auto results = Autocomplete(input);
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      cout << menu;
      if (results.size() != 0) {
        for (auto x : results) cout << x << endl;
      } else {
        cout << "No matched locations." << endl;
      }
      menu = "**************************************************************\n";
      cout << menu;
      cout << "Time taken by function: " << duration.count() << " microseconds" << endl << endl;
      PrintMenu();
      break;
    }
    case '2': {
      menu =
          "**************************************************************\n"
          "* 2. Find the position                                        \n"
          "**************************************************************\n";
      cout << menu << endl;
      menu = "Please input a location: ";
      cout << menu;
      getline(cin, input);
      auto start = chrono::high_resolution_clock::now();
      auto results = GetPosition(input);
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      cout << menu;
      if (results.first != -1) {
        cout << "Latitude: " << results.first << " Longitude: " << results.second << endl;
        PlotPoint(results.first, results.second);
      } else {
        cout << "No matched locations." << endl;
      }
      menu = "**************************************************************\n";
      cout << menu;
      cout << "Time taken by function: " << duration.count() << " microseconds" << endl << endl;
      PrintMenu();
      break;
    }
    case '3': {
      menu =
          "**************************************************************\n"
          "* 3. CalculateShortestPath                                    \n"
          "**************************************************************\n";
      cout << menu << endl;
      menu = "Please input the start location:";
      cout << menu;
      string input1;
      getline(cin, input1);
      menu = "Please input the destination:";
      cout << menu;
      string input2;
      getline(cin, input2);
      auto start = chrono::high_resolution_clock::now();
      auto results = CalculateShortestPath_Dijkstra(input1, input2);
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      cout << menu;
      if (results.size() != 0) {
        for (auto x : results) cout << x << endl;
        cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << endl;
        PlotPath(results);
      } else {
        cout << "No route from the start point to the destination." << endl;
      }
      menu = "**************************************************************\n";
      cout << menu;
      cout << "Time taken by function: " << duration.count() << " microseconds" << endl << endl;
      PrintMenu();
      break;
    }
    case '4': {
      menu =
          "**************************************************************\n"
          "* 4. Travelling salesman problem                              \n"
          "**************************************************************\n";
      cout << menu << endl;
      menu =
          "In this task, we will select N random points on the map and you need to find the path to travel these "
          "points and back to the start point.";
      cout << menu << endl << endl;
      menu = "Please input the number of the places:";
      cout << menu;
      getline(cin, input);
      int num = stoi(input);
      vector<string> keys;
      for (auto x : data) {
        keys.push_back(x.first);
      }
      vector<string> locations;
      srand(time(NULL));
      for (int i = 0; i < num; i++) locations.push_back(keys[rand() % keys.size()]);
      PlotPoints(locations);
      cout << "Calculating ..." << endl;
      auto start = chrono::high_resolution_clock::now();
      auto results = TravellingTrojan_2opt(locations);
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
      CreateAnimation(results.second);
      menu = "*************************Results******************************\n";
      cout << menu;
      if (results.second.size() != 0) {
        for (auto x : results.second[results.second.size() - 1]) cout << x << endl;
        menu = "**************************************************************\n";
        cout << menu;
        cout << "The distance of the path is:" << results.first << " miles" << endl;
        PlotPath(results.second[results.second.size() - 1]);
      } else {
        cout << "The size of the path is 0" << endl;
      }
      menu =
          "**************************************************************\n"
          "You could find your animation at src/lib/output.avi.          \n";
      cout << menu;
      cout << "Time taken by function: " << duration.count() << " microseconds" << endl << endl;
      PrintMenu();
      break;
    }
    case '5': {
      menu =
          "**************************************************************\n"
          "* 5. Cycle Detection                                          \n"
          "**************************************************************\n";
      cout << menu << endl;
      menu = "Please input the left bound longitude(between -118.299 and -118.264):";
      cout << menu;
      getline(cin, input);
      vector<double> square;
      square.push_back(atof(input.c_str()));

      menu = "Please input the right bound longitude(between -118.299 and -118.264):";
      cout << menu;
      getline(cin, input);
      square.push_back(atof(input.c_str()));

      menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
      cout << menu;
      getline(cin, input);
      square.push_back(atof(input.c_str()));

      menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
      cout << menu;
      getline(cin, input);
      square.push_back(atof(input.c_str()));

      auto start = chrono::high_resolution_clock::now();
      auto results = CycleDetection(square);
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
      menu = "*************************Results******************************\n";
      cout << menu;
      if (results == true)
        cout << "there exists cycle in the subgraph " << endl;
      else
        cout << "there exist no cycle in the subgraph " << endl;
      menu = "**************************************************************\n";
      cout << menu;
      cout << "Time taken by function: " << duration.count() << " microseconds" << endl << endl;
      PrintMenu();
      break;
    }
    case '6': {
      menu =
          "**************************************************************\n"
          "* 6. Topological Sort                                         \n"
          "**************************************************************\n";
      cout << menu << endl;
      menu = "Please input the locations filename:";
      cout << menu;
      string locations_filename;
      getline(cin, locations_filename);
      menu = "Please input the dependencies filename:";
      cout << menu;
      string dependencies_filename;
      getline(cin, dependencies_filename);

      // Read location names from CSV file
      vector<string> location_names;
      if (locations_filename == "")
        location_names = {"Cardinal Gardens", "Coffee Bean1", "CVS"};
      else
        location_names = ReadLocationsFromCSVFile(locations_filename);

      // Read dependencies from CSV file
      vector<vector<string>> dependencies;
      if (dependencies_filename == "")
        dependencies = {{"Coffee Bean1", "Cardinal Gardens"}, {"CVS", "Cardinal Gardens"}, {"CVS", "Coffee Bean1"}};
      else
        dependencies = ReadDependenciesFromCSVFile(dependencies_filename);

      // vector<string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
      // vector<vector<string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal
      // Gardens"}, {"CVS","Coffee Bean1"}};
      auto start = chrono::high_resolution_clock::now();
      auto result = DeliveringTrojan(location_names, dependencies);
      auto stop = chrono::high_resolution_clock::now();
      auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
      menu = "*************************Results******************************";
      cout << menu << endl;
      cout << "Topological Sorting Reults:" << endl;
      for (auto x : result) cout << x << endl;
      vector<string> node_ids;
      for (auto x : result) {
        Node node = GetNode(x);
        node_ids.push_back(node.id);
      }
      PlotPointsOrder(node_ids);
      menu = "**************************************************************\n";
      cout << menu;
      cout << "Time taken by function: " << duration.count() << " microseconds" << endl << endl;
      PrintMenu();
      break;
    }
    case '7':
      break;
    default: {
      cout << "Please select 1 - 7." << endl;
      PrintMenu();
      break;
    }
  }
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 *
 */
void TrojanMap::CreateGraphFromCSVFile() {
  fstream fin;
  fin.open("src/lib/map.csv", ios::in);
  string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(remove(word.begin(), word.end(), '\''), word.end());
      word.erase(remove(word.begin(), word.end(), '"'), word.end());
      word.erase(remove(word.begin(), word.end(), '['), word.end());
      word.erase(remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 *
 * @param  {string} id : location id
 */
void TrojanMap::PlotPoint(string id) {
  string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 *
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 *
 * @param  {vector<string>} location_ids : path
 */
void TrojanMap::PlotPath(vector<string> &location_ids) {
  string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)), cv::Point(int(end.first), int(end.second)),
             cv::Scalar(0, 255, 0), LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 *
 * @param  {vector<string>} location_ids : points
 */
void TrojanMap::PlotPoints(vector<string> &location_ids) {
  string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 *
 * @param  {vector<string>} location_ids : points inside square
 * @param  {vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(vector<string> &location_ids, vector<double> &square) {
  string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)), cv::Point(int(end.first), int(end.second)),
               cv::Scalar(0, 255, 0), LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 *
 * @param  {vector<string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(vector<string> &location_ids) {
  string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0,
                CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)), cv::Point(int(end.first), int(end.second)),
                    cv::Scalar(0, 255, 0), LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * CreateAnimation: Create the videos of the progress to get the path
 *
 * @param  {vector<vector<string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(vector<vector<string>> path_progress) {
  cv::VideoWriter video("src/lib/output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, cv::Size(1248, 992));
  for (auto location_ids : path_progress) {
    string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE, cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)), cv::Point(int(end.first), int(end.second)),
               cv::Scalar(0, 255, 0), LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
  video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 *
 * @param  {double} lat         : latitude
 * @param  {double} lon         : longitude
 * @return {pair<double, double>}  : position on the map
 */
pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  pair<double, double> bottomLeft(34.01001, -118.30000);
  pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  pair<double, double> result((lon - bottomLeft.second) / w * 1248, (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 *
 * @param  {string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(string id) { return data[id].lat; }

/**
 * GetLon: Get the longitude of a Node given its id.
 *
 * @param  {string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(string id) { return data[id].lon; }

/**
 * GetName: Get the name of a Node given its id.
 *
 * @param  {string} id : location id
 * @return {string}    : name
 */
string TrojanMap::GetName(string id) { return data[id].name; }

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 *
 * @param  {string} id            : location id
 * @return {vector<string>}  : neighbor ids
 */
vector<string> TrojanMap::GetNeighborIDs(string id) { return {}; }

/**
 * CalculateDistance: Get the distance between 2 nodes.
 *
 * @param  {Node} a  : node a
 * @param  {Node} b  : node b
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const Node &a, const Node &b) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c; where 3961 is the approximate radius of the earth at the latitude of Washington D.C. in miles
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 *
 * @param  {vector<string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const vector<string> &path) {
  double sum = 0;
  for (int i = 0; i < path.size() - 1; i++) {
    sum += CalculateDistance(data[path[i]], data[path[i + 1]]);
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {string} name          : partial name
 * @return {vector<string>}  : a vector of full names
 */
vector<string> TrojanMap::Autocomplete(string name) {
  vector<string> results;
  transform(name.begin(), name.end(), name.begin(), ::tolower);
  for (auto pr : data) {
    string str(pr.second.name);
    transform(pr.second.name.begin(), pr.second.name.end(), str.begin(), ::tolower);
    if (name == str.substr(0, name.size())) {
      results.push_back(pr.second.name);
    }
  }
  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {string} name          : location name
 * @return {pair<double,double>}  : (lat, lon)
 */
pair<double, double> TrojanMap::GetPosition(string name) {
  for (auto pr : data) {
    if (pr.second.name == name) {
      return make_pair(GetLat(pr.first), GetLon(pr.first));
    }
  }
  return make_pair(-1, -1);
}

/**
 * GetNode: Given a location name, return the node.
 *
 * @param  {string} name          : location name
 * @return {Node}  : node
 */
Node TrojanMap::GetNode(string name) {
  Node n;
  n.id = "";
  return n;
}

string TrojanMap::GetID(const string &name) {
  for (auto &pr : data) {
    if (pr.second.name == name) {
      return pr.first;
    }
  }
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {string} location1_name     : start
 * @param  {string} location2_name     : goal
 * @return {vector<string>}       : path
 */
vector<string> TrojanMap::CalculateShortestPath_Dijkstra(string location1_name, string location2_name) {
  unordered_set<string> visited;
  unordered_map<string, pair<string, double>> dis(data.size());  // distance map: <ID, <predecessor ID, distance>

  string id1 = GetID(location1_name), id2 = GetID(location2_name);

  // initialization
  for (auto &pr : data) {
    dis[pr.first] = make_pair("", DBL_MAX);
  }
  dis[id1] = make_pair("", 0);
  for (auto &id : data[id1].neighbors) {
    dis[id] = make_pair(id1, CalculateDistance(data[id1], data[id]));
  }
  visited.insert(id1);
  string p_id, u_id;
  while (visited.size() < data.size()) {
    double min_dis = DBL_MAX * 0.9;

    // find an unvisited neighbor with min distance
    for (auto &pr : dis) {
      if (visited.end() == find(visited.begin(), visited.end(), pr.first)) {  // this is unvisited
        if (pr.second.second < min_dis) {
          p_id = pr.second.first;
          min_dis = pr.second.second;
          u_id = pr.first;
        }
      }
    }
    visited.insert(u_id);

    // if the destination has been found
    if (u_id == id2) {
      break;
    }

    // update with the distance to the neighbors of u
    for (auto &id : data[u_id].neighbors) {
      double new_dis = min_dis + CalculateDistance(data[u_id], data[id]);
      if (new_dis < dis[id].second) {
        dis[id] = make_pair(u_id, new_dis);
      }
    }
  }
  vector<string> path;
  u_id = id2;
  while (u_id != "") {
    path.push_back(u_id);
    u_id = dis[u_id].first;
  }
  reverse(path.begin(), path.end());
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {string} location1_name     : start
 * @param  {string} location2_name     : goal
 * @return {vector<string>}       : path
 */
vector<string> TrojanMap::CalculateShortestPath_Bellman_Ford(string location1_name, string location2_name) {
  vector<string> path;
  return path;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {string} locations_filename     : locations_filename
 * @return {vector<string>}           : locations
 */
vector<string> TrojanMap::ReadLocationsFromCSVFile(string locations_filename) {
  fstream fin;
  fin.open(locations_filename, ios::in);
  string line, word;
  vector<string> location_names_from_csv;

  getline(fin, line);
  while(getline(fin, line)) { 
    stringstream s(line);
    string location;
    getline(s, location, ',');
    location_names_from_csv.push_back(location);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {string} dependencies_filename     : dependencies_filename
 * @return {vector<vector<string>>} : dependencies
 */
vector<vector<string>> TrojanMap::ReadDependenciesFromCSVFile(string dependencies_filename) {

  fstream fin;
  fin.open(dependencies_filename, ios::in);
  string line, word;
  vector<vector<string>> dependencies_from_csv;

  getline(fin, line);
  while(getline(fin, line)) { 
    stringstream s(line);
    vector<string> locations;
    string location;
    while(getline(s, location, ',')) {
      locations.push_back(location);
    }
    dependencies_from_csv.push_back(locations);
  }
  fin.close();

  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {vector<string>} locations                     : locations
 * @param  {vector<vector<string>>} dependencies     : prerequisites
 * @return {vector<string>} results                       : results
 */
vector<string> TrojanMap::DeliveringTrojan(vector<string> &locations, vector<vector<string>> &dependencies) {
  map<string, int> total_map;
  vector<string> result;
  queue<string> zero_indegree;

  //initialize total_map: key:location, value:indegree
  for(int i = 0; i < locations.size(); i++) {
    total_map.insert(pair<string, int>(locations[i], 0));
  }   
  for(int i = 0; i < dependencies.size(); i++) {
    //std::cout << dependencies[i][1] << std::endl;
    total_map[dependencies[i][1]]++;
  }

  //initialize 0_indegree queue
  for(auto &item : total_map){
    if(item.second == 0) {
      zero_indegree.push(item.first);
    }
  }

  //update 0_indegree queue
  while (!zero_indegree.empty()) {
    // take out a 0_indegree location
    string cur_location = zero_indegree.front();
    result.push_back(cur_location);
    zero_indegree.pop();
    // then decrease indegree of other locations related to it
    for(auto &item : dependencies) {
      if(item[0] == cur_location){
        // put the new 0_indegree location into queue
        if(--total_map[item[1]] == 0) {
          zero_indegree.push(item[1]);
        }
      }
    }
  }
  
  return result;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {vector<string>} input : a list of locations needs to visit
 * @return {pair<double, vector<vector<string>>} : a pair of total distance and the all the progress
 * to get final path
 */
pair<double, vector<vector<string>>> TrojanMap::TravellingTrojan(vector<string> &location_ids) {
  vector<vector<string>> path;
  vector<string> cur_path;
  double min_dis = 0, cur_dis = 0;
  TravellingTrojan_(location_ids, path, cur_path, cur_dis, min_dis);
  return make_pair(min_dis, path);
}

void TrojanMap::TravellingTrojan_(vector<string> &ids, vector<vector<string>> &paths, vector<string> &cur_path,
                                  double &cur_dis, double &min_dis) {
  // each cur_path starts from ids[0]
  if (cur_path.empty()) {
    cur_dis = 0;
    cur_path.push_back(ids[0]);
  }

  // each cur_path ends at ids[0]
  if (cur_path.size() == ids.size()) {
    double delta_dis = CalculateDistance(data[cur_path.back()], data[ids[0]]);
    if (min_dis == 0 || cur_dis + delta_dis < min_dis) {
      min_dis = cur_dis + delta_dis;
      cur_path.push_back(ids[0]);
      paths.push_back(cur_path);  // save cur_path to path in descending order
      cur_path.pop_back();
    }
    return;
  }

  // early backtracking
  if (min_dis && cur_dis >= min_dis) {
    return;
  }

  // iterate children
  for (int i = 1; i < ids.size(); i++) {
    if (find(cur_path.begin(), cur_path.end(), ids[i]) == cur_path.end()) {
      double delta_dis = CalculateDistance(data[cur_path.back()], data[ids[i]]);
      cur_dis += delta_dis;
      cur_path.push_back(ids[i]);
      TravellingTrojan_(ids, paths, cur_path, cur_dis, min_dis);
      cur_path.pop_back();
      cur_dis -= delta_dis;
    }
  }
}

pair<double, vector<vector<string>>> TrojanMap::TravellingTrojan_2opt(vector<string> &location_ids) {
  vector<vector<string>> paths; // store the progress
  int size = location_ids.size();

  //initialize the path
  vector<string> initial_path;  
  double initial_length = 0;
  initial_path.assign(location_ids.begin(), location_ids.end());
  initial_path.push_back(location_ids[0]);
  paths.push_back(initial_path);
  for(int i = 0; i < initial_path.size() - 1; i++) {
    initial_length += CalculateDistance(data[initial_path[i]], data[initial_path[i+1]]);
  }

  // 2-opt, get a shorter path
  vector<string> cur_path = initial_path;
  double change_length;
  double min_change;
  bool isImproved = true;
  int left;
  int right;
  while(isImproved) {
    isImproved = false;
    min_change = 0;
    left = 0;
    right = 0;
    for(int i = 1; i < size - 1; i++) {
      for(int j = i + 1; j < size; j++) {
        change_length = CalculateDistance(data[cur_path[i - 1]], data[cur_path[j]]) 
                      + CalculateDistance(data[cur_path[i]], data[cur_path[j + 1]]) 
                      - CalculateDistance(data[cur_path[i - 1]], data[cur_path[i]])
                      - CalculateDistance(data[cur_path[j]], data[cur_path[j + 1]]);    
        if(change_length < min_change) {
          min_change = change_length;
          left = i;
          right = j;
          isImproved = true;
        }
      }
    }
    // generate the shorter path and put it in paths
    if(isImproved){
      UpdatePaths(paths, cur_path, left, right);
    }
  }

  //generate final length
  double final_length = 0;
  for(int i = 0; i < paths[paths.size() - 1].size(); i++){
    if(i == paths[paths.size() - 1].size() - 1) { 
      final_length += CalculateDistance(data[paths[paths.size() - 1][i]], data[paths[paths.size() - 1][0]]); 
    } else {
      final_length += CalculateDistance(data[paths[paths.size() - 1][i]], data[paths[paths.size() - 1][i + 1]]); 
    }
  }

  pair<double, vector<vector<string>>> results(final_length, paths);
  return results;
}

void TrojanMap::UpdatePaths(vector<vector<string>> &paths, vector<string> &cur_path, int left, int right) {
    swap(cur_path[left], cur_path[right]);
    paths.push_back(cur_path);
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 *
 * @param {vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(vector<double> &square) { return false; }