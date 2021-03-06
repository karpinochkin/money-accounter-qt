#ifndef BASE_H
#define BASE_H

#include <memory>
#include <QString>
#include <QVariant>

#define S_NUM(...) QString::number(__VA_ARGS__)

///
/// Unique ptr
///
template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}


///
/// Shared ptr
///
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

///
/// QVariant unpack
///
template< typename T >
T unpack( const QVariant& var, const T& defVal = T() ) {
    if( var.isValid() && var.canConvert< T >() ) {
        return var.value< T >();
    }
    return defVal;
}

#endif // BASE_H
