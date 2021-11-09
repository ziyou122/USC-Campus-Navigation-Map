#include <cmath>
#include <iomanip>
#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();

  // Test case 1: null input
  auto names = m.Autocomplete("");
  std::vector<std::string> gt1;  // expect a null vector
  EXPECT_EQ(names, gt1);

  // Test case 2: random input
  names = m.Autocomplete("hahahaha");
  std::vector<std::string> gt2;  // expect a null vector
  EXPECT_EQ(names, gt2);

  // Test case 3
  names = m.Autocomplete("UsC");
  std::vector<std::string> gt3 = {"USC Fisher Museum of Art", "USC Village Gym", "USC Parking",
                                  "USC Village Dining Hall"};
  EXPECT_EQ(names, gt3);
}

TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();

  // Test case 1: null input
  auto position = m.GetPosition("");
  std::pair<double, double> gt1(-1, -1);
  EXPECT_EQ(position, gt1);

  // Test case 2: random input
  position = m.GetPosition("hahahaha");
  std::pair<double, double> gt2(-1, -1);
  EXPECT_EQ(position, gt2);

  // Test case 3
  position = m.GetPosition("Mercado la Paloma");
  std::pair<double, double> gt3(34.0173353, -118.2784674);
  EXPECT_EQ(position, gt3);
}

// Test case 1: unconnected
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Moreton Fig", "Mercado la Paloma");
  std::vector<std::string> gt;  // expect a null vector
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  // Reverse
  path = m.CalculateShortestPath_Dijkstra("Mercado la Paloma", "Moreton Fig");
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 2: invalid input
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Moreton Fig", "hahahaha");  // random input
  std::vector<std::string> gt;                                              // expect a null vector
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  path = m.CalculateShortestPath_Dijkstra("", "Moreton Fig");  // null input
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 3
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Metro 40", "Vermont 38 Leighton Metro 204 Northbound05637");
  std::vector<std::string> gt = {
      "6503044367", "1837206589", "1837206591", "2898445153", "1837206590", "1837206588", "2898445152", "1837206592",
      "21302795",   "4060035996", "4015492467", "6788332708", "21302785",   "6788332705", "216153383",  "4020099339",
      "122609808",  "4020099340", "348123012",  "1870797772", "5617976418", "21302801",   "1855143774", "1855150054",
      "1855143763", "1855143760", "1855143759", "1855143758", "1855173112", "1855143756", "1855173115", "1855147948",
      "123166179",  "1855173116", "1862312661", "1862312636", "1862312582", "933930930",  "1855150091", "123182692",
      "1855137491", "122684539",  "348121025",  "6815190428", "122670230",  "4020099362", "4020099359", "123053759",
      "4020099352", "6512300966"};
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  // Reverse
  path = m.CalculateShortestPath_Dijkstra("Vermont 38 Leighton Metro 204 Northbound05637", "Metro 40");
  std::reverse(gt.begin(), gt.end());
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 1: unconnected
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Moreton Fig", "Mercado la Paloma");
  std::vector<std::string> gt;  // expect a null vector
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  // Reverse
  path = m.CalculateShortestPath_Bellman_Ford("Mercado la Paloma", "Moreton Fig");
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 2: invalid input
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Moreton Fig", "giuahoiawgjpogd");  // random input
  std::vector<std::string> gt;                                                         // expect a null vector
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  path = m.CalculateShortestPath_Bellman_Ford("", "Moreton Fig");  // null input
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 3
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Metro 40", "Vermont 38 Leighton Metro 204 Northbound05637");
  std::vector<std::string> gt = {
      "6503044367", "1837206589", "1837206591", "2898445153", "1837206590", "1837206588", "2898445152", "1837206592",
      "21302795",   "4060035996", "4015492467", "6788332708", "21302785",   "6788332705", "216153383",  "4020099339",
      "122609808",  "4020099340", "348123012",  "1870797772", "5617976418", "21302801",   "1855143774", "1855150054",
      "1855143763", "1855143760", "1855143759", "1855143758", "1855173112", "1855143756", "1855173115", "1855147948",
      "123166179",  "1855173116", "1862312661", "1862312636", "1862312582", "933930930",  "1855150091", "123182692",
      "1855137491", "122684539",  "348121025",  "6815190428", "122670230",  "4020099362", "4020099359", "123053759",
      "4020099352", "6512300966"};
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  path = m.CalculateShortestPath_Bellman_Ford("Vermont 38 Leighton Metro 204 Northbound05637", "Metro 40");
  std::reverse(gt.begin(), gt.end());
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 1: invalid input
TEST(TrojanMapTest, TSP1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input;  // null input
  auto result = m.TravellingTrojan(input);
  EXPECT_EQ(result.first, 0);
  input = {"123120189"};  // only one element input
  result = m.TravellingTrojan(input);
  EXPECT_EQ(result.first, 0);
}

