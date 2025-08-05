/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: VGFOps.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::mlir::vgf::SegmentOp,
::mlir::vgf::SegmentOutputOp,
::mlir::vgf::SegmentRunOp,
::mlir::vgf::SequenceOp,
::mlir::vgf::SequenceOutputOp,
::mlir::vgf::ShaderPlaceholderOp
#endif  // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//

namespace mlir {
namespace vgf {

static ::mlir::LogicalResult __mlir_ods_local_type_constraint_VGFOps0(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((true))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be variadic of any type, but got " << type;
  }
  return ::mlir::success();
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps0(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps0(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps0(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::vgf::SegmentTypeEnumAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Type of segment";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::TypeAttr>(attr))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(attr).getValue())))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: type attribute of function type";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps3(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: Array of dictionary attributes";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps3(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps3(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps4(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::SymbolRefAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: symbol reference attribute";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps4(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps4(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps5(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: i64 dense array attribute";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps5(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps5(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps6(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::IntegerAttr>(attr))) && ((::llvm::cast<::mlir::IntegerAttr>(attr).getType().isSignlessInteger(64)))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: 64-bit signless integer attribute";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps6(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps6(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps7(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !(((::llvm::isa<::mlir::ArrayAttr>(attr))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(attr), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string array attribute";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps7(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps7(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps8(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DenseI32ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: i32 dense array attribute";
  return ::mlir::success();
}
static ::mlir::LogicalResult __mlir_ods_local_attr_constraint_VGFOps8(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_VGFOps8(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::mlir::LogicalResult __mlir_ods_local_region_constraint_VGFOps0(
    ::mlir::Operation *op, ::mlir::Region &region, ::llvm::StringRef regionName,
    unsigned regionIndex) {
  if (!((true))) {
    return op->emitOpError("region #") << regionIndex
        << (regionName.empty() ? " " : " ('" + regionName + "') ")
        << "failed to verify constraint: any region";
  }
  return ::mlir::success();
}
} // namespace vgf
} // namespace mlir
namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SegmentOp definitions
//===----------------------------------------------------------------------===//

namespace detail {
SegmentOpGenericAdaptorBase::SegmentOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("vgf.segment", odsAttrs.getContext());
}

SegmentOpGenericAdaptorBase::SegmentOpGenericAdaptorBase(SegmentOp op) : SegmentOpGenericAdaptorBase(op->getDiscardableAttrDictionary(), op.getProperties(), op->getRegions()) {}

std::pair<unsigned, unsigned> SegmentOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  return {index, 1};
}

::mlir::DictionaryAttr SegmentOpGenericAdaptorBase::getAttributes() {
  return odsAttrs;
}

::mlir::StringAttr SegmentOpGenericAdaptorBase::getSymNameAttr() {
  auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  return attr;
}

::llvm::StringRef SegmentOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::vgf::SegmentTypeEnumAttr SegmentOpGenericAdaptorBase::getSegmentTypeAttr() {
  auto attr = ::llvm::cast<::mlir::vgf::SegmentTypeEnumAttr>(getProperties().segment_type);
  return attr;
}

::mlir::vgf::SegmentTypeEnum SegmentOpGenericAdaptorBase::getSegmentType() {
  auto attr = getSegmentTypeAttr();
  return attr.getValue();
}

::mlir::TypeAttr SegmentOpGenericAdaptorBase::getFunctionTypeAttr() {
  auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  return attr;
}

::mlir::FunctionType SegmentOpGenericAdaptorBase::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::mlir::ArrayAttr SegmentOpGenericAdaptorBase::getArgAttrsAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  return attr;
}

::std::optional< ::mlir::ArrayAttr > SegmentOpGenericAdaptorBase::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr SegmentOpGenericAdaptorBase::getResAttrsAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  return attr;
}

::std::optional< ::mlir::ArrayAttr > SegmentOpGenericAdaptorBase::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::Region &SegmentOpGenericAdaptorBase::getBody() {
  return *odsRegions[0];
}

::mlir::RegionRange SegmentOpGenericAdaptorBase::getRegions() {
  return odsRegions;
}

} // namespace detail
SegmentOpAdaptor::SegmentOpAdaptor(SegmentOp op) : SegmentOpGenericAdaptor(op->getOperands(), op) {}

::mlir::LogicalResult SegmentOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitError(loc, "'vgf.segment' op ""requires attribute 'function_type'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;
  auto tblgen_segment_type = getProperties().segment_type; (void)tblgen_segment_type;
  if (!tblgen_segment_type) return emitError(loc, "'vgf.segment' op ""requires attribute 'segment_type'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'vgf.segment' op ""requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'vgf.segment' op ""attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_segment_type && !((::llvm::isa<::mlir::vgf::SegmentTypeEnumAttr>(tblgen_segment_type))))
    return emitError(loc, "'vgf.segment' op ""attribute 'segment_type' failed to satisfy constraint: Type of segment");

  if (tblgen_function_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_function_type))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue())))))
    return emitError(loc, "'vgf.segment' op ""attribute 'function_type' failed to satisfy constraint: type attribute of function type");

  if (tblgen_arg_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_arg_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_arg_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'vgf.segment' op ""attribute 'arg_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_res_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_res_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_res_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'vgf.segment' op ""attribute 'res_attrs' failed to satisfy constraint: Array of dictionary attributes");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SegmentOp::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::operand_range SegmentOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

std::pair<unsigned, unsigned> SegmentOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range SegmentOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::Region &SegmentOp::getBody() {
  return (*this)->getRegion(0);
}

::mlir::LogicalResult SegmentOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.arg_attrs;
       auto attr = dict.get("arg_attrs");
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for arg_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `arg_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.function_type;
       auto attr = dict.get("function_type");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for function_type in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `function_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.res_attrs;
       auto attr = dict.get("res_attrs");
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for res_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `res_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.segment_type;
       auto attr = dict.get("segment_type");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for segment_type in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `segment_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sym_name;
       auto attr = dict.get("sym_name");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for sym_name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SegmentOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.arg_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("arg_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.function_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("function_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.res_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("res_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.segment_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("segment_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SegmentOp::computePropertiesHash(const Properties &prop) {
  return llvm::hash_combine(
    llvm::hash_value(prop.arg_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.function_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.res_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.segment_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SegmentOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "arg_attrs")
      return prop.arg_attrs;

    if (name == "function_type")
      return prop.function_type;

    if (name == "res_attrs")
      return prop.res_attrs;

    if (name == "segment_type")
      return prop.segment_type;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SegmentOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "arg_attrs") {
       prop.arg_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.arg_attrs)>>(value);
       return;
    }

    if (name == "function_type") {
       prop.function_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.function_type)>>(value);
       return;
    }

    if (name == "res_attrs") {
       prop.res_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.res_attrs)>>(value);
       return;
    }

    if (name == "segment_type") {
       prop.segment_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.segment_type)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SegmentOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.arg_attrs) attrs.append("arg_attrs", prop.arg_attrs);

    if (prop.function_type) attrs.append("function_type", prop.function_type);

    if (prop.res_attrs) attrs.append("res_attrs", prop.res_attrs);

    if (prop.segment_type) attrs.append("segment_type", prop.segment_type);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::mlir::LogicalResult SegmentOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps3(attr, "arg_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFunctionTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps2(attr, "function_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps3(attr, "res_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSegmentTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps1(attr, "segment_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps0(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::mlir::LogicalResult SegmentOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.arg_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.function_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.res_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.segment_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SegmentOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.arg_attrs);
  writer.writeAttribute(prop.function_type);

  writer.writeOptionalAttribute(prop.res_attrs);
  writer.writeAttribute(prop.segment_type);
  writer.writeAttribute(prop.sym_name);
}

::mlir::StringAttr SegmentOp::getSymNameAttr() {
  return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
}

::llvm::StringRef SegmentOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::vgf::SegmentTypeEnumAttr SegmentOp::getSegmentTypeAttr() {
  return ::llvm::cast<::mlir::vgf::SegmentTypeEnumAttr>(getProperties().segment_type);
}

::mlir::vgf::SegmentTypeEnum SegmentOp::getSegmentType() {
  auto attr = getSegmentTypeAttr();
  return attr.getValue();
}

::mlir::TypeAttr SegmentOp::getFunctionTypeAttr() {
  return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
}

::mlir::FunctionType SegmentOp::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::mlir::ArrayAttr SegmentOp::getArgAttrsAttr() {
  return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
}

::std::optional< ::mlir::ArrayAttr > SegmentOp::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr SegmentOp::getResAttrsAttr() {
  return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
}

::std::optional< ::mlir::ArrayAttr > SegmentOp::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void SegmentOp::setSymNameAttr(::mlir::StringAttr attr) {
  (*this)->setAttr(getSymNameAttrName(), attr);
}

void SegmentOp::setSymName(::llvm::StringRef attrValue) {
  (*this)->setAttr(getSymNameAttrName(), ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue));
}

void SegmentOp::setSegmentTypeAttr(::mlir::vgf::SegmentTypeEnumAttr attr) {
  (*this)->setAttr(getSegmentTypeAttrName(), attr);
}

void SegmentOp::setSegmentType(::mlir::vgf::SegmentTypeEnum attrValue) {
  (*this)->setAttr(getSegmentTypeAttrName(), ::mlir::vgf::SegmentTypeEnumAttr::get(::mlir::Builder((*this)->getContext()).getContext(), attrValue));
}

void SegmentOp::setFunctionTypeAttr(::mlir::TypeAttr attr) {
  (*this)->setAttr(getFunctionTypeAttrName(), attr);
}

void SegmentOp::setFunctionType(::mlir::FunctionType attrValue) {
  (*this)->setAttr(getFunctionTypeAttrName(), ::mlir::TypeAttr::get(attrValue));
}

void SegmentOp::setArgAttrsAttr(::mlir::ArrayAttr attr) {
  (*this)->setAttr(getArgAttrsAttrName(), attr);
}

void SegmentOp::setResAttrsAttr(::mlir::ArrayAttr attr) {
  (*this)->setAttr(getResAttrsAttrName(), attr);
}

::mlir::Attribute SegmentOp::removeArgAttrsAttr() {
    auto &attr = getProperties().arg_attrs;
    attr = {};
    return attr;
}

::mlir::Attribute SegmentOp::removeResAttrsAttr() {
    auto &attr = getProperties().res_attrs;
    attr = {};
    return attr;
}

void SegmentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::vgf::SegmentTypeEnumAttr segment_type, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().segment_type = segment_type;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
}

void SegmentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::vgf::SegmentTypeEnumAttr segment_type, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().segment_type = segment_type;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void SegmentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::vgf::SegmentTypeEnum segment_type, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().segment_type = ::mlir::vgf::SegmentTypeEnumAttr::get(odsBuilder.getContext(), segment_type);
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
}

void SegmentOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::vgf::SegmentTypeEnum segment_type, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().segment_type = ::mlir::vgf::SegmentTypeEnumAttr::get(odsBuilder.getContext(), segment_type);
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void SegmentOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

::mlir::LogicalResult SegmentOp::verifyInvariantsImpl() {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitOpError("requires attribute 'function_type'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;
  auto tblgen_segment_type = getProperties().segment_type; (void)tblgen_segment_type;
  if (!tblgen_segment_type) return emitOpError("requires attribute 'segment_type'");
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps0(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps1(*this, tblgen_segment_type, "segment_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps2(*this, tblgen_function_type, "function_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps3(*this, tblgen_arg_attrs, "arg_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps3(*this, tblgen_res_attrs, "res_attrs")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_VGFOps0(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::mlir::LogicalResult SegmentOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

} // namespace vgf
} // namespace mlir
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::vgf::SegmentOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SegmentOutputOp definitions
//===----------------------------------------------------------------------===//

namespace detail {
SegmentOutputOpGenericAdaptorBase::SegmentOutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const ::mlir::EmptyProperties &properties, ::mlir::RegionRange regions) : odsAttrs(attrs), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("vgf.segment_output", odsAttrs.getContext());
}

SegmentOutputOpGenericAdaptorBase::SegmentOutputOpGenericAdaptorBase(SegmentOutputOp op) : SegmentOutputOpGenericAdaptorBase(op->getAttrDictionary(), op.getProperties(), op->getRegions()) {}

std::pair<unsigned, unsigned> SegmentOutputOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::DictionaryAttr SegmentOutputOpGenericAdaptorBase::getAttributes() {
  return odsAttrs;
}

} // namespace detail
SegmentOutputOpAdaptor::SegmentOutputOpAdaptor(SegmentOutputOp op) : SegmentOutputOpGenericAdaptor(op->getOperands(), op) {}

::mlir::LogicalResult SegmentOutputOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SegmentOutputOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::Operation::operand_range SegmentOutputOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Operation::operand_range SegmentOutputOp::getOperands() {
  return getODSOperands(0);
}

::mlir::MutableOperandRange SegmentOutputOp::getOperandsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> SegmentOutputOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range SegmentOutputOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

void SegmentOutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
}

void SegmentOutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

::mlir::LogicalResult SegmentOutputOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_VGFOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult SegmentOutputOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SegmentOutputOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> operandsOperands;
  ::llvm::SMLoc operandsOperandsLoc;
  (void)operandsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> operandsTypes;

  operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(operandsOperands))
    return ::mlir::failure();
  if (!operandsOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(operandsTypes))
    return ::mlir::failure();
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
  }
  if (parser.resolveOperands(operandsOperands, operandsTypes, operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SegmentOutputOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (!getOperands().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getOperands();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getOperands().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SegmentOutputOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

} // namespace vgf
} // namespace mlir
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::vgf::SegmentOutputOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SegmentRunOp definitions
//===----------------------------------------------------------------------===//

namespace detail {
SegmentRunOpGenericAdaptorBase::SegmentRunOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("vgf.run_segment", odsAttrs.getContext());
}

SegmentRunOpGenericAdaptorBase::SegmentRunOpGenericAdaptorBase(SegmentRunOp op) : SegmentRunOpGenericAdaptorBase(op->getDiscardableAttrDictionary(), op.getProperties(), op->getRegions()) {}

std::pair<unsigned, unsigned> SegmentRunOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::DictionaryAttr SegmentRunOpGenericAdaptorBase::getAttributes() {
  return odsAttrs;
}

::mlir::SymbolRefAttr SegmentRunOpGenericAdaptorBase::getSegmentAttr() {
  auto attr = ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().segment);
  return attr;
}

::mlir::SymbolRefAttr SegmentRunOpGenericAdaptorBase::getSegment() {
  auto attr = getSegmentAttr();
  return attr;
}

} // namespace detail
SegmentRunOpAdaptor::SegmentRunOpAdaptor(SegmentRunOp op) : SegmentRunOpGenericAdaptor(op->getOperands(), op) {}

