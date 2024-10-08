#include "Framework.h"
#include "Path.h"

// 파일 존재 여부
bool Path::ExistFile(wstring path)
{
	// 파일이나 폴더의 속성을 알아보는 함수 DWORD를 반환
	// 실패하면 INVALID_FILE_ATTRIBUTES를 반환
	DWORD fileValue = GetFileAttributes(path.c_str());

	// 파일이 존재할경우 True 없을경우 False
	return fileValue != INVALID_FILE_ATTRIBUTES;
}

bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWstring(path));
}

// 폴더 존재 여부
bool Path::ExistDirectory(wstring path)
{
	DWORD attribute = GetFileAttributes(path.c_str());

	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES &&
		attribute & FILE_ATTRIBUTE_DIRECTORY);	// 이 조건문이 참이면 검사 중인 항목이 폴더

	return temp == TRUE;
}

bool Path::ExistDirectory(string path)
{
	return ExistDirectory(String::ToWstring(path));
}

// 병합 (경로 합치는거)
string Path::Combine(string path1, string path2)
{
	return path1 + path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

// 입력된 경로에서 폴더 이름을 반환
string Path::GetDirectoryName(string path)
{
	String::Replace(&path, "\\", "/"); // 백슬을 슬래시로 교환하는 역할
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

// 파일의 확장자를 반환
string Path::GetExtension(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.'); // 점 기준 끝으로 가면 확장자만 받음

	return path.substr(index + 1, path.length());;
}

wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());;
}

// 파일 이름과 확장자를 반환
string Path::GetFileName(string path)
{
	String::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length()); // 파일경로 마지막 백슬 이후로 쭉 받으면 파일 이름 받음
}

wstring Path::GetFileName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

// 파일 이름만 반환
string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index); // 위애서 했다가 쩜 뒤로 배제하면 확장자 없는 파일 이름만
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

// 특정 확장자 파일의 필터
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text file\0*.txt";
const WCHAR* Path::TileFilter = L"Tile file\0*.png;*.bmp;*.jpg;*.json;*.data";
const WCHAR* Path::TMapFilter = L"TMap file\0*.tmap"; // tmap은 타일맵

// 파일 선택 대화 상자를 열어 사용자가 파일을 선택하도록 해줌(winAPI의 역할)
// 메모장 같은거 저장할때 뜨는 창
void Path::OpenFileDialog(wstring defaultFileName, const WCHAR* fileTypeFilter, const wstring defaultFolder, const function<void(wstring)> callback, HWND parentWindowHandle)
{
	WCHAR name[255];
	wcscpy_s(name, defaultFileName.c_str());

	wstring tempFolder = defaultFolder;

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = parentWindowHandle;			// 부모창 핸들
	ofn.lpstrFilter = fileTypeFilter;			// 파일 유형 필터
	ofn.lpstrFile = name;						// 파일 이름
	ofn.lpstrFileTitle = L"불러오기";			// 대화 상자 제목
	ofn.nMaxFile = 255;							// 파일 이름 최대 크기
	ofn.lpstrInitialDir = tempFolder.c_str();	// 기본 폴더 경로
	ofn.Flags = OFN_NOCHANGEDIR;				// 대화 상자 옵션

	if (GetOpenFileName(&ofn) == TRUE)			// 대화 상자 열고 사용자가 파일을 선택하면
	{
		if (callback != NULL)					// 콜백 함수가 지정되어 있으면
		{
			wstring loadName = name;			// 선택된 파일의 경로를 저장
			String::Replace(&loadName, L"\\", L"/"); // 경로에서 역슬래시를 슬래시로 변환

			callback(loadName);					// 콜백 함수 호출
		}
	}
}
/*
typedef struct tagOFN {
  DWORD         lStructSize; 구조체의 크기지정, 버전확인을 위해 사용됨
  HWND          hwndOwner; 핸들의 주인을 지정, 주인이 될 윈도우가 없을경우 NULL
  HINSTANCE     hInstance;  인스턴스 핸들을 지정
  LPCTSTR       lpstrFilter; 파일 형식들을 구분해줄 필터들을 지정 여러개의 필터를 동시에 지정가능
  LPTSTR        lpstrCustomFilter; 사용자가 만든 커스텀 필터를 지정
  DWORD         nMaxCustFilter; 커스텀 필터의 버퍼의 길이를 지정 최소 40자
  DWORD         nFilterIndex;  필터들의 목록중 사용할 필터의 인덱스를 지정
  LPTSTR        lpstrFile; 파일이름 지정에 첫번째로 나타날 파일명을 지정, 필요없을시 NULL
  DWORD         nMaxFile;
  LPTSTR        lpstrFileTitle;
  DWORD         nMaxFileTitle;
  LPCTSTR       lpstrInitialDir;
  LPCTSTR       lpstrTitle;
  DWORD         Flags;
  WORD          nFileOffset;
  WORD          nFileExtension;
  LPCTSTR       lpstrDefExt;
  LPARAM        lCustData;
  LPOFNHOOKPROC lpfnHook;
  LPCTSTR       lpTemplateName;
#if (_WIN32_WINNT >= 0x0500)
  void *        pvReserved;
  DWORD         dwReserved;
  DWORD         FlagsEx;
#endif // (_WIN32_WINNT >= 0x0500)
} OPENFILENAME, *LPOPENFILENAME;

*/

