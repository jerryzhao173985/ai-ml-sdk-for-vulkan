/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: VGFOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#if defined(GET_OP_CLASSES) || defined(GET_OP_FWD_DEFINES)
#undef GET_OP_FWD_DEFINES
namespace mlir {
namespace vgf {
class SegmentOp;
} // namespace vgf
} // namespace mlir
namespace mlir {
namespace vgf {
class SegmentOutputOp;
} // namespace vgf
} // namespace mlir
namespace mlir {
namespace vgf {
class SegmentRunOp;
} // namespace vgf
} // namespace mlir
namespace mlir {
namespace vgf {
class SequenceOp;
} // namespace vgf
} // namespace mlir
namespace mlir {
namespace vgf {
class SequenceOutputOp;
} // namespace vgf
} // namespace mlir
namespace mlir {
namespace vgf {
class ShaderPlaceholderOp;
} // namespace vgf
} // namespace mlir
#endif

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SegmentOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class SegmentOpGenericAdaptorBase {
public:
  struct Properties {
    using arg_attrsTy = ::mlir::ArrayAttr;
    arg_attrsTy arg_attrs;

    auto getArgAttrs() {
      auto &propStorage = this->arg_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgAttrs(const ::mlir::ArrayAttr &propValue) {
      this->arg_attrs = propValue;
    }
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using res_attrsTy = ::mlir::ArrayAttr;
    res_attrsTy res_attrs;

    auto getResAttrs() {
      auto &propStorage = this->res_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResAttrs(const ::mlir::ArrayAttr &propValue) {
      this->res_attrs = propValue;
    }
    using segment_typeTy = ::mlir::vgf::SegmentTypeEnumAttr;
    segment_typeTy segment_type;

    auto getSegmentType() {
      auto &propStorage = this->segment_type;
      return ::llvm::cast<::mlir::vgf::SegmentTypeEnumAttr>(propStorage);
    }
    void setSegmentType(const ::mlir::vgf::SegmentTypeEnumAttr &propValue) {
      this->segment_type = propValue;
    }
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
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.res_attrs == this->res_attrs &&
        rhs.segment_type == this->segment_type &&
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
  SegmentOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  SegmentOpGenericAdaptorBase(SegmentOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  ::mlir::vgf::SegmentTypeEnumAttr getSegmentTypeAttr();
  ::mlir::vgf::SegmentTypeEnum getSegmentType();
  ::mlir::TypeAttr getFunctionTypeAttr();
  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr();
  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr();
  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::Region &getBody();
  ::mlir::RegionRange getRegions();
};
} // namespace detail
template <typename RangeT>
class SegmentOpGenericAdaptor : public detail::SegmentOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SegmentOpGenericAdaptorBase;
public:
  SegmentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SegmentOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SegmentOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = SegmentOp, typename = std::enable_if_t<std::is_same_v<LateInst, SegmentOp>>>
  SegmentOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SegmentOpAdaptor : public SegmentOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SegmentOpGenericAdaptor::SegmentOpGenericAdaptor;
  SegmentOpAdaptor(SegmentOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class SegmentOp : public ::mlir::Op<SegmentOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::HasParent<SequenceOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::SymbolTable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SegmentOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SegmentOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("segment_type"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSegmentTypeAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSegmentTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vgf.segment");
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
  ::mlir::vgf::SegmentTypeEnumAttr getSegmentTypeAttr();
  ::mlir::vgf::SegmentTypeEnum getSegmentType();
  ::mlir::TypeAttr getFunctionTypeAttr();
  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr();
  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr();
  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  void setSymNameAttr(::mlir::StringAttr attr);
  void setSymName(::llvm::StringRef attrValue);
  void setSegmentTypeAttr(::mlir::vgf::SegmentTypeEnumAttr attr);
  void setSegmentType(::mlir::vgf::SegmentTypeEnum attrValue);
  void setFunctionTypeAttr(::mlir::TypeAttr attr);
  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr);
  void setResAttrsAttr(::mlir::ArrayAttr attr);
  ::mlir::Attribute removeArgAttrsAttr();
  ::mlir::Attribute removeResAttrsAttr();
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::vgf::SegmentTypeEnumAttr segment_type, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::vgf::SegmentTypeEnumAttr segment_type, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::vgf::SegmentTypeEnum segment_type, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::vgf::SegmentTypeEnum segment_type, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 5 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  /// CallableOpInterface
  Region *getCallableRegion() { return &getBody(); }
};
} // namespace vgf
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vgf::SegmentOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SegmentOutputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class SegmentOutputOpGenericAdaptorBase {
public:
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  ::mlir::RegionRange odsRegions;
public:
  SegmentOutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {});

  SegmentOutputOpGenericAdaptorBase(SegmentOutputOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  ::mlir::DictionaryAttr getAttributes();
};
} // namespace detail
template <typename RangeT>
class SegmentOutputOpGenericAdaptor : public detail::SegmentOutputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SegmentOutputOpGenericAdaptorBase;
public:
  SegmentOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SegmentOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SegmentOutputOpGenericAdaptor(values, attrs, (properties ? *properties.as<::mlir::EmptyProperties *>() : ::mlir::EmptyProperties{}), regions) {}

  template <typename LateInst = SegmentOutputOp, typename = std::enable_if_t<std::is_same_v<LateInst, SegmentOutputOp>>>
  SegmentOutputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return getODSOperands(0);
  }

