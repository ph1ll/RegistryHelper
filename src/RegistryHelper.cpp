#include <RegistryHelper.h>

#include <RegistryHelperInternal.h>
#include <ktmw32.h>

using RegistryHelper::RegistryEntry;
using RegistryHelperInternal::AddRegistryEntriesInternal;
using RegistryHelperInternal::CreateRegistryTransaction;
using RegistryHelperInternal::RemoveRegistryEntriesInternal;
using std::vector;

bool RegistryHelper::AddRegistryEntries(const vector<RegistryEntry> &entries) noexcept
{
    auto transaction = CreateRegistryTransaction();

    if (!transaction.IsValid())
    {
        return false;
    }

    if (!AddRegistryEntriesInternal(transaction, entries))
    {
        return false;
    }

    if (CommitTransaction(transaction.Get()) != TRUE)
    {
        return false;
    }

    return true;
}

bool RegistryHelper::RemoveRegistryEntries(const vector<RegistryEntry> &entries) noexcept
{
    auto transaction = CreateRegistryTransaction();

    if (!transaction.IsValid())
    {
        return false;
    }

    if (!RemoveRegistryEntriesInternal(transaction, entries))
    {
        return false;
    }

    if (CommitTransaction(transaction.Get()) != TRUE)
    {
        return false;
    }

    return true;
}