// 파일 대화 상자를 열어 사용자가 파일을 저장하도록 함
void Path::SaveFileDialog(wstring defaultFileName, const WCHAR* fileTypeFilter, const wstring defaultFolder, const function<void(wstring)> callback, HWND parentWindowHandle)
{
	WCHAR name[255];
	wcscpy_s(name, defaultFileName.c_str());

	wstring tempFolder = defaultFolder;

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = parentWindowHandle;
	ofn.lpstrFilter = fileTypeFilter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = L"저장하기";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		if (callback != NULL)
		{
			wstring saveName = name;
			String::Replace(&saveName, L"\\", L"/");

			callback(saveName);
		}
	}
}

// 지정된 폴더에서 특정 유형의 파일들을 찾아 반환하는 함수
void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = String::ToWstring(path);
	wstring wFilter = String::ToWstring(filter);

	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	for (wstring str : wFiles)
		files->push_back(String::ToString(str));
}

//path : ../Temp/
//filter : *.txt
// 지정된 폴더에서 특정 파일들을 찾아 반환하는 함수
void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder/*하위폴더 검색 옵션*/)
{
	wstring file = path + filter; // 검색할 파일의 경로와 필터를 결합하여 검색할 파일의 전체 경로 생성

	WIN32_FIND_DATA findData;
	HANDLE handle = FindFirstFile(file.c_str(), &findData);	// 첫 번째 파일 검색
	if (handle != INVALID_HANDLE_VALUE)	// 파일이 발견되면
	{
		do
		{
			// 발견된 파일이 디렉토리인 경우
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) 
			{
				// 하위 폴더 검색 옵션 활성화 & 발견된 디렉토리가 '.'으로 시작하지 않는 경우
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					// 발견된 디렉토리의 전체 경로 설정
					wstring folder = path + wstring(findData.cFileName) + L"/";
					// 재귀적으로 하위 폴더에서 파일을 검색
					GetFiles(files, folder, filter, bFindSubFolder);
				}
			}
			else // 발견된 파일이 디렉토리가 아닌 경우
			{
				// 발견된 파일의 전체 경로 생성
				wstring fileName = path + wstring(findData.cFileName);
				// 벡터에 발견된 파일의 전체 경로를 추가
				files->push_back(fileName);
			}
		} while (FindNextFile(handle, &findData)); // 다음 파일 검색
		// 파일 검색 종료
		FindClose(handle);
	}
}

// 주어진 경로에 폴더가 존재하지 않는 경우 생성하는 함수
// 주어진 경로의 폴더만 생성
void Path::CreateFolder(wstring path)
{
	// 주어진 경로에 폴더가 없을 경우
	if (ExistDirectory(path) == false)
		// 폴더 생성
		CreateDirectory(path.c_str(), NULL);
}

void Path::CreateFolder(string path)
{
	CreateFolder(String::ToWstring(path));
}

// 폴더가 없을 경우 폴더를 생성하는 함수
// 주어진 경로의 모든 하위 폴더를 생성
void Path::CreateFolders(wstring path)
{
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;
	String::SplitString(&folders, path, L"/");

	wstring temp = L"";
	for (wstring folder : folders)
	{
		temp += folder + L"/";

		CreateFolder(temp);
	}
}

void Path::CreateFolders(string path)
{
	CreateFolders(String::ToWstring(path));
}