private:
  RangeT odsOperands;
};
class SegmentOutputOpAdaptor : public SegmentOutputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SegmentOutputOpGenericAdaptor::SegmentOutputOpGenericAdaptor;
  SegmentOutputOpAdaptor(SegmentOutputOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class SegmentOutputOp : public ::mlir::Op<SegmentOutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<SegmentOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SegmentOutputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SegmentOutputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vgf.segment_output");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getOperands();
  ::mlir::MutableOperandRange getOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};
} // namespace vgf
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vgf::SegmentOutputOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SegmentRunOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class SegmentRunOpGenericAdaptorBase {
public:
  struct Properties {
    using segmentTy = ::mlir::SymbolRefAttr;
    segmentTy segment;

    auto getSegment() {
      auto &propStorage = this->segment;
      return ::llvm::cast<::mlir::SymbolRefAttr>(propStorage);
    }
    void setSegment(const ::mlir::SymbolRefAttr &propValue) {
      this->segment = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.segment == this->segment &&
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
  SegmentRunOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  SegmentRunOpGenericAdaptorBase(SegmentRunOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::SymbolRefAttr getSegmentAttr();
  ::mlir::SymbolRefAttr getSegment();
};
} // namespace detail
template <typename RangeT>
class SegmentRunOpGenericAdaptor : public detail::SegmentRunOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SegmentRunOpGenericAdaptorBase;
public:
  SegmentRunOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SegmentRunOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SegmentRunOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = SegmentRunOp, typename = std::enable_if_t<std::is_same_v<LateInst, SegmentRunOp>>>
  SegmentRunOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return getODSOperands(0);
  }

private:
  RangeT odsOperands;
};
class SegmentRunOpAdaptor : public SegmentRunOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SegmentRunOpGenericAdaptor::SegmentRunOpGenericAdaptor;
  SegmentRunOpAdaptor(SegmentRunOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class SegmentRunOp : public ::mlir::Op<SegmentRunOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<SequenceOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::CallOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SegmentRunOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SegmentRunOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("segment")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getSegmentAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getSegmentAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vgf.run_segment");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getOperands();
  ::mlir::MutableOperandRange getOperandsMutable();
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
  ::mlir::SymbolRefAttr getSegmentAttr();
  ::mlir::SymbolRefAttr getSegment();
  void setSegmentAttr(::mlir::SymbolRefAttr attr);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::mlir::SymbolRefAttr segment, ::mlir::ValueRange operands);
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
  operand_range getArgOperands() {
    return {operand_begin(), operand_end()};
  }

  MutableOperandRange getArgOperandsMutable() {
    return getOperandsMutable();
  }

  CallInterfaceCallable getCallableForCallee() {
    return (*this)->getAttrOfType<SymbolRefAttr>("segment");
  }

  void setCalleeFromCallable(CallInterfaceCallable segment) {
    (*this)->setAttr("segment", segment.get<SymbolRefAttr>());
  }

  ArrayAttr getArgAttrsAttr() { return {}; }
  ArrayAttr getResAttrsAttr() { return {}; }

  void setArgAttrsAttr(ArrayAttr attrs) {}
  void setResAttrsAttr(ArrayAttr attrs) {}

  Attribute removeArgAttrsAttr() { return {}; }
  Attribute removeResAttrsAttr() { return {}; }

};
} // namespace vgf
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vgf::SegmentRunOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SequenceOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class SequenceOpGenericAdaptorBase {
public:
  struct Properties {
    using arg_attrsTy = ::mlir::ArrayAttr;
    arg_attrsTy arg_attrs;

    auto getArgAttrs() {
      auto &propStorage = this->arg_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setArgAttrs(const ::mlir::ArrayAttr &propValue) {
      this->arg_attrs = propValue;
    }
    using function_typeTy = ::mlir::TypeAttr;
    function_typeTy function_type;

    auto getFunctionType() {
      auto &propStorage = this->function_type;
      return ::llvm::cast<::mlir::TypeAttr>(propStorage);
    }
    void setFunctionType(const ::mlir::TypeAttr &propValue) {
      this->function_type = propValue;
    }
    using res_attrsTy = ::mlir::ArrayAttr;
    res_attrsTy res_attrs;

    auto getResAttrs() {
      auto &propStorage = this->res_attrs;
      return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(propStorage);
    }
    void setResAttrs(const ::mlir::ArrayAttr &propValue) {
      this->res_attrs = propValue;
    }
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
        rhs.arg_attrs == this->arg_attrs &&
        rhs.function_type == this->function_type &&
        rhs.res_attrs == this->res_attrs &&
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
  SequenceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  SequenceOpGenericAdaptorBase(SequenceOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::StringAttr getSymNameAttr();
  ::llvm::StringRef getSymName();
  ::mlir::TypeAttr getFunctionTypeAttr();
  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr();
  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr();
  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  ::mlir::Region &getBody();
  ::mlir::RegionRange getRegions();
};
} // namespace detail
template <typename RangeT>
class SequenceOpGenericAdaptor : public detail::SequenceOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SequenceOpGenericAdaptorBase;
public:
  SequenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SequenceOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SequenceOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = SequenceOp, typename = std::enable_if_t<std::is_same_v<LateInst, SequenceOp>>>
  SequenceOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

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
class SequenceOpAdaptor : public SequenceOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SequenceOpGenericAdaptor::SequenceOpGenericAdaptor;
  SequenceOpAdaptor(SequenceOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class SequenceOp : public ::mlir::Op<SequenceOp, ::mlir::OpTrait::OneRegion, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::ZeroOperands, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::OpTrait::IsIsolatedFromAbove, ::mlir::SymbolOpInterface::Trait, ::mlir::CallableOpInterface::Trait, ::mlir::FunctionOpInterface::Trait, ::mlir::OpTrait::SymbolTable> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SequenceOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SequenceOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("arg_attrs"), ::llvm::StringRef("function_type"), ::llvm::StringRef("res_attrs"), ::llvm::StringRef("sym_name")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getArgAttrsAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getArgAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getFunctionTypeAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getFunctionTypeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getResAttrsAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getResAttrsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getSymNameAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getSymNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vgf.sequence");
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
  ::mlir::TypeAttr getFunctionTypeAttr();
  ::mlir::FunctionType getFunctionType();
  ::mlir::ArrayAttr getArgAttrsAttr();
  ::std::optional< ::mlir::ArrayAttr > getArgAttrs();
  ::mlir::ArrayAttr getResAttrsAttr();
  ::std::optional< ::mlir::ArrayAttr > getResAttrs();
  void setSymNameAttr(::mlir::StringAttr attr);
  void setSymName(::llvm::StringRef attrValue);
  void setFunctionTypeAttr(::mlir::TypeAttr attr);
  void setFunctionType(::mlir::FunctionType attrValue);
  void setArgAttrsAttr(::mlir::ArrayAttr attr);
  void setResAttrsAttr(::mlir::ArrayAttr attr);
  ::mlir::Attribute removeArgAttrsAttr();
  ::mlir::Attribute removeResAttrsAttr();
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &p);
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 4 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
  /// Returns the argument types of this function.
  ArrayRef<Type> getArgumentTypes() { return getFunctionType().getInputs(); }

  /// Returns the result types of this function.
  ArrayRef<Type> getResultTypes() { return getFunctionType().getResults(); }

  /// CallableOpInterface
  Region *getCallableRegion() { return &getBody(); }
};
} // namespace vgf
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vgf::SequenceOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SequenceOutputOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class SequenceOutputOpGenericAdaptorBase {
public:
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  ::mlir::RegionRange odsRegions;
public:
  SequenceOutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {});

  SequenceOutputOpGenericAdaptorBase(SequenceOutputOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  ::mlir::DictionaryAttr getAttributes();
};
} // namespace detail
template <typename RangeT>
class SequenceOutputOpGenericAdaptor : public detail::SequenceOutputOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::SequenceOutputOpGenericAdaptorBase;
public:
  SequenceOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const ::mlir::EmptyProperties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  SequenceOutputOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : SequenceOutputOpGenericAdaptor(values, attrs, (properties ? *properties.as<::mlir::EmptyProperties *>() : ::mlir::EmptyProperties{}), regions) {}

  template <typename LateInst = SequenceOutputOp, typename = std::enable_if_t<std::is_same_v<LateInst, SequenceOutputOp>>>
  SequenceOutputOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return getODSOperands(0);
  }