::mlir::LogicalResult SegmentRunOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_segment = getProperties().segment; (void)tblgen_segment;
  if (!tblgen_segment) return emitError(loc, "'vgf.run_segment' op ""requires attribute 'segment'");

  if (tblgen_segment && !((::llvm::isa<::mlir::SymbolRefAttr>(tblgen_segment))))
    return emitError(loc, "'vgf.run_segment' op ""attribute 'segment' failed to satisfy constraint: symbol reference attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SegmentRunOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::Operation::operand_range SegmentRunOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Operation::operand_range SegmentRunOp::getOperands() {
  return getODSOperands(0);
}

::mlir::MutableOperandRange SegmentRunOp::getOperandsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> SegmentRunOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::Operation::result_range SegmentRunOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::LogicalResult SegmentRunOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.segment;
       auto attr = dict.get("segment");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for segment in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `segment` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SegmentRunOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.segment;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("segment",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SegmentRunOp::computePropertiesHash(const Properties &prop) {
  return llvm::hash_combine(
    llvm::hash_value(prop.segment.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SegmentRunOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "segment")
      return prop.segment;
  return std::nullopt;
}

void SegmentRunOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "segment") {
       prop.segment = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.segment)>>(value);
       return;
    }
}

void SegmentRunOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.segment) attrs.append("segment", prop.segment);
}

::mlir::LogicalResult SegmentRunOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getSegmentAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps4(attr, "segment", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::mlir::LogicalResult SegmentRunOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.segment)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SegmentRunOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.segment);
}

::mlir::SymbolRefAttr SegmentRunOp::getSegmentAttr() {
  return ::llvm::cast<::mlir::SymbolRefAttr>(getProperties().segment);
}

::mlir::SymbolRefAttr SegmentRunOp::getSegment() {
  auto attr = getSegmentAttr();
  return attr;
}

void SegmentRunOp::setSegmentAttr(::mlir::SymbolRefAttr attr) {
  (*this)->setAttr(getSegmentAttrName(), attr);
}

void SegmentRunOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::mlir::SymbolRefAttr segment, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
  odsState.getOrAddProperties<Properties>().segment = segment;
  odsState.addTypes(resultType0);
}

void SegmentRunOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);
}

