#pragma once

#define STRONG_TYPEDEF(T, D)                                                                                     \
struct D                                                                                                         \
{                                                                                                                \
    T t;                                                                                                         \
    explicit D(const T& t_) noexcept : t(t_) {}                                                                  \
    D() noexcept: t() {}                                                                                         \
    D(const D & t_) noexcept: t(t_.t) {}                                                                         \
    D& operator=(const D& rhs) noexcept {t = rhs.t; return *this;}                                               \
    D& operator=(const T& rhs) noexcept {t = rhs; return *this;}                                                 \
    operator const T&() const {return t;}                                                                        \
    operator T&() {return t;}                                                                                    \
    bool operator==(const D& rhs) const {return t == rhs.t;}                                                     \
    bool operator<(const D& rhs) const {return t < rhs.t;}                                                       \
};