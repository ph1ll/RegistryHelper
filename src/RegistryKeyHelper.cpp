#include <RegistryKeyHelper.h>

using RegistryKeyHelper::RegistryKey;

RegistryKey RegistryKeyHelper::OpenRegistryKey(HKEY key, wchar_t const *path, RegistryHelperInternal::Transaction const &transaction, REGSAM access) noexcept
{
    HKEY handle = nullptr;

    auto result = RegOpenKeyTransacted(key, path, 0, access, &handle, transaction.Get(), nullptr);

    if (result != ERROR_SUCCESS)
    {
        SetLastError(result);
    }

    return RegistryKey(handle);
}

RegistryKey RegistryKeyHelper::CreateRegistryKey(HKEY key, wchar_t const *path, RegistryHelperInternal::Transaction const &transaction, REGSAM access) noexcept
{
    HKEY handle = nullptr;

    auto result = RegCreateKeyTransacted(key, path, 0, nullptr, REG_OPTION_NON_VOLATILE, access, nullptr, &handle, nullptr, transaction.Get(), nullptr);

    if (result != ERROR_SUCCESS)
    {
        SetLastError(result);
    }

    return RegistryKey(handle);
}
