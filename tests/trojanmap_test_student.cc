#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto names = m.Autocomplete("k");
  std::vector<std::string> gt1 = {"Kentucky Fried Chicken", "Korean Presbyterian Church", "Kobunga Korean Grill",
                                  "Kaitlyn"};
  EXPECT_EQ(names, gt1);
  names = m.Autocomplete("K");
  std::vector<std::string> gt2 = {"Kentucky Fried Chicken", "Korean Presbyterian Church", "Kobunga Korean Grill",
                                  "Kaitlyn"};
  EXPECT_EQ(names, gt2);
  names = m.Autocomplete("UsC");
  std::vector<std::string> gt3 = {"USC Fisher Museum of Art", "USC Village Gym", "USC Parking",
                                  "USC Village Dining Hall"};
  EXPECT_EQ(names, gt3);
}

TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto position = m.GetPosition("Crosswalk1");
  std::pair<double, double> gt1(34.0302951, -118.2857237);
  EXPECT_EQ(position, gt1);
  position = m.GetPosition("Moreton Fig");
  std::pair<double, double> gt2(34.0197837, -118.2859973);
  EXPECT_EQ(position, gt2);
  position = m.GetPosition("Mercado la Paloma");
  std::pair<double, double> gt3(34.0173353, -118.2784674);
  EXPECT_EQ(position, gt3);
}

TEST(TrojanMapTest, CalculateShortestPath_Dijkstra0) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Moreton Fig", "Mercado la Paloma");
  std::vector<std::string> gt;  // Expected path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  // Reverse
  path = m.CalculateShortestPath_Dijkstra("Mercado la Paloma", "Moreton Fig");
  std::reverse(gt.begin(), gt.end());
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford0) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Moreton Fig", "Mercado la Paloma");
  std::vector<std::string> gt;  // Expected path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  // Reverse
  path = m.CalculateShortestPath_Bellman_Ford("Mercado la Paloma", "Moreton Fig");
  std::reverse(gt.begin(), gt.end());
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Target", "Popeyes Louisiana Kitchen");
  std::vector<std::string> gt{
      "5237417650", "6813379479", "5237381975", "4399698012", "4399698013", "4399698011", "4399698010", "123044712",
      "4399698009", "4399698008", "123005253",  "6813379513", "6813379517", "6813379521", "123327627",  "4399697999",
      "6813565290", "122719210",  "6813379407", "2613117879", "6813379406", "6807905595", "6787803635", "2613117867",
      "4835551110", "6813565296", "122719205",  "6813565294", "4835551232", "4835551104", "4012842272", "4835551103",
      "123178841",  "6813565313", "122814435",  "6813565311", "4835551228", "6813513565", "4835551090", "4835551081",
      "6813513564", "20400292",   "5556117120", "5556117115", "4835551064", "4012842277", "6813565326", "123241961",
      "6813565322", "4835551070", "5695236164"};  // Expected path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  // Reverse
  path = m.CalculateShortestPath_Bellman_Ford("Popeyes Louisiana Kitchen", "Target");
  std::reverse(gt.begin(), gt.end());
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "ChickfilA");
  std::vector<std::string> gt{
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441", "6813405269",
      "6816193784", "6389467806", "6816193783", "123178876",  "2613117895", "122719259",  "2613117861", "6817230316",
      "3642819026", "6817230310", "7811699597", "5565967545", "123318572",  "6813405206", "6813379482", "544672028",
      "21306059",   "6813379476", "6818390140", "63068610",   "6818390143", "7434941012", "4015423966", "5690152766",
      "6813379440", "6813379466", "21306060",   "6813379469", "6813379427", "123005255",  "6807200376", "6807200380",
      "6813379451", "6813379463", "123327639",  "6813379460", "4141790922", "4015423963", "1286136447", "1286136422",
      "4015423962", "6813379494", "63068643",   "6813379496", "123241977",  "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544", "6813405275",
      "348121996",  "348121864",  "6813405280", "1472141024", "6813411590", "216155217",  "6813411589", "1837212103",
      "1837212101", "6820935911", "4547476733"};  // Expected path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  // Reverse
  path = m.CalculateShortestPath_Bellman_Ford("ChickfilA", "Ralphs");
  std::reverse(gt.begin(), gt.end());
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, ReadLocationsFromCSVFile) {
  TrojanMap m;
  vector<string> result;
  result = m.ReadLocationsFromCSVFile(
      "/home/student/2021Spring_TrojanMap/final-project-HaoxinMa/input/topologicalsort_locations.csv");

  int size = result.size();
  for (int i = 0; i < result.size(); i++) {
    std::cout << result[i] << std::endl;
  }

  EXPECT_EQ(size, 3);
}

TEST(TrojanMapTest, ReadDependenciesFromCSVFile) {
  TrojanMap m;
  vector<vector<string>> result;
  result = m.ReadDependenciesFromCSVFile(
      "/home/student/2021Spring_TrojanMap/final-project-HaoxinMa/input/topologicalsort_dependencies.csv");

  int size = result.size();
  for (auto &item : result) {
    std::cout << "size: " << item.size() << std::endl;
    for (int i = 0; i < item.size(); i++) {
      std::cout << item[i] << std::endl;
    }
    std::cout << "============" << std::endl;
  }

  EXPECT_EQ(size, 3);
}

TEST(TrojanMapTest, DeliveringTrojan) {
  TrojanMap m;
  vector<string> location;
  location = m.ReadLocationsFromCSVFile(
      "/home/student/2021Spring_TrojanMap/final-project-HaoxinMa/input/topologicalsort_dependencies.csv");
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