#pragma once

#include <RegistryHelper.h>
#include <wrl/wrappers/corewrappers.h>
#include <vector>

namespace RegistryHelperInternal
{
using Transaction = Microsoft::WRL::Wrappers::HandleT<Microsoft::WRL::Wrappers::HandleTraits::HANDLETraits>;

Transaction CreateRegistryTransaction() noexcept;
bool AddRegistryEntriesInternal(Transaction const &transaction, const std::vector<RegistryHelper::RegistryEntry> &entries) noexcept;
bool RemoveRegistryEntriesInternal(Transaction const &transaction, const std::vector<RegistryHelper::RegistryEntry> &entries) noexcept;
} // namespace RegistryHelperInternal
