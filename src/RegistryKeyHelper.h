#pragma once

#include <RegistryHelperInternal.h>
#include <wrl/wrappers/corewrappers.h>

namespace RegistryKeyHelper
{
struct RegistryKeyTraits
{
    typedef HKEY Type;

    inline static bool Close(_In_ Type h) noexcept
    {
        return RegCloseKey(h) == ERROR_SUCCESS;
    }

    inline static Type GetInvalidValue() noexcept
    {
        return nullptr;
    }
};

using RegistryKey = Microsoft::WRL::Wrappers::HandleT<RegistryKeyTraits>;

RegistryKey OpenRegistryKey(HKEY key, wchar_t const *path, RegistryHelperInternal::Transaction const &transaction, REGSAM access) noexcept;
RegistryKey CreateRegistryKey(HKEY key, wchar_t const *path, RegistryHelperInternal::Transaction const &transaction, REGSAM access) noexcept;
} // namespace RegistryKeyHelper