// Test case 2
TEST(TrojanMapTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"348123012",  "1870797772", "5617976418", "21302801",   "1855143774", "1855150054",
                                 "1855143763", "1855143760", "1855143759", "1855143758", "1855173112"};
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl;
  std::vector<std::string> gt{"348123012",  "5617976418", "21302801",   "1855173112", "1855143758", "1855143759",
                              "1855143760", "1855143763", "1855150054", "1855143774", "1870797772", "348123012"};
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  bool flag = false;
  if (gt == result.second[result.second.size() - 1]) flag = true;
  std::reverse(gt.begin(), gt.end());
  if (gt == result.second[result.second.size() - 1]) flag = true;
  EXPECT_EQ(flag, true);
}

// Test case 3
TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"123120189",  "4011837224", "2514541020", "1931345270",
                                 "4015477529", "214470792",  "63068532",   "6807909279"};
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl;
  std::vector<std::string> gt{"123120189",  "4015477529", "214470792",  "63068532", "6807909279",
                              "2514541020", "1931345270", "4011837224", "123120189"};
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  bool flag = false;
  if (gt == result.second[result.second.size() - 1]) flag = true;
  std::reverse(gt.begin(), gt.end());
  if (gt == result.second[result.second.size() - 1]) flag = true;
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();

  // Test case 1: whole graph
  std::vector<double> square1 = {-120, 0, 35, 0};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, true);

  // Test case 2
  std::vector<double> square2 = {-118.290, -118.283, 34.022, 34.020};
  bool result2 = m.CycleDetection(square2);
  EXPECT_EQ(result2, false);

  // Test case 3: invalid input
  std::vector<double> square3 = {0, -120, 35, 0};
  bool result3 = m.CycleDetection(square3);
  EXPECT_EQ(result3, false);
}

TEST(TrojanMapTest, DeliveringTrojan_1) {
  TrojanMap m;
  vector<string> location;
  location = m.ReadLocationsFromCSVFile(
      "/home/student/2021Spring_TrojanMap/final-project-HaoxinMa/input/topologicalsort_locations.csv");
  vector<vector<string>> dep;
  dep = m.ReadDependenciesFromCSVFile(
      "/home/student/2021Spring_TrojanMap/final-project-HaoxinMa/input/topologicalsort_dependencies.csv");
  vector<string> result;
  result = m.DeliveringTrojan(location, dep);
  for (auto &item : result) {
    std::cout << item << std::endl;
  }
  EXPECT_EQ(true, true);
}

TEST(TrojanMapTest, DeliveringTrojan_2) {
  TrojanMap m;
  vector<string> location;
  location = {"FlixBus USC", "The Mirage", "Driveway", "Saint James Park", "University Park"};
  vector<vector<string>> dep;
  dep = {{"The Mirage", "FlixBus USC"},
         {"The Mirage", "Driveway"},
         {"Driveway", "University Park"},
         {"Driveway", "FlixBus USC"},
         {"FlixBus USC", "Saint James Park"}};
  vector<string> result;
  result = m.DeliveringTrojan(location, dep);
  for (auto &item : result) {
    std::cout << item << std::endl;
  }
  vector<string> expected = {"The Mirage", "Driveway", "University Park", "FlixBus USC", "Saint James Park"};
  EXPECT_EQ(result, expected);
}

TEST(TrojanMapTest, DeliveringTrojan_3) {
  TrojanMap m;
  vector<string> location;
  location = {"FlixBus USC", "The Mirage", "Driveway", "Saint James Park", "University Park"};
  vector<vector<string>> dep;
  dep = {{"The Mirage", "FlixBus USC"}, {"The Mirage", "Driveway"},          {"Driveway", "University Park"},
         {"Driveway", "FlixBus USC"},   {"FlixBus USC", "Saint James Park"}, {"Saint James Park", "Driveway"}};
  vector<string> result;
  result = m.DeliveringTrojan(location, dep);
  for (auto &item : result) {
    std::cout << item << std::endl;
  }
  vector<string> expected = {};
  EXPECT_EQ(result, expected);
}

TEST(TrojanMapTest, DeliveringTrojan_4) {
  TrojanMap m;
  vector<string> location;
  location = {};
  vector<vector<string>> dep;
  dep = {};
  vector<string> result;
  result = m.DeliveringTrojan(location, dep);
  for (auto &item : result) {
    std::cout << item << std::endl;
  }
  vector<string> expected = {};
  EXPECT_EQ(result, expected);
}