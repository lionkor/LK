#ifndef LK_EXCEPTION_H
#define LK_EXCEPTION_H

#include "Meta.h"

#define LK_ENABLE_STD_EXCEPTION true

#if defined(LK_ENABLE_STD_EXCEPTION) && LK_ENABLE_STD_EXCEPTION
#include <exception>
#endif

namespace LK {

class LK_API Exception
#if defined(LK_ENABLE_STD_EXCEPTION) && LK_ENABLE_STD_EXCEPTION
    : public std::exception {
#endif
public:
    Exception(const char* what);
    virtual ~Exception() noexcept;

    virtual const char* what() const noexcept override;

private:
    const char* m_what;
};

}

#endif //LK_EXCEPTION_H
