// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <string>
#include <vector>
#include <tvm/tvm.h>
#include "core/codegen/mti/common.h"

namespace onnxruntime {
namespace tvm_codegen {

tvm::Array<tvm::Expr> ToTvmArray(const std::vector<int64_t>& shape);

tvm::Array<tvm::Integer> ToTvmArrayInt(const std::vector<int64_t>& shape);

// Helper function to compute sub shape size to axis (not included)
tvm::Expr SizeToDimension(const tvm::Array<tvm::Expr>& shape, int64_t axis);

// Helper function to compute sub shape size from axis (included)
tvm::Expr SizeFromDimension(const tvm::Array<tvm::Expr>& shape, int64_t axis);

// Helper function to align
tvm::Expr RoundUp(tvm::Expr value, tvm::Expr alignment);

tvm::Array<tvm::Expr> ConcatShapes(
    const tvm::Array<tvm::Expr>& shape1,
    const tvm::Array<tvm::Expr>& shape2);

// Helper function to rename tvm::Tensor
tvm::Tensor Rename(tvm::Tensor X, const std::string& name);

// Helper function to slice TVM shape
tvm::Array<tvm::Expr> SliceShape(const tvm::Array<tvm::Expr>& shape, const std::vector<int64_t>& axes);

// Helper function to slice TVM shape from axis (inclusive).
// Basically, this function returns the shape of [axis, shape.size()-1]
tvm::Array<tvm::Expr> SliceShapeFromDimension(const tvm::Array<tvm::Expr>& shape, int64_t axis);

// this function returns the shape of [0, axis-1]
tvm::Array<tvm::Expr> SliceShapeToDimension(const tvm::Array<tvm::Expr>& shape, int64_t axis);

// check if dimension is 1
bool IsOne(const tvm::Array<tvm::Expr>& shape, int64_t axis);

// Helper function to convert tvm::Expr to tvm::Tensor
tvm::Tensor Promote(const tvm::Expr& expr,
                    const tvm::Array<tvm::Expr>& shape,
                    const std::string& name = "PromoteExpr");

tvm::Tensor MakeZeroTensor(const tvm::Array<tvm::Expr>& shape, HalideIR::Type type, const std::string& name);

void DumpTVMModuleToFile(const std::string& filename_prefix, tvm::runtime::Module& module);

inline int64_t HandleNegativeAxis(int64_t axis, int64_t rank) {
  MTI_ASSERT(axis >= -rank && axis <= rank - 1);
  return axis = axis < 0 ? (axis + rank) : axis;
}

}  //  namespace tvm_codegen
}  //  namespace onnxruntime
