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
        if (stringValue[0] == '=')
        {
            // This cell will contain a mathematical operation based on other cells
            // Parse the string to find the other cells in the operation
            size_t mathOperator = stringValue.find_first_of('+');
            string cell1 = stringValue.substr(1, mathOperator - 1);
            string cell2 = stringValue.substr(mathOperator + 1);
            int value1 = cells[cell1];
            int value2 = cells[cell2];
            cells[cellName] = value1 + value2;
        }
        else
        {
            int value = atoi(stringValue.c_str());
            cells[cellName] = value;
        }
    }

    string GetCell(const string& cellName) {
        int value = cells[cellName];
        return to_string(value);
    }

private:
    map<const string, int> cells;
};  

SCENARIO("Backend Spread Sheet API Tests") {
    GIVEN( "Some cells in a spreadsheet") {
        Sheet sheet;
        sheet.SetCell("A1", "1");
        sheet.SetCell("BB1", "1");
        sheet.SetCell("A2", "2");
        sheet.SetCell("A3", "3");

        REQUIRE(sheet.GetCell("A1") == "1");
        REQUIRE(sheet.GetCell("BB1") == "1");
        REQUIRE(sheet.GetCell("A2") == "2");
        REQUIRE(sheet.GetCell("A3") == "3");

        WHEN("new cells are created with mathmatical operations")
        {
            sheet.SetCell("A4", "=A3+A2");
            sheet.SetCell("BB2", "=A3+BB1");

            REQUIRE(sheet.GetCell("A4") == "5");
            REQUIRE(sheet.GetCell("BB2") == "4");

            // Change the values of the existing cells
            sheet.SetCell("A1", "10");
            sheet.SetCell("BB1", "11");
            sheet.SetCell("A2", "20");
            sheet.SetCell("A3", "30");

            REQUIRE(sheet.GetCell("A1") == "10");
            REQUIRE(sheet.GetCell("BB1") == "11");
            REQUIRE(sheet.GetCell("A2") == "20");
            REQUIRE(sheet.GetCell("A3") == "30");

            REQUIRE(sheet.GetCell("A4") == "50");
            REQUIRE(sheet.GetCell("BB2") == "41");
        }
    }
}