private:
  RangeT odsOperands;
};
class SequenceOutputOpAdaptor : public SequenceOutputOpGenericAdaptor<::mlir::ValueRange> {
public:
  using SequenceOutputOpGenericAdaptor::SequenceOutputOpGenericAdaptor;
  SequenceOutputOpAdaptor(SequenceOutputOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class SequenceOutputOp : public ::mlir::Op<SequenceOutputOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<SequenceOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::ConditionallySpeculatable::Trait, ::mlir::OpTrait::AlwaysSpeculatableImplTrait, ::mlir::MemoryEffectOpInterface::Trait, ::mlir::OpTrait::IsTerminator> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = SequenceOutputOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = SequenceOutputOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vgf.sequence_output");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getOperands();
  ::mlir::MutableOperandRange getOperandsMutable();
  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index);
  ::mlir::Operation::result_range getODSResults(unsigned index);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  ::mlir::LogicalResult verifyInvariantsImpl();
  ::mlir::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
public:
};
} // namespace vgf
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vgf::SequenceOutputOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::ShaderPlaceholderOp declarations
//===----------------------------------------------------------------------===//

namespace detail {
class ShaderPlaceholderOpGenericAdaptorBase {
public:
  struct Properties {
    using entry_pointTy = ::mlir::StringAttr;
    entry_pointTy entry_point;

