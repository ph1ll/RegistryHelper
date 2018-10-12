### Usage

```
std::vector<RegistryEntry> GetRegistryEntries() noexcept
{
    return {
        {L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\Credential Providers",
         L"{ab2b3e96-1017-43af-99b8-cdc055135a5d}",
         RegistryEntryOption::Delete,
         nullptr,
         L"PasswordProvider"},
}

extern "C" HRESULT __stdcall DllRegisterServer(void)
{
    if (!AddRegistryEntries(GetRegistryEntries()))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

extern "C" HRESULT __stdcall DllUnregisterServer(void)
{
    if (!RemoveRegistryEntries(GetRegistryEntries()))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}
```