::mlir::LogicalResult SegmentRunOp::verifyInvariantsImpl() {
  auto tblgen_segment = getProperties().segment; (void)tblgen_segment;
  if (!tblgen_segment) return emitOpError("requires attribute 'segment'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps4(*this, tblgen_segment, "segment")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_VGFOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_VGFOps0(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult SegmentRunOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SegmentRunOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::SymbolRefAttr segmentAttr;
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> operandsOperands;
  ::llvm::SMLoc operandsOperandsLoc;
  (void)operandsOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> operandsTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;

  if (parser.parseCustomAttributeWithFallback(segmentAttr, parser.getBuilder().getType<::mlir::NoneType>())) {
    return ::mlir::failure();
  }
  if (segmentAttr) result.getOrAddProperties<SegmentRunOp::Properties>().segment = segmentAttr;
  if (::mlir::succeeded(parser.parseOptionalColon())) {
  if (parser.parseLParen())
    return ::mlir::failure();

  operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(operandsOperands))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();
  }

  ::mlir::FunctionType operands__allResult_functionType;
  if (parser.parseType(operands__allResult_functionType))
    return ::mlir::failure();
  operandsTypes = operands__allResult_functionType.getInputs();
  allResultTypes = operands__allResult_functionType.getResults();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(operandsOperands, operandsTypes, operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SegmentRunOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter.printAttributeWithoutType(getSegmentAttr());
  if (!getOperands().empty()) {
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ' << "(";
    _odsPrinter << getOperands();
    _odsPrinter << ")";
  }
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperands().getTypes(), getOperation()->getResultTypes());
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  elidedAttrs.push_back("segment");
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

} // namespace vgf
} // namespace mlir
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::vgf::SegmentRunOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SequenceOp definitions
//===----------------------------------------------------------------------===//

namespace detail {
SequenceOpGenericAdaptorBase::SequenceOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("vgf.sequence", odsAttrs.getContext());
}

SequenceOpGenericAdaptorBase::SequenceOpGenericAdaptorBase(SequenceOp op) : SequenceOpGenericAdaptorBase(op->getDiscardableAttrDictionary(), op.getProperties(), op->getRegions()) {}

std::pair<unsigned, unsigned> SequenceOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  return {index, 1};
}

::mlir::DictionaryAttr SequenceOpGenericAdaptorBase::getAttributes() {
  return odsAttrs;
}

::mlir::StringAttr SequenceOpGenericAdaptorBase::getSymNameAttr() {
  auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
  return attr;
}

::llvm::StringRef SequenceOpGenericAdaptorBase::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::TypeAttr SequenceOpGenericAdaptorBase::getFunctionTypeAttr() {
  auto attr = ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
  return attr;
}

::mlir::FunctionType SequenceOpGenericAdaptorBase::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::mlir::ArrayAttr SequenceOpGenericAdaptorBase::getArgAttrsAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
  return attr;
}

::std::optional< ::mlir::ArrayAttr > SequenceOpGenericAdaptorBase::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr SequenceOpGenericAdaptorBase::getResAttrsAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
  return attr;
}

::std::optional< ::mlir::ArrayAttr > SequenceOpGenericAdaptorBase::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::Region &SequenceOpGenericAdaptorBase::getBody() {
  return *odsRegions[0];
}

::mlir::RegionRange SequenceOpGenericAdaptorBase::getRegions() {
  return odsRegions;
}

} // namespace detail
SequenceOpAdaptor::SequenceOpAdaptor(SequenceOp op) : SequenceOpGenericAdaptor(op->getOperands(), op) {}

::mlir::LogicalResult SequenceOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitError(loc, "'vgf.sequence' op ""requires attribute 'function_type'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitError(loc, "'vgf.sequence' op ""requires attribute 'sym_name'");

  if (tblgen_sym_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_sym_name))))
    return emitError(loc, "'vgf.sequence' op ""attribute 'sym_name' failed to satisfy constraint: string attribute");

  if (tblgen_function_type && !(((::llvm::isa<::mlir::TypeAttr>(tblgen_function_type))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue()))) && ((::llvm::isa<::mlir::FunctionType>(::llvm::cast<::mlir::TypeAttr>(tblgen_function_type).getValue())))))
    return emitError(loc, "'vgf.sequence' op ""attribute 'function_type' failed to satisfy constraint: type attribute of function type");

  if (tblgen_arg_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_arg_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_arg_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'vgf.sequence' op ""attribute 'arg_attrs' failed to satisfy constraint: Array of dictionary attributes");

  if (tblgen_res_attrs && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_res_attrs))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_res_attrs), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::DictionaryAttr>(attr))); }))))
    return emitError(loc, "'vgf.sequence' op ""attribute 'res_attrs' failed to satisfy constraint: Array of dictionary attributes");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SequenceOp::getODSOperandIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::operand_range SequenceOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

std::pair<unsigned, unsigned> SequenceOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range SequenceOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::Region &SequenceOp::getBody() {
  return (*this)->getRegion(0);
}

::mlir::LogicalResult SequenceOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.arg_attrs;
       auto attr = dict.get("arg_attrs");
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for arg_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `arg_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.function_type;
       auto attr = dict.get("function_type");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for function_type in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `function_type` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.res_attrs;
       auto attr = dict.get("res_attrs");
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for res_attrs in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `res_attrs` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.sym_name;
       auto attr = dict.get("sym_name");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for sym_name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `sym_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute SequenceOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.arg_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("arg_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.function_type;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("function_type",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.res_attrs;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("res_attrs",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.sym_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("sym_name",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code SequenceOp::computePropertiesHash(const Properties &prop) {
  return llvm::hash_combine(
    llvm::hash_value(prop.arg_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.function_type.getAsOpaquePointer()), 
    llvm::hash_value(prop.res_attrs.getAsOpaquePointer()), 
    llvm::hash_value(prop.sym_name.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> SequenceOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "arg_attrs")
      return prop.arg_attrs;

    if (name == "function_type")
      return prop.function_type;

    if (name == "res_attrs")
      return prop.res_attrs;

    if (name == "sym_name")
      return prop.sym_name;
  return std::nullopt;
}

void SequenceOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "arg_attrs") {
       prop.arg_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.arg_attrs)>>(value);
       return;
    }

    if (name == "function_type") {
       prop.function_type = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.function_type)>>(value);
       return;
    }

    if (name == "res_attrs") {
       prop.res_attrs = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.res_attrs)>>(value);
       return;
    }

    if (name == "sym_name") {
       prop.sym_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.sym_name)>>(value);
       return;
    }
}

void SequenceOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.arg_attrs) attrs.append("arg_attrs", prop.arg_attrs);

    if (prop.function_type) attrs.append("function_type", prop.function_type);

    if (prop.res_attrs) attrs.append("res_attrs", prop.res_attrs);

    if (prop.sym_name) attrs.append("sym_name", prop.sym_name);
}

::mlir::LogicalResult SequenceOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getArgAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps3(attr, "arg_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getFunctionTypeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps2(attr, "function_type", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getResAttrsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps3(attr, "res_attrs", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getSymNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps0(attr, "sym_name", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::mlir::LogicalResult SequenceOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readOptionalAttribute(prop.arg_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.function_type)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.res_attrs)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.sym_name)))
    return ::mlir::failure();
  return ::mlir::success();
}

void SequenceOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;

  writer.writeOptionalAttribute(prop.arg_attrs);
  writer.writeAttribute(prop.function_type);

  writer.writeOptionalAttribute(prop.res_attrs);
  writer.writeAttribute(prop.sym_name);
}

::mlir::StringAttr SequenceOp::getSymNameAttr() {
  return ::llvm::cast<::mlir::StringAttr>(getProperties().sym_name);
}

::llvm::StringRef SequenceOp::getSymName() {
  auto attr = getSymNameAttr();
  return attr.getValue();
}

::mlir::TypeAttr SequenceOp::getFunctionTypeAttr() {
  return ::llvm::cast<::mlir::TypeAttr>(getProperties().function_type);
}

::mlir::FunctionType SequenceOp::getFunctionType() {
  auto attr = getFunctionTypeAttr();
  return ::llvm::cast<::mlir::FunctionType>(attr.getValue());
}

::mlir::ArrayAttr SequenceOp::getArgAttrsAttr() {
  return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().arg_attrs);
}

::std::optional< ::mlir::ArrayAttr > SequenceOp::getArgAttrs() {
  auto attr = getArgAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

::mlir::ArrayAttr SequenceOp::getResAttrsAttr() {
  return ::llvm::dyn_cast_or_null<::mlir::ArrayAttr>(getProperties().res_attrs);
}

::std::optional< ::mlir::ArrayAttr > SequenceOp::getResAttrs() {
  auto attr = getResAttrsAttr();
  return attr ? ::std::optional< ::mlir::ArrayAttr >(attr) : (::std::nullopt);
}

void SequenceOp::setSymNameAttr(::mlir::StringAttr attr) {
  (*this)->setAttr(getSymNameAttrName(), attr);
}

void SequenceOp::setSymName(::llvm::StringRef attrValue) {
  (*this)->setAttr(getSymNameAttrName(), ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue));
}

