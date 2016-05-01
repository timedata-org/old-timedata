#include <tdsp/Tile.h>
#include <tdsp/Rows.h>

namespace tdsp {
namespace color {

FColorList expand(const FColorList& fcl, int xMult, int yMult, int columns)
{
    auto rows = computeRows(fcl.size(), columns);
    auto newColumns = columns * xMult;
    auto newRows = rows * yMult;

    FColorList result;
    result.reserve(newColumns * newRows);

    for (auto y = 0; y < rows; ++y)
        for (auto ym = 0; ym < yMult; ++ym)
            for (auto x = 0; x < columns; ++x)
                for (auto xm = 0; xm < xMult; ++xm)
                    result.push_back(fcl.get(y * rows + x));

    return result;
}

}  // namespace color
}  // namespace tdsp
