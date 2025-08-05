/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Definitions                                                   *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: VGFEnums.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {
namespace vgf {
::llvm::StringRef stringifySegmentTypeEnum(SegmentTypeEnum val) {
  switch (val) {
    case SegmentTypeEnum::GRAPH: return "graph";
    case SegmentTypeEnum::COMPUTE: return "compute";
  }
  return "";
}

::std::optional<SegmentTypeEnum> symbolizeSegmentTypeEnum(::llvm::StringRef str) {
  return ::llvm::StringSwitch<::std::optional<SegmentTypeEnum>>(str)
      .Case("graph", SegmentTypeEnum::GRAPH)
      .Case("compute", SegmentTypeEnum::COMPUTE)
      .Default(::std::nullopt);
}
::std::optional<SegmentTypeEnum> symbolizeSegmentTypeEnum(uint32_t value) {
  switch (value) {
  case 0: return SegmentTypeEnum::GRAPH;
  case 1: return SegmentTypeEnum::COMPUTE;
  default: return ::std::nullopt;
  }
}

bool SegmentTypeEnumAttr::classof(::mlir::Attribute attr) {
  return (((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(32)))) && (((::llvm::cast<::mlir::IntegerAttr>(attr).getInt() == 0)) || ((::llvm::cast<::mlir::IntegerAttr>(attr).getInt() == 1)));
}
SegmentTypeEnumAttr SegmentTypeEnumAttr::get(::mlir::MLIRContext *context, SegmentTypeEnum val) {
  ::mlir::IntegerType intType = ::mlir::IntegerType::get(context, 32);
  ::mlir::IntegerAttr baseAttr = ::mlir::IntegerAttr::get(intType, static_cast<uint32_t>(val));
  return ::llvm::cast<SegmentTypeEnumAttr>(baseAttr);
}
SegmentTypeEnum SegmentTypeEnumAttr::getValue() const {
  return static_cast<SegmentTypeEnum>(::mlir::IntegerAttr::getInt());
}
} // namespace vgf
} // namespace mlir