void SequenceOp::setFunctionTypeAttr(::mlir::TypeAttr attr) {
  (*this)->setAttr(getFunctionTypeAttrName(), attr);
}

void SequenceOp::setFunctionType(::mlir::FunctionType attrValue) {
  (*this)->setAttr(getFunctionTypeAttrName(), ::mlir::TypeAttr::get(attrValue));
}

void SequenceOp::setArgAttrsAttr(::mlir::ArrayAttr attr) {
  (*this)->setAttr(getArgAttrsAttrName(), attr);
}

void SequenceOp::setResAttrsAttr(::mlir::ArrayAttr attr) {
  (*this)->setAttr(getResAttrsAttrName(), attr);
}

::mlir::Attribute SequenceOp::removeArgAttrsAttr() {
    auto &attr = getProperties().arg_attrs;
    attr = {};
    return attr;
}

::mlir::Attribute SequenceOp::removeResAttrsAttr() {
    auto &attr = getProperties().res_attrs;
    attr = {};
    return attr;
}

void SequenceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
}

void SequenceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::StringAttr sym_name, ::mlir::TypeAttr function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().sym_name = sym_name;
  odsState.getOrAddProperties<Properties>().function_type = function_type;
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void SequenceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
}

void SequenceOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::llvm::StringRef sym_name, ::mlir::FunctionType function_type, /*optional*/::mlir::ArrayAttr arg_attrs, /*optional*/::mlir::ArrayAttr res_attrs) {
  odsState.getOrAddProperties<Properties>().sym_name = odsBuilder.getStringAttr(sym_name);
  odsState.getOrAddProperties<Properties>().function_type = ::mlir::TypeAttr::get(function_type);
  if (arg_attrs) {
    odsState.getOrAddProperties<Properties>().arg_attrs = arg_attrs;
  }
  if (res_attrs) {
    odsState.getOrAddProperties<Properties>().res_attrs = res_attrs;
  }
  (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

void SequenceOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 0u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  for (unsigned i = 0; i != 1; ++i)
    (void)odsState.addRegion();
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

::mlir::LogicalResult SequenceOp::verifyInvariantsImpl() {
  auto tblgen_arg_attrs = getProperties().arg_attrs; (void)tblgen_arg_attrs;
  auto tblgen_function_type = getProperties().function_type; (void)tblgen_function_type;
  if (!tblgen_function_type) return emitOpError("requires attribute 'function_type'");
  auto tblgen_res_attrs = getProperties().res_attrs; (void)tblgen_res_attrs;
  auto tblgen_sym_name = getProperties().sym_name; (void)tblgen_sym_name;
  if (!tblgen_sym_name) return emitOpError("requires attribute 'sym_name'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps0(*this, tblgen_sym_name, "sym_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps2(*this, tblgen_function_type, "function_type")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps3(*this, tblgen_arg_attrs, "arg_attrs")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps3(*this, tblgen_res_attrs, "res_attrs")))
    return ::mlir::failure();
  if (!(((*this->getOperation()).getParentOp()->hasTrait<OpTrait::SymbolTable>())))
    return emitOpError("failed to verify that ");
  {
    unsigned index = 0; (void)index;

    for (auto &region : ::llvm::MutableArrayRef((*this)->getRegion(0)))
      if (::mlir::failed(__mlir_ods_local_region_constraint_VGFOps0(*this, region, "body", index++)))
        return ::mlir::failure();
  }
  return ::mlir::success();
}

::mlir::LogicalResult SequenceOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

} // namespace vgf
} // namespace mlir
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::vgf::SequenceOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::SequenceOutputOp definitions
//===----------------------------------------------------------------------===//

namespace detail {
SequenceOutputOpGenericAdaptorBase::SequenceOutputOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const ::mlir::EmptyProperties &properties, ::mlir::RegionRange regions) : odsAttrs(attrs), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("vgf.sequence_output", odsAttrs.getContext());
}

SequenceOutputOpGenericAdaptorBase::SequenceOutputOpGenericAdaptorBase(SequenceOutputOp op) : SequenceOutputOpGenericAdaptorBase(op->getAttrDictionary(), op.getProperties(), op->getRegions()) {}

std::pair<unsigned, unsigned> SequenceOutputOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::DictionaryAttr SequenceOutputOpGenericAdaptorBase::getAttributes() {
  return odsAttrs;
}

} // namespace detail
SequenceOutputOpAdaptor::SequenceOutputOpAdaptor(SequenceOutputOp op) : SequenceOutputOpGenericAdaptor(op->getOperands(), op) {}

::mlir::LogicalResult SequenceOutputOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

std::pair<unsigned, unsigned> SequenceOutputOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::Operation::operand_range SequenceOutputOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Operation::operand_range SequenceOutputOp::getOperands() {
  return getODSOperands(0);
}

::mlir::MutableOperandRange SequenceOutputOp::getOperandsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> SequenceOutputOp::getODSResultIndexAndLength(unsigned index) {
  return {index, 1};
}

::mlir::Operation::result_range SequenceOutputOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

void SequenceOutputOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
}

void SequenceOutputOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

::mlir::LogicalResult SequenceOutputOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_VGFOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult SequenceOutputOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult SequenceOutputOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> operandsOperands;
  ::llvm::SMLoc operandsOperandsLoc;
  (void)operandsOperandsLoc;
  ::llvm::SmallVector<::mlir::Type, 1> operandsTypes;

  operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(operandsOperands))
    return ::mlir::failure();
  if (!operandsOperands.empty()) {
  if (parser.parseColon())
    return ::mlir::failure();

  if (parser.parseTypeList(operandsTypes))
    return ::mlir::failure();
  }
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
  }
  if (parser.resolveOperands(operandsOperands, operandsTypes, operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void SequenceOutputOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  if (!getOperands().empty()) {
    _odsPrinter << ' ';
    _odsPrinter << getOperands();
    _odsPrinter << ' ' << ":";
    _odsPrinter << ' ';
    _odsPrinter << getOperands().getTypes();
  }
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
}

void SequenceOutputOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
}

} // namespace vgf
} // namespace mlir
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::vgf::SequenceOutputOp)

namespace mlir {
namespace vgf {

//===----------------------------------------------------------------------===//
// ::mlir::vgf::ShaderPlaceholderOp definitions
//===----------------------------------------------------------------------===//

namespace detail {
ShaderPlaceholderOpGenericAdaptorBase::ShaderPlaceholderOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
    odsOpName.emplace("vgf.shader_placeholder", odsAttrs.getContext());
}

ShaderPlaceholderOpGenericAdaptorBase::ShaderPlaceholderOpGenericAdaptorBase(ShaderPlaceholderOp op) : ShaderPlaceholderOpGenericAdaptorBase(op->getDiscardableAttrDictionary(), op.getProperties(), op->getRegions()) {}

std::pair<unsigned, unsigned> ShaderPlaceholderOpGenericAdaptorBase::getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (odsOperandsSize - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::DictionaryAttr ShaderPlaceholderOpGenericAdaptorBase::getAttributes() {
  return odsAttrs;
}

::mlir::StringAttr ShaderPlaceholderOpGenericAdaptorBase::getShaderNameAttr() {
  auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().shader_name);
  return attr;
}

::llvm::StringRef ShaderPlaceholderOpGenericAdaptorBase::getShaderName() {
  auto attr = getShaderNameAttr();
  return attr.getValue();
}

::mlir::StringAttr ShaderPlaceholderOpGenericAdaptorBase::getEntryPointAttr() {
  auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().entry_point);
  return attr;
}

::llvm::StringRef ShaderPlaceholderOpGenericAdaptorBase::getEntryPoint() {
  auto attr = getEntryPointAttr();
  return attr.getValue();
}

::mlir::DenseI64ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getInputBindingsAttr() {
  auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().input_bindings);
  return attr;
}

::llvm::ArrayRef<int64_t> ShaderPlaceholderOpGenericAdaptorBase::getInputBindings() {
  auto attr = getInputBindingsAttr();
  return attr;
}

::mlir::DenseI64ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getOutputBindingsAttr() {
  auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().output_bindings);
  return attr;
}

::llvm::ArrayRef<int64_t> ShaderPlaceholderOpGenericAdaptorBase::getOutputBindings() {
  auto attr = getOutputBindingsAttr();
  return attr;
}

::mlir::IntegerAttr ShaderPlaceholderOpGenericAdaptorBase::getInputDescriptorSetAttr() {
  auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().input_descriptor_set);
  return attr;
}

