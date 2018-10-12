#pragma once

#include <vector>

namespace RegistryHelper
{
enum class RegistryEntryOption
{
    None,
    Delete,
    FileName,
};

struct RegistryEntry
{
    wchar_t const *Path;
    wchar_t const *Key;
    RegistryEntryOption Option;

    wchar_t const *Name;
    wchar_t const *Value;
};

bool AddRegistryEntries(const std::vector<RegistryEntry> &entries) noexcept;
bool RemoveRegistryEntries(const std::vector<RegistryEntry> &entries) noexcept;
} // namespace RegistryHelper
