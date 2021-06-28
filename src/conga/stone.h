#ifndef CONGA_STONE_H_
#define CONGA_STONE_H_

namespace conga {

struct Stone {
 public:
  enum Value {
    kBlack,
    kWhite,
  };

  Stone() = default;
  Stone(const Value value);

  const Stone Complement() const;

  Value value;
};

const bool operator==(const Stone& lhs, const Stone& rhs);
const bool operator!=(const Stone& lhs, const Stone& rhs);

}  // namespace conga

#endif  // CONGA_STONE_H_