uint64_t ShaderPlaceholderOpGenericAdaptorBase::getInputDescriptorSet() {
  auto attr = getInputDescriptorSetAttr();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr ShaderPlaceholderOpGenericAdaptorBase::getOutputDescriptorSetAttr() {
  auto attr = ::llvm::cast<::mlir::IntegerAttr>(getProperties().output_descriptor_set);
  return attr;
}

uint64_t ShaderPlaceholderOpGenericAdaptorBase::getOutputDescriptorSet() {
  auto attr = getOutputDescriptorSetAttr();
  return attr.getValue().getZExtValue();
}

::mlir::ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getInputVkDescriptorTypesAttr() {
  auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().input_vk_descriptor_types);
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getInputVkDescriptorTypes() {
  auto attr = getInputVkDescriptorTypesAttr();
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getOutputVkDescriptorTypesAttr() {
  auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().output_vk_descriptor_types);
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getOutputVkDescriptorTypes() {
  auto attr = getOutputVkDescriptorTypesAttr();
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getInputVkFormatsAttr() {
  auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().input_vk_formats);
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getInputVkFormats() {
  auto attr = getInputVkFormatsAttr();
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getOutputVkFormatsAttr() {
  auto attr = ::llvm::cast<::mlir::ArrayAttr>(getProperties().output_vk_formats);
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getOutputVkFormats() {
  auto attr = getOutputVkFormatsAttr();
  return attr;
}

::mlir::DenseI64ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getWorkgroupSizesAttr() {
  auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().workgroup_sizes);
  return attr;
}

::llvm::ArrayRef<int64_t> ShaderPlaceholderOpGenericAdaptorBase::getWorkgroupSizes() {
  auto attr = getWorkgroupSizesAttr();
  return attr;
}

::mlir::DenseI32ArrayAttr ShaderPlaceholderOpGenericAdaptorBase::getShaderCodeAttr() {
  auto attr = ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().shader_code);
  return attr;
}

::std::optional<::llvm::ArrayRef<int32_t>> ShaderPlaceholderOpGenericAdaptorBase::getShaderCode() {
  auto attr = getShaderCodeAttr();
  return attr ? ::std::optional<::llvm::ArrayRef<int32_t>>(attr) : (::std::nullopt);
}

} // namespace detail
ShaderPlaceholderOpAdaptor::ShaderPlaceholderOpAdaptor(ShaderPlaceholderOp op) : ShaderPlaceholderOpGenericAdaptor(op->getOperands(), op) {}

::mlir::LogicalResult ShaderPlaceholderOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_entry_point = getProperties().entry_point; (void)tblgen_entry_point;
  if (!tblgen_entry_point) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'entry_point'");
  auto tblgen_input_bindings = getProperties().input_bindings; (void)tblgen_input_bindings;
  if (!tblgen_input_bindings) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'input_bindings'");
  auto tblgen_input_descriptor_set = getProperties().input_descriptor_set; (void)tblgen_input_descriptor_set;
  if (!tblgen_input_descriptor_set) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'input_descriptor_set'");
  auto tblgen_input_vk_descriptor_types = getProperties().input_vk_descriptor_types; (void)tblgen_input_vk_descriptor_types;
  if (!tblgen_input_vk_descriptor_types) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'input_vk_descriptor_types'");
  auto tblgen_input_vk_formats = getProperties().input_vk_formats; (void)tblgen_input_vk_formats;
  if (!tblgen_input_vk_formats) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'input_vk_formats'");
  auto tblgen_output_bindings = getProperties().output_bindings; (void)tblgen_output_bindings;
  if (!tblgen_output_bindings) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'output_bindings'");
  auto tblgen_output_descriptor_set = getProperties().output_descriptor_set; (void)tblgen_output_descriptor_set;
  if (!tblgen_output_descriptor_set) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'output_descriptor_set'");
  auto tblgen_output_vk_descriptor_types = getProperties().output_vk_descriptor_types; (void)tblgen_output_vk_descriptor_types;
  if (!tblgen_output_vk_descriptor_types) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'output_vk_descriptor_types'");
  auto tblgen_output_vk_formats = getProperties().output_vk_formats; (void)tblgen_output_vk_formats;
  if (!tblgen_output_vk_formats) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'output_vk_formats'");
  auto tblgen_shader_code = getProperties().shader_code; (void)tblgen_shader_code;
  auto tblgen_shader_name = getProperties().shader_name; (void)tblgen_shader_name;
  if (!tblgen_shader_name) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'shader_name'");
  auto tblgen_workgroup_sizes = getProperties().workgroup_sizes; (void)tblgen_workgroup_sizes;
  if (!tblgen_workgroup_sizes) return emitError(loc, "'vgf.shader_placeholder' op ""requires attribute 'workgroup_sizes'");

  if (tblgen_shader_name && !((::llvm::isa<::mlir::StringAttr>(tblgen_shader_name))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'shader_name' failed to satisfy constraint: string attribute");

  if (tblgen_entry_point && !((::llvm::isa<::mlir::StringAttr>(tblgen_entry_point))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'entry_point' failed to satisfy constraint: string attribute");

  if (tblgen_input_bindings && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_input_bindings))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'input_bindings' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_output_bindings && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_output_bindings))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'output_bindings' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_input_descriptor_set && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_input_descriptor_set))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_input_descriptor_set).getType().isSignlessInteger(64)))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'input_descriptor_set' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_output_descriptor_set && !(((::llvm::isa<::mlir::IntegerAttr>(tblgen_output_descriptor_set))) && ((::llvm::cast<::mlir::IntegerAttr>(tblgen_output_descriptor_set).getType().isSignlessInteger(64)))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'output_descriptor_set' failed to satisfy constraint: 64-bit signless integer attribute");

  if (tblgen_input_vk_descriptor_types && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_input_vk_descriptor_types))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_input_vk_descriptor_types), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'input_vk_descriptor_types' failed to satisfy constraint: string array attribute");

  if (tblgen_output_vk_descriptor_types && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_output_vk_descriptor_types))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_output_vk_descriptor_types), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'output_vk_descriptor_types' failed to satisfy constraint: string array attribute");

  if (tblgen_input_vk_formats && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_input_vk_formats))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_input_vk_formats), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'input_vk_formats' failed to satisfy constraint: string array attribute");

  if (tblgen_output_vk_formats && !(((::llvm::isa<::mlir::ArrayAttr>(tblgen_output_vk_formats))) && (::llvm::all_of(::llvm::cast<::mlir::ArrayAttr>(tblgen_output_vk_formats), [&](::mlir::Attribute attr) { return attr && ((::llvm::isa<::mlir::StringAttr>(attr))); }))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'output_vk_formats' failed to satisfy constraint: string array attribute");

  if (tblgen_workgroup_sizes && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_workgroup_sizes))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'workgroup_sizes' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_shader_code && !((::llvm::isa<::mlir::DenseI32ArrayAttr>(tblgen_shader_code))))
    return emitError(loc, "'vgf.shader_placeholder' op ""attribute 'shader_code' failed to satisfy constraint: i32 dense array attribute");
  return ::mlir::success();
}

