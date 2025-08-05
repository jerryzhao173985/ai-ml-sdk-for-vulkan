/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: VGFDialect.td                                                        *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {
namespace vgf {

class VGFDialect : public ::mlir::Dialect {
  explicit VGFDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~VGFDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("vgf");
  }
};
} // namespace vgf
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vgf::VGFDialect)
