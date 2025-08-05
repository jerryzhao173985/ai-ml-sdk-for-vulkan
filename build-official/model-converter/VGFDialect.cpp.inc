/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: VGFDialect.td                                                        *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::vgf::VGFDialect)
namespace mlir {
namespace vgf {

VGFDialect::VGFDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<VGFDialect>()) {
  
  initialize();
}

VGFDialect::~VGFDialect() = default;

} // namespace vgf
} // namespace mlir
