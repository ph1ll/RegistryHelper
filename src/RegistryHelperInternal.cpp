#include <RegistryHelperInternal.h>

#include <atlbase.h>
#include <ktmw32.h>
#include <RegistryKeyHelper.h>

using RegistryHelper::RegistryEntry;
using RegistryHelper::RegistryEntryOption;
using RegistryHelperInternal::Transaction;
using RegistryKeyHelper::CreateRegistryKey;
using RegistryKeyHelper::OpenRegistryKey;
using std::vector;

Transaction RegistryHelperInternal::CreateRegistryTransaction() noexcept
{
    return Transaction(CreateTransaction(nullptr, nullptr, TRANSACTION_DO_NOT_PROMOTE, 0, 0, INFINITE, nullptr));
}

bool RegistryHelperInternal::AddRegistryEntriesInternal(Transaction const &transaction, const vector<RegistryEntry> &entries) noexcept
{
    if (!RegistryHelperInternal::RemoveRegistryEntriesInternal(transaction, entries))
    {
        return false;
    }

    wchar_t filename[MAX_PATH];

    auto const length = GetModuleFileName(reinterpret_cast<HMODULE>(&__ImageBase),
                                          filename,
                                          _countof(filename));

    if (0 == length || _countof(filename) == length)
    {
        return false;
    }

    for (auto const &entry : entries)
    {
        std::wstring path(entry.Path);
        path.append(L"\\");
        path.append(entry.Key);

        auto key = CreateRegistryKey(HKEY_LOCAL_MACHINE,
                                     path.c_str(),
                                     transaction,
                                     KEY_WRITE);

        if (!key.IsValid())
        {
            return false;
        }

        if (RegistryEntryOption::FileName != entry.Option && !entry.Value)
        {
            continue;
        }

        auto value = entry.Value;

        if (!value)
        {
            //ASSERT(RegistryEntryOption::FileName == entry.Option);
            value = filename;
        }

        auto result = RegSetValueEx(key.Get(),
                                    entry.Name,
                                    0, // reserved
                                    REG_SZ,
                                    reinterpret_cast<BYTE const *>(value),
                                    static_cast<DWORD>(sizeof(wchar_t) * (wcslen(value) + 1)));

        if (result != ERROR_SUCCESS)
        {
            SetLastError(result);
            return false;
        }
    }

    return true;
}

bool RegistryHelperInternal::RemoveRegistryEntriesInternal(Transaction const &transaction, const vector<RegistryEntry> &entries) noexcept
{
    for (auto const &entry : entries)
    {
        if (entry.Option != RegistryEntryOption::Delete)
        {
            continue;
        }

        auto key = OpenRegistryKey(HKEY_LOCAL_MACHINE,
                                   entry.Path,
                                   transaction,
                                   DELETE | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_SET_VALUE);

        if (!key.IsValid())
        {
            if (ERROR_FILE_NOT_FOUND == GetLastError())
            {
                continue;
            }

            return false;
        }

        auto result = RegDeleteTree(key.Get(),
                                    entry.Key); // delete the key itself

        if (result != ERROR_SUCCESS && result != ERROR_FILE_NOT_FOUND)
        {
            SetLastError(result);
            return false;
        }
    }

    return true;
}
