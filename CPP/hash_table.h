#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <vector>
#include <list>

#define SUCCESS                     0
#define DATA_EXISTS                 1
#define DATA_NOT_EXISTS             2


////////////////////////////////////////////////////////////////////////////////
//                         Class objects declaration                          //
////////////////////////////////////////////////////////////////////////////////

namespace xtl
{
template <typename T_key, typename T_data>
class HashTable
{
public:
    HashTable();
    HashTable(int size);
    HashTable(HashTable &table);

public:
    struct Item
    {
        T_key key_;
        T_key data_;
    };

public:
    int Insert(T_key key);
    int Delete(T_key key);
    void Resize(int size);

private:
    bool KeyExists(T_key key);
    long ConvertDType(T_data data);     // Convert datatype to enable arithmetic operations.

public:
    T_data operator[](T_key key);

private:
    int div_key_;
    int data_cnt_;
    std::vector<std::list<Item> > hash_table_;
};
};


////////////////////////////////////////////////////////////////////////////////
//                         HashTable object definition                        //
////////////////////////////////////////////////////////////////////////////////

template <typename T_key, typename T_data>
xtl::HashTable<T_key, T_data>::HashTable()
{
    hash_table_.resize(0);
    div_key_ = 0;
    data_cnt_ = 0;
}

template <typename T_key, typename T_data>
xtl::HashTable<T_key, T_data>::HashTable(int size)
{
    hash_table_.resize(size);
    for (int i = 0; i < size; i++)
        hash_table_[i].resize(0);
    div_key_ = 0;
    data_cnt_ = 0;
}

template <typename T_key, typename T_data>
xtl::HashTable<T_key, T_data>::HashTable(HashTable &table)
{
    hash_table_ = table.hash_table_;
    for (int i = 0; i < size; i++)
        hash_table_[i] = table.hash_table_[i];
    div_key_ = table.div_key_;
    data_cnt_ = table.data_cnt_;
}

template <typename T_key, typename T_data>
int xtl::HashTable<T_key, T_data>::Insert(T_data data)
{
    if (KeyExists(data))
        return DATA_EXISTS;
    
    long key = ConvertDType(data) % long(div_key_);
    hash_table_[key].push_back(data);
    return SUCCESS;
}

template <typename T_key, typename T_data>
int xtl::HashTable<T_key, T_data>::Delete(T_data data)
{
    long key = ConvertDType(data) % long(div_key_);
    
    typename std::list<T_data>::iterator iter;
    for (iter = hash_table_[key].begin(); iter != hash_table_[key].end(); iter++)
    {
        if (*iter == data)
        {
            hash_table_[key].erase(iter);
            return SUCCESS;
        }
    }
    return DATA_NOT_EXISTS;
}

template <typename T_key, typename T_data>
T_data xtl::HashTable<T_key, T_data>::operator[](T_key key)
{
    if (KeyExists())
}

template <typename T_key, typename T_data>
bool xtl::HashTable<T_key, T_data>::KeyExists(T_data data)
{
    long key = ConvertDType(data);
    key %= div_key_;

    typename std::list<T_data>::iterator iter;
    for (iter = hash_table_[key].begin(); iter != hash_table_[key].end(); iter++)
        if (*iter == data)
            return true;
    return false;
}

template <typename T_key, typename T_data>
long xtl::HashTable<T_key, T_data>::ConvertDType(T_data data)
{
    return long(data);
}



#endif