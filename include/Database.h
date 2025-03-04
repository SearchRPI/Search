#pragma once

/**
 * @file  Database.h
 * @brief Inverted index wrapper
 */

#include <lmdb.h>

#include "index/IDatabase.h"

#include <string>
#include <vector>

class Database : IDatabase {
public:
    // Get the singleton instance
    static Database& getInstance();

    // Delete copy constructor and assignment operator
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    /**
     * @brief Add data to database
     * 
     * @param key Index to add data to.
     * @param data Data to be added.
     */
    void add(const std::string& key, const Data& data);

    /**
     * @brief Remove all data for a specific key
     * 
     * @param key Index to remove data from.
     */
    void remove(const std::string& key);

    /**
     * @brief Retrieve the first value for a given key
     * 
     * @param key Index to retrieve from.
     * @return First entry at provided key.
     */
    std::vector<Data> get(const std::string& key);

    /**
     * @brief Retrieve the first 'n' values for a given key
     *
     * @param key Index to retrieve from.
     * @param n Maximum number of values returned
     * @return At most the first 'n' entries at provided key
     */
    std::vector<Data> get(const std::string& key, size_t n);

    // TODO: Clarify when get is used and its purpose, add bulk get

private:
    MDB_env* env = nullptr;
    MDB_dbi dbi;
    MDB_txn* write_txn = nullptr;
    MDB_txn* read_txn = nullptr;

    // Private constructor for singleton
    Database();

    // Destructor to clean up LMDB resources
    ~Database();

    // Serialize the Data struct
    void serialize_data(const Data& data, MDB_val& value);

    // Deserialize the Data struct
    void deserialize_data(const MDB_val& value, Data& data);

    // Custom comparison function for ranking by priority
    static int custom_compare(const MDB_val* a, const MDB_val* b);
};
