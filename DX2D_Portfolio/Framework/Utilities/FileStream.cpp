#include "Framework.h"
#include "FileStream.h"

FileStream::FileStream(string path, uint flags)
    : flag(flags)
{
    int iosFlags = ios::binary;

    // 쓰기 / 읽기 모드로 열리는지 확인
    iosFlags |= flags && FILE_STREAM_WRITE 
        ? ios::out : 0;
    iosFlags |= flags && FILE_STREAM_READ
        ? ios::in : 0;

    if (flags & FILE_STREAM_WRITE)
    {
        // 출력 파일 스트림 여는
        out.open(path, iosFlags);
        // 만약 파일 스트림이 정상적이지 않다면
        if (out.fail())
        {
            // flush조차 안되면 경로 문제
            out.flush(); // 데이터 지우고
            out.close(); // 스트림 닫기
            assert(false);
        }
    }
    // 읽기 모드라면
    else if (flags & FILE_STREAM_READ)
    {
        in.open(path, iosFlags);
        if (in.fail())
        {
            in.clear(); // 데이터 지우고
            in.close(); // 스트림 닫기
            assert(false);
        }
    }
}

FileStream::~FileStream()
{
    if (flag & FILE_STREAM_WRITE)
    {
        // 쓰기모드 파일 데이터 지우고 닫기
        out.flush();
        out.close();
    }
    else if (flag & FILE_STREAM_READ)
    {
        // 읽기모드 파일 데이터 지우고 닫기
        in.clear();
        in.close();
    }

}