    auto getEntryPoint() {
      auto &propStorage = this->entry_point;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setEntryPoint(const ::mlir::StringAttr &propValue) {
      this->entry_point = propValue;
    }
    using input_bindingsTy = ::mlir::DenseI64ArrayAttr;
    input_bindingsTy input_bindings;

    auto getInputBindings() {
      auto &propStorage = this->input_bindings;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setInputBindings(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->input_bindings = propValue;
    }
    using input_descriptor_setTy = ::mlir::IntegerAttr;
    input_descriptor_setTy input_descriptor_set;

    auto getInputDescriptorSet() {
      auto &propStorage = this->input_descriptor_set;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setInputDescriptorSet(const ::mlir::IntegerAttr &propValue) {
      this->input_descriptor_set = propValue;
    }
    using input_vk_descriptor_typesTy = ::mlir::ArrayAttr;
    input_vk_descriptor_typesTy input_vk_descriptor_types;

    auto getInputVkDescriptorTypes() {
      auto &propStorage = this->input_vk_descriptor_types;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInputVkDescriptorTypes(const ::mlir::ArrayAttr &propValue) {
      this->input_vk_descriptor_types = propValue;
    }
    using input_vk_formatsTy = ::mlir::ArrayAttr;
    input_vk_formatsTy input_vk_formats;

    auto getInputVkFormats() {
      auto &propStorage = this->input_vk_formats;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setInputVkFormats(const ::mlir::ArrayAttr &propValue) {
      this->input_vk_formats = propValue;
    }
    using output_bindingsTy = ::mlir::DenseI64ArrayAttr;
    output_bindingsTy output_bindings;

    auto getOutputBindings() {
      auto &propStorage = this->output_bindings;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setOutputBindings(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->output_bindings = propValue;
    }
    using output_descriptor_setTy = ::mlir::IntegerAttr;
    output_descriptor_setTy output_descriptor_set;

    auto getOutputDescriptorSet() {
      auto &propStorage = this->output_descriptor_set;
      return ::llvm::cast<::mlir::IntegerAttr>(propStorage);
    }
    void setOutputDescriptorSet(const ::mlir::IntegerAttr &propValue) {
      this->output_descriptor_set = propValue;
    }
    using output_vk_descriptor_typesTy = ::mlir::ArrayAttr;
    output_vk_descriptor_typesTy output_vk_descriptor_types;

    auto getOutputVkDescriptorTypes() {
      auto &propStorage = this->output_vk_descriptor_types;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setOutputVkDescriptorTypes(const ::mlir::ArrayAttr &propValue) {
      this->output_vk_descriptor_types = propValue;
    }
    using output_vk_formatsTy = ::mlir::ArrayAttr;
    output_vk_formatsTy output_vk_formats;

    auto getOutputVkFormats() {
      auto &propStorage = this->output_vk_formats;
      return ::llvm::cast<::mlir::ArrayAttr>(propStorage);
    }
    void setOutputVkFormats(const ::mlir::ArrayAttr &propValue) {
      this->output_vk_formats = propValue;
    }
    using shader_codeTy = ::mlir::DenseI32ArrayAttr;
    shader_codeTy shader_code;

    auto getShaderCode() {
      auto &propStorage = this->shader_code;
      return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(propStorage);
    }
    void setShaderCode(const ::mlir::DenseI32ArrayAttr &propValue) {
      this->shader_code = propValue;
    }
    using shader_nameTy = ::mlir::StringAttr;
    shader_nameTy shader_name;

    auto getShaderName() {
      auto &propStorage = this->shader_name;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setShaderName(const ::mlir::StringAttr &propValue) {
      this->shader_name = propValue;
    }
    using workgroup_sizesTy = ::mlir::DenseI64ArrayAttr;
    workgroup_sizesTy workgroup_sizes;

    auto getWorkgroupSizes() {
      auto &propStorage = this->workgroup_sizes;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setWorkgroupSizes(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->workgroup_sizes = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.entry_point == this->entry_point &&
        rhs.input_bindings == this->input_bindings &&
        rhs.input_descriptor_set == this->input_descriptor_set &&
        rhs.input_vk_descriptor_types == this->input_vk_descriptor_types &&
        rhs.input_vk_formats == this->input_vk_formats &&
        rhs.output_bindings == this->output_bindings &&
        rhs.output_descriptor_set == this->output_descriptor_set &&
        rhs.output_vk_descriptor_types == this->output_vk_descriptor_types &&
        rhs.output_vk_formats == this->output_vk_formats &&
        rhs.shader_code == this->shader_code &&
        rhs.shader_name == this->shader_name &&
        rhs.workgroup_sizes == this->workgroup_sizes &&
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
  ShaderPlaceholderOpGenericAdaptorBase(::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {});

  ShaderPlaceholderOpGenericAdaptorBase(ShaderPlaceholderOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize);
  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes();
  ::mlir::StringAttr getShaderNameAttr();
  ::llvm::StringRef getShaderName();
  ::mlir::StringAttr getEntryPointAttr();
  ::llvm::StringRef getEntryPoint();
  ::mlir::DenseI64ArrayAttr getInputBindingsAttr();
  ::llvm::ArrayRef<int64_t> getInputBindings();
  ::mlir::DenseI64ArrayAttr getOutputBindingsAttr();
  ::llvm::ArrayRef<int64_t> getOutputBindings();
  ::mlir::IntegerAttr getInputDescriptorSetAttr();
  uint64_t getInputDescriptorSet();
  ::mlir::IntegerAttr getOutputDescriptorSetAttr();
  uint64_t getOutputDescriptorSet();
  ::mlir::ArrayAttr getInputVkDescriptorTypesAttr();
  ::mlir::ArrayAttr getInputVkDescriptorTypes();
  ::mlir::ArrayAttr getOutputVkDescriptorTypesAttr();
  ::mlir::ArrayAttr getOutputVkDescriptorTypes();
  ::mlir::ArrayAttr getInputVkFormatsAttr();
  ::mlir::ArrayAttr getInputVkFormats();
  ::mlir::ArrayAttr getOutputVkFormatsAttr();
  ::mlir::ArrayAttr getOutputVkFormats();
  ::mlir::DenseI64ArrayAttr getWorkgroupSizesAttr();
  ::llvm::ArrayRef<int64_t> getWorkgroupSizes();
  ::mlir::DenseI32ArrayAttr getShaderCodeAttr();
  ::std::optional<::llvm::ArrayRef<int32_t>> getShaderCode();
};
} // namespace detail
template <typename RangeT>
class ShaderPlaceholderOpGenericAdaptor : public detail::ShaderPlaceholderOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::ShaderPlaceholderOpGenericAdaptorBase;
public:
  ShaderPlaceholderOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr, const Properties &properties = {}, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  ShaderPlaceholderOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : ShaderPlaceholderOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  template <typename LateInst = ShaderPlaceholderOp, typename = std::enable_if_t<std::is_same_v<LateInst, ShaderPlaceholderOp>>>
  ShaderPlaceholderOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  RangeT getOperands() {
    return getODSOperands(0);
  }

private:
  RangeT odsOperands;
};
class ShaderPlaceholderOpAdaptor : public ShaderPlaceholderOpGenericAdaptor<::mlir::ValueRange> {
public:
  using ShaderPlaceholderOpGenericAdaptor::ShaderPlaceholderOpGenericAdaptor;
  ShaderPlaceholderOpAdaptor(ShaderPlaceholderOp op);

  ::mlir::LogicalResult verify(::mlir::Location loc);
};
class ShaderPlaceholderOp : public ::mlir::Op<ShaderPlaceholderOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::VariadicResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::VariadicOperands, ::mlir::OpTrait::HasParent<SegmentOp>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = ShaderPlaceholderOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = ShaderPlaceholderOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("entry_point"), ::llvm::StringRef("input_bindings"), ::llvm::StringRef("input_descriptor_set"), ::llvm::StringRef("input_vk_descriptor_types"), ::llvm::StringRef("input_vk_formats"), ::llvm::StringRef("output_bindings"), ::llvm::StringRef("output_descriptor_set"), ::llvm::StringRef("output_vk_descriptor_types"), ::llvm::StringRef("output_vk_formats"), ::llvm::StringRef("shader_code"), ::llvm::StringRef("shader_name"), ::llvm::StringRef("workgroup_sizes")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getEntryPointAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getEntryPointAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getInputBindingsAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getInputBindingsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  ::mlir::StringAttr getInputDescriptorSetAttrName() {
    return getAttributeNameForIndex(2);
  }

  static ::mlir::StringAttr getInputDescriptorSetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 2);
  }

  ::mlir::StringAttr getInputVkDescriptorTypesAttrName() {
    return getAttributeNameForIndex(3);
  }

  static ::mlir::StringAttr getInputVkDescriptorTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 3);
  }

  ::mlir::StringAttr getInputVkFormatsAttrName() {
    return getAttributeNameForIndex(4);
  }

  static ::mlir::StringAttr getInputVkFormatsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 4);
  }

  ::mlir::StringAttr getOutputBindingsAttrName() {
    return getAttributeNameForIndex(5);
  }

  static ::mlir::StringAttr getOutputBindingsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 5);
  }