std::pair<unsigned, unsigned> ShaderPlaceholderOp::getODSOperandIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumOperands() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::Operation::operand_range ShaderPlaceholderOp::getODSOperands(unsigned index) {
  auto valueRange = getODSOperandIndexAndLength(index);
  return {std::next(getOperation()->operand_begin(), valueRange.first),
           std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
}

::mlir::Operation::operand_range ShaderPlaceholderOp::getOperands() {
  return getODSOperands(0);
}

::mlir::MutableOperandRange ShaderPlaceholderOp::getOperandsMutable() {
  auto range = getODSOperandIndexAndLength(0);
  auto mutableRange = ::mlir::MutableOperandRange(getOperation(), range.first, range.second);
  return mutableRange;
}

std::pair<unsigned, unsigned> ShaderPlaceholderOp::getODSResultIndexAndLength(unsigned index) {
  bool isVariadic[] = {true};
  int prevVariadicCount = 0;
  for (unsigned i = 0; i < index; ++i)
    if (isVariadic[i]) ++prevVariadicCount;

  // Calculate how many dynamic values a static variadic operand corresponds to.
  // This assumes all static variadic operands have the same dynamic value count.
  int variadicSize = (getOperation()->getNumResults() - 0) / 1;
  // `index` passed in as the parameter is the static index which counts each
  // operand (variadic or not) as size 1. So here for each previous static variadic
  // operand, we need to offset by (variadicSize - 1) to get where the dynamic
  // value pack for this static operand starts.
  int start = index + (variadicSize - 1) * prevVariadicCount;
  int size = isVariadic[index] ? variadicSize : 1;
  return {start, size};
}

::mlir::Operation::result_range ShaderPlaceholderOp::getODSResults(unsigned index) {
  auto valueRange = getODSResultIndexAndLength(index);
  return {std::next(getOperation()->result_begin(), valueRange.first),
           std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
}

::mlir::LogicalResult ShaderPlaceholderOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.entry_point;
       auto attr = dict.get("entry_point");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for entry_point in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `entry_point` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.input_bindings;
       auto attr = dict.get("input_bindings");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for input_bindings in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `input_bindings` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.input_descriptor_set;
       auto attr = dict.get("input_descriptor_set");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for input_descriptor_set in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `input_descriptor_set` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.input_vk_descriptor_types;
       auto attr = dict.get("input_vk_descriptor_types");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for input_vk_descriptor_types in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `input_vk_descriptor_types` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.input_vk_formats;
       auto attr = dict.get("input_vk_formats");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for input_vk_formats in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `input_vk_formats` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.output_bindings;
       auto attr = dict.get("output_bindings");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for output_bindings in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `output_bindings` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.output_descriptor_set;
       auto attr = dict.get("output_descriptor_set");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for output_descriptor_set in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `output_descriptor_set` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.output_vk_descriptor_types;
       auto attr = dict.get("output_vk_descriptor_types");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for output_vk_descriptor_types in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `output_vk_descriptor_types` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.output_vk_formats;
       auto attr = dict.get("output_vk_formats");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for output_vk_formats in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `output_vk_formats` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.shader_code;
       auto attr = dict.get("shader_code");
    if (attr || /*isRequired=*/false) {
      if (!attr) {
        emitError() << "expected key entry for shader_code in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `shader_code` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.shader_name;
       auto attr = dict.get("shader_name");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for shader_name in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `shader_name` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.workgroup_sizes;
       auto attr = dict.get("workgroup_sizes");
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for workgroup_sizes in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `workgroup_sizes` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ShaderPlaceholderOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.entry_point;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("entry_point",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.input_bindings;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("input_bindings",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.input_descriptor_set;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("input_descriptor_set",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.input_vk_descriptor_types;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("input_vk_descriptor_types",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.input_vk_formats;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("input_vk_formats",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.output_bindings;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("output_bindings",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.output_descriptor_set;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("output_descriptor_set",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.output_vk_descriptor_types;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("output_vk_descriptor_types",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.output_vk_formats;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("output_vk_formats",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.shader_code;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("shader_code",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.shader_name;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("shader_name",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.workgroup_sizes;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("workgroup_sizes",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ShaderPlaceholderOp::computePropertiesHash(const Properties &prop) {
  return llvm::hash_combine(
    llvm::hash_value(prop.entry_point.getAsOpaquePointer()), 
    llvm::hash_value(prop.input_bindings.getAsOpaquePointer()), 
    llvm::hash_value(prop.input_descriptor_set.getAsOpaquePointer()), 
    llvm::hash_value(prop.input_vk_descriptor_types.getAsOpaquePointer()), 
    llvm::hash_value(prop.input_vk_formats.getAsOpaquePointer()), 
    llvm::hash_value(prop.output_bindings.getAsOpaquePointer()), 
    llvm::hash_value(prop.output_descriptor_set.getAsOpaquePointer()), 
    llvm::hash_value(prop.output_vk_descriptor_types.getAsOpaquePointer()), 
    llvm::hash_value(prop.output_vk_formats.getAsOpaquePointer()), 
    llvm::hash_value(prop.shader_code.getAsOpaquePointer()), 
    llvm::hash_value(prop.shader_name.getAsOpaquePointer()), 
    llvm::hash_value(prop.workgroup_sizes.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ShaderPlaceholderOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "entry_point")
      return prop.entry_point;

    if (name == "input_bindings")
      return prop.input_bindings;

    if (name == "input_descriptor_set")
      return prop.input_descriptor_set;

    if (name == "input_vk_descriptor_types")
      return prop.input_vk_descriptor_types;

    if (name == "input_vk_formats")
      return prop.input_vk_formats;

    if (name == "output_bindings")
      return prop.output_bindings;

    if (name == "output_descriptor_set")
      return prop.output_descriptor_set;

    if (name == "output_vk_descriptor_types")
      return prop.output_vk_descriptor_types;

    if (name == "output_vk_formats")
      return prop.output_vk_formats;

    if (name == "shader_code")
      return prop.shader_code;

    if (name == "shader_name")
      return prop.shader_name;

    if (name == "workgroup_sizes")
      return prop.workgroup_sizes;
  return std::nullopt;
}

void ShaderPlaceholderOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "entry_point") {
       prop.entry_point = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.entry_point)>>(value);
       return;
    }

    if (name == "input_bindings") {
       prop.input_bindings = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.input_bindings)>>(value);
       return;
    }

    if (name == "input_descriptor_set") {
       prop.input_descriptor_set = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.input_descriptor_set)>>(value);
       return;
    }

    if (name == "input_vk_descriptor_types") {
       prop.input_vk_descriptor_types = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.input_vk_descriptor_types)>>(value);
       return;
    }

    if (name == "input_vk_formats") {
       prop.input_vk_formats = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.input_vk_formats)>>(value);
       return;
    }

    if (name == "output_bindings") {
       prop.output_bindings = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.output_bindings)>>(value);
       return;
    }

    if (name == "output_descriptor_set") {
       prop.output_descriptor_set = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.output_descriptor_set)>>(value);
       return;
    }

    if (name == "output_vk_descriptor_types") {
       prop.output_vk_descriptor_types = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.output_vk_descriptor_types)>>(value);
       return;
    }

    if (name == "output_vk_formats") {
       prop.output_vk_formats = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.output_vk_formats)>>(value);
       return;
    }

    if (name == "shader_code") {
       prop.shader_code = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.shader_code)>>(value);
       return;
    }

    if (name == "shader_name") {
       prop.shader_name = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.shader_name)>>(value);
       return;
    }

    if (name == "workgroup_sizes") {
       prop.workgroup_sizes = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.workgroup_sizes)>>(value);
       return;
    }
}

void ShaderPlaceholderOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
    if (prop.entry_point) attrs.append("entry_point", prop.entry_point);

    if (prop.input_bindings) attrs.append("input_bindings", prop.input_bindings);

    if (prop.input_descriptor_set) attrs.append("input_descriptor_set", prop.input_descriptor_set);

    if (prop.input_vk_descriptor_types) attrs.append("input_vk_descriptor_types", prop.input_vk_descriptor_types);

    if (prop.input_vk_formats) attrs.append("input_vk_formats", prop.input_vk_formats);

    if (prop.output_bindings) attrs.append("output_bindings", prop.output_bindings);

    if (prop.output_descriptor_set) attrs.append("output_descriptor_set", prop.output_descriptor_set);

    if (prop.output_vk_descriptor_types) attrs.append("output_vk_descriptor_types", prop.output_vk_descriptor_types);

    if (prop.output_vk_formats) attrs.append("output_vk_formats", prop.output_vk_formats);

    if (prop.shader_code) attrs.append("shader_code", prop.shader_code);

    if (prop.shader_name) attrs.append("shader_name", prop.shader_name);

    if (prop.workgroup_sizes) attrs.append("workgroup_sizes", prop.workgroup_sizes);
}

::mlir::LogicalResult ShaderPlaceholderOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getEntryPointAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps0(attr, "entry_point", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInputBindingsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps5(attr, "input_bindings", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInputDescriptorSetAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps6(attr, "input_descriptor_set", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInputVkDescriptorTypesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps7(attr, "input_vk_descriptor_types", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getInputVkFormatsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps7(attr, "input_vk_formats", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOutputBindingsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps5(attr, "output_bindings", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOutputDescriptorSetAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps6(attr, "output_descriptor_set", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOutputVkDescriptorTypesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps7(attr, "output_vk_descriptor_types", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getOutputVkFormatsAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps7(attr, "output_vk_formats", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getShaderCodeAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps8(attr, "shader_code", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getShaderNameAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps0(attr, "shader_name", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getWorkgroupSizesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps5(attr, "workgroup_sizes", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::mlir::LogicalResult ShaderPlaceholderOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.entry_point)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.input_bindings)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.input_descriptor_set)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.input_vk_descriptor_types)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.input_vk_formats)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.output_bindings)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.output_descriptor_set)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.output_vk_descriptor_types)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.output_vk_formats)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readOptionalAttribute(prop.shader_code)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.shader_name)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.workgroup_sizes)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShaderPlaceholderOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.entry_point);
  writer.writeAttribute(prop.input_bindings);
  writer.writeAttribute(prop.input_descriptor_set);
  writer.writeAttribute(prop.input_vk_descriptor_types);
  writer.writeAttribute(prop.input_vk_formats);
  writer.writeAttribute(prop.output_bindings);
  writer.writeAttribute(prop.output_descriptor_set);
  writer.writeAttribute(prop.output_vk_descriptor_types);
  writer.writeAttribute(prop.output_vk_formats);

  writer.writeOptionalAttribute(prop.shader_code);
  writer.writeAttribute(prop.shader_name);
  writer.writeAttribute(prop.workgroup_sizes);
}

::mlir::StringAttr ShaderPlaceholderOp::getShaderNameAttr() {
  return ::llvm::cast<::mlir::StringAttr>(getProperties().shader_name);
}

::llvm::StringRef ShaderPlaceholderOp::getShaderName() {
  auto attr = getShaderNameAttr();
  return attr.getValue();
}

::mlir::StringAttr ShaderPlaceholderOp::getEntryPointAttr() {
  return ::llvm::cast<::mlir::StringAttr>(getProperties().entry_point);
}

::llvm::StringRef ShaderPlaceholderOp::getEntryPoint() {
  auto attr = getEntryPointAttr();
  return attr.getValue();
}

::mlir::DenseI64ArrayAttr ShaderPlaceholderOp::getInputBindingsAttr() {
  return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().input_bindings);
}

