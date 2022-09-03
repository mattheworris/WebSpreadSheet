#include <map>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

#define CATCH_CONFIG_MAIN
#include "catch2.hpp"

using namespace std;

class Sheet {
public:
    Sheet() { }

    void SetCell(const string& cellName, const string& stringValue) {
        int value = atoi(stringValue.c_str());
        cells[cellName] = value;
    }

    string GetCell(const string& cellName) {
        int value = cells[cellName];
        return to_string(value);
    }

private:
    map<const string, int> cells;
};  

TEST_CASE("Sheet") {
    Sheet sheet;
    sheet.SetCell("A1", "1");
    sheet.SetCell("A2", "2");
    sheet.SetCell("A3", "3");
    REQUIRE(sheet.GetCell("A1") == "1");
    REQUIRE(sheet.GetCell("A2") == "2");
    REQUIRE(sheet.GetCell("A3") == "3");
}