  ::mlir::StringAttr getOutputDescriptorSetAttrName() {
    return getAttributeNameForIndex(6);
  }

  static ::mlir::StringAttr getOutputDescriptorSetAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 6);
  }

  ::mlir::StringAttr getOutputVkDescriptorTypesAttrName() {
    return getAttributeNameForIndex(7);
  }

  static ::mlir::StringAttr getOutputVkDescriptorTypesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 7);
  }

  ::mlir::StringAttr getOutputVkFormatsAttrName() {
    return getAttributeNameForIndex(8);
  }

  static ::mlir::StringAttr getOutputVkFormatsAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 8);
  }

  ::mlir::StringAttr getShaderCodeAttrName() {
    return getAttributeNameForIndex(9);
  }

  static ::mlir::StringAttr getShaderCodeAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 9);
  }

  ::mlir::StringAttr getShaderNameAttrName() {
    return getAttributeNameForIndex(10);
  }

  static ::mlir::StringAttr getShaderNameAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 10);
  }

  ::mlir::StringAttr getWorkgroupSizesAttrName() {
    return getAttributeNameForIndex(11);
  }

  static ::mlir::StringAttr getWorkgroupSizesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 11);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("vgf.shader_placeholder");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index);
  ::mlir::Operation::operand_range getODSOperands(unsigned index);
  ::mlir::Operation::operand_range getOperands();
  ::mlir::MutableOperandRange getOperandsMutable();
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
  ::mlir::StringAttr getShaderNameAttr();
  ::llvm::StringRef getShaderName();
  ::mlir::StringAttr getEntryPointAttr();
  ::llvm::StringRef getEntryPoint();
  ::mlir::DenseI64ArrayAttr getInputBindingsAttr();
  ::llvm::ArrayRef<int64_t> getInputBindings();
  ::mlir::DenseI64ArrayAttr getOutputBindingsAttr();
  ::llvm::ArrayRef<int64_t> getOutputBindings();
  ::mlir::IntegerAttr getInputDescriptorSetAttr();
  uint64_t getInputDescriptorSet();
  ::mlir::IntegerAttr getOutputDescriptorSetAttr();
  uint64_t getOutputDescriptorSet();
  ::mlir::ArrayAttr getInputVkDescriptorTypesAttr();
  ::mlir::ArrayAttr getInputVkDescriptorTypes();
  ::mlir::ArrayAttr getOutputVkDescriptorTypesAttr();
  ::mlir::ArrayAttr getOutputVkDescriptorTypes();
  ::mlir::ArrayAttr getInputVkFormatsAttr();
  ::mlir::ArrayAttr getInputVkFormats();
  ::mlir::ArrayAttr getOutputVkFormatsAttr();
  ::mlir::ArrayAttr getOutputVkFormats();
  ::mlir::DenseI64ArrayAttr getWorkgroupSizesAttr();
  ::llvm::ArrayRef<int64_t> getWorkgroupSizes();
  ::mlir::DenseI32ArrayAttr getShaderCodeAttr();
  ::std::optional<::llvm::ArrayRef<int32_t>> getShaderCode();
  void setShaderNameAttr(::mlir::StringAttr attr);
  void setShaderName(::llvm::StringRef attrValue);
  void setEntryPointAttr(::mlir::StringAttr attr);
  void setEntryPoint(::llvm::StringRef attrValue);
  void setInputBindingsAttr(::mlir::DenseI64ArrayAttr attr);
  void setInputBindings(::llvm::ArrayRef<int64_t> attrValue);
  void setOutputBindingsAttr(::mlir::DenseI64ArrayAttr attr);
  void setOutputBindings(::llvm::ArrayRef<int64_t> attrValue);
  void setInputDescriptorSetAttr(::mlir::IntegerAttr attr);
  void setInputDescriptorSet(uint64_t attrValue);
  void setOutputDescriptorSetAttr(::mlir::IntegerAttr attr);
  void setOutputDescriptorSet(uint64_t attrValue);
  void setInputVkDescriptorTypesAttr(::mlir::ArrayAttr attr);
  void setOutputVkDescriptorTypesAttr(::mlir::ArrayAttr attr);
  void setInputVkFormatsAttr(::mlir::ArrayAttr attr);
  void setOutputVkFormatsAttr(::mlir::ArrayAttr attr);
  void setWorkgroupSizesAttr(::mlir::DenseI64ArrayAttr attr);
  void setWorkgroupSizes(::llvm::ArrayRef<int64_t> attrValue);
  void setShaderCodeAttr(::mlir::DenseI32ArrayAttr attr);
  void setShaderCode(::std::optional<::llvm::ArrayRef<int32_t>> attrValue);
  ::mlir::Attribute removeShaderCodeAttr();
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::mlir::StringAttr shader_name, ::mlir::StringAttr entry_point, ::mlir::DenseI64ArrayAttr input_bindings, ::mlir::DenseI64ArrayAttr output_bindings, ::mlir::IntegerAttr input_descriptor_set, ::mlir::IntegerAttr output_descriptor_set, ::mlir::ArrayAttr input_vk_descriptor_types, ::mlir::ArrayAttr output_vk_descriptor_types, ::mlir::ArrayAttr input_vk_formats, ::mlir::ArrayAttr output_vk_formats, ::mlir::DenseI64ArrayAttr workgroup_sizes, /*optional*/::mlir::DenseI32ArrayAttr shader_code, ::mlir::ValueRange operands);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::llvm::StringRef shader_name, ::llvm::StringRef entry_point, ::llvm::ArrayRef<int64_t> input_bindings, ::llvm::ArrayRef<int64_t> output_bindings, uint64_t input_descriptor_set, uint64_t output_descriptor_set, ::mlir::ArrayAttr input_vk_descriptor_types, ::mlir::ArrayAttr output_vk_descriptor_types, ::mlir::ArrayAttr input_vk_formats, ::mlir::ArrayAttr output_vk_formats, ::llvm::ArrayRef<int64_t> workgroup_sizes, /*optional*/::mlir::DenseI32ArrayAttr shader_code, ::mlir::ValueRange operands);
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
    assert(index < 12 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};
} // namespace vgf
} // namespace mlir
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::vgf::ShaderPlaceholderOp)


#endif  // GET_OP_CLASSES

