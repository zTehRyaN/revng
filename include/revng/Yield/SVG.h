#pragma once

//
// This file is distributed under the MIT License. See LICENSE.md for details.
//

#include <string>

class MetaAddress;
namespace model {
class Binary;
}

namespace yield {

class Function;
class CrossRelations;

namespace svg {

std::string controlFlowGraph(const yield::Function &InternalFunction,
                             const model::Binary &Binary);
std::string callGraph(const yield::CrossRelations &CrossRelationTree,
                      const model::Binary &Binary);
std::string callGraphSlice(const MetaAddress &SlicePoint,
                           const yield::CrossRelations &CrossRelationTree,
                           const model::Binary &Binary);

} // namespace svg

} // namespace yield
