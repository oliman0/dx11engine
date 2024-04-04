#include "shader.h"

Shader::Shader(ID3D11Device* device, ID3D11DeviceContext* deviceContext) : m_device(device), m_deviceContext(deviceContext) {}
Shader::~Shader() {}

bool Shader::CompileShader(const WCHAR* scrFilePath, const char* entryPoint, const char* profile, ID3DBlob** blob) {
	*blob = nullptr;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	// Compile Shader.
	HRESULT result = D3DCompileFromFile(scrFilePath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint, profile,
		flags, 0, &shaderBlob, &errorBlob);

	if (FAILED(result)) {
		// If compile failed then print error message.
		if (errorBlob) {
			const char* errormsg = (char*)errorBlob->GetBufferPointer();
			std::wstring errorstr(errormsg, errormsg + strlen(errormsg));

			if (GetMessager()->ShowErrorBox((LPCWSTR)(scrFilePath + std::wstring(L":\n") + errorstr).c_str(), L"Shader Compile Error") == IDRETRY)
				return false;
		}
		// If there's no error message then file is not found.
		else {
			if (GetMessager()->ShowErrorBox((LPCWSTR)(std::wstring(L"Cannot Find File:\n") + scrFilePath).c_str(), L"Missing Shader File") == IDRETRY)
				return false;
		}
	}

	*blob = shaderBlob;

	return true;
}