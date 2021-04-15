#pragma once

#include <vector>

template<typename B>
class WrapperBase {
 public:
  virtual size_t size() const = 0;
  virtual const B& operator[](int) const = 0;
};

template<typename B, typename D>
class WrapperTemplate : public WrapperBase<B> {
 public:
  explicit WrapperTemplate(const std::vector<D>& v) : vector_(v) {}

  const B& operator[](int i) const override {
    return vector_[i];
  }

  size_t size() const override {
    return vector_.size();
  }

 private:
  const std::vector<D>& vector_;
};
