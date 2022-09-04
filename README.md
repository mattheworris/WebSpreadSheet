# WebSpreadSheet

Backend toy code to simulate an online spread sheet.

Compile: `g++-11 Sheet.cpp`

## API:

`void SetCell(const string& cellName, const string& stringValue)`

Parameter: `std::string cellName`

    Any arbitrary string to name a cell in the spreadsheet.
    Typical values: A1, A2, A3, B1, B2, B3.

Parameter: `std::string stringValue`

    The string representation of an integer value. The parameter is a string so
    that it can be easily used in front-end code that would display the value.

    The string representation can also be used to create mathematical operations
    with existing cells. For example:
    `SetCell("=A1+A2)`

    Addition (+) is currently the only supported operator.

`string GetCell(const string& cellName)`

Parameter: `const string& cellName`

    String representing the name of the cell in the spreadsheet.

Return: `std::string value`

    `value` corresponds to the value stored in the cell named cellName.
    Internally, the string is converted to an integer to allow for mathematical
    operations on the value.

Bug 1:

    Changing the values of existing cells does not update the value of cells
    created with mathematical operations. I chose a std::map<> as the underlying
    datastructure, and there is no tracking between dependent cells.

Potential Solution:

    Modify GetCell() to always reconstruct the mathematical operation.
    Sheet would have to know which cells are based on mathematical operators
    which would require SetCell() to "mark" each math cell. SetCel() could
    simply store the original string value, instead of converting it to an
    integer value.

    Pros: Sheet can use std::map<> with a modification of the types.
          SetCell() becomes very simple, just stores the input strings in the
          std::map<> data structure.
    Cons: GetCell() will have to take over the work from SetCell() to keep the
          data values consistent.

### Further Development

    This implementation could be expanded to accept more mathematical operations,
    more types of numbers, and more complicated mathematical formulas.