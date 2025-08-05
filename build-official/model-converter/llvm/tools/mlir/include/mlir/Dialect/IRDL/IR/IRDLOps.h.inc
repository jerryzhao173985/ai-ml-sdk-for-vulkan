/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: IRDLOps.td                                                           *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#if defined(GET_OP_CLASSES) || defined(GET_OP_FWD_DEFINES)
#undef GET_OP_FWD_DEFINES
namespace mlir {
namespace irdl {
class AllOfOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class AnyOfOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class AnyOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class AttributeOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class AttributesOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class BaseOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class CPredOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class DialectOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class IsOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class OperandsOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class OperationOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class ParametersOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class ParametricOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class RegionOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class RegionsOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class ResultsOp;
} // namespace irdl
} // namespace mlir
namespace mlir {
namespace irdl {
class TypeOp;
} // namespace irdl
} // namespace mlir
#endif

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::AllOfOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class AllOfOpGenericAdaptorBase {
public:
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  ::mlir::RegionRange odsRegions;
public:
  AllOfOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {});

  AllOfOpGenericAdaptorBase(AllOfOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  ::mlir::DictionaryAttr getAttributes();
};
} // namespace detail
template <typename RangeT>
class AllOfOpGenericAdaptor : public detail::AllOfOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AllOfOpGenericAdaptorBase;
public:
  AllOfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AllOfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AllOfOpGenericAdaptor(values, attrs, (properties ? *properties.as<::mlir::EmptyProperties *>() : ::mlir::EmptyProperties{}), regions) {}

  template <typename LateInst = AllOfOp, typename = std::enable_if_t<std::is_same_v<LateInst, AllOfOp>>>
  AllOfOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AllOfOpAdaptor : public AllOfOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AllOfOpGenericAdaptor::AllOfOpGenericAdaptor;
  AllOfOpAdaptor(AllOfOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class AllOfOp : public ::mlir::Op<AllOfOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::irdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<TypeOp, AttributeOp, OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::irdl::VerifyConstraintInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AllOfOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AllOfOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.all_of");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getArgs();
  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::TypedValue<::mlir::irdl::AttributeType> getOutput();
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  std::unique_ptr<::mlir::irdl::Constraint> getVerifier(::mlir::ArrayRef<Value> valueToConstr, ::mlir::DenseMap<::mlir::irdl::TypeOp,
          std::unique_ptr<::mlir::DynamicTypeDefinition>> const&types, ::mlir::DenseMap<::mlir::irdl::AttributeOp,
          std::unique_ptr<::mlir::DynamicAttrDefinition>> const&attrs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::AllOfOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::AnyOfOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class AnyOfOpGenericAdaptorBase {
public:
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  ::mlir::RegionRange odsRegions;
public:
  AnyOfOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {});

  AnyOfOpGenericAdaptorBase(AnyOfOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  ::mlir::DictionaryAttr getAttributes();
};
} // namespace detail
template <typename RangeT>
class AnyOfOpGenericAdaptor : public detail::AnyOfOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AnyOfOpGenericAdaptorBase;
public:
  AnyOfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AnyOfOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AnyOfOpGenericAdaptor(values, attrs, (properties ? *properties.as<::mlir::EmptyProperties *>() : ::mlir::EmptyProperties{}), regions) {}

  template <typename LateInst = AnyOfOp, typename = std::enable_if_t<std::is_same_v<LateInst, AnyOfOp>>>
  AnyOfOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AnyOfOpAdaptor : public AnyOfOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AnyOfOpGenericAdaptor::AnyOfOpGenericAdaptor;
  AnyOfOpAdaptor(AnyOfOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class AnyOfOp : public ::mlir::Op<AnyOfOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::irdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<TypeOp, AttributeOp, OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::irdl::VerifyConstraintInterface::Trait, ::mlir::OpTrait::SameOperandsAndResultType> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AnyOfOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AnyOfOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.any_of");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getArgs();
  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::TypedValue<::mlir::irdl::AttributeType> getOutput();
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  std::unique_ptr<::mlir::irdl::Constraint> getVerifier(::mlir::ArrayRef<Value> valueToConstr, ::mlir::DenseMap<::mlir::irdl::TypeOp,
          std::unique_ptr<::mlir::DynamicTypeDefinition>> const&types, ::mlir::DenseMap<::mlir::irdl::AttributeOp,
          std::unique_ptr<::mlir::DynamicAttrDefinition>> const&attrs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::AnyOfOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::AnyOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class AnyOpGenericAdaptorBase {
public:
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  ::mlir::RegionRange odsRegions;
public:
  AnyOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {});

  AnyOpGenericAdaptorBase(AnyOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  ::mlir::DictionaryAttr getAttributes();
};
} // namespace detail
template <typename RangeT>
class AnyOpGenericAdaptor : public detail::AnyOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AnyOpGenericAdaptorBase;
public:
  AnyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AnyOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AnyOpGenericAdaptor(values, attrs, (properties ? *properties.as<::mlir::EmptyProperties *>() : ::mlir::EmptyProperties{}), regions) {}

  template <typename LateInst = AnyOp, typename = std::enable_if_t<std::is_same_v<LateInst, AnyOp>>>
  AnyOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AnyOpAdaptor : public AnyOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AnyOpGenericAdaptor::AnyOpGenericAdaptor;
  AnyOpAdaptor(AnyOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class AnyOp : public ::mlir::Op<AnyOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::irdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<TypeOp, AttributeOp, OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::irdl::VerifyConstraintInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AnyOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AnyOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.any");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::TypedValue<::mlir::irdl::AttributeType> getOutput();
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  std::unique_ptr<::mlir::irdl::Constraint> getVerifier(::mlir::ArrayRef<Value> valueToConstr, ::mlir::DenseMap<::mlir::irdl::TypeOp,
          std::unique_ptr<::mlir::DynamicTypeDefinition>> const&types, ::mlir::DenseMap<::mlir::irdl::AttributeOp,
          std::unique_ptr<::mlir::DynamicAttrDefinition>> const&attrs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::AnyOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::AttributeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class AttributeOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AttributeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  AttributeOpGenericAdaptorBase(AttributeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  ::mlir::Region &getBody();
  ::mlir::RegionRange getRegions();
};
} // namespace detail
template <typename RangeT>
class AttributeOpGenericAdaptor : public detail::AttributeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AttributeOpGenericAdaptorBase;
public:
  AttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AttributeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AttributeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = AttributeOp, typename = std::enable_if_t<std::is_same_v<LateInst, AttributeOp>>>
  AttributeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AttributeOpAdaptor : public AttributeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AttributeOpGenericAdaptor::AttributeOpGenericAdaptor;
  AttributeOpAdaptor(AttributeOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class AttributeOp : public ::mlir::Op<AttributeOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<DialectOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AtMostOneChildOf<ParametersOp>::Impl, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AttributeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AttributeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.attribute");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::Region &getBody();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr);
  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::AttributeOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::AttributesOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class AttributesOpGenericAdaptorBase {
public:
  struct Properties {
    using attributeValueNamesTy = ::mlir::ArrayAttr;
    attributeValueNamesTy attributeValueNames;

    auto getAttributeValueNames() {
      auto &propStorage = this->attributeValueNames;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setAttributeValueNames(const ::mlir::ArrayAttr &propValue) {
      this->attributeValueNames = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.attributeValueNames == this->attributeValueNames &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  AttributesOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  AttributesOpGenericAdaptorBase(AttributesOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::ArrayAttr getAttributeValueNamesAttr();
  ::mlir::ArrayAttr getAttributeValueNames();
};
} // namespace detail
template <typename RangeT>
class AttributesOpGenericAdaptor : public detail::AttributesOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::AttributesOpGenericAdaptorBase;
public:
  AttributesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  AttributesOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : AttributesOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = AttributesOp, typename = std::enable_if_t<std::is_same_v<LateInst, AttributesOp>>>
  AttributesOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getAttributeValues() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class AttributesOpAdaptor : public AttributesOpGenericAdaptor<::mlir::ValueRange> {
public:
  using AttributesOpGenericAdaptor::AttributesOpGenericAdaptor;
  AttributesOpAdaptor(AttributesOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class AttributesOp : public ::mlir::Op<AttributesOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = AttributesOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = AttributesOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("attributeValueNames")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getAttributeValueNamesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getAttributeValueNamesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.attributes");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getAttributeValues();
  ::mlir::MutableOperandRange getAttributeValuesMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::ArrayAttr getAttributeValueNamesAttr();
  ::mlir::ArrayAttr getAttributeValueNames();
  void setAttributeValueNamesAttr(::mlir::ArrayAttr attr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange attributeValues, ::mlir::ArrayAttr attributeValueNames);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange attributeValues, ::mlir::ArrayAttr attributeValueNames);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::AttributesOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::BaseOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class BaseOpGenericAdaptorBase {
public:
  struct Properties {
    using base_nameTy = ::mlir::StringAttr;
    base_nameTy base_name;

    auto getBaseName() {
      auto &propStorage = this->base_name;
      return ::llvm::dyn_cast_or_null<::mlir::StringAttr>(propStorage);
    }
    void setBaseName(const ::mlir::StringAttr &propValue) {
      this->base_name = propValue;
    }
    using base_refTy = ::mlir::SymbolRefAttr;
    base_refTy base_ref;

    auto getBaseRef() {
      auto &propStorage = this->base_ref;
      return ::llvm::dyn_cast_or_null<::mlir::SymbolRefAttr>(propStorage);
    }
    void setBaseRef(const ::mlir::SymbolRefAttr &propValue) {
      this->base_ref = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.base_name == this->base_name &&
        rhs.base_ref == this->base_ref &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  BaseOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  BaseOpGenericAdaptorBase(BaseOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::SymbolRefAttr getBaseRefAttr();
  ::std::optional< ::mlir::SymbolRefAttr > getBaseRef();
  ::mlir::StringAttr getBaseNameAttr();
  ::std::optional< ::llvm::StringRef > getBaseName();
};
} // namespace detail
template <typename RangeT>
class BaseOpGenericAdaptor : public detail::BaseOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::BaseOpGenericAdaptorBase;
public:
  BaseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  BaseOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : BaseOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = BaseOp, typename = std::enable_if_t<std::is_same_v<LateInst, BaseOp>>>
  BaseOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class BaseOpAdaptor : public BaseOpGenericAdaptor<::mlir::ValueRange> {
public:
  using BaseOpGenericAdaptor::BaseOpGenericAdaptor;
  BaseOpAdaptor(BaseOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class BaseOp : public ::mlir::Op<BaseOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::irdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<TypeOp, AttributeOp, OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::irdl::VerifyConstraintInterface::Trait, ::mlir::SymbolUserOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = BaseOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = BaseOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("base_name"), ::llvm::StringRef("base_ref")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBaseNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBaseNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getBaseRefAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getBaseRefAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.base");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::TypedValue<::mlir::irdl::AttributeType> getOutput();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::SymbolRefAttr getBaseRefAttr();
  ::std::optional< ::mlir::SymbolRefAttr > getBaseRef();
  ::mlir::StringAttr getBaseNameAttr();
  ::std::optional< ::llvm::StringRef > getBaseName();
  void setBaseRefAttr(::mlir::SymbolRefAttr attr);
  void setBaseNameAttr(::mlir::StringAttr attr);
  void setBaseName(::std::optional<::llvm::StringRef> attrValue);
  ::mlir::Attribute removeBaseRefAttr();
  ::mlir::Attribute removeBaseNameAttr();
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, SymbolRefAttr base_ref);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, StringAttr base_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, /*optional*/::mlir::SymbolRefAttr base_ref, /*optional*/::mlir::StringAttr base_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, /*optional*/::mlir::SymbolRefAttr base_ref, /*optional*/::mlir::StringAttr base_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, /*optional*/::mlir::SymbolRefAttr base_ref, /*optional*/::mlir::StringAttr base_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verify();
  static ::mlir::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  std::unique_ptr<::mlir::irdl::Constraint> getVerifier(::mlir::ArrayRef<Value> valueToConstr, ::mlir::DenseMap<::mlir::irdl::TypeOp,
          std::unique_ptr<::mlir::DynamicTypeDefinition>> const&types, ::mlir::DenseMap<::mlir::irdl::AttributeOp,
          std::unique_ptr<::mlir::DynamicAttrDefinition>> const&attrs);
  ::mlir::LogicalResult verifySymbolUses(::mlir::SymbolTableCollection &symbolTable);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::BaseOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::CPredOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class CPredOpGenericAdaptorBase {
public:
  struct Properties {
    using predTy = ::mlir::StringAttr;
    predTy pred;

    auto getPred() {
      auto &propStorage = this->pred;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setPred(const ::mlir::StringAttr &propValue) {
      this->pred = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.pred == this->pred &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  CPredOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  CPredOpGenericAdaptorBase(CPredOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::StringAttr getPredAttr();
  ::llvm::StringRef getPred();
};
} // namespace detail
template <typename RangeT>
class CPredOpGenericAdaptor : public detail::CPredOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::CPredOpGenericAdaptorBase;
public:
  CPredOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  CPredOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : CPredOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = CPredOp, typename = std::enable_if_t<std::is_same_v<LateInst, CPredOp>>>
  CPredOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class CPredOpAdaptor : public CPredOpGenericAdaptor<::mlir::ValueRange> {
public:
  using CPredOpGenericAdaptor::CPredOpGenericAdaptor;
  CPredOpAdaptor(CPredOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class CPredOp : public ::mlir::Op<CPredOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::irdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = CPredOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = CPredOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("pred")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getPredAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getPredAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.c_pred");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::TypedValue<::mlir::irdl::AttributeType> getOutput();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getPredAttr();
  ::llvm::StringRef getPred();
  void setPredAttr(::mlir::StringAttr attr);
  void setPred(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::StringAttr pred);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr pred);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr pred);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::llvm::StringRef pred);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef pred);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef pred);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::CPredOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::DialectOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class DialectOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  DialectOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  DialectOpGenericAdaptorBase(DialectOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  ::mlir::Region &getBody();
  ::mlir::RegionRange getRegions();
};
} // namespace detail
template <typename RangeT>
class DialectOpGenericAdaptor : public detail::DialectOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::DialectOpGenericAdaptorBase;
public:
  DialectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  DialectOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : DialectOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = DialectOp, typename = std::enable_if_t<std::is_same_v<LateInst, DialectOp>>>
  DialectOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class DialectOpAdaptor : public DialectOpGenericAdaptor<::mlir::ValueRange> {
public:
  using DialectOpGenericAdaptor::DialectOpGenericAdaptor;
  DialectOpAdaptor(DialectOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class DialectOp : public ::mlir::Op<DialectOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::mlir::OpTrait::SymbolTable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = DialectOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = DialectOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.dialect");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::Region &getBody();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr);
  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::DialectOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::IsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class IsOpGenericAdaptorBase {
public:
  struct Properties {
    using expectedTy = ::mlir::Attribute;
    expectedTy expected;

    auto getExpected() {
      auto &propStorage = this->expected;
      return ::llvm::cast<::mlir::Attribute>(propStorage);
    }
    void setExpected(const ::mlir::Attribute &propValue) {
      this->expected = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.expected == this->expected &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  IsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  IsOpGenericAdaptorBase(IsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::Attribute getExpectedAttr();
  ::mlir::Attribute getExpected();
};
} // namespace detail
template <typename RangeT>
class IsOpGenericAdaptor : public detail::IsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::IsOpGenericAdaptorBase;
public:
  IsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  IsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : IsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = IsOp, typename = std::enable_if_t<std::is_same_v<LateInst, IsOp>>>
  IsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class IsOpAdaptor : public IsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using IsOpGenericAdaptor::IsOpGenericAdaptor;
  IsOpAdaptor(IsOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class IsOp : public ::mlir::Op<IsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::irdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<TypeOp, AttributeOp, OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::irdl::VerifyConstraintInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = IsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = IsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("expected")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getExpectedAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getExpectedAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.is");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::TypedValue<::mlir::irdl::AttributeType> getOutput();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::Attribute getExpectedAttr();
  ::mlir::Attribute getExpected();
  void setExpectedAttr(::mlir::Attribute attr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::Attribute expected);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Attribute expected);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Attribute expected);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  std::unique_ptr<::mlir::irdl::Constraint> getVerifier(::mlir::ArrayRef<Value> valueToConstr, ::mlir::DenseMap<::mlir::irdl::TypeOp,
          std::unique_ptr<::mlir::DynamicTypeDefinition>> const&types, ::mlir::DenseMap<::mlir::irdl::AttributeOp,
          std::unique_ptr<::mlir::DynamicAttrDefinition>> const&attrs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::IsOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::OperandsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class OperandsOpGenericAdaptorBase {
public:
  struct Properties {
    using variadicityTy = ::mlir::irdl::VariadicityArrayAttr;
    variadicityTy variadicity;

    auto getVariadicity() {
      auto &propStorage = this->variadicity;
      return ::llvm::cast<::mlir::irdl::VariadicityArrayAttr>(propStorage);
    }
    void setVariadicity(const ::mlir::irdl::VariadicityArrayAttr &propValue) {
      this->variadicity = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.variadicity == this->variadicity &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  OperandsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  OperandsOpGenericAdaptorBase(OperandsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::irdl::VariadicityArrayAttr getVariadicityAttr();
  ::llvm::ArrayRef<VariadicityAttr> getVariadicity();
};
} // namespace detail
template <typename RangeT>
class OperandsOpGenericAdaptor : public detail::OperandsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OperandsOpGenericAdaptorBase;
public:
  OperandsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OperandsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OperandsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = OperandsOp, typename = std::enable_if_t<std::is_same_v<LateInst, OperandsOp>>>
  OperandsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OperandsOpAdaptor : public OperandsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OperandsOpGenericAdaptor::OperandsOpGenericAdaptor;
  OperandsOpAdaptor(OperandsOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class OperandsOp : public ::mlir::Op<OperandsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OperandsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OperandsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("variadicity")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getVariadicityAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getVariadicityAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.operands");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getArgs();
  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::irdl::VariadicityArrayAttr getVariadicityAttr();
  ::llvm::ArrayRef<VariadicityAttr> getVariadicity();
  void setVariadicityAttr(::mlir::irdl::VariadicityArrayAttr attr);
  void setVariadicity(::llvm::ArrayRef<VariadicityAttr> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange args, ::mlir::irdl::VariadicityArrayAttr variadicity);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::irdl::VariadicityArrayAttr variadicity);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange args, ::llvm::ArrayRef<VariadicityAttr> variadicity);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::llvm::ArrayRef<VariadicityAttr> variadicity);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::OperandsOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::OperationOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class OperationOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  OperationOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  OperationOpGenericAdaptorBase(OperationOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  ::mlir::Region &getBody();
  ::mlir::RegionRange getRegions();
};
} // namespace detail
template <typename RangeT>
class OperationOpGenericAdaptor : public detail::OperationOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::OperationOpGenericAdaptorBase;
public:
  OperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  OperationOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : OperationOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = OperationOp, typename = std::enable_if_t<std::is_same_v<LateInst, OperationOp>>>
  OperationOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class OperationOpAdaptor : public OperationOpGenericAdaptor<::mlir::ValueRange> {
public:
  using OperationOpGenericAdaptor::OperationOpGenericAdaptor;
  OperationOpAdaptor(OperationOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class OperationOp : public ::mlir::Op<OperationOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<DialectOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AtMostOneChildOf<OperandsOp, ResultsOp, AttributesOp, RegionsOp>::Impl, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = OperationOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = OperationOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.operation");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::Region &getBody();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr);
  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::OperationOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::ParametersOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class ParametersOpGenericAdaptorBase {
public:
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  ::mlir::RegionRange odsRegions;
public:
  ParametersOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {});

  ParametersOpGenericAdaptorBase(ParametersOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  ::mlir::DictionaryAttr getAttributes();
};
} // namespace detail
template <typename RangeT>
class ParametersOpGenericAdaptor : public detail::ParametersOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ParametersOpGenericAdaptorBase;
public:
  ParametersOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ParametersOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ParametersOpGenericAdaptor(values, attrs, (properties ? *properties.as<::mlir::EmptyProperties *>() : ::mlir::EmptyProperties{}), regions) {}

  template <typename LateInst = ParametersOp, typename = std::enable_if_t<std::is_same_v<LateInst, ParametersOp>>>
  ParametersOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ParametersOpAdaptor : public ParametersOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ParametersOpGenericAdaptor::ParametersOpGenericAdaptor;
  ParametersOpAdaptor(ParametersOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class ParametersOp : public ::mlir::Op<ParametersOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<AttributeOp, TypeOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParametersOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParametersOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.parameters");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getArgs();
  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::ParametersOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::ParametricOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class ParametricOpGenericAdaptorBase {
public:
  struct Properties {
    using base_typeTy = ::mlir::SymbolRefAttr;
    base_typeTy base_type;

    auto getBaseType() {
      auto &propStorage = this->base_type;
      return ::llvm::cast<::mlir::SymbolRefAttr>(propStorage);
    }
    void setBaseType(const ::mlir::SymbolRefAttr &propValue) {
      this->base_type = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.base_type == this->base_type &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ParametricOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  ParametricOpGenericAdaptorBase(ParametricOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::SymbolRefAttr getBaseTypeAttr();
  ::mlir::SymbolRefAttr getBaseType();
};
} // namespace detail
template <typename RangeT>
class ParametricOpGenericAdaptor : public detail::ParametricOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ParametricOpGenericAdaptorBase;
public:
  ParametricOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ParametricOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ParametricOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = ParametricOp, typename = std::enable_if_t<std::is_same_v<LateInst, ParametricOp>>>
  ParametricOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ParametricOpAdaptor : public ParametricOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ParametricOpGenericAdaptor::ParametricOpGenericAdaptor;
  ParametricOpAdaptor(ParametricOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class ParametricOp : public ::mlir::Op<ParametricOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::irdl::AttributeType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<TypeOp, AttributeOp, OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::irdl::VerifyConstraintInterface::Trait, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ParametricOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ParametricOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("base_type")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getBaseTypeAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getBaseTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.parametric");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getArgs();
  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::TypedValue<::mlir::irdl::AttributeType> getOutput();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::SymbolRefAttr getBaseTypeAttr();
  ::mlir::SymbolRefAttr getBaseType();
  void setBaseTypeAttr(::mlir::SymbolRefAttr attr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::SymbolRefAttr base_type, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::SymbolRefAttr base_type, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::SymbolRefAttr base_type, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  std::unique_ptr<::mlir::irdl::Constraint> getVerifier(::mlir::ArrayRef<Value> valueToConstr, ::mlir::DenseMap<::mlir::irdl::TypeOp,
          std::unique_ptr<::mlir::DynamicTypeDefinition>> const&types, ::mlir::DenseMap<::mlir::irdl::AttributeOp,
          std::unique_ptr<::mlir::DynamicAttrDefinition>> const&attrs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::ParametricOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::RegionOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class RegionOpGenericAdaptorBase {
public:
  struct Properties {
    using constrainedArgumentsTy = ::mlir::UnitAttr;
    constrainedArgumentsTy constrainedArguments;

    auto getConstrainedArguments() {
      auto &propStorage = this->constrainedArguments;
      return ::llvm::dyn_cast_or_null<::mlir::UnitAttr>(propStorage);
    }
    void setConstrainedArguments(const ::mlir::UnitAttr &propValue) {
      this->constrainedArguments = propValue;
    }
    using numberOfBlocksTy = ::mlir::IntegerAttr;
    numberOfBlocksTy numberOfBlocks;

    auto getNumberOfBlocks() {
      auto &propStorage = this->numberOfBlocks;
      return ::llvm::dyn_cast_or_null<::mlir::IntegerAttr>(propStorage);
    }
    void setNumberOfBlocks(const ::mlir::IntegerAttr &propValue) {
      this->numberOfBlocks = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.constrainedArguments == this->constrainedArguments &&
        rhs.numberOfBlocks == this->numberOfBlocks &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  RegionOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  RegionOpGenericAdaptorBase(RegionOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::IntegerAttr getNumberOfBlocksAttr();
  ::std::optional<uint32_t> getNumberOfBlocks();
  ::mlir::UnitAttr getConstrainedArgumentsAttr();
  bool getConstrainedArguments();
};
} // namespace detail
template <typename RangeT>
class RegionOpGenericAdaptor : public detail::RegionOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RegionOpGenericAdaptorBase;
public:
  RegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RegionOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RegionOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = RegionOp, typename = std::enable_if_t<std::is_same_v<LateInst, RegionOp>>>
  RegionOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getEntryBlockArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RegionOpAdaptor : public RegionOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RegionOpGenericAdaptor::RegionOpGenericAdaptor;
  RegionOpAdaptor(RegionOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class RegionOp : public ::mlir::Op<RegionOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::OneResult, ::mlir::OpTrait::OneTypedResult<::mlir::irdl::RegionType>::Impl, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::irdl::VerifyRegionInterface::Trait, ::mlir::InferTypeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RegionOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RegionOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("constrainedArguments"), ::llvm::StringRef("numberOfBlocks")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getConstrainedArgumentsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getConstrainedArgumentsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getNumberOfBlocksAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getNumberOfBlocksAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.region");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getEntryBlockArgs();
  ::mlir::MutableOperandRange getEntryBlockArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::TypedValue<::mlir::irdl::RegionType> getOutput();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::IntegerAttr getNumberOfBlocksAttr();
  ::std::optional<uint32_t> getNumberOfBlocks();
  ::mlir::UnitAttr getConstrainedArgumentsAttr();
  bool getConstrainedArguments();
  void setNumberOfBlocksAttr(::mlir::IntegerAttr attr);
  void setNumberOfBlocks(::std::optional<uint32_t> attrValue);
  void setConstrainedArgumentsAttr(::mlir::UnitAttr attr);
  void setConstrainedArguments(bool attrValue);
  ::mlir::Attribute removeNumberOfBlocksAttr();
  ::mlir::Attribute removeConstrainedArgumentsAttr();
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::ValueRange entryBlockArgs, /*optional*/::mlir::IntegerAttr numberOfBlocks, /*optional*/::mlir::UnitAttr constrainedArguments);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange entryBlockArgs, /*optional*/::mlir::IntegerAttr numberOfBlocks, /*optional*/::mlir::UnitAttr constrainedArguments);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange entryBlockArgs, /*optional*/::mlir::IntegerAttr numberOfBlocks, /*optional*/::mlir::UnitAttr constrainedArguments);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type output, ::mlir::ValueRange entryBlockArgs, /*optional*/::mlir::IntegerAttr numberOfBlocks, /*optional*/bool constrainedArguments = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange entryBlockArgs, /*optional*/::mlir::IntegerAttr numberOfBlocks, /*optional*/bool constrainedArguments = false);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange entryBlockArgs, /*optional*/::mlir::IntegerAttr numberOfBlocks, /*optional*/bool constrainedArguments = false);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verify();
  static ::mlir::LogicalResult inferReturnTypes(::mlir::MLIRContext *context, ::std::optional<::mlir::Location> location, ::mlir::ValueRange operands, ::mlir::DictionaryAttr attributes, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions, ::llvm::SmallVectorImpl<::mlir::Type>&inferredReturnTypes);
  std::unique_ptr<::mlir::irdl::RegionConstraint> getVerifier(::mlir::ArrayRef<Value> valueToConstr, ::mlir::DenseMap<::mlir::irdl::TypeOp,
          std::unique_ptr<::mlir::DynamicTypeDefinition>> const&types, ::mlir::DenseMap<::mlir::irdl::AttributeOp,
          std::unique_ptr<::mlir::DynamicAttrDefinition>> const&attrs);
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::RegionOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::RegionsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class RegionsOpGenericAdaptorBase {
public:
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  ::mlir::RegionRange odsRegions;
public:
  RegionsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {});

  RegionsOpGenericAdaptorBase(RegionsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  ::mlir::DictionaryAttr getAttributes();
};
} // namespace detail
template <typename RangeT>
class RegionsOpGenericAdaptor : public detail::RegionsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::RegionsOpGenericAdaptorBase;
public:
  RegionsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  RegionsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : RegionsOpGenericAdaptor(values, attrs, (properties ? *properties.as<::mlir::EmptyProperties *>() : ::mlir::EmptyProperties{}), regions) {}

  template <typename LateInst = RegionsOp, typename = std::enable_if_t<std::is_same_v<LateInst, RegionsOp>>>
  RegionsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class RegionsOpAdaptor : public RegionsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using RegionsOpGenericAdaptor::RegionsOpGenericAdaptor;
  RegionsOpAdaptor(RegionsOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class RegionsOp : public ::mlir::Op<RegionsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<OperationOp>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = RegionsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = RegionsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.regions");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getArgs();
  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange args);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::RegionsOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::ResultsOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class ResultsOpGenericAdaptorBase {
public:
  struct Properties {
    using variadicityTy = ::mlir::irdl::VariadicityArrayAttr;
    variadicityTy variadicity;

    auto getVariadicity() {
      auto &propStorage = this->variadicity;
      return ::llvm::cast<::mlir::irdl::VariadicityArrayAttr>(propStorage);
    }
    void setVariadicity(const ::mlir::irdl::VariadicityArrayAttr &propValue) {
      this->variadicity = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.variadicity == this->variadicity &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  ResultsOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  ResultsOpGenericAdaptorBase(ResultsOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::irdl::VariadicityArrayAttr getVariadicityAttr();
  ::llvm::ArrayRef<VariadicityAttr> getVariadicity();
};
} // namespace detail
template <typename RangeT>
class ResultsOpGenericAdaptor : public detail::ResultsOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ResultsOpGenericAdaptorBase;
public:
  ResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ResultsOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ResultsOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = ResultsOp, typename = std::enable_if_t<std::is_same_v<LateInst, ResultsOp>>>
  ResultsOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getArgs() {
    return getODSOperands(0);
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class ResultsOpAdaptor : public ResultsOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ResultsOpGenericAdaptor::ResultsOpGenericAdaptor;
  ResultsOpAdaptor(ResultsOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class ResultsOp : public ::mlir::Op<ResultsOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<OperationOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ResultsOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ResultsOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("variadicity")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getVariadicityAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getVariadicityAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.results");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getArgs();
  ::mlir::MutableOperandRange getArgsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::irdl::VariadicityArrayAttr getVariadicityAttr();
  ::llvm::ArrayRef<VariadicityAttr> getVariadicity();
  void setVariadicityAttr(::mlir::irdl::VariadicityArrayAttr attr);
  void setVariadicity(::llvm::ArrayRef<VariadicityAttr> attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange args, ::mlir::irdl::VariadicityArrayAttr variadicity);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::mlir::irdl::VariadicityArrayAttr variadicity);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange args, ::llvm::ArrayRef<VariadicityAttr> variadicity);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange args, ::llvm::ArrayRef<VariadicityAttr> variadicity);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  ::mlir::LogicalResult verify();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::ResultsOp)

namespace mlir {
namespace irdl {

//===----------------------------------------------------------------------===//
// ::mlir::irdl::TypeOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class TypeOpGenericAdaptorBase {
public:
  struct Properties {
    using sym_nameTy = ::mlir::StringAttr;
    sym_nameTy sym_name;

    auto getSymName() {
      auto &propStorage = this->sym_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setSymName(const ::mlir::StringAttr &propValue) {
      this->sym_name = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.sym_name == this->sym_name &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TypeOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  TypeOpGenericAdaptorBase(TypeOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  ::mlir::Region &getBody();
  ::mlir::RegionRange getRegions();
};
} // namespace detail
template <typename RangeT>
class TypeOpGenericAdaptor : public detail::TypeOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TypeOpGenericAdaptorBase;
public:
  TypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TypeOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TypeOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = TypeOp, typename = std::enable_if_t<std::is_same_v<LateInst, TypeOp>>>
  TypeOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TypeOpAdaptor : public TypeOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TypeOpGenericAdaptor::TypeOpGenericAdaptor;
  TypeOpAdaptor(TypeOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class TypeOp : public ::mlir::Op<TypeOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<DialectOp>::Impl, ::mlir::OpTrait::NoTerminator, ::mlir::OpTrait::NoRegionArguments, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::AtMostOneChildOf<ParametersOp>::Impl, ::mlir::SymbolOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TypeOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TypeOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("irdl.type");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  ::mlir::Region &getBody();
  static ::mlir::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::mlir::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  void setSymNameAttr(::mlir::StringAttr attr);
  void setSymName(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 1 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace irdl
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::irdl::TypeOp)


#endif  // GET_OP_CLASSES

