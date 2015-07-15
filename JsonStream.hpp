#ifndef JSONSTREAM_H
#define JSONSTREAM_H

#include <ostream>

using namespace std;

namespace mapper {

class JsonStream
{
    ostream& m_outputStream;

public:
    explicit JsonStream(ostream& outputStream);

    template<typename T>
    void write(T value);

    template<typename T>
    JsonStream& operator << (T value);

    void removeLastCommaSign();
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------
JsonStream::JsonStream(ostream& outputStream)
    : m_outputStream(outputStream)
{
}

// ----- METHODS --------------------------------------------------------------

template<typename T>
void JsonStream::write(T value)
{
    m_outputStream << value;
}

template<typename T>
JsonStream& JsonStream::operator <<(T value)
{
    m_outputStream << value;

    return *this;
}

void JsonStream::removeLastCommaSign()
{
    m_outputStream.seekp(-2, m_outputStream.cur);
}

} // namespace mapper

#endif // JSONSTREAM_H
