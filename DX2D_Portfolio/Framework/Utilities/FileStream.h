#pragma once

// Path에서 사용하는 파일 관련

enum  EFileStream : uint
{
    FILE_STREAM_READ = 1U << 0,
    FILE_STREAM_WRITE = 1U << 1
};

class Tile;
class FileStream
{
public:
    FileStream(string path, uint flags);
    ~FileStream();

    template<typename T, typename = typename enable_if <
        is_same<T, bool>::value ||
        is_same<T, char>::value ||
        is_same<T, int >::value ||
        is_same<T, float>::value ||
        is_same<T, uint>::value ||
        is_same<T, Vector2>::value ||
        is_same<T, Vector3>::value ||
        is_same<T, Matrix>::value ||
        is_same<T, Color>::value ||
        is_same<T, Tile>::value
    >::type>

        // 저 안에 있는 is_same안에 있는 것들만 불러오기 가능
    void Write(T value)
    {
        out.write(reinterpret_cast<const char*>(&value),
            sizeof(T));
    }

    template<typename T, typename = typename enable_if <
        is_same<T, bool>::value ||
        is_same<T, char>::value ||
        is_same<T, int >::value ||
        is_same<T, float>::value ||
        is_same<T, uint>::value ||
        is_same<T, Vector2>::value ||
        is_same<T, Vector3>::value ||
        is_same<T, Matrix>::value ||
        is_same<T, Color>::value ||
        is_same<T, Tile>::value
    >::type>
    T Read()
    {
        T value;

        in.read(reinterpret_cast<char*>(&value),
            sizeof(T));

        return value;
    }

private:
    ofstream out;
    ifstream in;

    uint flag;

};