::llvm::ArrayRef<int64_t> ShaderPlaceholderOp::getInputBindings() {
  auto attr = getInputBindingsAttr();
  return attr;
}

::mlir::DenseI64ArrayAttr ShaderPlaceholderOp::getOutputBindingsAttr() {
  return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().output_bindings);
}

::llvm::ArrayRef<int64_t> ShaderPlaceholderOp::getOutputBindings() {
  auto attr = getOutputBindingsAttr();
  return attr;
}

::mlir::IntegerAttr ShaderPlaceholderOp::getInputDescriptorSetAttr() {
  return ::llvm::cast<::mlir::IntegerAttr>(getProperties().input_descriptor_set);
}

uint64_t ShaderPlaceholderOp::getInputDescriptorSet() {
  auto attr = getInputDescriptorSetAttr();
  return attr.getValue().getZExtValue();
}

::mlir::IntegerAttr ShaderPlaceholderOp::getOutputDescriptorSetAttr() {
  return ::llvm::cast<::mlir::IntegerAttr>(getProperties().output_descriptor_set);
}

uint64_t ShaderPlaceholderOp::getOutputDescriptorSet() {
  auto attr = getOutputDescriptorSetAttr();
  return attr.getValue().getZExtValue();
}

::mlir::ArrayAttr ShaderPlaceholderOp::getInputVkDescriptorTypesAttr() {
  return ::llvm::cast<::mlir::ArrayAttr>(getProperties().input_vk_descriptor_types);
}

::mlir::ArrayAttr ShaderPlaceholderOp::getInputVkDescriptorTypes() {
  auto attr = getInputVkDescriptorTypesAttr();
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOp::getOutputVkDescriptorTypesAttr() {
  return ::llvm::cast<::mlir::ArrayAttr>(getProperties().output_vk_descriptor_types);
}

::mlir::ArrayAttr ShaderPlaceholderOp::getOutputVkDescriptorTypes() {
  auto attr = getOutputVkDescriptorTypesAttr();
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOp::getInputVkFormatsAttr() {
  return ::llvm::cast<::mlir::ArrayAttr>(getProperties().input_vk_formats);
}

::mlir::ArrayAttr ShaderPlaceholderOp::getInputVkFormats() {
  auto attr = getInputVkFormatsAttr();
  return attr;
}

::mlir::ArrayAttr ShaderPlaceholderOp::getOutputVkFormatsAttr() {
  return ::llvm::cast<::mlir::ArrayAttr>(getProperties().output_vk_formats);
}

::mlir::ArrayAttr ShaderPlaceholderOp::getOutputVkFormats() {
  auto attr = getOutputVkFormatsAttr();
  return attr;
}

::mlir::DenseI64ArrayAttr ShaderPlaceholderOp::getWorkgroupSizesAttr() {
  return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().workgroup_sizes);
}

::llvm::ArrayRef<int64_t> ShaderPlaceholderOp::getWorkgroupSizes() {
  auto attr = getWorkgroupSizesAttr();
  return attr;
}

::mlir::DenseI32ArrayAttr ShaderPlaceholderOp::getShaderCodeAttr() {
  return ::llvm::dyn_cast_or_null<::mlir::DenseI32ArrayAttr>(getProperties().shader_code);
}

::std::optional<::llvm::ArrayRef<int32_t>> ShaderPlaceholderOp::getShaderCode() {
  auto attr = getShaderCodeAttr();
  return attr ? ::std::optional<::llvm::ArrayRef<int32_t>>(attr) : (::std::nullopt);
}

void ShaderPlaceholderOp::setShaderNameAttr(::mlir::StringAttr attr) {
  (*this)->setAttr(getShaderNameAttrName(), attr);
}

void ShaderPlaceholderOp::setShaderName(::llvm::StringRef attrValue) {
  (*this)->setAttr(getShaderNameAttrName(), ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue));
}

void ShaderPlaceholderOp::setEntryPointAttr(::mlir::StringAttr attr) {
  (*this)->setAttr(getEntryPointAttrName(), attr);
}

void ShaderPlaceholderOp::setEntryPoint(::llvm::StringRef attrValue) {
  (*this)->setAttr(getEntryPointAttrName(), ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue));
}

void ShaderPlaceholderOp::setInputBindingsAttr(::mlir::DenseI64ArrayAttr attr) {
  (*this)->setAttr(getInputBindingsAttrName(), attr);
}

void ShaderPlaceholderOp::setInputBindings(::llvm::ArrayRef<int64_t> attrValue) {
  (*this)->setAttr(getInputBindingsAttrName(), ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue));
}

void ShaderPlaceholderOp::setOutputBindingsAttr(::mlir::DenseI64ArrayAttr attr) {
  (*this)->setAttr(getOutputBindingsAttrName(), attr);
}

void ShaderPlaceholderOp::setOutputBindings(::llvm::ArrayRef<int64_t> attrValue) {
  (*this)->setAttr(getOutputBindingsAttrName(), ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue));
}

void ShaderPlaceholderOp::setInputDescriptorSetAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(getInputDescriptorSetAttrName(), attr);
}

void ShaderPlaceholderOp::setInputDescriptorSet(uint64_t attrValue) {
  (*this)->setAttr(getInputDescriptorSetAttrName(), ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue));
}

void ShaderPlaceholderOp::setOutputDescriptorSetAttr(::mlir::IntegerAttr attr) {
  (*this)->setAttr(getOutputDescriptorSetAttrName(), attr);
}

void ShaderPlaceholderOp::setOutputDescriptorSet(uint64_t attrValue) {
  (*this)->setAttr(getOutputDescriptorSetAttrName(), ::mlir::Builder((*this)->getContext()).getIntegerAttr(::mlir::Builder((*this)->getContext()).getIntegerType(64), attrValue));
}

void ShaderPlaceholderOp::setInputVkDescriptorTypesAttr(::mlir::ArrayAttr attr) {
  (*this)->setAttr(getInputVkDescriptorTypesAttrName(), attr);
}

void ShaderPlaceholderOp::setOutputVkDescriptorTypesAttr(::mlir::ArrayAttr attr) {
  (*this)->setAttr(getOutputVkDescriptorTypesAttrName(), attr);
}

void ShaderPlaceholderOp::setInputVkFormatsAttr(::mlir::ArrayAttr attr) {
  (*this)->setAttr(getInputVkFormatsAttrName(), attr);
}

void ShaderPlaceholderOp::setOutputVkFormatsAttr(::mlir::ArrayAttr attr) {
  (*this)->setAttr(getOutputVkFormatsAttrName(), attr);
}

void ShaderPlaceholderOp::setWorkgroupSizesAttr(::mlir::DenseI64ArrayAttr attr) {
  (*this)->setAttr(getWorkgroupSizesAttrName(), attr);
}

void ShaderPlaceholderOp::setWorkgroupSizes(::llvm::ArrayRef<int64_t> attrValue) {
  (*this)->setAttr(getWorkgroupSizesAttrName(), ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue));
}

void ShaderPlaceholderOp::setShaderCodeAttr(::mlir::DenseI32ArrayAttr attr) {
  (*this)->setAttr(getShaderCodeAttrName(), attr);
}

void ShaderPlaceholderOp::setShaderCode(::std::optional<::llvm::ArrayRef<int32_t>> attrValue) {
    if (attrValue)
      return (*this)->setAttr(getShaderCodeAttrName(), ::mlir::Builder((*this)->getContext()).getDenseI32ArrayAttr(*attrValue));
    (*this)->removeAttr(getShaderCodeAttrName());
}

::mlir::Attribute ShaderPlaceholderOp::removeShaderCodeAttr() {
    auto &attr = getProperties().shader_code;
    attr = {};
    return attr;
}

void ShaderPlaceholderOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::mlir::StringAttr shader_name, ::mlir::StringAttr entry_point, ::mlir::DenseI64ArrayAttr input_bindings, ::mlir::DenseI64ArrayAttr output_bindings, ::mlir::IntegerAttr input_descriptor_set, ::mlir::IntegerAttr output_descriptor_set, ::mlir::ArrayAttr input_vk_descriptor_types, ::mlir::ArrayAttr output_vk_descriptor_types, ::mlir::ArrayAttr input_vk_formats, ::mlir::ArrayAttr output_vk_formats, ::mlir::DenseI64ArrayAttr workgroup_sizes, /*optional*/::mlir::DenseI32ArrayAttr shader_code, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
  odsState.getOrAddProperties<Properties>().shader_name = shader_name;
  odsState.getOrAddProperties<Properties>().entry_point = entry_point;
  odsState.getOrAddProperties<Properties>().input_bindings = input_bindings;
  odsState.getOrAddProperties<Properties>().output_bindings = output_bindings;
  odsState.getOrAddProperties<Properties>().input_descriptor_set = input_descriptor_set;
  odsState.getOrAddProperties<Properties>().output_descriptor_set = output_descriptor_set;
  odsState.getOrAddProperties<Properties>().input_vk_descriptor_types = input_vk_descriptor_types;
  odsState.getOrAddProperties<Properties>().output_vk_descriptor_types = output_vk_descriptor_types;
  odsState.getOrAddProperties<Properties>().input_vk_formats = input_vk_formats;
  odsState.getOrAddProperties<Properties>().output_vk_formats = output_vk_formats;
  odsState.getOrAddProperties<Properties>().workgroup_sizes = workgroup_sizes;
  if (shader_code) {
    odsState.getOrAddProperties<Properties>().shader_code = shader_code;
  }
  odsState.addTypes(resultType0);
}

void ShaderPlaceholderOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultType0, ::llvm::StringRef shader_name, ::llvm::StringRef entry_point, ::llvm::ArrayRef<int64_t> input_bindings, ::llvm::ArrayRef<int64_t> output_bindings, uint64_t input_descriptor_set, uint64_t output_descriptor_set, ::mlir::ArrayAttr input_vk_descriptor_types, ::mlir::ArrayAttr output_vk_descriptor_types, ::mlir::ArrayAttr input_vk_formats, ::mlir::ArrayAttr output_vk_formats, ::llvm::ArrayRef<int64_t> workgroup_sizes, /*optional*/::mlir::DenseI32ArrayAttr shader_code, ::mlir::ValueRange operands) {
  odsState.addOperands(operands);
  odsState.getOrAddProperties<Properties>().shader_name = odsBuilder.getStringAttr(shader_name);
  odsState.getOrAddProperties<Properties>().entry_point = odsBuilder.getStringAttr(entry_point);
  odsState.getOrAddProperties<Properties>().input_bindings = odsBuilder.getDenseI64ArrayAttr(input_bindings);
  odsState.getOrAddProperties<Properties>().output_bindings = odsBuilder.getDenseI64ArrayAttr(output_bindings);
  odsState.getOrAddProperties<Properties>().input_descriptor_set = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), input_descriptor_set);
  odsState.getOrAddProperties<Properties>().output_descriptor_set = odsBuilder.getIntegerAttr(odsBuilder.getIntegerType(64), output_descriptor_set);
  odsState.getOrAddProperties<Properties>().input_vk_descriptor_types = input_vk_descriptor_types;
  odsState.getOrAddProperties<Properties>().output_vk_descriptor_types = output_vk_descriptor_types;
  odsState.getOrAddProperties<Properties>().input_vk_formats = input_vk_formats;
  odsState.getOrAddProperties<Properties>().output_vk_formats = output_vk_formats;
  odsState.getOrAddProperties<Properties>().workgroup_sizes = odsBuilder.getDenseI64ArrayAttr(workgroup_sizes);
  if (shader_code) {
    odsState.getOrAddProperties<Properties>().shader_code = shader_code;
  }
  odsState.addTypes(resultType0);
}

void ShaderPlaceholderOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  odsState.addTypes(resultTypes);
}

::mlir::LogicalResult ShaderPlaceholderOp::verifyInvariantsImpl() {
  auto tblgen_entry_point = getProperties().entry_point; (void)tblgen_entry_point;
  if (!tblgen_entry_point) return emitOpError("requires attribute 'entry_point'");
  auto tblgen_input_bindings = getProperties().input_bindings; (void)tblgen_input_bindings;
  if (!tblgen_input_bindings) return emitOpError("requires attribute 'input_bindings'");
  auto tblgen_input_descriptor_set = getProperties().input_descriptor_set; (void)tblgen_input_descriptor_set;
  if (!tblgen_input_descriptor_set) return emitOpError("requires attribute 'input_descriptor_set'");
  auto tblgen_input_vk_descriptor_types = getProperties().input_vk_descriptor_types; (void)tblgen_input_vk_descriptor_types;
  if (!tblgen_input_vk_descriptor_types) return emitOpError("requires attribute 'input_vk_descriptor_types'");
  auto tblgen_input_vk_formats = getProperties().input_vk_formats; (void)tblgen_input_vk_formats;
  if (!tblgen_input_vk_formats) return emitOpError("requires attribute 'input_vk_formats'");
  auto tblgen_output_bindings = getProperties().output_bindings; (void)tblgen_output_bindings;
  if (!tblgen_output_bindings) return emitOpError("requires attribute 'output_bindings'");
  auto tblgen_output_descriptor_set = getProperties().output_descriptor_set; (void)tblgen_output_descriptor_set;
  if (!tblgen_output_descriptor_set) return emitOpError("requires attribute 'output_descriptor_set'");
  auto tblgen_output_vk_descriptor_types = getProperties().output_vk_descriptor_types; (void)tblgen_output_vk_descriptor_types;
  if (!tblgen_output_vk_descriptor_types) return emitOpError("requires attribute 'output_vk_descriptor_types'");
  auto tblgen_output_vk_formats = getProperties().output_vk_formats; (void)tblgen_output_vk_formats;
  if (!tblgen_output_vk_formats) return emitOpError("requires attribute 'output_vk_formats'");
  auto tblgen_shader_code = getProperties().shader_code; (void)tblgen_shader_code;
  auto tblgen_shader_name = getProperties().shader_name; (void)tblgen_shader_name;
  if (!tblgen_shader_name) return emitOpError("requires attribute 'shader_name'");
  auto tblgen_workgroup_sizes = getProperties().workgroup_sizes; (void)tblgen_workgroup_sizes;
  if (!tblgen_workgroup_sizes) return emitOpError("requires attribute 'workgroup_sizes'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps0(*this, tblgen_shader_name, "shader_name")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps0(*this, tblgen_entry_point, "entry_point")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps5(*this, tblgen_input_bindings, "input_bindings")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps5(*this, tblgen_output_bindings, "output_bindings")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps6(*this, tblgen_input_descriptor_set, "input_descriptor_set")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps6(*this, tblgen_output_descriptor_set, "output_descriptor_set")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps7(*this, tblgen_input_vk_descriptor_types, "input_vk_descriptor_types")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps7(*this, tblgen_output_vk_descriptor_types, "output_vk_descriptor_types")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps7(*this, tblgen_input_vk_formats, "input_vk_formats")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps7(*this, tblgen_output_vk_formats, "output_vk_formats")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps5(*this, tblgen_workgroup_sizes, "workgroup_sizes")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_VGFOps8(*this, tblgen_shader_code, "shader_code")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_VGFOps0(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_VGFOps0(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::mlir::LogicalResult ShaderPlaceholderOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult ShaderPlaceholderOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::llvm::SmallVector<::mlir::OpAsmParser::UnresolvedOperand, 4> operandsOperands;
  ::llvm::SMLoc operandsOperandsLoc;
  (void)operandsOperandsLoc;
  ::llvm::ArrayRef<::mlir::Type> operandsTypes;
  ::llvm::ArrayRef<::mlir::Type> allResultTypes;
  if (parser.parseLParen())
    return ::mlir::failure();

  operandsOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperandList(operandsOperands))
    return ::mlir::failure();
  if (parser.parseRParen())
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  ::mlir::FunctionType operands__allResult_functionType;
  if (parser.parseType(operands__allResult_functionType))
    return ::mlir::failure();
  operandsTypes = operands__allResult_functionType.getInputs();
  allResultTypes = operands__allResult_functionType.getResults();
  result.addTypes(allResultTypes);
  if (parser.resolveOperands(operandsOperands, operandsTypes, operandsOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void ShaderPlaceholderOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << "(";
  _odsPrinter << getOperands();
  _odsPrinter << ")";
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  _odsPrinter.printFunctionalType(getOperands().getTypes(), getOperation()->getResultTypes());
}

} // namespace vgf
} // namespace mlir
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::vgf::ShaderPlaceholderOp)


#endif  // GET_OP_CLASSES

