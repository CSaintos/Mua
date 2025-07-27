#pragma once

#include <cstddef>
#include <variant>

#include "Error.hpp"

namespace mua
{
  template<typename T = std::nullptr_t>
  class Result
  {
  private:
    std::variant<std::monostate, T, Error> variant;
  public:
    Result()
      : variant(std::monostate())
    {}

    Result(T data)
      : variant(std::move(data))
    {}

    Result(Error err)
      : variant(err)
    {}

    Result(const Result& other)
      : variant(other.variant)
    {}

    Result& operator=(T& data)
    {
      variant = std::move(data);
      return *this;
    }

    Result& operator=(Error err)
    {
      variant = err;
      return *this;
    }

    Result& operator=(const Result& res)
    {
      variant = res.variant;
      return *this;
    }

    bool is_ok()
    {
      return std::holds_alternative<T>(variant) && (typeid(T) != typeid(std::nullptr_t));
    }
    
    bool is_err()
    {
      return std::holds_alternative<Error>(variant);
    }

    T get_data()
    {
      if (std::holds_alternative<T>(variant))
        return std::get<T>(variant);
      return T();
    }

    Error get_err()
    {
      if (std::holds_alternative<Error>(variant)) 
        return std::get<Error>(variant);
      return Error();
    }
  };
}
