/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Enum Utility Declarations                                                  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: VGFEnums.td                                                          *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir {
namespace vgf {
// Type of segment
enum class SegmentTypeEnum : uint32_t {
  GRAPH = 0,
  COMPUTE = 1,
};

::std::optional<SegmentTypeEnum> symbolizeSegmentTypeEnum(uint32_t);
::llvm::StringRef stringifySegmentTypeEnum(SegmentTypeEnum);
::std::optional<SegmentTypeEnum> symbolizeSegmentTypeEnum(::llvm::StringRef);
inline constexpr unsigned getMaxEnumValForSegmentTypeEnum() {
  return 1;
}


inline ::llvm::StringRef stringifyEnum(SegmentTypeEnum enumValue) {
  return stringifySegmentTypeEnum(enumValue);
}

template <typename EnumType>
::std::optional<EnumType> symbolizeEnum(::llvm::StringRef);

template <>
inline ::std::optional<SegmentTypeEnum> symbolizeEnum<SegmentTypeEnum>(::llvm::StringRef str) {
  return symbolizeSegmentTypeEnum(str);
}

class SegmentTypeEnumAttr : public ::mlir::IntegerAttr {
public:
  using ValueType = SegmentTypeEnum;
  using ::mlir::IntegerAttr::IntegerAttr;
  static bool classof(::mlir::Attribute attr);
  static SegmentTypeEnumAttr get(::mlir::MLIRContext *context, SegmentTypeEnum val);
  SegmentTypeEnum getValue() const;
};
} // namespace vgf
} // namespace mlir

namespace mlir {
template <typename T, typename>
struct FieldParser;

template<>
struct FieldParser<::mlir::vgf::SegmentTypeEnum, ::mlir::vgf::SegmentTypeEnum> {
  template <typename ParserT>
  static FailureOr<::mlir::vgf::SegmentTypeEnum> parse(ParserT &parser) {
    // Parse the keyword/string containing the enum.
    std::string enumKeyword;
    auto loc = parser.getCurrentLocation();
    if (failed(parser.parseOptionalKeywordOrString(&enumKeyword)))
      return parser.emitError(loc, "expected keyword for Type of segment");

    // Symbolize the keyword.
    if (::std::optional<::mlir::vgf::SegmentTypeEnum> attr = ::mlir::vgf::symbolizeEnum<::mlir::vgf::SegmentTypeEnum>(enumKeyword))
      return *attr;
    return parser.emitError(loc, "invalid Type of segment specification: ") << enumKeyword;
  }
};
} // namespace mlir

namespace llvm {
inline ::llvm::raw_ostream &operator<<(::llvm::raw_ostream &p, ::mlir::vgf::SegmentTypeEnum value) {
  auto valueStr = stringifyEnum(value);
  return p << valueStr;
}
} // namespace llvm

namespace llvm {
template<> struct DenseMapInfo<::mlir::vgf::SegmentTypeEnum> {
  using StorageInfo = ::llvm::DenseMapInfo<uint32_t>;

  static inline ::mlir::vgf::SegmentTypeEnum getEmptyKey() {
    return static_cast<::mlir::vgf::SegmentTypeEnum>(StorageInfo::getEmptyKey());
  }

  static inline ::mlir::vgf::SegmentTypeEnum getTombstoneKey() {
    return static_cast<::mlir::vgf::SegmentTypeEnum>(StorageInfo::getTombstoneKey());
  }

  static unsigned getHashValue(const ::mlir::vgf::SegmentTypeEnum &val) {
    return StorageInfo::getHashValue(static_cast<uint32_t>(val));
  }

  static bool isEqual(const ::mlir::vgf::SegmentTypeEnum &lhs, const ::mlir::vgf::SegmentTypeEnum &rhs) {
    return lhs == rhs;
  }
};
}

