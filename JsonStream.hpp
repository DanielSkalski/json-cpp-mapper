#ifndef JSONSTREAM_H
#define JSONSTREAM_H

#include <ostream>

using namespace std;

namespace mapper {

class JsonStream
{
    ostream& m_outputStream;

    int m_currentIndent;

public:
    explicit JsonStream(ostream& outputStream);

    void beginObject();
    void endObject();

    void beginArray();
    void endArray();

    void beginArrayElement();
    void endArrayElement(bool isLastElement);

    void beginProperty(const string& propertyName);
    void endProperty(bool isLast);

    template<typename T>
    JsonStream& operator << (T value);

private:
    void putIndent();
    void putNewLine();
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------
JsonStream::JsonStream(ostream& outputStream)
    : m_outputStream(outputStream)
{
    m_currentIndent = 0;
}

// ----- METHODS --------------------------------------------------------------

void JsonStream::beginObject()
{
    m_outputStream << "{" << endl;
    m_currentIndent++;
}

void JsonStream::endObject()
{
    m_currentIndent--;
    putIndent();
    m_outputStream << "}";

    if (m_currentIndent == 0)
    {
        putNewLine();
    }
}

void JsonStream::beginArray()
{
    m_outputStream << "[" << endl;
    m_currentIndent++;
}

void JsonStream::endArray()
{
    m_currentIndent--;
    putNewLine();
    putIndent();
    m_outputStream << "]";
}

void JsonStream::beginArrayElement()
{
    putIndent();
}

void JsonStream::endArrayElement(bool isLastElement)
{
    if (!isLastElement)
    {
        m_outputStream << ",";
        putNewLine();
    }
}

void JsonStream::beginProperty(const string& propertyName)
{
    putIndent();
    m_outputStream << "\"" << propertyName << "\"" << " : ";
}

void JsonStream::endProperty(bool isLast)
{
    if (!isLast)
    {
        m_outputStream << ",";
    }
    putNewLine();
}

template<typename T>
JsonStream& JsonStream::operator <<(T value)
{
    m_outputStream << value;

    return *this;
}

void JsonStream::putIndent()
{
    for (int i = 0; i < m_currentIndent; i++)
    {
        m_outputStream << "  ";
    }
}

void JsonStream::putNewLine()
{
    m_outputStream << endl;
}

} // namespace mapper

#endif // JSONSTREAM_H
