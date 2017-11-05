#ifndef _NRSCRIPT_NRCHARS_H_
#define _NRSCRIPT_NRCHARS_H_

/**
 * 字符串
 */
template<typename T>
class NRSCRIPT_API_VISUAL NrChars {
public:
    typedef T CHAR;

public:

private:
    class Impl;
    Impl* impl {nullptr};
};

class NRSCRIPT_API_VISUAL NrString {
};

#endif
